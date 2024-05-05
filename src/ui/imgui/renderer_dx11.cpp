# include "renderer.h"
# include "setup.h"

# if RENDERER(IMGUI_DX11)

# if PLATFORM(WINDOWS)
#     define NOMINMAX
#     define WIN32_LEAN_AND_MEAN
#     include <windows.h>
# endif

# include <imgui.h>
# include "imgui_impl_dx11.h"
# include <d3d11.h>

#include <vector>
#include <map>


static ID3D11Device* g_pd3dDevice = NULL;

struct TEXTURE
{
    TEXTURE()
    {
        View   = NULL;
        Width  = 0;
        Height = 0;
    }

    ID3D11ShaderResourceView* View;
    int                       Width;
    int                       Height;
    ImVector<unsigned char>   Data;
};
static std::map<ImTextureID, TEXTURE*> g_Textures;

ImTextureID ImGui_CreateTexture(const void* data, int width, int height);
bool ImGui_UploadTexture(TEXTURE* texture);
void ImGui_ReleaseTexture(TEXTURE* texture);

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"
}

ImTextureID ImGui_LoadTexture(const char* path)
{
    int width = 0, height = 0, component = 0;
    if (auto data = stbi_load(path, &width, &height, &component, 4))
    {
        auto texture = ImGui_CreateTexture(data, width, height);
        stbi_image_free(data);
        return texture;
    }
    else
        return nullptr;
}

ImTextureID ImGui_CreateTexture(const void* data, int width, int height)
{
    auto texture    = IM_NEW(TEXTURE);
    texture->Width  = width;
    texture->Height = height;
    texture->Data.resize(width * height * 4);
    memcpy(texture->Data.Data, data, texture->Data.Size);

    if (!ImGui_UploadTexture(texture))
    {
        IM_DELETE(texture);
        return nullptr;
    }

    g_Textures[texture->View] = texture;

    return (ImTextureID)texture->View;
}

void ImGui_DestroyTexture(ImTextureID texture)
{
    if (!texture)
        return;

    if (auto iter = g_Textures.find(texture); iter != g_Textures.end())
    {
        TEXTURE* texture_object = iter->second;

        ImGui_ReleaseTexture(texture_object);

        g_Textures.erase(iter);

        IM_DELETE(texture_object);
    }
}

bool ImGui_UploadTexture(TEXTURE* texture)
{
    if (!g_pd3dDevice || !texture)
        return false;

    if (texture->View)
        return true;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width                = texture->Width;
    desc.Height               = texture->Height;
    desc.MipLevels            = 1;
    desc.ArraySize            = 1;
    desc.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count     = 1;
    desc.Usage                = D3D11_USAGE_DEFAULT;
    desc.BindFlags            = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags       = 0;

    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem                = texture->Data.Data;
    subResource.SysMemPitch            = desc.Width * 4;
    subResource.SysMemSlicePitch       = 0;

    ID3D11Texture2D* pTexture = nullptr;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    if (!pTexture)
        return false;

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format                          = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension                   = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels             = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip       = 0;

    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &texture->View);
    pTexture->Release();

    return true;
}

void ImGui_ReleaseTexture(TEXTURE* texture)
{
    if (texture)
    {
        if (texture->View)
        {
            texture->View->Release();
            texture->View = nullptr;
        }
    }
}

int ImGui_GetTextureWidth(ImTextureID texture)
{
    if (auto iter = g_Textures.find(texture); iter != g_Textures.end())
    {
        TEXTURE* texture_object = iter->second;
        return texture_object->Width;
    }

    return 0;
}

int ImGui_GetTextureHeight(ImTextureID texture)
{
    if (auto iter = g_Textures.find(texture); iter != g_Textures.end())
    {
        TEXTURE* texture_object = iter->second;
        return texture_object->Height;
    }

    return 0;
}

