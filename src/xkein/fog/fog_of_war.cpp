#include "fog_data.h"
#include "yr/yr_hook.h"
#include "yr/event/general_event.h"
#include "yr/parse/ini_reader.h"
#include <TechnoClass.h>
#include <UnitTypeClass.h>
#include <MapClass.h>
#include <InfantryClass.h>
#include <HouseClass.h>
#include <ColorScheme.h>
#include <ScenarioClass.h>
#include <AnimClass.h>
#include <TacticalClass.h>
#include <TerrainClass.h>
#include <SmudgeTypeClass.h>

DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadAfterTypeDataEvent)
{
    IniReader reader {E->pIni};
	bool fogOfWar;
	if (reader.Read("General", "FogOfWar", fogOfWar)) {
		ScenarioClass::Instance->SpecialFlags.FogOfWar = fogOfWar;
	}
}

SYRINGE_PATCH(0x586683, Fog_CellClass_DiscoverTechno, 5) {
	GET(CellClass* const, pCell, ESI);
	GET(TechnoClass* const, pTechno, EAX);
	GET_STACK(HouseClass* const, pHouse, 0x20);
	bool ret = false;

	if (pTechno) {
		ret = pTechno->DiscoveredBy(pHouse);
	}

	TechnoClass* pJumpjet = pCell->Jumpjet;
	if (pJumpjet) {
		ret |= pJumpjet->DiscoveredBy(pHouse);
	}

	R->EAX(ret);
	return 0x586696;
}


bool IsTechnoLocalVisible(TechnoClass* pTechno)
{
	return pTechno->GetTechnoType()->RevealToAll || (pTechno->DiscoveredByCurrentPlayer && pTechno->Owner->IsControlledByCurrentPlayer())
		|| RulesClass::Instance->AllyReveal && pTechno->Owner->IsAlliedWith(HouseClass::CurrentPlayer);
}

SYRINGE_PATCH(0x4ADFF0, Fog_MapClass_RevealShroud, 5)
{
	GET_STACK(bool, bIgnoreBuilding, 0x4);
	GET_STACK(bool, bRevealByHeight, 0x8);

	for (TechnoClass* pTechno : *TechnoClass::Array)
	{
		if (pTechno && (!bIgnoreBuilding || pTechno->WhatAmI() != AbstractType::Building)) {
			if (IsTechnoLocalVisible(pTechno))
			{
				pTechno->See(0, bRevealByHeight);
				if (pTechno->IsInAir()) {
					MapClass::Instance->RevealArea3(&pTechno->Location, pTechno->LastSightRange - 3, pTechno->LastSightRange + 3, false);
				}

			}
		}
	}

	return 0x4AE0A5;
}

SYRINGE_PATCH(0x5F4B3E, Fog_ObjectClass_DrawIfVisible, 6)
{
	GET(ObjectClass* const, pThis, ESI);
	GET(const AbstractType, whatAmI, EAX);
	CellClass* pCell = MapClass::Instance->GetCellAt(pThis->Location);

	if (pThis->InLimbo) {
		return 0x5F4B7F;
	}
	if (ScenarioClass::Instance->SpecialFlags.FogOfWar) {
		switch (pThis->WhatAmI())
		{
		case AbstractType::Anim:
			if (auto pAnim = (AnimClass*)pThis) {
				/*if (!pAnim->IsBuildingAnim && pAnim->Type->ShouldFogRemove && FogSystem::IsLocationFogged(pThis->Location)) {
					pThis->NeedsRedraw = false;
					return 0x5F4D06;
				}*/
				if (pAnim->Type->ShouldFogRemove == false) {
					break;
				}
			}
			[[fallthrough]];
		case AbstractType::Unit:
		case AbstractType::Infantry:
		//case AbstractType::Aircraft:
		//case AbstractType::Bullet:
		case AbstractType::Particle:
		case AbstractType::ParticleSystem:
		//case AbstractType::VoxelAnim:
			if (FogSystem::IsLocationFogged(pThis->GetCoords())) {
				pThis->NeedsRedraw = false;
				R->AL(1);
				return 0x5F4D08;
			}
		}
	}
	return 0x5F4B48;
}


SYRINGE_PATCH(0x71CC8C, Fog_TerrainClass_DrawIfVisible, 6)
{
	GET(TerrainClass* const, pThis, EDI);
	GET_STACK(RectangleStruct* const, pUnkRect, STACK_OFFSET(0x28, 0x4));

	pThis->NeedsRedraw = false;

	if (pThis->InLimbo || FogSystem::IsLocationFogged(pThis->GetCoords())) {
		return 0x71CD8D;
	}

	return 0x71CC9A;
}

