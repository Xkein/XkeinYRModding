#include "xkein/helldivers/helldivers.h"
#include "xkein/helldivers/helldiver_component.h"
#include "xkein/helldivers/helldiver_stratagem.h"
#include "input/input.h"

#include <FootClass.h>
#include <SuperClass.h>
#include <Unsorted.h>
#include <HouseClass.h>
#include <imgui.h>

std::string gInputSequence;
std::vector<std::unique_ptr<HelldiverStratagemInst>> gInsts;

enum HelldiverButtons
{
    Activate = 1111,
    Up, Down, Left, Right
};

void Helldivers::Tick()
{
    for (auto& inst : gInsts)
    {
        
    }
    

    std::vector<HelldiverStratagemInst*> candidateInsts;
    for (auto&& [entity, com] : gEntt->view<HelldiverComponent>().each())
    {
        if (com.owner->IsSelected)
        {
            candidateInsts.append_range(com.stratagemInsts);
        }
    }

    if (Input::gMap->GetBool(HelldiverButtons::Activate))
    {
        if (Input::gMap->GetBoolIsNew(HelldiverButtons::Up)) {
            gInputSequence.push_back('W');
        }
        else if (Input::gMap->GetBoolIsNew(HelldiverButtons::Down)) {
            gInputSequence.push_back('S');
        }
        else if (Input::gMap->GetBoolIsNew(HelldiverButtons::Left)) {
            gInputSequence.push_back('A');
        }
        else if (Input::gMap->GetBoolIsNew(HelldiverButtons::Right)) {
            gInputSequence.push_back('D');
        }
    }
    else if (!gInputSequence.empty())
    {
        gInputSequence.clear();
    }

    for (HelldiverStratagemInst* inst : candidateInsts)
    {
        if (inst->type->sequence == gInputSequence && inst->super->IsReady)
        {
            Unsorted::CurrentSWType = inst->type->swType->ArrayIndex;
            break;
        }
    }
    
    // render ui
    if (Input::gMap->GetBool(HelldiverButtons::Activate))
    {
        DSurface* surface = DSurface::Primary;
        RectangleStruct rect = { 0, 0, 0, 0 };
        surface->GetRect(&rect);

        Point2D pos {10,100};
        for (HelldiverStratagemInst* inst : candidateInsts)
        {
            HelldiverStratagem* stratagem = inst->type;
            std::wstring str = stratagem->swType->UIName;

            int color = inst->super->IsReady ? Drawing::RGB_To_Int(0, 0, 255) : Drawing::RGB_To_Int(255, 0, 0);
            surface->DrawText(str.c_str(), &pos, color);
            pos.Y += Drawing::GetTextDimensions(str.c_str(), { 0,0 }, 0).Height;

            int idx = 0;
            str.clear();
            while(stratagem->sequence[idx] == gInputSequence[idx] && idx < stratagem->sequence.size() && idx < gInputSequence.size()) {
                str.push_back(stratagem->sequence[idx]);
                idx++;
            }
            color = Drawing::RGB_To_Int(255, 0, 0);
            surface->DrawText(str.c_str(), &pos, color);
            pos.X += Drawing::GetTextDimensions(str.c_str(), { 0,0 }, 0).Width;

            str.clear();
            while(idx < stratagem->sequence.size()) {
                str.push_back(stratagem->sequence[idx]);
                idx++;
            }
            color = Drawing::RGB_To_Int(0, 255, 0);
            surface->DrawText(str.c_str(), &pos, color);
            pos.Y += Drawing::GetTextDimensions(str.c_str(), { 0,0 }, 0).Height;
        }
    }
}
void Helldivers::QueryStratagem(HelldiverComponent* com)
{
    for (HelldiverStratagem* stratagem : com->type->stratagems)
    {
        auto ptr = std::make_unique<HelldiverStratagemInst>();
        ptr->type = stratagem;
        ptr->super = com->owner->GetOwningHouse()->FindSuperWeapon(stratagem->swType->Type);
        com->stratagemInsts.push_back(ptr.get());
        gInsts.push_back(std::move(ptr));
    }
}

void Helldivers::ReturnStratagem(HelldiverStratagemInst* inst)
{
    std::erase_if(gInsts, [=](auto& ptr) { return ptr.get() == inst; });
}

static bool inited = false;
void Helldivers::Init()
{
    if (!inited) {
        Input::gMap->MapBool(HelldiverButtons::Activate, Input::gKeyboardId, gainput::KeyCtrlL);
        Input::gMap->MapBool(HelldiverButtons::Up, Input::gKeyboardId, gainput::KeyW);
        Input::gMap->MapBool(HelldiverButtons::Down, Input::gKeyboardId, gainput::KeyS);
        Input::gMap->MapBool(HelldiverButtons::Left, Input::gKeyboardId, gainput::KeyA);
        Input::gMap->MapBool(HelldiverButtons::Right, Input::gKeyboardId, gainput::KeyD);
    }
}

void Helldivers::Clear()
{
    gInsts.clear();
}

#include "yr/yr_all_events.h"

REGISTER_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent, Helldivers::Init)
REGISTER_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent, Helldivers::Clear)
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, Helldivers::Tick)
