#include "core/reflection/reflection_register.h"
#include "core/logger/logger.h"

CORE_API std::shared_ptr<spdlog::logger> gLogger;
CORE_API std::shared_ptr<spdlog::logger> gConsole;

CORE_API entt::locator<entt::meta_ctx>::node_type get_meta_ctx_handle()
{
    return entt::locator<entt::meta_ctx>::handle();
}
