#include "ui/rmlui/rmlui.h"

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi/Core/RenderInterfaceCompatibility.h>

#include <Unsorted.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <map>
#include <mutex>
#include "runtime/logger/logger.h"
#include "yr/debug_util.h"
#include "yr/event/windows_event.h"

#pragma comment(lib, "d3dcompiler.lib")

inline HWND GetGameHwnd()
{
    return Game::hWnd;
}

static bool                            gInited = false;
static ID3D11Device*                   gD3DDevice = nullptr;
static ID3D11DeviceContext*            gD3DDeviceContext = nullptr;
static ID3D11RenderTargetView*         gRenderTargetView = nullptr;

static ID3D11VertexShader*             gVertexShader = nullptr;
static ID3D11PixelShader*              gPixelShader = nullptr;
static ID3D11InputLayout*              gInputLayout = nullptr;
static ID3D11Buffer*                   gConstantBuffer = nullptr;
static ID3D11BlendState*               gBlendState = nullptr;
static ID3D11SamplerState*             gSamplerState = nullptr;
static ID3D11RasterizerState*          gRasterizerState = nullptr;
static ID3D11DepthStencilState*        gDepthStencilState = nullptr;

struct RmlTexture
{
    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11Texture2D*          texture = nullptr;
    int                       width = 0;
    int                       height = 0;
};

static std::map<Rml::TextureHandle, RmlTexture> gTextures;
static Rml::TextureHandle                       gNextTextureHandle = 1;

struct RmlCompiledGeometry
{
    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;
    int           numIndices = 0;
    Rml::TextureHandle texture = 0;
};

static std::map<Rml::CompiledGeometryHandle, RmlCompiledGeometry> gGeometries;
static Rml::CompiledGeometryHandle                                gNextGeometryHandle = 1;

struct ConstantBufferData
{
    float projectionMatrix[16];
};

static bool CompileShaders()
{
    const char* vsSource = R"(
cbuffer VS_Constants : register(b0)
{
    float4x4 ProjectionMatrix;
};

struct VS_INPUT
{
    float2 Position : POSITION;
    float4 Color    : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Position = mul(ProjectionMatrix, float4(input.Position, 0.0, 1.0));
    output.Color = input.Color;
    output.TexCoord = input.TexCoord;
    return output;
}
)";

    const char* psSource = R"(
Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(Sampler, input.TexCoord) * input.Color;
}
)";

    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    HRESULT hr = D3DCompile(vsSource, strlen(vsSource), "vs", nullptr, nullptr,
        "main", "vs_4_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &vsBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            gLogger->error("RmlUi VS compile error: {}", (char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        return false;
    }

    hr = D3DCompile(psSource, strlen(psSource), "ps", nullptr, nullptr,
        "main", "ps_4_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &psBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            gLogger->error("RmlUi PS compile error: {}", (char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        vsBlob->Release();
        return false;
    }

    gD3DDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &gVertexShader);
    gD3DDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &gPixelShader);

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, offsetof(Rml::Vertex, position),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, offsetof(Rml::Vertex, colour),    D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, offsetof(Rml::Vertex, tex_coord), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    gD3DDevice->CreateInputLayout(layout, 3, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &gInputLayout);

    vsBlob->Release();
    psBlob->Release();

    D3D11_BUFFER_DESC cbDesc = {};
    cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.ByteWidth = sizeof(ConstantBufferData);
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    gD3DDevice->CreateBuffer(&cbDesc, nullptr, &gConstantBuffer);

    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    gD3DDevice->CreateBlendState(&blendDesc, &gBlendState);

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    gD3DDevice->CreateSamplerState(&sampDesc, &gSamplerState);

    D3D11_RASTERIZER_DESC rasterDesc = {};
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.ScissorEnable = TRUE;
    rasterDesc.DepthClipEnable = TRUE;
    gD3DDevice->CreateRasterizerState(&rasterDesc, &gRasterizerState);

    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = FALSE;
    dsDesc.StencilEnable = FALSE;
    gD3DDevice->CreateDepthStencilState(&dsDesc, &gDepthStencilState);

    return true;
}

