#include "core/raii_invoker.h"
#include "yr/event/general_event.h"
#include "ui/imgui/yr_imgui.h"

REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, []() {
    YrImGui::Init();
});

REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, [](){
    YrImGui::Destory();
});

REGISTER_YR_HOOK_EVENT_LISTENER(YrEndRenderEvent, [](){
    YrImGui::Render();
});

GLOBAL_INVOKE_ON_CTOR_DTOR([]() {

}, []() {
	
})