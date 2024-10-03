#pragma once
#include "core/reflection/container.h"
#include <ArrayClasses.h>

namespace entt
{
    template<typename TElem>
    struct meta_sequence_container_traits<VectorClass<TElem>> {
        using Type = VectorClass<TElem>;

        static_assert(std::is_same_v<Type, std::remove_cv_t<std::remove_reference_t<Type>>>, "Unexpected type");

        using size_type = typename meta_sequence_container::size_type;
        using iterator = typename meta_sequence_container::iterator;

        // static constexpr bool fixed_size = true;

        [[nodiscard]] static size_type size(const void *container) {
            return static_cast<const Type *>(container)->Capacity;
        }

        [[nodiscard]] static bool clear([[maybe_unused]] void *container) {
            static_cast<Type *>(container)->Clear();
            return true;
        }

        [[nodiscard]] static bool reserve([[maybe_unused]] void *container, [[maybe_unused]] const size_type sz) {
            static_cast<Type *>(container)->Reserve(sz);
            return true;
        }

        [[nodiscard]] static bool resize([[maybe_unused]] void *container, [[maybe_unused]] const size_type sz) {
            return false;
        }

        static iterator begin(const meta_ctx &area, void *container, const void *as_const) {
            return container ? iterator{area, static_cast<Type *>(container)->Items}
                            : iterator{area, static_cast<const Type *>(as_const)->Items};
        }

        static iterator end(const meta_ctx &area, void *container, const void *as_const) {
            return container ? iterator{area, static_cast<Type *>(container)->Items + size(container)}
                            : iterator{area, static_cast<const Type *>(as_const)->Items + size(as_const)};
        }

        [[nodiscard]] static iterator insert([[maybe_unused]] const meta_ctx &area, [[maybe_unused]] void *container, [[maybe_unused]] const void *value, [[maybe_unused]] const void *cref, [[maybe_unused]] const iterator &it) {
            return iterator{};
        }

        [[nodiscard]] static iterator erase([[maybe_unused]] const meta_ctx &area, [[maybe_unused]] void *container, [[maybe_unused]] const iterator &it) {
            return iterator{};
        }
    };

    
    template<typename TElem>
    struct meta_sequence_container_traits<DynamicVectorClass<TElem>> {
        using Type = DynamicVectorClass<TElem>;

        static_assert(std::is_same_v<Type, std::remove_cv_t<std::remove_reference_t<Type>>>, "Unexpected type");

        using size_type = typename meta_sequence_container::size_type;
        using iterator = typename meta_sequence_container::iterator;

        static constexpr bool fixed_size = false;

        [[nodiscard]] static size_type size(const void *container) {
            return static_cast<const Type *>(container)->Count;
        }

        [[nodiscard]] static bool clear([[maybe_unused]] void *container) {
            static_cast<Type *>(container)->Clear();
            return true;
        }

        [[nodiscard]] static bool reserve([[maybe_unused]] void *container, [[maybe_unused]] const size_type sz) {
            static_cast<Type *>(container)->Reserve(sz);
            return true;
        }

        [[nodiscard]] static bool resize([[maybe_unused]] void *container, [[maybe_unused]] const size_type sz) {
            return false;
        }

        static iterator begin(const meta_ctx &area, void *container, const void *as_const) {
            return container ? iterator{area, static_cast<Type *>(container)->begin()}
                            : iterator{area, static_cast<const Type *>(as_const)->begin()};
        }

        static iterator end(const meta_ctx &area, void *container, const void *as_const) {
            return container ? iterator{area, static_cast<Type *>(container)->end()}
                            : iterator{area, static_cast<const Type *>(as_const)->end()};
        }

        [[nodiscard]] static iterator insert([[maybe_unused]] const meta_ctx &area, [[maybe_unused]] void *container, [[maybe_unused]] const void *value, [[maybe_unused]] const void *cref, [[maybe_unused]] const iterator &it) {
            return iterator{};
        }

        [[nodiscard]] static iterator erase([[maybe_unused]] const meta_ctx &area, [[maybe_unused]] void *container, [[maybe_unused]] const iterator &it) {
            // auto *const non_const = any_cast<TElem>(&it.base());
            // return {area, static_cast<Type *>(container)->Remove(non_const ? non_const : any_cast<const TElem* &>(it.base()))};
            return iterator{};
        }
    };

    template<typename TElem>
    struct meta_sequence_container_traits<TypeList<TElem>> : meta_sequence_container_traits<DynamicVectorClass<TElem>> {};
} // namespace entt