static void ReleaseShaders()
{
    if (gVertexShader) { gVertexShader->Release(); gVertexShader = nullptr; }
    if (gPixelShader) { gPixelShader->Release(); gPixelShader = nullptr; }
    if (gInputLayout) { gInputLayout->Release(); gInputLayout = nullptr; }
    if (gConstantBuffer) { gConstantBuffer->Release(); gConstantBuffer = nullptr; }
    if (gBlendState) { gBlendState->Release(); gBlendState = nullptr; }
    if (gSamplerState) { gSamplerState->Release(); gSamplerState = nullptr; }
    if (gRasterizerState) { gRasterizerState->Release(); gRasterizerState = nullptr; }
    if (gDepthStencilState) { gDepthStencilState->Release(); gDepthStencilState = nullptr; }
}

class RmlRenderInterface : public Rml::RenderInterfaceCompatibility
{
public:
    void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices,
        int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation) override
    {
        if (!gD3DDeviceContext || !gRenderTargetView)
            return;

        Rml::CompiledGeometryHandle geoHandle = CompileGeometry(
            vertices, num_vertices, indices, num_indices, texture);
        RenderCompiledGeometry(geoHandle, translation);
        Rml::RenderInterfaceCompatibility::ReleaseCompiledGeometry(geoHandle);
    }

    Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, int num_vertices,
        int* indices, int num_indices, Rml::TextureHandle texture) override
    {
        RmlCompiledGeometry geo;

        {
            D3D11_BUFFER_DESC desc = {};
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.ByteWidth = num_vertices * sizeof(Rml::Vertex);
            desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

            D3D11_SUBRESOURCE_DATA data = {};
            data.pSysMem = vertices;
            gD3DDevice->CreateBuffer(&desc, &data, &geo.vertexBuffer);
        }

        {
            D3D11_BUFFER_DESC desc = {};
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.ByteWidth = num_indices * sizeof(int);
            desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

            D3D11_SUBRESOURCE_DATA data = {};
            data.pSysMem = indices;
            gD3DDevice->CreateBuffer(&desc, &data, &geo.indexBuffer);
        }

        geo.numIndices = num_indices;
        geo.texture = texture;

        Rml::CompiledGeometryHandle handle = gNextGeometryHandle++;
        gGeometries[handle] = geo;
        return handle;
    }

    void RenderCompiledGeometry(Rml::CompiledGeometryHandle handle, const Rml::Vector2f& translation) override
    {
        auto it = gGeometries.find(handle);
        if (it == gGeometries.end() || !gD3DDeviceContext)
            return;

        const auto& geo = it->second;

        Rml::Vector2i viewportSize;
        if (auto* context = Rml::GetContext(0))
        {
            viewportSize = context->GetDimensions();
        }
        else
        {
            RECT rect;
            GetClientRect(GetGameHwnd(), &rect);
            viewportSize.x = rect.right - rect.left;
            viewportSize.y = rect.bottom - rect.top;
        }

        float W = (float)viewportSize.x;
        float H = (float)viewportSize.y;

        float proj[16] = {
            2.0f / W,          0.0f,              0.0f,  0.0f,
            0.0f,             -2.0f / H,          0.0f,  0.0f,
            0.0f,              0.0f,              0.5f,  0.0f,
            (2.0f * translation.x) / W - 1.0f,
            1.0f - (2.0f * translation.y) / H,
            0.5f,              1.0f,
        };

        ConstantBufferData cbData = {};
        memcpy(cbData.projectionMatrix, proj, sizeof(proj));

        D3D11_MAPPED_SUBRESOURCE mapped;
        gD3DDeviceContext->Map(gConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
        memcpy(mapped.pData, &cbData, sizeof(cbData));
        gD3DDeviceContext->Unmap(gConstantBuffer, 0);

        gD3DDeviceContext->IASetInputLayout(gInputLayout);
        gD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        UINT stride = sizeof(Rml::Vertex);
        UINT offset = 0;
        gD3DDeviceContext->IASetVertexBuffers(0, 1, &geo.vertexBuffer, &stride, &offset);
        gD3DDeviceContext->IASetIndexBuffer(geo.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

        gD3DDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
        gD3DDeviceContext->VSSetConstantBuffers(0, 1, &gConstantBuffer);
        gD3DDeviceContext->PSSetShader(gPixelShader, nullptr, 0);

        ID3D11ShaderResourceView* srv = nullptr;
        if (geo.texture != 0)
        {
            auto texIt = gTextures.find(geo.texture);
            if (texIt != gTextures.end())
                srv = texIt->second.srv;
        }
        gD3DDeviceContext->PSSetShaderResources(0, 1, &srv);
        gD3DDeviceContext->PSSetSamplers(0, 1, &gSamplerState);

        gD3DDeviceContext->OMSetBlendState(gBlendState, nullptr, 0xFFFFFFFF);
        gD3DDeviceContext->OMSetDepthStencilState(gDepthStencilState, 0);
        gD3DDeviceContext->RSSetState(gRasterizerState);

        gD3DDeviceContext->DrawIndexed(geo.numIndices, 0, 0);
    }

    void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle handle) override
    {
        auto it = gGeometries.find(handle);
        if (it != gGeometries.end())
        {
            if (it->second.vertexBuffer) it->second.vertexBuffer->Release();
            if (it->second.indexBuffer) it->second.indexBuffer->Release();
            gGeometries.erase(it);
        }
    }

    void EnableScissorRegion(bool enable) override
    {
        if (gD3DDeviceContext)
        {
            gD3DDeviceContext->RSSetScissorRects(0, nullptr);
        }
    }

    void SetScissorRegion(int x, int y, int width, int height) override
    {
        if (gD3DDeviceContext)
        {
            D3D11_RECT rect;
            rect.left = (LONG)x;
            rect.top = (LONG)y;
            rect.right = (LONG)(x + width);
            rect.bottom = (LONG)(y + height);
            gD3DDeviceContext->RSSetScissorRects(1, &rect);
        }
    }

    bool LoadTexture(Rml::TextureHandle& textureHandle, Rml::Vector2i& textureDimensions,
        const Rml::String& source) override
    {
        return false;
    }

    bool GenerateTexture(Rml::TextureHandle& textureHandle, const Rml::byte* source,
        const Rml::Vector2i& sourceDimensions) override
    {
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = (UINT)sourceDimensions.x;
        desc.Height = (UINT)sourceDimensions.y;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = source;
        initData.SysMemPitch = desc.Width * 4;

        RmlTexture tex;
        tex.width = sourceDimensions.x;
        tex.height = sourceDimensions.y;

        HRESULT hr = gD3DDevice->CreateTexture2D(&desc, &initData, &tex.texture);
        if (FAILED(hr))
            return false;

        gD3DDevice->CreateShaderResourceView(tex.texture, nullptr, &tex.srv);

        textureHandle = gNextTextureHandle++;
        gTextures[textureHandle] = tex;
        return true;
    }

    void ReleaseTexture(Rml::TextureHandle textureHandle) override
    {
        auto it = gTextures.find(textureHandle);
        if (it != gTextures.end())
        {
            if (it->second.srv) it->second.srv->Release();
            if (it->second.texture) it->second.texture->Release();
            gTextures.erase(it);
        }
    }

    void SetTransform(const Rml::Matrix4f* transform) override
    {
    }
};

