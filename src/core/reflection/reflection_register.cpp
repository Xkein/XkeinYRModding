#include "core/reflection/reflection_register.h"

CORE_API entt::locator<entt::meta_ctx>::node_type get_meta_ctx_handle()
{
    return entt::locator<entt::meta_ctx>::handle();
}
