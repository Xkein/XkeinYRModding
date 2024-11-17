#pragma once

class RenderBackend
{
public:
    RenderBackend();
    ~RenderBackend();
    void StartServer();

    void Tick();

private:
    class RenderBackendImpl* _impl;
};
