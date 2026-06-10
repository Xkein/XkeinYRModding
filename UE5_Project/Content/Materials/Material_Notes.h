// UE5 材质说明 - 需在 UE5 编辑器中创建

/*
=== M_SHP_Base (Material) ===
  Blend Mode: Masked 或 Translucent
  Shading Model: Unlit

  参数:
    Texture2D  Spritesheet    - SHP spritesheet 纹理
    Scalar     FrameVOffset   - 当前帧的 V 偏移
    Scalar     FrameVScale    - 当前帧的 V 缩放
    Scalar     Brightness     - 亮度 (0.0~2.0)
    Scalar     Alpha          - 透明度

  节点:
    TexCoord[0] → Mask(G) → Append(0) → 作为 U
    TexCoord[0] → Mask(R) → * FrameVScale → + FrameVOffset → 作为 V
    → TextureSample(Spritesheet, UV)
    → * Brightness → Multiply Alpha → FinalColor

=== M_IsoTile (Material) ===
  Blend Mode: Masked
  Shading Model: Unlit

=== M_Voxel (Material) ===
  Blend Mode: Opaque
  Shading Model: DefaultLit (法线方向决定亮度，模拟原引擎光照)

=== M_FogPostProcess (Material) ===
  Domain: PostProcess
  Blendable Location: Before Tonemapping
  参数:
    Texture2D  FogMap       - 迷雾状态纹理 (R8, 每像素=Cell)
    Scalar     FogAlpha     - 迷雾透明度

  节点:
    SceneTexture(PostProcessInput0) 作为基础
    ScreenPosition → * MapScale → UV 采样 FogMap
    FogMap.R 的值映射：0=全黑(Fogged), 0.5=半透明(Fogged但Revealed), 1=完全可见
    → Lerp(Black, SceneColor, FogMap.R * FogAlpha) → Output
*/