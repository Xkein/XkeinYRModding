#include "xkein/fog/fog_data.h"
#include "fog_data.h"
#include "runtime/logger/logger.h"
#include "xkein/compat/compat_ares.h"
#include <AnimClass.h>
#include <BuildingClass.h>
#include <MapClass.h>
#include <TacticalClass.h>
#include <ScenarioClass.h>
#include <TerrainClass.h>
#include <SmudgeClass.h>
#include <HouseClass.h>
#include <Matrix3D.h>
#include <unordered_map>

template<typename Type>
struct FogCache
{
    std::vector<std::unique_ptr<Type>> items;
    std::vector<Type*> freeList;
    Type* Take() {
        if (freeList.empty()) {
            items.push_back(std::make_unique<Type>());
            return items.back().get();
        }
        Type* item = freeList.back();
        freeList.pop_back();
        return item;
    }

    void Return(Type* item) {
        freeList.push_back(item);
    }

    void Clear() {
        items.clear();
        freeList.clear();
    }
};

BYTE VXLBuffer[sizeof(BuildingClass)]{};
bool VXLBufferInitialized = false;

inline BuildingClass* GetVXLBuffer()
{
	return reinterpret_cast<BuildingClass*>(VXLBuffer);
}

inline void SetVXLBuffer(FoggedBuilding* pFogged)
{
	auto buffer = GetVXLBuffer();
	buffer->Type = pFogged->BuildingType;
	buffer->SecondaryFacing = pFogged->TurretFacing;
	buffer->BarrelFacing = pFogged->BarrelFacing;
	buffer->TurretRecoil = pFogged->TurretRecoil;
	buffer->BarrelRecoil = pFogged->BarrelRecoil;
	buffer->Owner = pFogged->Owner;
	buffer->Location = pFogged->Location;
}

inline void InitVXLBuffer(BuildingClass* pBuilding)
{
	VXLBufferInitialized = true;
	CopyMemory(VXLBuffer, pBuilding, sizeof(VXLBuffer));
	auto buffer = GetVXLBuffer();
	buffer->BeingWarpedOut = false;
	buffer->WarpingOut = false;
	buffer->WarpFactor = 0.0f;
}

std::unordered_map<CellClass*, CellFogData> gFogData;
FogCache<FoggedBuilding> gCacheFoggedBuilding;
FogCache<FoggedTerrain> gCacheFoggedTerrain;
FogCache<FoggedSmudge> gCacheFoggedSmudge;
FogCache<FoggedOverlay> gCacheFoggedOverlay;
std::vector<FoggedObject*> gFoggedObjects;

const CellStruct FoundationEndMarker = {0x7FFF, 0x7FFF};

void AddFoggedObject(FoggedObject* foggedObject) {
	foggedObject->arrayIndex = gFoggedObjects.size();
	gFoggedObjects.push_back(foggedObject);
}

void RemoveFoggedObject(FoggedObject* foggedObject) {
	gFoggedObjects[foggedObject->arrayIndex] = gFoggedObjects.back();
	gFoggedObjects.back()->arrayIndex = foggedObject->arrayIndex;
	gFoggedObjects.pop_back();
}

void FogSystem::Init()
{
    
}

void FogSystem::Clear()
{
    gFogData.clear();
    gCacheFoggedBuilding.Clear();
    gCacheFoggedTerrain.Clear();
    gCacheFoggedSmudge.Clear();
    gCacheFoggedOverlay.Clear();
	gFoggedObjects.clear();
}

CellFogData* FogSystem::GetFogData(CellClass* pCell)
{
	auto iter = gFogData.find(pCell);
	if (iter == gFogData.end()) {
		auto pair = gFogData.emplace(pCell, CellFogData{nullptr,nullptr,nullptr,nullptr});
		iter = pair.first;
	}
    return &iter->second;
}

void FogSystem::CleanFog(CellClass* pCell)
{
	CellStruct cell = pCell->MapCoords;
	int level = 1;// pThis->Level;
	do
	{
		CellClass* const pCur = MapClass::Instance->GetCellAt(cell);
		int curLevel = pCur->Level;
		if (curLevel >= level - 2 && curLevel <= level)
		{
			pCur->Flags &= ~CellFlags::Fogged;
			ClearFoggedObjects(pCur);
		}

		++cell.X;
		++cell.Y;
		level += 2;
	} while (level < 15);
}

