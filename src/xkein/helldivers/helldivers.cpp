#include "xkein/helldivers/helldivers.h"
#include "xkein/helldivers/helldiver_component.h"
#include "xkein/helldivers/helldiver_stratagem.h"

#include <FootClass.h>
#include <SuperClass.h>
#include <Unsorted.h>
#include <HouseClass.h>
#include <imgui.h>

std::string gInputSequence;
std::vector<std::unique_ptr<HelldiverStratagemInst>> gInsts;

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

    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
    {
        if (ImGui::IsKeyReleased(ImGuiKey::ImGuiKey_W)) {
            gInputSequence.push_back('W');
        }
        else if (ImGui::IsKeyReleased(ImGuiKey::ImGuiKey_S)) {
            gInputSequence.push_back('S');
        }
        else if (ImGui::IsKeyReleased(ImGuiKey::ImGuiKey_A)) {
            gInputSequence.push_back('A');
        }
        else if (ImGui::IsKeyReleased(ImGuiKey::ImGuiKey_D)) {
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
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
    {
        DSurface* surface = DSurface::Primary;
        RectangleStruct rect = { 0, 0, 0, 0 };
        surface->GetRect(&rect);

        Point2D pos {10,100};
        for (HelldiverStratagemInst* inst : candidateInsts)
        {
            HelldiverStratagem* stratagem = inst->type;
            std::wstring str = stratagem->swType->UIName;
            Point2D endPos { 0,0 };
            int color = inst->super->IsReady ? Drawing::RGB_To_Int(0, 0, 255) : Drawing::RGB_To_Int(255, 0, 0);
            Fancy_Text_Print_Wide(endPos, stratagem->swType->UIName, surface, rect, pos, color, 0, TextPrintType::NoShadow);
            pos.Y = endPos.Y;

            int idx = 0;
            str.clear();
            while(stratagem->sequence[idx] == gInputSequence[idx] && idx < stratagem->sequence.size() && idx < gInputSequence.size()) {
                str.push_back(stratagem->sequence[idx]);
                idx++;
            }
            color = Drawing::RGB_To_Int(255, 0, 0);
            Fancy_Text_Print_Wide(endPos, str.c_str(), surface, rect, pos, color, 0, TextPrintType::NoShadow);
            pos.X = endPos.X;

            str.clear();
            while(idx < stratagem->sequence.size()) {
                str.push_back(stratagem->sequence[idx]);
                idx++;
            }
            color = Drawing::RGB_To_Int(0, 255, 0);
            Fancy_Text_Print_Wide(endPos, str.c_str(), surface, rect, pos, color, 0, TextPrintType::NoShadow);
            pos.Y = endPos.Y;
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


void Helldivers::Init()
{

}

void Helldivers::Clear()
{
    gInsts.clear();
}

#include "yr/yr_all_events.h"

REGISTER_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent, Helldivers::Init)
REGISTER_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent, Helldivers::Clear)
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent, Helldivers::Tick)
