#include <serialization.h>
#include "protocol.h"
#include <assert.h>
#include <jansson.h>
#include <student.h>

PbList * Serialization_deserializeStudentsNew(const char * text) {
    json_error_t error;
    json_t * root = json_loads(text, 0, &error);
    if (!root) { return NULL; }
    PbList * list = PbList_new();
    for(int i = 0; i < json_array_size(root); i++) {
        json_t * jobject = json_array_get(root, i);
        Student * s = Student_new(
            json_integer_value(json_object_get(jobject, "id")),
            json_string_value(json_object_get(jobject, "name")),
            json_number_value(json_object_get(jobject, "score"))
        );
        PbList_add(list, s);
    }
    return list;
}
char * Serialization_serializeStudentsNew(PbList * list) {
    json_t * jarray = json_array();
    for (int i = 0; i < PbList_count(list); i++) {
        Student * s = PbList_at(list, i);
        json_t * jobject = json_object();
        json_object_set_new(jobject, "id", json_integer(s->id));
        json_object_set_new(jobject, "name", json_string(s->name));
        json_object_set_new(jobject, "score", json_real(s->score));
        json_array_append_new(jarray, jobject);
    }
    char * jsonStr = json_dumps(jarray, JSON_INDENT(2));
    json_decref(jarray);
    return jsonStr;
}

Request Serialization_deserializeRequest(const char * text) {
    Request req;
    // assert(0 && "Not impl");
    return req;
}
char * Serialization_serializeRequest(Request * request) {
    // assert(0 && "Not impl");
    return "";
}

Response Serialization_deserializeResponse(const char * text) {
    Response res;
    // assert(0 && "Not impl");
    return res;
}
char * Serialization_serializeResponse(Response * response) {
    // assert(0 && "Not impl");
    return "";
}