class RmlSystemInterface : public Rml::SystemInterface
{
public:
    double GetElapsedTime() override
    {
        static LARGE_INTEGER frequency = {};
        static LARGE_INTEGER start = {};
        if (!frequency.QuadPart)
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
        }
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (double)(now.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
    }

    bool LogMessage(Rml::Log::Type type, const Rml::String& message) override
    {
        switch (type)
        {
        case Rml::Log::LT_ERROR:
            gLogger->error("[RmlUi] {}", message);
            break;
        case Rml::Log::LT_WARNING:
            gLogger->warn("[RmlUi] {}", message);
            break;
        case Rml::Log::LT_INFO:
            gLogger->info("[RmlUi] {}", message);
            break;
        default:
            gLogger->debug("[RmlUi] {}", message);
            break;
        }
        return true;
    }
};

static std::unique_ptr<RmlRenderInterface> gRenderInterface;
static std::unique_ptr<RmlSystemInterface> gSystemInterface;

std::mutex rmlMtx;

static Rml::Context* RmlWndProc_GetTargetContext()
{
    for (auto& ctx : YrRmlUi::gContexts)
    {
        if (ctx->IsOpened())
            return ctx->GetContext();
    }
    return nullptr;
}

static void RmlWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!gInited)
        return;

    Rml::Context* context = RmlWndProc_GetTargetContext();
    if (!context)
        return;

    int keyModifiers = 0;
    if (GetKeyState(VK_CONTROL) & 0x8000) keyModifiers |= Rml::Input::KM_CTRL;
    if (GetKeyState(VK_SHIFT) & 0x8000)   keyModifiers |= Rml::Input::KM_SHIFT;
    if (GetKeyState(VK_MENU) & 0x8000)    keyModifiers |= Rml::Input::KM_ALT;
    if (GetKeyState(VK_CAPITAL) & 0x0001) keyModifiers |= Rml::Input::KM_CAPSLOCK;
    if (GetKeyState(VK_NUMLOCK) & 0x0001) keyModifiers |= Rml::Input::KM_NUMLOCK;

    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        context->ProcessMouseMove(LOWORD(lParam), HIWORD(lParam), keyModifiers);
        break;
    case WM_LBUTTONDOWN:
        context->ProcessMouseButtonDown(0, keyModifiers);
        break;
    case WM_LBUTTONUP:
        context->ProcessMouseButtonUp(0, keyModifiers);
        break;
    case WM_RBUTTONDOWN:
        context->ProcessMouseButtonDown(1, keyModifiers);
        break;
    case WM_RBUTTONUP:
        context->ProcessMouseButtonUp(1, keyModifiers);
        break;
    case WM_MBUTTONDOWN:
        context->ProcessMouseButtonDown(2, keyModifiers);
        break;
    case WM_MBUTTONUP:
        context->ProcessMouseButtonUp(2, keyModifiers);
        break;
    case WM_MOUSEWHEEL:
        context->ProcessMouseWheel(-(float)(short)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA, keyModifiers);
        break;
    case WM_MOUSELEAVE:
        context->ProcessMouseLeave();
        break;
    case WM_KEYDOWN:
    {
        Rml::Input::KeyIdentifier ki = Rml::Input::KI_UNKNOWN;
        switch (wParam)
        {
        case VK_BACK:   ki = Rml::Input::KI_BACK; break;
        case VK_TAB:    ki = Rml::Input::KI_TAB; break;
        case VK_RETURN: ki = Rml::Input::KI_RETURN; break;
        case VK_ESCAPE: ki = Rml::Input::KI_ESCAPE; break;
        case VK_SPACE:  ki = Rml::Input::KI_SPACE; break;
        case VK_LEFT:   ki = Rml::Input::KI_LEFT; break;
        case VK_RIGHT:  ki = Rml::Input::KI_RIGHT; break;
        case VK_UP:     ki = Rml::Input::KI_UP; break;
        case VK_DOWN:   ki = Rml::Input::KI_DOWN; break;
        case VK_INSERT: ki = Rml::Input::KI_INSERT; break;
        case VK_DELETE: ki = Rml::Input::KI_DELETE; break;
        case VK_HOME:   ki = Rml::Input::KI_HOME; break;
        case VK_END:    ki = Rml::Input::KI_END; break;
        case VK_PRIOR:  ki = Rml::Input::KI_PRIOR; break;
        case VK_NEXT:   ki = Rml::Input::KI_NEXT; break;
        case VK_F1:  ki = Rml::Input::KI_F1; break;
        case VK_F2:  ki = Rml::Input::KI_F2; break;
        case VK_F3:  ki = Rml::Input::KI_F3; break;
        case VK_F4:  ki = Rml::Input::KI_F4; break;
        case VK_F5:  ki = Rml::Input::KI_F5; break;
        case VK_F6:  ki = Rml::Input::KI_F6; break;
        case VK_F7:  ki = Rml::Input::KI_F7; break;
        case VK_F8:  ki = Rml::Input::KI_F8; break;
        case VK_F9:  ki = Rml::Input::KI_F9; break;
        case VK_F10: ki = Rml::Input::KI_F10; break;
        case VK_F11: ki = Rml::Input::KI_F11; break;
        case VK_F12: ki = Rml::Input::KI_F12; break;
        case VK_NUMPAD0: ki = Rml::Input::KI_NUMPAD0; break;
        case VK_NUMPAD1: ki = Rml::Input::KI_NUMPAD1; break;
        case VK_NUMPAD2: ki = Rml::Input::KI_NUMPAD2; break;
        case VK_NUMPAD3: ki = Rml::Input::KI_NUMPAD3; break;
        case VK_NUMPAD4: ki = Rml::Input::KI_NUMPAD4; break;
        case VK_NUMPAD5: ki = Rml::Input::KI_NUMPAD5; break;
        case VK_NUMPAD6: ki = Rml::Input::KI_NUMPAD6; break;
        case VK_NUMPAD7: ki = Rml::Input::KI_NUMPAD7; break;
        case VK_NUMPAD8: ki = Rml::Input::KI_NUMPAD8; break;
        case VK_NUMPAD9: ki = Rml::Input::KI_NUMPAD9; break;
        case VK_MULTIPLY: ki = Rml::Input::KI_MULTIPLY; break;
        case VK_ADD:      ki = Rml::Input::KI_ADD; break;
        case VK_SUBTRACT: ki = Rml::Input::KI_SUBTRACT; break;
        case VK_DECIMAL:  ki = Rml::Input::KI_DECIMAL; break;
        case VK_DIVIDE:   ki = Rml::Input::KI_DIVIDE; break;
        case VK_CAPITAL: ki = Rml::Input::KI_CAPITAL; break;
        default:
            if (wParam >= 'A' && wParam <= 'Z')
                ki = (Rml::Input::KeyIdentifier)(Rml::Input::KI_A + (wParam - 'A'));
            else if (wParam >= '0' && wParam <= '9')
                ki = (Rml::Input::KeyIdentifier)(Rml::Input::KI_0 + (wParam - '0'));
            break;
        }
        if (ki != Rml::Input::KI_UNKNOWN)
            context->ProcessKeyDown(ki, keyModifiers);
        break;
    }
    case WM_KEYUP:
    {
        Rml::Input::KeyIdentifier ki = Rml::Input::KI_UNKNOWN;
        switch (wParam)
        {
        case VK_BACK:   ki = Rml::Input::KI_BACK; break;
        case VK_TAB:    ki = Rml::Input::KI_TAB; break;
        case VK_RETURN: ki = Rml::Input::KI_RETURN; break;
        case VK_ESCAPE: ki = Rml::Input::KI_ESCAPE; break;
        case VK_SPACE:  ki = Rml::Input::KI_SPACE; break;
        case VK_LEFT:   ki = Rml::Input::KI_LEFT; break;
        case VK_RIGHT:  ki = Rml::Input::KI_RIGHT; break;
        case VK_UP:     ki = Rml::Input::KI_UP; break;
        case VK_DOWN:   ki = Rml::Input::KI_DOWN; break;
        case VK_INSERT: ki = Rml::Input::KI_INSERT; break;
        case VK_DELETE: ki = Rml::Input::KI_DELETE; break;
        case VK_HOME:   ki = Rml::Input::KI_HOME; break;
        case VK_END:    ki = Rml::Input::KI_END; break;
        case VK_PRIOR:  ki = Rml::Input::KI_PRIOR; break;
        case VK_NEXT:   ki = Rml::Input::KI_NEXT; break;
        case VK_F1:  ki = Rml::Input::KI_F1; break;
        case VK_F2:  ki = Rml::Input::KI_F2; break;
        case VK_F3:  ki = Rml::Input::KI_F3; break;
        case VK_F4:  ki = Rml::Input::KI_F4; break;
        case VK_F5:  ki = Rml::Input::KI_F5; break;
        case VK_F6:  ki = Rml::Input::KI_F6; break;
        case VK_F7:  ki = Rml::Input::KI_F7; break;
        case VK_F8:  ki = Rml::Input::KI_F8; break;
        case VK_F9:  ki = Rml::Input::KI_F9; break;
        case VK_F10: ki = Rml::Input::KI_F10; break;
        case VK_F11: ki = Rml::Input::KI_F11; break;
        case VK_F12: ki = Rml::Input::KI_F12; break;
        case VK_NUMPAD0: ki = Rml::Input::KI_NUMPAD0; break;
        case VK_NUMPAD1: ki = Rml::Input::KI_NUMPAD1; break;
        case VK_NUMPAD2: ki = Rml::Input::KI_NUMPAD2; break;
        case VK_NUMPAD3: ki = Rml::Input::KI_NUMPAD3; break;
        case VK_NUMPAD4: ki = Rml::Input::KI_NUMPAD4; break;
        case VK_NUMPAD5: ki = Rml::Input::KI_NUMPAD5; break;
        case VK_NUMPAD6: ki = Rml::Input::KI_NUMPAD6; break;
        case VK_NUMPAD7: ki = Rml::Input::KI_NUMPAD7; break;
        case VK_NUMPAD8: ki = Rml::Input::KI_NUMPAD8; break;
        case VK_NUMPAD9: ki = Rml::Input::KI_NUMPAD9; break;
        case VK_MULTIPLY: ki = Rml::Input::KI_MULTIPLY; break;
        case VK_ADD:      ki = Rml::Input::KI_ADD; break;
        case VK_SUBTRACT: ki = Rml::Input::KI_SUBTRACT; break;
        case VK_DECIMAL:  ki = Rml::Input::KI_DECIMAL; break;
        case VK_DIVIDE:   ki = Rml::Input::KI_DIVIDE; break;
        case VK_CAPITAL: ki = Rml::Input::KI_CAPITAL; break;
        }
        if (ki != Rml::Input::KI_UNKNOWN)
            context->ProcessKeyUp(ki, keyModifiers);
        break;
    }
    case WM_CHAR:
        if (wParam > 0 && wParam < 0x10000)
            context->ProcessTextInput((Rml::Character)wParam);
        break;
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrMainWndProcEvent)
{
    RmlWndProc(E->hWnd, E->uMsg, E->wParam, E->lParam);
}

