#pragma once

#include "runtime/platform/platform.h"
#include <jolt/jolt.h>
#include <Jolt/Renderer/DebugRenderer.h>

class DebugRendererImpl final : public JPH::DebugRenderer
{
    void  DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor) override;
    void  DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow) override;
    Batch CreateTriangleBatch(const Triangle* inTriangles, int inTriangleCount) override;
    Batch CreateTriangleBatch(const Vertex* inVertices, int inVertexCount, const uint32* inIndices, int inIndexCount) override;
    void  DrawGeometry(JPH::RMat44Arg     inModelMatrix,
                       const JPH::AABox&  inWorldSpaceBounds,
                       float              inLODScaleSq,
                       JPH::ColorArg      inModelColor,
                       const GeometryRef& inGeometry,
                       ECullMode          inCullMode,
                       ECastShadow        inCastShadow,
                       EDrawMode          inDrawMode) override;
    void  DrawText3D(JPH::RVec3Arg inPosition, const std::string_view& inString, JPH::ColorArg inColor, float inHeight) override;
};
