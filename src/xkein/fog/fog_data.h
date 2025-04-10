#pragma once

#include <GeneralStructures.h>
#include <FootClass.h>
#include <vector>

class FoggedObject
{
public:
	virtual void Render(const RectangleStruct& rect) = 0;

	void UpdateSortingKey();

	bool operator<(const FoggedObject& other) const;

	int arrayIndex;
	unsigned long long sortingKey;

	CoordStruct Location;
	RectangleStruct Bound;
};

class FoggedBuilding : public FoggedObject
{
public:
	virtual void Render(const RectangleStruct& rect) override;

	struct AnimRecord
	{
		AnimTypeClass* AnimType;
		int FrameIndex;
		int zAdjust;
	};
	bool IsVisible;
	HouseClass* Owner;
	BuildingTypeClass* BuildingType;
	int FrameIndex;
	FacingClass TurretFacing;
	FacingClass BarrelFacing;
	RecoilData TurretRecoil;
	RecoilData BarrelRecoil;
	bool IsFireStormWall;
	std::vector<AnimRecord> Records;
	unsigned int BuildingTypeIndex;
};

class FoggedTerrain : public FoggedObject
{
public:
	virtual void Render(const RectangleStruct& rect) override;

	TerrainTypeClass* TerrainType;
};

class FoggedSmudge : public FoggedObject
{
public:
	virtual void Render(const RectangleStruct& rect) override;

	int SmudgeIndex;
};

class FoggedOverlay : public FoggedObject
{
public:
	virtual void Render(const RectangleStruct& rect) override;

	int OverlayIndex;
	int Powerup;
};

struct CellFogData
{
    FoggedBuilding* Building;
    FoggedTerrain* Terrain;
    FoggedSmudge* Smudge;
    FoggedOverlay* Overlay;
};

class FogSystem
{
public:
    static void Init();

    static void Clear();

	static void Save();

	static void Load();

    static CellFogData* GetFogData(CellClass* pCell);

	static void CleanFog(CellClass* pCell);

	static void ClearFoggedObjects(CellClass* pCell);

	static void FogBuilding(CellClass* pCell, BuildingClass* pBuilding, bool visible);

	static void FogCell(CellClass* pCell);

	static bool RevealFogShroud(CellStruct cellStruct, HouseClass* pHouse);

	static bool IsLocationFogged(CoordStruct const& location);

    static void RenderAllFoggedObjects(RectangleStruct const& dirtyRect1, RectangleStruct const& dirtyRect2, bool fullScreenRedraw);
};

