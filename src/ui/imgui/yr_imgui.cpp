#include "yr_imgui.h"
#include "renderer.h"

#include <Unsorted.h>
#include <imgui_impl_win32.h>
# include <d3d11.h>
#include <vector>
#include <map>
#include <imgui_impl_dx11.h>
#include "core/logger/logger.h"
#include "yr/debug_util.h"
#include <CommCtrl.h>
#include "yr/event/windows_event.h"

HWND GetGameHwnd() {
    return Game::hWnd;
}

bool                      inited = false;
ImGuiContext* g_Context = nullptr;
std::unique_ptr<Renderer> m_Renderer;
bool                      m_WindowScaleChanged = false;
float                     m_WindowScale = 1.0f;
bool                      m_FramebufferScaleChanged = false;
float                     m_FramebufferScale = 1.0f;
bool                      m_IsMinimized = false;
bool                      m_WasMinimized = false;
bool                      m_CanCloseResult = false;

ImGuiWindowFlags g_WindowFlags =
ImGuiWindowFlags_NoTitleBar |
ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_NoMove |
ImGuiWindowFlags_NoScrollbar |
ImGuiWindowFlags_NoScrollWithMouse |
ImGuiWindowFlags_NoSavedSettings |
ImGuiWindowFlags_NoBringToFrontOnFocus;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!inited)
    {
        return;
    }

    switch (uMsg)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            break;
        case WM_MOUSEMOVE:
        case WM_NCMOUSEMOVE:
        case WM_MOUSELEAVE:
        case WM_NCMOUSELEAVE:
        default:
            ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
            break;
    }

    switch (uMsg)
    {
        case WM_CLOSE:
            ImGui_ImplWin32_Shutdown();
            break;
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
            {
                m_IsMinimized  = true;
                m_WasMinimized = true;
            }
            else if (wParam == SIZE_RESTORED && m_IsMinimized)
            {
                m_IsMinimized = false;
            }

            if (m_Renderer != nullptr && wParam != SIZE_MINIMIZED)
            {
                m_Renderer->Resize(static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)));
            }
            break;
        case WM_DPICHANGED:
            YrImGui::SetDpiScale(ImGui_ImplWin32_GetDpiScaleForHwnd(hWnd));
            break;
    }
}


REGISTER_YR_HOOK_EVENT_LISTENER(YrMainWndProcEvent, [](YrHookContext* const C, YrMainWndProcEvent* const E) {
    WndProc(E->hWnd, E->uMsg, E->wParam, E->lParam);
});

void YrImGui::Init()
{
    if (inited)
        return;
    HWND hWnd = GetGameHwnd();

    ImGui_ImplWin32_EnableDpiAwareness();
    g_Context = ImGui::CreateContext();
    ImGui::SetCurrentContext(g_Context);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable;
    io.ConfigViewportsNoAutoMerge = true;

    if (!ImGui_ImplWin32_Init(hWnd))
    {
        return;
    }

    SetDpiScale(ImGui_ImplWin32_GetDpiScaleForHwnd(hWnd));

    m_Renderer = CreateRenderer();
    m_Renderer->Create(hWnd);

    ImGui::StyleColorsDark();

    YrImGui::Render();

    inited = true;
}

void YrImGui::Destory()
{
    if (!inited)
        return;
    inited = false;

    HWND hWnd = GetGameHwnd();

    if (m_Renderer)
    {
        m_Renderer->Destroy();
        m_Renderer = nullptr;
    }

    ImGui_ImplWin32_Shutdown();

    if (g_Context)
    {
        ImGui::DestroyContext(g_Context);
        g_Context = nullptr;
    }
}

void YrImGui::Render()
{
    auto& io = ImGui::GetIO();

    if (m_WindowScaleChanged)
    {
        m_WindowScaleChanged = false;
    }

    if (m_FramebufferScaleChanged)
    {
        m_FramebufferScaleChanged = false;
    }

    const float windowScale      = m_WindowScale;
    const float framebufferScale = m_FramebufferScale;

    if (io.WantSetMousePos)
    {
        io.MousePos.x *= windowScale;
        io.MousePos.y *= windowScale;
    }

    ImGui_ImplWin32_NewFrame();

    if (m_WasMinimized)
    {
        ImGui::GetIO().DeltaTime = 0.1e-6f;
        m_WasMinimized           = false;
    }

    // Don't touch "uninitialized" mouse position
    if (io.MousePos.x > -FLT_MAX && io.MousePos.y > -FLT_MAX)
    {
        io.MousePos.x /= windowScale;
        io.MousePos.y /= windowScale;
    }
    io.DisplaySize.x /= windowScale;
    io.DisplaySize.y /= windowScale;

    io.DisplayFramebufferScale.x = framebufferScale;
    io.DisplayFramebufferScale.y = framebufferScale;

    m_Renderer->NewFrame();

    ImGui::NewFrame();

    for (auto& window : gWindows)
    {
        window->NewFrame();
    }

    //m_Renderer->Clear(ImColor(0, 0, 0, 0));
    ImGui::Render();
    //m_Renderer->RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    //m_Renderer->Present();
}

void SetWindowScale(float windowScale)
{
    if (windowScale == m_WindowScale)
        return;
    m_WindowScale        = windowScale;
    m_WindowScaleChanged = true;
}

void SetFramebufferScale(float framebufferScale)
{
    if (framebufferScale == m_FramebufferScale)
        return;
    m_FramebufferScale        = framebufferScale;
    m_FramebufferScaleChanged = true;
}

void YrImGui::SetDpiScale(float dpiScale)
{
    SetWindowScale(dpiScale);
    SetFramebufferScale(dpiScale);
}


ImTextureID YrImGui::LoadTexture(const char* path)
{
    return m_Renderer->LoadTexture(path);
}

ImTextureID YrImGui::CreateTexture(const void* data, int width, int height)
{
    return m_Renderer->CreateTexture(data, width, height);
}

void YrImGui::DestroyTexture(ImTextureID texture)
{
    return m_Renderer->DestroyTexture(texture);
}

int YrImGui::GetTextureWidth(ImTextureID texture)
{
    return m_Renderer->GetTextureWidth(texture);
}

int YrImGui::GetTextureHeight(ImTextureID texture)
{
    return m_Renderer->GetTextureHeight(texture);
}

YREXTUI_API std::vector<YrImGuiWindow*> YrImGui::gWindows;

YrImGuiWindow::YrImGuiWindow()
{
    YrImGui::gWindows.push_back(this);
}

YrImGuiWindow::~YrImGuiWindow() {
    if (_started)
    {
        this->OnStop();
    }
    if (auto iter = std::find(YrImGui::gWindows.begin(), YrImGui::gWindows.end(), this); iter != YrImGui::gWindows.end())
    {
        YrImGui::gWindows.erase(iter);
    }
}

void YrImGuiWindow::NewFrame() {
    if (!_started)
    {
        this->OnStart();
    }
    this->OnFrame();
}