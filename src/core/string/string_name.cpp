#include "core/string/string_name.h"
#include "string_name.h"

struct State
{
    std::unordered_map<std::string, std::weak_ptr<const std::string>> Map;
    std::mutex                                                        Mtx;
};

std::shared_ptr<const std::string> StringNamePool::Intern(const std::string& Str)
{
    // Using a function-local static shared_ptr ensures that the pool state
    // safely outlives all StringName instances, preventing global teardown crashes.
    static std::shared_ptr<State> SharedState = std::make_shared<State>();

    std::lock_guard<std::mutex> Lock(SharedState->Mtx);

    // 1. Check if the string already exists and is alive
    auto It = SharedState->Map.find(Str);
    if (It != SharedState->Map.end())
    {
        if (auto Shared = It->second.lock())
        {
            return Shared;
        }
    }

    // 2. Custom deleter: removes the string from the map when refcount reaches zero.
    // Captures a weak_ptr to the State to ensure safety if the global pool is already destroyed.
    std::weak_ptr<State>               WeakState = SharedState;
    std::shared_ptr<const std::string> NewStr(new std::string(Str), [WeakState](const std::string* Ptr) {
        if (auto LockedState = WeakState.lock())
        {
            std::lock_guard<std::mutex> InnerLock(LockedState->Mtx);
            LockedState->Map.erase(*Ptr);
        }
        delete Ptr;
    });

    SharedState->Map[Str] = NewStr;
    return NewStr;
}

std::shared_ptr<const std::string> StringNamePool::GetEmpty()
{
    static std::shared_ptr<const std::string> EmptyStr = Intern("");
    return EmptyStr;
}