void YrRmlUi::Init()
{
    if (gInited)
        return;

    HWND hWnd = GetGameHwnd();
    if (!hWnd)
        return;

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGISwapChain* swapChain = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        featureLevels, 1, D3D11_SDK_VERSION, &sd, &swapChain, &gD3DDevice, &featureLevel, &gD3DDeviceContext)))
    {
        gLogger->error("RmlUi: Failed to create D3D11 device and swap chain");
        return;
    }

    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (backBuffer)
    {
        gD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &gRenderTargetView);
        backBuffer->Release();
    }
    swapChain->Release();

    if (!CompileShaders())
    {
        gLogger->error("RmlUi: Failed to compile shaders");
        return;
    }

    gSystemInterface = std::make_unique<RmlSystemInterface>();
    gRenderInterface = std::make_unique<RmlRenderInterface>();

    Rml::SetSystemInterface(gSystemInterface.get());
    Rml::SetRenderInterface(gRenderInterface->GetAdaptedInterface());
    Rml::Initialise();

    gInited = true;
    gLogger->info("RmlUi initialized");
}

void YrRmlUi::Destory()
{
    if (!gInited)
        return;
    gInited = false;

    for (auto& ctx : gContexts)
    {
        ctx->Close();
    }

    Rml::Shutdown();

    gRenderInterface.reset();
    gSystemInterface.reset();

    for (auto& [handle, geo] : gGeometries)
    {
        if (geo.vertexBuffer) geo.vertexBuffer->Release();
        if (geo.indexBuffer) geo.indexBuffer->Release();
    }
    gGeometries.clear();

    for (auto& [handle, tex] : gTextures)
    {
        if (tex.srv) tex.srv->Release();
        if (tex.texture) tex.texture->Release();
    }
    gTextures.clear();

    ReleaseShaders();

    if (gRenderTargetView) { gRenderTargetView->Release(); gRenderTargetView = nullptr; }
    if (gD3DDeviceContext) { gD3DDeviceContext->Release(); gD3DDeviceContext = nullptr; }
    if (gD3DDevice) { gD3DDevice->Release(); gD3DDevice = nullptr; }
}