void FogSystem::ClearFoggedObjects(CellClass* pCell)
{
    CellFogData* fogData = GetFogData(pCell);
    if (FoggedBuilding* foggedBuilding = fogData->Building) {
        if (foggedBuilding->BuildingTypeIndex < BuildingTypeClass::Array->Count) {
            auto base = CellClass::Coord2Cell(foggedBuilding->Location);
    
            auto firstCell = base;
            auto data = foggedBuilding->BuildingType->GetFoundationData(false);
            if (data[0] != FoundationEndMarker) {
                firstCell += data[0];
            }
    
            if (auto pCur = MapClass::Instance->GetCellAt(firstCell)) {
                if (auto pBuilding = pCur->GetBuilding())
                {
                    for (auto pAnim : pBuilding->Anims)
                    {
                        if (pAnim) {
                            pAnim->IsFogged = false;
                        }
                    }
                    pBuilding->IsFogged = false;
                }
                foggedBuilding->Records.clear();
    
                for (;*data != FoundationEndMarker; ++data)
                {
                    pCur = MapClass::Instance->GetCellAt(CellStruct{ base.X + data->X ,base.Y + data->Y });
                    if (pCur != pCell)
                    {
                        CellFogData* otherFogData = GetFogData(pCur);
                        if (otherFogData->Building == foggedBuilding)
                        {
                            otherFogData->Building = nullptr;
                        }
					}
                    if (TacticalClass* instance = TacticalClass::Instance) {
                        foggedBuilding->Bound.X -= instance->TacticalPos.X;
                        foggedBuilding->Bound.Y -= instance->TacticalPos.Y;
                        instance->RegisterDirtyArea(foggedBuilding->Bound, false);
                    }
                }
            }
        }
        gCacheFoggedBuilding.Return(fogData->Building);
		RemoveFoggedObject(fogData->Building);
		fogData->Building = nullptr;
    }
    if (fogData->Terrain) {
        gCacheFoggedTerrain.Return(fogData->Terrain);
		RemoveFoggedObject(fogData->Terrain);
		fogData->Terrain = nullptr;
    }
    if (fogData->Smudge) {
        gCacheFoggedSmudge.Return(fogData->Smudge);
		RemoveFoggedObject(fogData->Smudge);
		fogData->Smudge = nullptr;
    }
    if (fogData->Overlay) {
        gCacheFoggedOverlay.Return(fogData->Overlay);
		RemoveFoggedObject(fogData->Overlay);
		fogData->Overlay = nullptr;
    }
}


