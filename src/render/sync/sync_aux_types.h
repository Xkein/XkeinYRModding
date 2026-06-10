#pragma once

#include <cstdint>
#include <vector>

// Cell Fog 状态变化
struct CellUpdate
{
    int32_t CellX, CellY;
    bool    Revealed : 1;
    bool    Fogged   : 1;
    bool    Shrouded : 1;
};

// 激光数据
struct LaserData
{
    float    StartX, StartY, StartZ;
    float    EndX, EndY, EndZ;
    uint32_t InnerColor;  // RGB
    uint32_t OuterColor;
    uint8_t  Type;         // 0=Standard, 1=Sonic, 2=BigLaser, 3=Magnetron
    int32_t  Duration;     // 剩余帧数（-1=永久）
};

// 文字数据
struct TextData
{
    float    ScreenX, ScreenY;
    char     Text[128];
    uint32_t Color;     // RGB
    uint8_t  Style;     // 0=普通, 1=粗体, 2=小号...
};

// 粒子数据
struct ParticleData
{
    uint32_t EntityID;
    uint32_t AssetNameHash;
    float    PosX, PosY, PosZ;
    float    VelX, VelY, VelZ;
    float    LifeRemaining;
    int32_t  FrameIndex;
};