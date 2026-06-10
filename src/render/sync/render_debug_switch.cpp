#include "render/sync/render_debug_switch.h"
#include "yr/extcore_config.h"

static bool _initialized = false;
static bool _skipRender  = false;

void RenderDebugSwitch::Initialize()
{
    _initialized = true;
    if (gYrExtConfig) {
        _skipRender = gYrExtConfig->IsUe5RenderEnabled() && !gYrExtConfig->enableOriginalRender;
    }
}

bool RenderDebugSwitch::ShouldSkipOriginalRender()
{
    if (!_initialized) Initialize();
    return _skipRender;
}

bool RenderDebugSwitch::ShouldSkipZBuffer()
{
    return ShouldSkipOriginalRender();
}