SYRINGE_PATCH(0x5865E2, Fog_IsLocationFogged, 5)
{
	GET_STACK(CoordStruct const*, pCoords, 0x4);
	R->AL(FogSystem::IsLocationFogged(*pCoords));
	return 0;
}

SYRINGE_PATCH(0x577EBF, Fog_MapClass_Reveal, 6)
{
	GET(CellClass* const, pCell, EAX);

	pCell->ShroudCounter = 0;
	pCell->GapsCoveringThisCell = 0;
	pCell->AltFlags |= AltCellFlags::Mapped | AltCellFlags::NoFog;
	pCell->Flags |= CellFlags::EdgeRevealed | CellFlags::CenterRevealed;
	// clean the fogged objects
	pCell->CleanFog();
	//Debug::Log("MapClass_Reveal\n");
	return 0x577EE9;
}


SYRINGE_PATCH(0x70076E, Fog_TechnoClass_GetCursorOverCell_OverFog, 5)
{
	GET(CellClass* const, pCell, EBP);

	CellFogData* fogData = FogSystem::GetFogData(pCell);

	if (auto foggedBuilding = fogData->Building)
	{
		if (!HouseClass::CurrentPlayer->IsAlliedWith(foggedBuilding->Owner)) {
			if (foggedBuilding->BuildingType->LegalTarget) {
				R->Stack(0x13, true);
			}
		}
	}
	else if (auto foggedOverlay = fogData->Overlay)
	{
		int overlayIndex = foggedOverlay->OverlayIndex;
		if (overlayIndex > 0) {
			R->Stack(0x18, overlayIndex);
		}
	}

	return 0x700800;
}

SYRINGE_PATCH(0x51F97C, Fog_InfantryClass_MouseOverCell_OverFog, 5)
{
	GET(CellClass* const, pCell, EAX);

	CellFogData* fogData = FogSystem::GetFogData(pCell);

	if (auto foggedBuilding = fogData->Building) {
		R->EBP(foggedBuilding->BuildingType);

		if (foggedBuilding->BuildingType->BridgeRepairHut) {
			GET(InfantryClass* const, pThis, EDI);
			if (pThis->Type->Engineer && pThis->Owner->IsControlledByCurrentPlayer()) {
				REF_STACK(CellStruct, cell, STACK_OFFSET(0x1C, 0xC));
				cell = CellClass::Coord2Cell(foggedBuilding->Location);
				R->EDX(&cell);
				return 0x51FA6A;
			}
		}
	}

	return 0x51F9F4;
}

SYRINGE_PATCH(0x6B8E7A, Fog_ScenarioClass_LoadSpecialFlags, 6)
{
	GET(ScenarioClass* const, pScenario, ESI);
	bool fogOfWar = R->AL();

	pScenario->SpecialFlags.FogOfWar = RulesClass::Instance->FogOfWar || fogOfWar || GameModeOptionsClass::Instance->FogOfWar;
	//Debug::Log("ScenarioClass_LoadSpecialFlags::%X\n", ((int&&)pScenario->SpecialFlags) & 0x1000);
	R->ECX(R->EDI());

	return 0x6B8E8B;
}

SYRINGE_PATCH(0x686C03, Fog_SetScenarioFlags_FogOfWar, 5) {
	GET(ScenarioFlags, SpecialFlags, EAX);
	SpecialFlags.CTFMode = false; // and ah, 0EFh
	SpecialFlags.FogOfWar = RulesClass::Instance->FogOfWar || GameModeOptionsClass::Instance->FogOfWar;
	//Debug::Log("SetScenarioFlags_FogOfWar::%X\n", ((int&&)SpecialFlags) & 0x1000);
	R->EDX((int&&)SpecialFlags);
	return 0x686C0E;
}

SYRINGE_PATCH(0x4ACE3C, Fog_MapClass_TryReshroudCell_SetCopyFlag, 6)
{
	GET(CellClass* const, pCell, EAX);
	auto flags = pCell->AltFlags;

	pCell->AltFlags &= ~AltCellFlags::NoFog;

	char shroudedness = TacticalClass::Instance->GetOcclusion(pCell->MapCoords, false);
	// work just like fog
	if ((flags & AltCellFlags::NoFog || pCell->Visibility != shroudedness) && shroudedness >= 0 && pCell->Visibility >= -1) {
		pCell->Visibility = shroudedness;
		pCell->AltFlags |= AltCellFlags::Mapped;

	}

	TacticalClass::Instance->RegisterCellAsVisible(pCell);

	return 0x4ACE57;
}