void FogSystem::FogBuilding(CellClass* pCell, BuildingClass* pBuilding, bool visible)
{
    CellFogData* fogData = GetFogData(pCell);
    FoggedBuilding* foggedBuilding = fogData->Building;
    if (!foggedBuilding) {
        fogData->Building = foggedBuilding = gCacheFoggedBuilding.Take();
		AddFoggedObject(foggedBuilding);
    }
    
	foggedBuilding->Location = pBuilding->Location;
	foggedBuilding->Owner = pBuilding->Owner;
	foggedBuilding->BuildingType = pBuilding->Type;
	foggedBuilding->FrameIndex = pBuilding->GetCurrentFrame();
	//foggedBuilding->TurretFacing = pBuilding->TurretFacing;
	foggedBuilding->TurretFacing = pBuilding->PrimaryFacing;
	foggedBuilding->BarrelFacing = pBuilding->BarrelFacing;
	foggedBuilding->TurretRecoil = pBuilding->TurretRecoil;
	foggedBuilding->BarrelRecoil = pBuilding->BarrelRecoil;
	foggedBuilding->IsFireStormWall = pBuilding->Type->FirestormWall;
	foggedBuilding->IsVisible = visible;
	
	foggedBuilding->BuildingTypeIndex = foggedBuilding->BuildingType->ArrayIndex;

	pBuilding->GetRenderDimensions(&foggedBuilding->Bound);

    foggedBuilding->Records.clear();
	for (auto pAnim : pBuilding->Anims)
	{
		if (pAnim) {
			FoggedBuilding::AnimRecord record;
			record.AnimType = pAnim->Type;
			record.FrameIndex = pAnim->Type->Start + pAnim->Animation.Value;

			int zAdujst = pAnim->ZAdjust + pAnim->Type->YDrawOffset - TacticalClass::AdjustForZ(pAnim->GetZ()) - pAnim->Type->Flat ? 3 : 2;
			record.zAdjust = zAdujst;

			foggedBuilding->Records.push_back(record);

			pAnim->IsFogged = true;

			RectangleStruct animRect;
			pAnim->GetDimensions(&animRect);
			foggedBuilding->Bound = Drawing::Union(foggedBuilding->Bound, animRect);
		}
	}

	TacticalClass::Instance->RegisterDirtyArea(foggedBuilding->Bound, false);
	foggedBuilding->Bound.X += TacticalClass::Instance->TacticalPos.X;
	foggedBuilding->Bound.Y += TacticalClass::Instance->TacticalPos.Y;

	pBuilding->IsFogged = true;

	if (VXLBufferInitialized == false && foggedBuilding->BuildingType->TurretAnimIsVoxel || foggedBuilding->BuildingType->BarrelAnimIsVoxel) {
		InitVXLBuffer(pBuilding);
	}

	if (foggedBuilding->Owner == nullptr) {
		gLogger->error("FoggedBuilding::CTOR::meet nullptr Owner, type:[{}], location: {}, {}, {}\n", foggedBuilding->BuildingType->ID, foggedBuilding->Location.X,foggedBuilding->Location.Y,foggedBuilding->Location.Z);
	}

	auto base = pBuilding->GetMapCoords();
	for (auto data = pBuilding->Type->GetFoundationData(false); *data != FoundationEndMarker; ++data)
	{
		auto pCur = MapClass::Instance->GetCellAt(CellStruct{ base.X + data->X ,base.Y + data->Y });
		if (pCell != pCur) {
			CellFogData* otherFogData = GetFogData(pCell);
			otherFogData->Building = foggedBuilding;
		}
	}

	foggedBuilding->UpdateSortingKey();
}

void FogTerrain(CellClass* pCell, TerrainClass* pTerrain)
{
    CellFogData* fogData = FogSystem::GetFogData(pCell);
    FoggedTerrain* foggedTerrain = fogData->Terrain;
    if (!foggedTerrain) {
        fogData->Terrain = foggedTerrain = gCacheFoggedTerrain.Take();
		AddFoggedObject(foggedTerrain);
    }

    foggedTerrain->Location = pTerrain->Location;
    foggedTerrain->TerrainType = pTerrain->Type;

    pTerrain->GetRenderDimensions(&foggedTerrain->Bound);
    foggedTerrain->Bound.X += TacticalClass::Instance->TacticalPos.X;
    foggedTerrain->Bound.Y += TacticalClass::Instance->TacticalPos.Y;
	
	foggedTerrain->UpdateSortingKey();
}

void FogSmudge(CellClass* pCell)
{
    CellFogData* fogData = FogSystem::GetFogData(pCell);
    FoggedSmudge* foggedSmudge = fogData->Smudge;
    if (!foggedSmudge) {
        fogData->Smudge = foggedSmudge = gCacheFoggedSmudge.Take();
		AddFoggedObject(foggedSmudge);
    }

	foggedSmudge->Location = pCell->GetCoords();
	foggedSmudge->SmudgeIndex = pCell->SmudgeTypeIndex;

	Point2D drawPoint;
	TacticalClass::Instance->CoordsToClient(&foggedSmudge->Location, &drawPoint);

	foggedSmudge->Bound = { TacticalClass::Instance->TacticalPos.X + drawPoint.X - 30, TacticalClass::Instance->TacticalPos.Y + drawPoint.Y - 15, 60, 30 };

	foggedSmudge->UpdateSortingKey();
}

void FogOverlay(CellClass* pCell)
{
    CellFogData* fogData = FogSystem::GetFogData(pCell);
    FoggedOverlay* foggedOverlay = fogData->Overlay;
    if (!foggedOverlay) {
        fogData->Overlay = foggedOverlay = gCacheFoggedOverlay.Take();
		AddFoggedObject(foggedOverlay);
    }

	foggedOverlay->Location = pCell->GetCoords();
	foggedOverlay->OverlayIndex = pCell->OverlayTypeIndex;
	foggedOverlay->Powerup = pCell->OverlayData;

	RectangleStruct rect, rect2;
	pCell->ShapeRect(&rect);
	pCell->GetContainingRect(&rect2);

	foggedOverlay->Bound = Drawing::Union(rect, rect2);
	
	foggedOverlay->Bound.X += TacticalClass::Instance->TacticalPos.X - DSurface::ViewBounds->X;
	foggedOverlay->Bound.Y += TacticalClass::Instance->TacticalPos.Y - DSurface::ViewBounds->Y;
	
	foggedOverlay->UpdateSortingKey();
}

