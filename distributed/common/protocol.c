#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include "serialization.h"
#include <progbase/net.h>

char * FunctionName_toString(FunctionName fn) {
    switch (fn) {
        case FN_GET_FILES: return "GetFiles";
        case FN_NEW_LIST: return "NewList";
        case FN_LOAD_LIST: return "LoadList";
        case FN_SAVE_LIST: return "SaveList";
        case FN_GET_STUDENTS: return "GetStudents";
        case FN_INSERT_STUDENT: return "InsertStudent";
        case FN_UPDATE_STUDENT: return "UpdateStudent";
        case FN_DELETE_STUDENT: return "DeleteStudent";
        default: return "<error>";
    }
    return "";
}

int Protocol_sendRequest(Request * req, Response * res) {
    TcpClient client;
    TcpClient_init(&client);
    if (!TcpClient_connect(&client, IpAddress_init(&(IpAddress){}, "127.0.0.1", 3030))) {
        fprintf(stderr, "[Client]> Can't connect to server\n");
        return 1;
    }
    printf("[Client]> Connected to server\n");
    fflush(stdout);

    char buffer[2048] = "";
    NetMessage message;
    NetMessage_init(&message, buffer, 2048);

    const char * out = Serialization_serializeRequest(req);
    // @todo check out
    NetMessage_setDataString(&message, out);
    free((void *)out);

    if (!TcpClient_send(&client, &message)) {
        fprintf(stderr, "[Client]> Can't send request\n");
        return 1;
    }

    printf("[Client]> Request sent.\n");

    if (!TcpClient_receive(&client, &message)) {
        fprintf(stderr, "[Client]> Can't receive response\n");
        return 1;
    }

    printf("[Client]> Got response\n");

    *res = Serialization_deserializeResponse(NetMessage_data(&message));
    TcpClient_close(&client);
    return 0;
}

void Response_clear(Response * res) {
    if (res->files != NULL) {
        // @todo
    }
    if (res->students != NULL) {
        // @todo
    }
}