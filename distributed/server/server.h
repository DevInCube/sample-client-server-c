#pragma once

#include <protocol.h>

typedef void (*ServerRequestHandler)(Request * req, Response * res, void * context);

int Server_run(int port, ServerRequestHandler handler, void * context);