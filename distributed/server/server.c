#include "server.h"
#include <stdio.h>
#include <progbase/net.h>
#include <serialization.h>

int Server_run(int port, ServerRequestHandler handler) {
    TcpListener server;
    TcpListener_init(&server);
    if (!TcpListener_bind(&server, IpAddress_initAny(&(IpAddress){}, port))) {
        fprintf(stderr, "cant bind server");
        return 1;
    }
    if (!TcpListener_start(&server)) {
        fprintf(stderr, "cant start server");
        return 1;
    }

    NetMessage message;
    enum { BUFFER_LEN = 2048 };
    char buffer[BUFFER_LEN] = "";
    NetMessage_init(&message, buffer, BUFFER_LEN);

    bool isRunning = true;
    while (isRunning) {
        printf("[Server]> Waiting for connections...");
        fflush(stdout);
        TcpClient * client = TcpListener_accept(&server, &(TcpClient){});
        if (client == NULL) {
            fprintf(stderr, "accept error");
            continue;
        }
        puts("[Server]> New client accepted");
        if (!TcpClient_receive(client, &message)) {
            fprintf(stderr, "receive message error");
            continue;
        }
        const char * in = NetMessage_data(&message);
        printf("[Server]> got request string:\n%s\n", in);
        Request req = Serialization_deserializeRequest(in);
        Response res = handler(&req);
        char * out = Serialization_serializeResponse(&res);
        NetMessage_setDataString(&message, out);
        if (!TcpClient_send(client, &message)) {
            fprintf(stderr, "receive message error");
            continue;
        }
        printf("[Server]> sent response string:\n%s\n", out);
        TcpClient_close(client);
        puts("[Server]> connection closed.");
    }
    return 0;
}
