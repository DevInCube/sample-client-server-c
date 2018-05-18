#pragma once

#include <progbase/collections/pblist.h>

PbList * Serialization_deserializeStudentsNew(const char * text);
char * Serialization_serializeStudentsNew(PbList * list);