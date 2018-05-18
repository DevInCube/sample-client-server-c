#include <serialization.h>
#include "protocol.h"
#include <assert.h>
#include <jansson.h>
#include <student.h>
#include <string.h>
#include <string_ext.h>

static Student * json_student_value(json_t * jobject) {
    return Student_new(
        json_integer_value(json_object_get(jobject, "id")),
        json_string_value(json_object_get(jobject, "name")),
        json_number_value(json_object_get(jobject, "score"))
    );
}

PbList * Serialization_deserializeStudentsNew(const char * text) {
    json_error_t error;
    json_t * root = json_loads(text, 0, &error);
    if (!root) { return NULL; }
    PbList * list = PbList_new();
    for(int i = 0; i < json_array_size(root); i++) {
        json_t * jobject = json_array_get(root, i);
        PbList_add(list, json_student_value(jobject));
    }
    return list;
}

static json_t * json_student(Student * s) {
    json_t * jobject = json_object();
    json_object_set_new(jobject, "id", json_integer(s->id));
    json_object_set_new(jobject, "name", json_string(s->name));
    json_object_set_new(jobject, "score", json_real(s->score));
    return jobject;
}

char * Serialization_serializeStudentsNew(PbList * list) {
    json_t * jarray = json_array();
    for (int i = 0; i < PbList_count(list); i++) {
        Student * s = PbList_at(list, i);
        json_t * jobject = json_student(s);
        json_array_append_new(jarray, jobject);
    }
    char * jsonStr = json_dumps(jarray, JSON_INDENT(2));
    json_decref(jarray);
    return jsonStr;
}

Request Serialization_deserializeRequest(const char * text) {
    json_error_t error;
    json_t * root = json_loads(text, 0, &error);
    if (!root) { return (Request){0}; }

    Request req = {0};
    req.functionName = json_integer_value(json_object_get(root, "functionName"));
    req.id = json_integer_value(json_object_get(root, "id"));
    Student * s = json_student_value(json_object_get(root, "student"));
    req.student = *s;
    Student_free(s);
    strcpy(req.fileName, json_string_value(json_object_get(root, "fileName")));
    json_decref(root);
    return req;
}

char * Serialization_serializeRequest(Request * request) {
    json_t * jobject = json_object();
    json_object_set_new(jobject, "functionName", json_integer(request->functionName));
    json_object_set_new(jobject, "id", json_integer(request->id));
    json_t * jstudent = json_student(&request->student);
    json_object_set_new(jobject, "student", jstudent);
    json_object_set_new(jobject, "fileName", json_string(request->fileName));
    char * jsonStr = json_dumps(jobject, 0);
    json_decref(jobject);
    return jsonStr;
}

Response Serialization_deserializeResponse(const char * text) {
    json_error_t error;
    json_t * root = json_loads(text, 0, &error);
    if (!root) { return (Response){0}; }

    Response res = {0};
    res.id = json_integer_value(json_object_get(root, "id"));
    res.status = json_integer_value(json_object_get(root, "status"));
    json_t * jfiles = json_object_get(root, "files");
    if (json_is_array(jfiles)) {
        res.files = PbList_new();
        for(int i = 0; i < json_array_size(jfiles); i++) {
            json_t * jitem = json_array_get(jfiles, i);
            char * str = ft_strdup((char *)json_string_value(jitem));
            puts(str);
            PbList_add(res.files, str);
        }
    }
    json_t * jstudents = json_object_get(root, "students");
    if (json_is_array(jstudents)) {
        res.students = PbList_new();
        for(int i = 0; i < json_array_size(jstudents); i++) {
            json_t * jitem = json_array_get(jstudents, i);
            PbList_add(res.students, json_student_value(jitem));
        }
    }
    json_decref(root);
    return res;
}
char * Serialization_serializeResponse(Response * response) {
    json_t * jobject = json_object();
    json_object_set_new(jobject, "status", json_integer(response->status));
    json_object_set_new(jobject, "id", json_integer(response->id));
    json_t * jfiles = json_null();
    if (response->files != NULL) {
        json_decref(jfiles);
        jfiles = json_array();
        for (int i = 0; i < PbList_count(response->files); i++) {
            char * file = PbList_at(response->files, i);
            json_t * jitem = json_string(file);
            json_array_append_new(jfiles, jitem);
        }
    }
    json_object_set_new(jobject, "files", jfiles);
    json_t * jstudents = json_null();
    if (response->students != NULL) {
        json_decref(jstudents);
        jstudents = json_array();
        for (int i = 0; i < PbList_count(response->students); i++) {
            Student * s = PbList_at(response->students, i);
            json_t * jitem = json_student(s);
            json_array_append_new(jstudents, jitem);
        }
    }
    json_object_set_new(jobject, "students", jstudents);
    char * jsonStr = json_dumps(jobject, 0);
    json_decref(jobject);
    return jsonStr;
}