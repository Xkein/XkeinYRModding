#pragma once
#include <entt/entity/snapshot.hpp>

namespace entt
{
    /**
     * @brief Utility class for _continuous loading_.
     *
     * A _continuous loader_ is designed to load data from a source registry to a
     * (possibly) non-empty destination. The loader can accommodate in a registry
     * more than one snapshot in a sort of _continuous loading_ that updates the
     * destination one step at a time.<br/>
     * Identifiers that entities originally had are not transferred to the target.
     * Instead, the loader maps remote identifiers to local ones while restoring a
     * snapshot.<br/>
     * An example of use is the implementation of a client-server application with
     * the requirement of transferring somehow parts of the representation side to
     * side.
     *
     * @tparam Registry Basic registry type.
     */
    template<typename Registry>
    class BasicEntitySnapshotLoader {
        static_assert(!std::is_const_v<Registry>, "Non-const registry type required");
        using traits_type = entt_traits<typename Registry::entity_type>;

        void restore(typename Registry::entity_type entt) {
            if(const auto entity = to_entity(entt); remloc.contains(entity) && remloc[entity].first == entt) {
                if(!reg->valid(remloc[entity].second)) {
                    remloc[entity].second = reg->create();
                }
            } else {
                remloc.insert_or_assign(entity, std::make_pair(entt, reg->create()));
            }
        }

    public:
        /*! Basic registry type. */
        using registry_type = Registry;
        /*! @brief Underlying entity identifier. */
        using entity_type = typename registry_type::entity_type;

        /**
         * @brief Constructs an instance that is bound to a given registry.
         * @param source A valid reference to a registry.
         */
        BasicEntitySnapshotLoader(registry_type &source) noexcept
            : remloc{source.get_allocator()},
            reg{&source} {}

        /*! @brief Default copy constructor, deleted on purpose. */
        BasicEntitySnapshotLoader(const BasicEntitySnapshotLoader &) = delete;

        /*! @brief Default move constructor. */
        BasicEntitySnapshotLoader(BasicEntitySnapshotLoader &&) noexcept = default;

        /*! @brief Default destructor. */
        ~BasicEntitySnapshotLoader() = default;

        /**
         * @brief Default copy assignment operator, deleted on purpose.
         * @return This loader.
         */
        BasicEntitySnapshotLoader &operator=(const BasicEntitySnapshotLoader &) = delete;

        /**
         * @brief Default move assignment operator.
         * @return This loader.
         */
        BasicEntitySnapshotLoader &operator=(BasicEntitySnapshotLoader &&) noexcept = default;

        /**
         * @brief Restores all elements of a type with associated identifiers.
         *
         * It creates local counterparts for remote elements as needed.<br/>
         * Members are either data members of type entity_type or containers of
         * entities. In both cases, a loader visits them and replaces entities with
         * their local counterpart.
         *
         * @tparam Type Type of elements to restore.
         * @tparam Archive Type of input archive.
         * @param archive A valid reference to an input archive.
         * @param id Optional name used to map the storage within the registry.
         * @return A valid loader to continue restoring data.
         */
        template<typename Type, typename Archive>
        BasicEntitySnapshotLoader &get(Archive &archive, const id_type id = type_hash<Type>::value()) {
            auto &storage = reg->template storage<Type>(id);
            typename traits_type::entity_type length{};
            entity_type entt{null};

            archive(length);

            if constexpr(std::is_same_v<Type, entity_type>) {
                typename traits_type::entity_type in_use{};

                storage.reserve(length);
                archive(in_use);

                for(std::size_t pos{}; pos < in_use; ++pos) {
                    archive(entt);
                    restore(entt);
                }

                for(std::size_t pos = in_use; pos < length; ++pos) {
                    archive(entt);

                    if(const auto entity = to_entity(entt); remloc.contains(entity)) {
                        if(reg->valid(remloc[entity].second)) {
                            reg->destroy(remloc[entity].second);
                        }

                        remloc.erase(entity);
                    }
                }
            } else {
                for(auto &&ref: remloc) {
                    storage.remove(ref.second.second);
                }

                while(length--) {
                    if(archive(entt); entt != null) {
                        restore(entt);

                        if constexpr(std::tuple_size_v<decltype(storage.get_as_tuple({}))> == 0u) {
                            storage.emplace(map(entt));
                        } else {
                            // !! here we change the implementation to make component swizzleable 
                            Type& elem = storage.emplace(map(entt), Type{});
                            archive(elem);
                        }
                    }
                }
            }

            return *this;
        }

        /**
         * @brief Destroys those entities that have no elements.
         *
         * In case all the entities were serialized but only part of the elements
         * was saved, it could happen that some of the entities have no elements
         * once restored.<br/>
         * This function helps to identify and destroy those entities.
         *
         * @return A non-const reference to this loader.
         */
        BasicEntitySnapshotLoader &orphans() {
            internal::orphans(*reg);
            return *this;
        }

        /**
         * @brief Tests if a loader knows about a given entity.
         * @param entt A valid identifier.
         * @return True if `entity` is managed by the loader, false otherwise.
         */
        [[nodiscard]] bool contains(entity_type entt) const noexcept {
            const auto it = remloc.find(to_entity(entt));
            return it != remloc.cend() && it->second.first == entt;
        }

        /**
         * @brief Returns the identifier to which an entity refers.
         * @param entt A valid identifier.
         * @return The local identifier if any, the null entity otherwise.
         */
        [[nodiscard]] entity_type map(entity_type entt) const noexcept {
            if(const auto it = remloc.find(to_entity(entt)); it != remloc.cend() && it->second.first == entt) {
                return it->second.second;
            }

            return null;
        }

    private:
        dense_map<typename traits_type::entity_type, std::pair<entity_type, entity_type>> remloc;
        registry_type *reg;
    };
}

#define ENTITY_SNAPSHOT entt::snapshot
#define ENTITY_SNAPSHOT_LOADER entt::BasicEntitySnapshotLoader<entt::registry>
