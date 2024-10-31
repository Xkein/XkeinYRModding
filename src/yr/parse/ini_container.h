#pragma once

#include <map>
#include <memory>

template<class T>
class DefaultIniContainer
{
    std::map<const char*, std::unique_ptr<T>> _items;
public:
	T* FindOrAllocate(const char *name, bool& allocated)
	{
        auto iter = _items.find(name);
        if (iter != _items.end())
        {
            allocated = false;
            return iter->second.get();
        }
        allocated = true;
        auto& ptr = _items[name];
        ptr = std::make_unique<T>();
        return ptr.get();
	}

    void Clear()
    {
        _list.clear();
    }
};