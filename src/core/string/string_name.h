#pragma once
#include "core/reflection/reflection.h"
#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <functional>

// Internal pool implementation to manage shared string instances safely.
// It uses reference counting to automatically release strings when no longer in use.
class StringNamePool {
public:
    CORE_API static std::shared_ptr<const std::string> Intern(const std::string& Str);

    // Cached empty string to avoid mutex locks for default constructors
    CORE_API static std::shared_ptr<const std::string> GetEmpty();
};

CLASS(BindJs)
class StringName {
private:
    // Holds a reference-counted pointer to the interned string
    std::shared_ptr<const std::string> NameStr;
    size_t Id;

    // Centralizes initialization to cache the hash ID immediately
    explicit StringName(std::shared_ptr<const std::string> SP) 
        : NameStr(std::move(SP)), Id(std::hash<std::string>{}(*NameStr)) {}

public:
    StringName() : StringName(StringNamePool::GetEmpty()) {}
    
    FUNCTION()
    StringName(const char* Str) : StringName(Str ? StringNamePool::Intern(Str) : StringNamePool::GetEmpty()) {}
    
    StringName(std::string_view Str) : StringName(StringNamePool::Intern(std::string(Str))) {}
    StringName(const std::string& Str) : StringName(StringNamePool::Intern(Str)) {}
    StringName(std::string&& Str) : StringName(StringNamePool::Intern(Str)) {}

    // Copy operations
    StringName(const StringName& Other) = default;
    StringName& operator=(const StringName& Other) = default;

    // Move operations: We restore the moved-from object to a safe empty state 
    // to prevent nullptr crashes if accessed later.
    StringName(StringName&& Other) noexcept 
        : NameStr(std::move(Other.NameStr)), Id(Other.Id) {
        Other.NameStr = StringNamePool::GetEmpty();
        Other.Id = std::hash<std::string>{}(*Other.NameStr);
    }

    StringName& operator=(StringName&& Other) noexcept {
        if (this != &Other) {
            NameStr = std::move(Other.NameStr);
            Id = Other.Id;
            Other.NameStr = StringNamePool::GetEmpty();
            Other.Id = std::hash<std::string>{}(*Other.NameStr);
        }
        return *this;
    }

    operator std::string_view() const {
        return *NameStr; 
    }

    operator const char*() const {
        return NameStr->c_str();
    }

    FUNCTION()
    const char* c_str() const {
        return NameStr->c_str();
    }

    FUNCTION()
    size_t GetId() const noexcept {
        return Id;
    }
    
    FUNCTION()
    bool IsEmpty() const noexcept {
        return NameStr->empty() && NameStr == StringNamePool::GetEmpty();
    }

    // Shared pointer instances pointing to the same interned string will have identical memory addresses.
    // This allows for O(1) pointer comparison just like boost::flyweight.
    FUNCTION()
    bool operator==(const StringName& Other) const {
        return NameStr.get() == Other.NameStr.get();
    }
    FUNCTION()
    bool operator!=(const StringName& Other) const {
        return NameStr.get() != Other.NameStr.get();
    }

    bool operator==(std::string_view Other) const {
        return static_cast<std::string_view>(*this) == Other;
    }
    bool operator!=(std::string_view Other) const {
        return static_cast<std::string_view>(*this) != Other;
    }

    friend struct std::hash<StringName>;
    
    template<class Archive>
    void save(Archive& ar) const {
        ar(*NameStr);
    }

    template<class Archive>
    void load(Archive& ar) {
        std::string str;
        ar(str);
        *this = StringName(str);
    }
};

namespace std {
    template <>
    struct hash<StringName> {
        // Zero-overhead O(1) lookup by returning the pre-cached ID directly
        size_t operator()(const StringName& Name) const noexcept {
            return Name.Id;
        }
    };
}