#pragma once

class RenderBackend
{
public:
    RenderBackend();
    ~RenderBackend();
    void StartServer();

private:
    class RenderBackendImpl* _impl;
};