void FogSystem::FogCell(CellClass* pCell)
{
	if (ScenarioClass::Instance->SpecialFlags.FogOfWar) {
		CellStruct cell = pCell->MapCoords;

		int level = 1;// pThis->Level;
		do
		{
			CellClass* const pCur = MapClass::Instance->GetCellAt(cell);
			int curLevel = pCur->Level;
			if (curLevel >= level - 2 && curLevel <= level && !(pCur->Flags & CellFlags::Fogged))
			{
				pCur->Flags |= CellFlags::Fogged;
				auto pObject = pCur->FirstObject;
				for (; pObject; pObject = pObject->NextObject)
				{
					switch (pObject->WhatAmI())
					{
					case AbstractType::Building: {
						auto pBuilding = (BuildingClass*)pObject;
						if (pBuilding->IsAllFogged())
						{
							FogBuilding(pCur, pBuilding, true);
						}
					}
					    break;
					case AbstractType::Unit:
					case AbstractType::Infantry:
					case AbstractType::Aircraft:
						pObject->Deselect();
						break;
					case AbstractType::Terrain:
                        FogTerrain(pCur, (TerrainClass*)pObject);
						break;
					}
				}

				if (pCur->OverlayTypeIndex != -1) {
                   FogOverlay(pCur);
				}

				if (pCur->SmudgeTypeIndex != -1 && pCur->SmudgeData == 0) {
                    FogSmudge(pCur);
				}
			}

			++cell.X;
			++cell.Y;
			level += 2;
		} while (level < 15);
	}
}

bool FogSystem::RevealFogShroud(CellStruct cellStruct, HouseClass* pHouse)
{
	CellClass* pCell = MapClass::Instance->GetCellAt(cellStruct);
	bool shouldCleanFoggedObject = !(pCell->Flags & CellFlags::EdgeRevealed);
	bool reDraw = shouldCleanFoggedObject || !(pCell->AltFlags & AltCellFlags::Mapped);
	bool unk = reDraw;

	pCell->Flags = pCell->Flags & ~CellFlags::FlagToShroud | CellFlags::EdgeRevealed;
	// work just like fog
	pCell->AltFlags = pCell->AltFlags & ~AltCellFlags::Unknown_20 | AltCellFlags::Mapped;

	auto shroudedness = TacticalClass::Instance->GetOcclusion(cellStruct, false);
	if (shroudedness != pCell->Visibility) {
		reDraw = true;
		pCell->Visibility = static_cast<char>(shroudedness);
	}

	if (pCell->Visibility == -1) {
		pCell->AltFlags |= AltCellFlags::NoFog;
	}

	auto foggedness = TacticalClass::Instance->GetOcclusion(cellStruct, true);
	if (foggedness != pCell->Foggedness)
	{
		pCell->Foggedness = static_cast<char>(foggedness);
		reDraw = true;
	}

	if (pCell->Foggedness == -1) {
		pCell->Flags |= CellFlags::CenterRevealed;
	}

	if (reDraw)
	{
		TacticalClass::Instance->RegisterCellAsVisible(pCell);
		MapClass::Instance->RevealCheck(pCell, pHouse, unk);
	}

	if (/*pCell->Flags & cf_NotFullyFog && */shouldCleanFoggedObject && ScenarioClass::Instance->SpecialFlags.FogOfWar) {
		//if (IsFogged(pCell)) {
		pCell->CleanFog();
		//}
	}

	return reDraw;
}

CellStruct TranslateBaseCell(const CoordStruct& coords) {
    auto const adjust = (TacticalClass::AdjustForZ(coords.Z) / -30) << 8;
    auto const baseCoords = coords + CoordStruct{adjust, adjust, 0};
    return CellClass::Coord2Cell(baseCoords);
}

