#pragma once

#include <progbase/collections/pblist.h>
#include "protocol.h"

PbList * Serialization_deserializeStudentsNew(const char * text);
char * Serialization_serializeStudentsNew(PbList * list);

Request Serialization_deserializeRequest(const char * text);
char * Serialization_serializeRequest(Request * request);

Response Serialization_deserializeResponse(const char * text);
char * Serialization_serializeResponse(Response * response);