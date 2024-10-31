#include "render/backend/render_backend.h"
#include "yr/extcore_config.h"
#include <zmq.hpp>

class RenderBackendImpl
{
public:
    RenderBackendImpl()
    {
        int port = gYrExtConfig->rawData.value("render_server_port", 9900);

        zmq::context_t context {-1};
        socket = zmq::socket_t(context, ZMQ_REP);

        socket.bind(std::format("tcp://*:{}", port));

        
    }

    ~RenderBackendImpl()
    {

    }

    void StartServer()
    {

    }

    zmq::socket_t socket;
};

RenderBackend::RenderBackend()
{
    _impl = new RenderBackendImpl();
}

RenderBackend::~RenderBackend()
{
    delete _impl;
}

void RenderBackend::StartServer()
{
    _impl->StartServer();
}