bool FogSystem::IsLocationFogged(CoordStruct const& location)
{
	CellClass* pCell = MapClass::Instance->GetCellAt(TranslateBaseCell(location));

	if (pCell->Flags & CellFlags::EdgeRevealed) {
		return 0;
	}

	pCell = pCell->GetNeighbourCell(FacingType::SouthEast);
	return !(pCell->Flags & CellFlags::EdgeRevealed);
}

template<typename TKey, typename TValue>
IndexClass<int, int>& CastIndexClass(IndexClass<TKey, TValue>& index) {
    return *reinterpret_cast<IndexClass<int, int>*>(&index);
}

LightConvertClass* GetValidLightConvert(CellClass* pCell)
{
    if (pCell->LightConvert == nullptr) {
        pCell->InitLightConvert(nullptr, 0x10000, 0, 1000, 1000, 1000);
    }
    return pCell->LightConvert;
}


void RenderFoggedBuilding(FoggedBuilding* foggedBuilding, const RectangleStruct& rect)
{
    CoordStruct&                             Location          = foggedBuilding->Location;
    RectangleStruct&                         Bound             = foggedBuilding->Bound;
    bool&                                    IsVisible         = foggedBuilding->IsVisible;
    HouseClass*&                             Owner             = foggedBuilding->Owner;
    BuildingTypeClass*&                      BuildingType      = foggedBuilding->BuildingType;
    int&                                     FrameIndex        = foggedBuilding->FrameIndex;
    FacingClass&                             TurretFacing      = foggedBuilding->TurretFacing;
    FacingClass&                             BarrelFacing      = foggedBuilding->BarrelFacing;
    RecoilData&                              TurretRecoil      = foggedBuilding->TurretRecoil;
    RecoilData&                              BarrelRecoil      = foggedBuilding->BarrelRecoil;
    bool&                                    IsFireStormWall   = foggedBuilding->IsFireStormWall;
    std::vector<FoggedBuilding::AnimRecord>& Records           = foggedBuilding->Records;
    unsigned int&                            BuildingTypeIndex = foggedBuilding->BuildingTypeIndex;

    if (BuildingType->InvisibleInGame || !IsVisible) {
		return;
	}

	const int colorIdx = Owner->ColorSchemeIndex;
	ConvertClass* const defPal = ColorScheme::Array->Items[colorIdx]->LightConvert;

	auto baseSHP = BuildingType->GetImage();

	CoordStruct location = Location;
	location.X -= 128;// ???
	location.Y -= 128;

	Point2D drawPoint;
	TacticalClass::Instance->CoordsToClient(&location, &drawPoint);
	drawPoint.X += DSurface::ViewBounds->X - rect.X;
	drawPoint.Y += DSurface::ViewBounds->Y - rect.Y;

	auto pCell = MapClass::Instance->TryGetCellAt(Location);

	ConvertClass* pal = BuildingType->TerrainPalette ? GetValidLightConvert(pCell) : defPal;
	if (auto pPalVector = BuildingType->Palette) {
		pal = pPalVector->GetItem(colorIdx)->LightConvert;
	}

	if (baseSHP) {
		RectangleStruct baseRect = rect;
		int height = drawPoint.Y + baseSHP->Height / 2;
		if (rect.Height > height)
			baseRect.Height = height;// ???

		int zAdjust = -TacticalClass::AdjustForZ(Location.Z) - 2;
		int intensity = BuildingType->ExtraLight + pCell->Intensity_Normal;

		// draw basic image
		if (baseRect.Height > 0)
		{
			if (IsFireStormWall)
			{
				DSurface::Temp->DrawSHP(pal, baseSHP, FrameIndex, &drawPoint, &baseRect,
					BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
					0, zAdjust, ZGradient::Ground, intensity, 0, 0, 0, 0, 0);
			}
			else
			{
				Point2D ZS = BuildingType->ZShapePointMove;
				Point2D client{ BuildingType->GetFoundationWidth() * 256 - 256, BuildingType->GetFoundationHeight(false) * 256 - 256 };
				Point2D dest = TacticalClass::Instance->AdjustForZShapeMove(client.X, client.Y);
				ZS.X += 144 - dest.X;
				ZS.Y += 172 - dest.Y;

				SHPStruct* BUILDINGZ_SHA = FileSystem::BUILDINGZ_SHA;

				DSurface::Temp->DrawSHP(pal, baseSHP, FrameIndex, &drawPoint, &baseRect,
					BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
					0, zAdjust + BuildingType->NormalZAdjust, ZGradient::Deg90, intensity, 0,
					//BUILDINGZ_SHA, 0, ZS.X, ZS.Y);
					nullptr, 0, 0, 0);

				// draw shadow 
				DSurface::Temp->DrawSHP(pal, baseSHP, FrameIndex + baseSHP->Frames / 2, &drawPoint, &baseRect,
					BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered | BlitterFlags::Darken,
					0, zAdjust, ZGradient::Ground, 0x3E8, 0, nullptr, 0, 0, 0);

				if (BuildingType->BibShape) {
					DSurface::Temp->DrawSHP(pal, BuildingType->BibShape, FrameIndex, &drawPoint, &baseRect,
						BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
						0, zAdjust - 1, ZGradient::Ground, intensity, 0, nullptr, 0, 0, 0);
				}
			}
		}

		Point2D drawPoint_VXL = drawPoint + BuildingType->BuildingAnim[9].Position;

		if (BuildingType->TurretAnimIsVoxel || BuildingType->BarrelAnimIsVoxel) {
			bool hasTurret = BuildingType->TurretVoxel.VXL && BuildingType->TurretVoxel.HVA;
			bool hasBarrel = BuildingType->BarrelVoxel.VXL && BuildingType->BarrelVoxel.HVA;
			SetVXLBuffer(foggedBuilding);
			Matrix3D turretMatrix = Matrix3D::GetIdentity();
			Vector3D<float> negTranslation = -turretMatrix.GetTranslation();
			if (hasTurret) {
                turretMatrix.RotateZ(TurretFacing.Current().GetRadian<16>());
				turretMatrix.TranslateX(float(BuildingType->TurretOffset / 8));
			}
			else if (hasBarrel) {
				turretMatrix.Translate(negTranslation);
				turretMatrix.RotateZ((float)TurretFacing.Current().GetRadian<16>());
			}

			auto turretFacingValue = TurretFacing.Current().GetValue<16>();
			if (TurretRecoil.State != RecoilData::RecoilState::Inactive) {
				turretMatrix.TranslateX(TurretRecoil.TravelSoFar);
				turretFacingValue = -1;
			}

			if (hasTurret) {
				Matrix3D drawMatrix = (Matrix3D)Matrix3D::VoxelDefaultMatrix * turretMatrix;
				GetVXLBuffer()->DrawVoxel(BuildingType->TurretVoxel, 0, turretFacingValue, CastIndexClass(BuildingType->VoxelTurretWeaponCache), rect, drawPoint_VXL, drawMatrix, intensity, 0, 0);
			}

			if (hasBarrel) {
				Matrix3D barrelMatrix = turretMatrix;
				turretMatrix.Translate(negTranslation);

				if (BarrelRecoil.State != RecoilData::RecoilState::Inactive) {
					barrelMatrix.TranslateX(BarrelRecoil.TravelSoFar);
					turretFacingValue = -1;
				}
				barrelMatrix.RotateY((float)-BarrelFacing.Current().GetRadian<16>());
				barrelMatrix.Translate(-negTranslation);

				Matrix3D drawMatrix = (Matrix3D)Matrix3D::VoxelDefaultMatrix * barrelMatrix;
				GetVXLBuffer()->DrawVoxel(BuildingType->BarrelVoxel, 0, turretFacingValue, CastIndexClass(BuildingType->VoxelTurretBarrelCache), rect, drawPoint_VXL, drawMatrix, intensity, 0, 0);
			}
		}
	}
	else {
		gConsole->info("FoggedBuilding::Draw::meet null shp ptr, type:[{}]\n", BuildingType->ID);
	}

	for (auto& record : Records)
	{ // draw anims
		if (AnimTypeClass* pAnimType = record.AnimType)
		{
			if (auto animSHP = pAnimType->GetImage()) {
				ConvertClass* pal = CompatAres::GetAnimConvert(pAnimType, defPal);
				int zAdjust = record.zAdjust;// -TacticalClass::AdjustForZ(pFO->Location.Z) - 2;

				DSurface::Temp->DrawSHP(pal, animSHP, record.FrameIndex, &drawPoint, &rect,
					//BlitterFlags::Plain | BlitterFlags::Warp | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
					BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
					0,
                    zAdjust, pAnimType->Flat ? ZGradient::Ground : ZGradient::Deg90,
                    pAnimType->UseNormalLight ? 1000 : pCell->Intensity_Normal, 0, nullptr, 0, 0, 0);

				if (pAnimType->Shadow) {
					DSurface::Temp->DrawSHP(pal, animSHP, record.FrameIndex + animSHP->Frames / 2, &drawPoint, &rect,
						BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered | BlitterFlags::Darken,
						0, zAdjust, ZGradient::Deg90, 0x3E8, 0, nullptr, 0, 0, 0);
				}
			}
			else {
				gConsole->info("FoggedBuilding::Draw::meet null shp ptr, type:[{}]\n", pAnimType->ID);
			}
		}
	}
}

