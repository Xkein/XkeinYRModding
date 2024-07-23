#include "physics/jolt/debug_renderer.h"
#include "physics/yr_math.h"
#include <Surface.h>
#include <TacticalClass.h>

ColorStruct ToColor(JPH::Color color)
{
    return ColorStruct {color.r, color.g, color.b};
}

void DebugRendererImpl::DrawLine(JPH::RVec3Arg inFrom, JPH::RVec3Arg inTo, JPH::ColorArg inColor)
{
    auto [from, visible1] = TacticalClass::Instance->CoordsToClient(ToCoord(inFrom));
    auto [to, visible2] = TacticalClass::Instance->CoordsToClient(ToCoord(inFrom));
    if (!visible1 && ! visible2)
        return;

    // DSurface::Composite->DrawLine(&from, &to, (DWORD)ToColor(inColor));
}

void DebugRendererImpl::DrawTriangle(JPH::RVec3Arg inV1, JPH::RVec3Arg inV2, JPH::RVec3Arg inV3, JPH::ColorArg inColor, ECastShadow inCastShadow)
{

    
}

JPH::DebugRenderer::Batch DebugRendererImpl::CreateTriangleBatch(const Triangle* inTriangles, int inTriangleCount)
{
    return Batch();
}

JPH::DebugRenderer::Batch DebugRendererImpl::CreateTriangleBatch(const Vertex* inVertices, int inVertexCount, const uint32* inIndices, int inIndexCount)
{
    return Batch();
}

void DebugRendererImpl::DrawGeometry(JPH::RMat44Arg     inModelMatrix,
                                     const JPH::AABox&  inWorldSpaceBounds,
                                     float              inLODScaleSq,
                                     JPH::ColorArg      inModelColor,
                                     const GeometryRef& inGeometry,
                                     ECullMode          inCullMode,
                                     ECastShadow        inCastShadow,
                                     EDrawMode          inDrawMode)
{}

void DebugRendererImpl::DrawText3D(JPH::RVec3Arg inPosition, const std::string_view& inString, JPH::ColorArg inColor, float inHeight)
{
    
}
