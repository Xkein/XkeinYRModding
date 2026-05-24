#pragma once
#include <string>
#include <string_view>
#include <utility>
#include <boost/flyweight.hpp>

class StringName {
private:
    using FlyString = boost::flyweight<std::string>;

    // Declaration order matters: NameStr must be initialized before Id
    FlyString NameStr;
    size_t Id;

    // Centralizes initialization to cache the hash ID immediately
    explicit StringName(FlyString FS) 
        : NameStr(std::move(FS)), Id(std::hash<FlyString>{}(NameStr)) {}

public:
    StringName() : StringName(FlyString()) {}
    StringName(const char* Str) : StringName(FlyString(Str)) {}
    StringName(std::string_view Str) : StringName(FlyString(std::string(Str))) {}
    StringName(const std::string& Str) : StringName(FlyString(Str)) {}
    StringName(std::string&& Str) : StringName(FlyString(std::move(Str))) {}

    // Default operations work perfectly as Id is a trivial scalar type
    StringName(const StringName& Other) = default;
    StringName(StringName&& Other) noexcept = default;
    StringName& operator=(const StringName& Other) = default;
    StringName& operator=(StringName&& Other) noexcept = default;

    operator std::string_view() const {
        return NameStr.get(); 
    }

    operator const char*() const {
        return NameStr.get().c_str();
    }

    const char* c_str() const {
        return NameStr.get().c_str();
    }

    size_t GetId() const noexcept {
        return Id;
    }
    
    // High-performance check for empty/uninitialized state
    bool IsEmpty() const noexcept {
        static const size_t EmptyId = StringName().GetId();
        return Id == EmptyId;
    }

    // Always compare using flyweight pointers to prevent hash collision bugs
    bool operator==(const StringName& Other) const {
        return NameStr == Other.NameStr;
    }
    bool operator!=(const StringName& Other) const {
        return NameStr != Other.NameStr;
    }

    bool operator==(std::string_view Other) const {
        return static_cast<std::string_view>(*this) == Other;
    }
    bool operator!=(std::string_view Other) const {
        return static_cast<std::string_view>(*this) != Other;
    }

    friend struct std::hash<StringName>;
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