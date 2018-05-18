#include "client.h"
#include <stdio.h>
#include "../common/serialization.h"
#include <progbase/net.h>


int Client_sendRequest(Request * req, Response * res) {
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
    const char * in = NetMessage_data(&message);
    printf("[Client]> Got response\n%s\n", in);

    *res = Serialization_deserializeResponse(in);
    TcpClient_close(&client);
    return 0;
}