void YrRmlUi::Render()
{
    if (!gInited)
        return;

    for (auto& ctx : gContexts)
    {
        GuardExecute([=]() {
            ctx->NewFrame();
        }, [](std::string stackTrace) {
            gLogger->error("RmlUi render error!");
            gLogger->error("stack trace : {}", stackTrace);
        });
    }
}

XKEINEXT_API std::vector<YrRmlContext*> YrRmlUi::gContexts;
static int                               gOpenedContextCount = 0;

class YrRmlContext_Impl
{
public:
    YrRmlContext_Impl(YrRmlContext* ctx, const char* name, int width, int height)
        : context(ctx)
        , name(name)
        , width(width)
        , height(height)
    {
        YrRmlUi::gContexts.push_back(ctx);
    }

    ~YrRmlContext_Impl()
    {
        Close();
        if (auto iter = std::find(YrRmlUi::gContexts.begin(), YrRmlUi::gContexts.end(), context);
            iter != YrRmlUi::gContexts.end())
        {
            YrRmlUi::gContexts.erase(iter);
        }
    }

    void NewFrame()
    {
        if (!opened || !rmlContext)
            return;

        context->OnFrame();

        rmlContext->Update();

        if (gD3DDeviceContext && gRenderTargetView)
        {
            const float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            gD3DDeviceContext->ClearRenderTargetView(gRenderTargetView, clearColor);
            gD3DDeviceContext->OMSetRenderTargets(1, &gRenderTargetView, nullptr);

            D3D11_VIEWPORT viewport = {};
            viewport.Width = (float)rmlContext->GetDimensions().x;
            viewport.Height = (float)rmlContext->GetDimensions().y;
            viewport.MinDepth = 0.0f;
            viewport.MaxDepth = 1.0f;
            gD3DDeviceContext->RSSetViewports(1, &viewport);
        }

        rmlContext->Render();

        if (gD3DDeviceContext)
        {
            ID3D11RenderTargetView* nullRTV = nullptr;
            gD3DDeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
        }
    }