void RenderFoggedTerrain(FoggedTerrain* foggedTerrain, const RectangleStruct& rect)
{
	auto pTerrainType = foggedTerrain->TerrainType;
	auto SHP = pTerrainType->GetImage();

	CoordStruct location = foggedTerrain->Location;

	Point2D drawPoint;
	TacticalClass::Instance->CoordsToClient(&location, &drawPoint);
	drawPoint.X += DSurface::ViewBounds->X - rect.X;
	drawPoint.Y += DSurface::ViewBounds->Y - rect.Y;

	auto pCell = MapClass::Instance->TryGetCellAt(foggedTerrain->Location);
	int zAdjust = -TacticalClass::AdjustForZ(foggedTerrain->Location.Z);

	int tintColor;
	ConvertClass* pal;
	if (pTerrainType->SpawnsTiberium) {
		pal = FileSystem::GRFTXT_TIBERIUM_PAL;
		tintColor = pCell->Intensity_Normal;
		drawPoint.Y -= 16;
	}
	else {
		pal = GetValidLightConvert(pCell);
		tintColor = pCell->Intensity_Terrain;
	}

	DSurface::Temp->DrawSHP(pal, SHP, 0, &drawPoint, &rect,
		(pTerrainType->IsAnimated ? BlitterFlags::Flat : BlitterFlags::ZReadWrite) | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
		0, zAdjust - 12, ZGradient::Deg90, tintColor, 0, nullptr, 0, 0, 0);

	// draw shadow 
	DSurface::Temp->DrawSHP(GetValidLightConvert(pCell), SHP, 0 + SHP->Frames / 2, &drawPoint, &rect,
		BlitterFlags::ZReadWrite | BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered | BlitterFlags::Darken,
		0, zAdjust - 3, ZGradient::Ground, 0x3E8, 0, nullptr, 0, 0, 0);
}

