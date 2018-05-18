#pragma once

#include <protocol.h>

typedef Response (*ServerRequestHandler)(Request * req, void * context);

int Server_run(int port, ServerRequestHandler handler, void * context);