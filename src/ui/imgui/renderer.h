# pragma once
# include "setup.h"
# include <memory>
#include <Windows.h>

struct Platform;
struct ImDrawData;
struct ImVec4;

struct Renderer
{
    virtual ~Renderer() {};

    virtual bool Create(HWND hWnd) = 0;
    virtual void Destroy() = 0;

    virtual void NewFrame() = 0;

    virtual void RenderDrawData(ImDrawData* drawData) = 0;

    virtual void Clear(const ImVec4& color) = 0;
    virtual void Present() = 0;

    virtual void Resize(int width, int height) = 0;

    virtual ImTextureID LoadTexture(const char* path)                          = 0;
    virtual ImTextureID CreateTexture(const void* data, int width, int height) = 0;
    virtual void        DestroyTexture(ImTextureID texture) = 0;
    virtual int         GetTextureWidth(ImTextureID texture) = 0;
    virtual int         GetTextureHeight(ImTextureID texture) = 0;
};

std::unique_ptr<Renderer> CreateRenderer();