void RenderFoggedSmudge(FoggedSmudge* foggedSmudge, const RectangleStruct& rect)
{
	auto pSmudgeType = SmudgeTypeClass::Array->GetItem(foggedSmudge->SmudgeIndex);
	auto SHP = pSmudgeType->GetImage();

	if (SHP) {
		Point2D drawPoint;
		drawPoint.X = DSurface::ViewBounds->X + foggedSmudge->Bound.X - TacticalClass::Instance->TacticalPos.X - rect.X + 30;
		drawPoint.Y = DSurface::ViewBounds->Y + foggedSmudge->Bound.Y - TacticalClass::Instance->TacticalPos.Y - rect.Y;

		auto pCell = MapClass::Instance->TryGetCellAt(foggedSmudge->Location);
		int zAdjust = -TacticalClass::AdjustForZ(foggedSmudge->Location.Z);

		DSurface::Temp->DrawSHP(GetValidLightConvert(pCell), SHP, 0, &drawPoint, &rect,
			BlitterFlags::Alpha | BlitterFlags::bf_400 | BlitterFlags::Centered,
			0, zAdjust, ZGradient::Deg90, pCell->Intensity_Terrain, 0, nullptr, 0, 0, 0);
	}
}

void RenderFoggedOverlay(FoggedOverlay* foggedOverlay, const RectangleStruct& rect)
{
	auto pCell = MapClass::Instance->TryGetCellAt(foggedOverlay->Location);

	Point2D drawPoint;
	CoordStruct tmp{ pCell->MapCoords.X * 256, pCell->MapCoords.Y * 256, 0 };
	TacticalClass::Instance->CoordsToClient(&tmp, &drawPoint);
	drawPoint.X -= 30;

	auto oldOverlayIdx = pCell->OverlayTypeIndex;
	auto oldPowerUp = pCell->OverlayData;

	pCell->OverlayTypeIndex = foggedOverlay->OverlayIndex;
	pCell->OverlayData = foggedOverlay->Powerup;

	pCell->DrawOverlay(drawPoint, rect);
	pCell->DrawOverlayShadow(drawPoint, rect);

	pCell->OverlayTypeIndex = oldOverlayIdx;
	pCell->OverlayData = oldPowerUp;
}

