#pragma once

#include <protocol.h>

typedef Response (*ServerRequestHandler)(Request * req);

int Server_run(int port, ServerRequestHandler handler);