struct RendererDX11 final
    : Renderer
{
    bool Create(HWND hWnd) override;
    void Destroy() override;
    void NewFrame() override;
    void RenderDrawData(ImDrawData* drawData) override;
    void Clear(const ImVec4& color) override;
    void Present() override;
    void Resize(int width, int height) override;

    virtual ImTextureID LoadTexture(const char* path) override;
    ImTextureID CreateTexture(const void* data, int width, int height) override;
    void        DestroyTexture(ImTextureID texture) override;
    int         GetTextureWidth(ImTextureID texture) override;
    int         GetTextureHeight(ImTextureID texture) override;

    HRESULT CreateDeviceD3D(HWND hWnd);
    void CleanupDeviceD3D();

    void CreateRenderTarget();
    void CleanupRenderTarget();

    Platform*               m_Platform = nullptr;
    ID3D11Device*           m_device = nullptr;
    ID3D11DeviceContext*    m_deviceContext = nullptr;
    IDXGISwapChain*         m_swapChain = nullptr;
    ID3D11RenderTargetView* m_mainRenderTargetView = nullptr;
};

std::unique_ptr<Renderer> CreateRenderer()
{
    return std::make_unique<RendererDX11>();
}

bool RendererDX11::Create(HWND hWnd)
{
    auto hr = CreateDeviceD3D(hWnd);
    if (FAILED(hr))
        return false;

    if (!ImGui_ImplDX11_Init(m_device, m_deviceContext))
    {
        CleanupDeviceD3D();
        return false;
    }

    g_pd3dDevice = m_device;

    return true;
}

void RendererDX11::Destroy()
{
    if (!m_Platform)
        return;

    ImGui_ImplDX11_Shutdown();

    CleanupDeviceD3D();
}

void RendererDX11::NewFrame()
{
    ImGui_ImplDX11_NewFrame();
}

void RendererDX11::RenderDrawData(ImDrawData* drawData)
{
    ImGui_ImplDX11_RenderDrawData(drawData);
}

void RendererDX11::Clear(const ImVec4& color)
{
    m_deviceContext->ClearRenderTargetView(m_mainRenderTargetView, (float*)&color.x);
}

void RendererDX11::Present()
{
    m_swapChain->Present(1, 0);
}

void RendererDX11::Resize(int width, int height)
{
    ImGui_ImplDX11_InvalidateDeviceObjects();
    CleanupRenderTarget();
    m_swapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}

HRESULT RendererDX11::CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[1] = { D3D_FEATURE_LEVEL_11_0, };
    if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 1, D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, &featureLevel, &m_deviceContext) != S_OK)
        return E_FAIL;

    CreateRenderTarget();

    return S_OK;
}

void RendererDX11::CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (m_swapChain) { m_swapChain->Release(); m_swapChain = nullptr; }
    if (m_deviceContext) { m_deviceContext->Release(); m_deviceContext = nullptr; }
    if (m_device) { m_device->Release(); m_device = nullptr; }
}

void RendererDX11::CreateRenderTarget()
{
    DXGI_SWAP_CHAIN_DESC sd;
    m_swapChain->GetDesc(&sd);

    // Create the render target
    ID3D11Texture2D* pBackBuffer;
    D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
    ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
    render_target_view_desc.Format = sd.BufferDesc.Format;
    render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    m_device->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &m_mainRenderTargetView);
    m_deviceContext->OMSetRenderTargets(1, &m_mainRenderTargetView, nullptr);
    pBackBuffer->Release();
}

void RendererDX11::CleanupRenderTarget()
{
    if (m_mainRenderTargetView) { m_mainRenderTargetView->Release(); m_mainRenderTargetView = nullptr; }
}

ImTextureID RendererDX11::LoadTexture(const char* path)
{
    return ImGui_LoadTexture(path);
}

ImTextureID RendererDX11::CreateTexture(const void* data, int width, int height)
{
    return ImGui_CreateTexture(data, width, height);
}

void RendererDX11::DestroyTexture(ImTextureID texture)
{
    return ImGui_DestroyTexture(texture);
}

int RendererDX11::GetTextureWidth(ImTextureID texture)
{
    return ImGui_GetTextureWidth(texture);
}

int RendererDX11::GetTextureHeight(ImTextureID texture)
{
    return ImGui_GetTextureHeight(texture);
}

# endif // RENDERER(IMGUI_DX11)