void RenderAllFoggedObjectInRect(const RectangleStruct& rect)
{
	int offsetX = DSurface::ViewBounds->X - TacticalClass::Instance->TacticalPos.X;
	int offsetY = DSurface::ViewBounds->Y - TacticalClass::Instance->TacticalPos.Y;
	for (FoggedObject* foggedObject : gFoggedObjects)
	{
		RectangleStruct drawRect {
			foggedObject->Bound.X + offsetX,
			foggedObject->Bound.Y + offsetY,
			foggedObject->Bound.Width,
			foggedObject->Bound.Height,
		};
		RectangleStruct ret = Drawing::Intersect(rect, drawRect, nullptr, nullptr);
		
		if (ret.Width > 0 && ret.Height > 0) {
			foggedObject->Render(rect);
		}
	}
}

void FogSystem::RenderAllFoggedObjects(RectangleStruct const& dirtyRect1, RectangleStruct const& dirtyRect2, bool fullScreenRedraw)
{
	std::sort(gFoggedObjects.begin(), gFoggedObjects.end());
	for (int idx = gFoggedObjects.size() - 1; idx >= 0; idx--) {
		gFoggedObjects[idx]->arrayIndex = idx;
	}

	if (fullScreenRedraw) {
		RenderAllFoggedObjectInRect(DSurface::ViewBounds);
	}
	else {
		if (dirtyRect1.Width > 0 && dirtyRect1.Height > 0) {
			RenderAllFoggedObjectInRect(dirtyRect1);
		}
		if (dirtyRect2.Width > 0 && dirtyRect2.Height > 0) {
			RenderAllFoggedObjectInRect(dirtyRect2);
		}
	}

	 {
		const auto pCells = TacticalClass::Instance->VisibleCells;
		const auto cellCount = TacticalClass::Instance->VisibleCellCount;

		for (size_t idx = 0; idx < cellCount; idx++) {
			CellClass* pCell = pCells[idx];
			auto [drawPoint, _] = TacticalClass::Instance->CoordsToClient(pCell->GetCoords());

			RectangleStruct rect = { drawPoint.X - 30 + DSurface::ViewBounds->X, drawPoint.Y + DSurface::ViewBounds->Y, 60, 30 * 2/*30*/ };
			RenderAllFoggedObjectInRect(rect);
		}

		DynamicVectorClass<DirtyAreaStruct>& dirtyAreas = Drawing::DirtyAreas;
		for (DirtyAreaStruct& dirtyArea : dirtyAreas) {
			RectangleStruct rect = Drawing::Intersect(dirtyArea.Rect, DSurface::ViewBounds, nullptr, nullptr);
			if (rect.Width > 0 && rect.Height > 0) {
				RenderAllFoggedObjectInRect(rect);
			}
		}
	}
}

void FoggedObject::UpdateSortingKey() {
	sortingKey = (unsigned long long)Location.Y << 32 | Location.X;
}

bool FoggedObject::operator<(const FoggedObject& other) const {
	return sortingKey < other.sortingKey;
}

void FoggedBuilding::Render(const RectangleStruct& rect)
{
	RenderFoggedBuilding(this, rect);
}

void FoggedTerrain::Render(const RectangleStruct& rect)
{
	RenderFoggedTerrain(this, rect);
}

void FoggedSmudge::Render(const RectangleStruct& rect)
{
	RenderFoggedSmudge(this, rect);
}

void FoggedOverlay::Render(const RectangleStruct& rect)
{
	RenderFoggedOverlay(this, rect);
}

#include "yr/event/general_event.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrSaveGameEndStreamEvent)
{

}

DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameEndStreamEvent)
{

}
