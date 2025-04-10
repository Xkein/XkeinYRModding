#include "compat_ares.h"
#include <AnimClass.h>
#include <FootClass.h>

ConvertClass* CompatAres::GetAnimConvert(AnimTypeClass* pAnimType, ConvertClass* ownerColorSchemeConvert)
{
    return pAnimType->ShouldUseCellDrawer ? ownerColorSchemeConvert : FileSystem::ANIM_PAL;
    // TODO
    // auto pData = AnimTypeExt::ExtMap.Find(pAnimType);

    // ConvertClass* pal = pAnimType->ShouldUseCellDrawer ? ownerColorSchemeConvert : FileSystem::ANIM_PAL;
    // if (pData->Palette.Convert) {
    //     pal = pData->Palette.GetConvert();
    // }

    // return pal;
}

#include "yr/event/general_event.h"
#include "yr/yr_hook.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent)
{
    // AnimTypeClass::Array->
}