    void Open()
    {
        if (opened)
            return;

        rmlContext = Rml::CreateContext(name, Rml::Vector2i(width, height));
        if (!rmlContext)
        {
            gLogger->error("RmlUi: Failed to create context '{}'", name);
            return;
        }

        gOpenedContextCount++;
        opened = true;
        context->OnOpen();
    }

    void Close()
    {
        if (!opened)
            return;

        gOpenedContextCount--;
        opened = false;
        context->OnClose();

        if (rmlContext)
        {
            rmlContext->UnloadAllDocuments();
            Rml::RemoveContext(name);
            rmlContext = nullptr;
        }
    }

    void SetDimensions(int w, int h)
    {
        width = w;
        height = h;
        if (rmlContext)
            rmlContext->SetDimensions(Rml::Vector2i(w, h));
    }

    YrRmlContext* context = nullptr;
    Rml::Context* rmlContext = nullptr;
    std::string name;
    int width = 0;
    int height = 0;
    bool opened = false;
};

int YrRmlUi::GetOpenedWinCount()
{
    return gOpenedContextCount;
}

YrRmlContext::YrRmlContext(const char* name, int width, int height)
{
    std::lock_guard lock(rmlMtx);
    _impl = std::make_unique<YrRmlContext_Impl>(this, name, width, height);
}

YrRmlContext::~YrRmlContext()
{
    std::lock_guard lock(rmlMtx);
    _impl.reset();
}

void YrRmlContext::NewFrame()
{
    _impl->NewFrame();
}

void YrRmlContext::Open()
{
    _impl->Open();
}

void YrRmlContext::Close()
{
    _impl->Close();
}

bool YrRmlContext::IsOpened() const
{
    return _impl->opened;
}

Rml::Context* YrRmlContext::GetContext() const
{
    return _impl->rmlContext;
}

void YrRmlContext::SetDimensions(int width, int height)
{
    _impl->SetDimensions(width, height);
}

void YrRmlContext::Update()
{
    if (_impl->rmlContext)
        _impl->rmlContext->Update();
}

void YrRmlContext::Render()
{
    if (_impl->rmlContext)
        _impl->rmlContext->Render();
}