SYRINGE_PATCH(0x4A9CA0, Fog_MapClass_RevealFogShroud, 7)
{
	GET(MapClass* const, pThis, ECX);
	GET_STACK(CellStruct* const, pCellStruct, 0x4);
	GET_STACK(HouseClass* const, pHouse, 0x8);
	//GET_STACK(bool, addShroudCounter, 0x10);

	R->EAX(FogSystem::RevealFogShroud(*pCellStruct, pHouse));

	return 0x4A9DC6;
}
//#undef CellMember_NeedRegetOcclusion

SYRINGE_PATCH(0x486BF0, Fog_CellClass_CleanFog, 9)
{
	GET(CellClass* const, pThis, ECX);
	FogSystem::CleanFog(pThis);
	return 0x486C4C;
}

// SYRINGE_PATCH(0x4ACC50, Fog_MapClass_TryFogCell, 5)
// {
// 	GET_STACK(CellStruct* const, pCellStruct, 0x4);

// 	if (MapClass::Instance->CoordinatesLegal(*pCellStruct))
// 	{
// 		auto pCell = MapClass::Instance->GetCellAt(*pCellStruct);
// 	}

// 	return 0x4ACD8E;
// }

SYRINGE_PATCH(0x486A70, Fog_CellClass_FogCell, 5)
{
	GET(CellClass* const, pThis, ECX);
	FogSystem::FogCell(pThis);
	return 0x486BE6;
}

SYRINGE_PATCH(0x486C50, Fog_CellClass_ClearFoggedObjects, 6)
{
	GET(CellClass* const, pThis, ECX);
	FogSystem::ClearFoggedObjects(pThis);
	return 0x486D8A;
}

SYRINGE_PATCH(0x4FC1FF, Fog_HouseClass_AcceptDefeat_CleanShroudFog, 6)
{
	GET(HouseClass* const, pHouse, ESI);
	// instead of MapClass::Instance->sub_577F30(pHouse);
	MapClass::Instance->Reveal(pHouse);
	//Debug::Log("HouseClass_AcceptDefeat_CleanShroudFog::RevealMap\n");
	return 0x4FC214;
}

SYRINGE_PATCH(0x6F5190, Fog_TechnoClass_DrawExtras_CheckFog, 6)
{
	GET(TechnoClass* const, pThis, ECX);
	return FogSystem::IsLocationFogged(pThis->GetCoords()) ? 0x6F5EEC : 0;
}

SYRINGE_PATCH(0x6D3470, Fog_TacticalClass_DrawFoggedObject, 8)
{
	GET_STACK(RectangleStruct* const, pRedrawRect, STACK_OFFSET(0, 0x4));
	GET_STACK(RectangleStruct* const, pRedrawRect2, STACK_OFFSET(0, 0x8));
	GET_STACK(bool, reDrawScreen, STACK_OFFSET(0, 0xC));

	FogSystem::RenderAllFoggedObjects(*pRedrawRect, *pRedrawRect2, reDrawScreen);

	return 0x6D3650;
}

SYRINGE_PATCH(0x440B8D, Fog_BuildingClass_Put_CheckFog, 6)
{
	GET(BuildingClass* const, pBuilding, ESI);

	if (pBuilding->IsAllFogged()) {
		FogSystem::FogBuilding(pBuilding->GetCell(), pBuilding, false);
	}

	return 0x440C08;
}

SYRINGE_PATCH(0x48049E, Fog_CellClass_DrawTileAndSmudge_CheckFog, 6)
{
	GET(CellClass* const, pCell, ESI);

	if (pCell->SmudgeTypeIndex != -1 && !pCell->IsFogged()) {
		return 0x4804A4;
	}

	return 0x4804FB;
}

SYRINGE_PATCH(0x6D6EDA, Fog_TacticalClass_Overlay_CheckFog1, 0xA)
{
	GET(CellClass* const, pCell, EAX);

	if (pCell->OverlayTypeIndex != -1 && !pCell->IsFogged()) {
		return 0x6D6EE4;
	}

	return 0x6D7006;
}

SYRINGE_PATCH(0x6D70BC, Fog_TacticalClass_Overlay_CheckFog2, 0xA)
{
	GET(CellClass* const, pCell, EAX);

	if (pCell->OverlayTypeIndex != -1 && !pCell->IsFogged()) {
		return 0x6D70C6;
	}

	return 0x6D71A4;
}

// SYRINGE_PATCH(0x6F8E1F, Fog_TechnoClass_SelectAutoTarget_CheckFog, 6)
// {
// 	GET(TechnoTypeClass* const, pType, EAX);
// 	//GET(TechnoClass* const, pType, ESI);
// 	GET_STACK(CoordStruct* const, pTargetCoord, STACK_OFFSET(0x6C, 0x8));



// 	// return nullptr
// 	return 0x6F8E38;
// }
