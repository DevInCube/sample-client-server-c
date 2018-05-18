#include "server.h"
#include <stdio.h>
#include <progbase/net.h>
#include "../common/serialization.h"

int Server_run(int port, ServerRequestHandler handler, void * context) {

    // init and start server 
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

    // init io buffer message
    NetMessage message;
    enum { BUFFER_LEN = 2048 };
    char buffer[BUFFER_LEN] = "";
    NetMessage_init(&message, buffer, BUFFER_LEN);

    bool isRunning = true;
    while (isRunning) {
        const char * in = NULL;
        char * out = NULL;

        // accept connection
        printf("[Server]> Waiting for connections...");
        fflush(stdout);
        TcpClient * client = TcpListener_accept(&server, &(TcpClient){});
        if (client == NULL) {
            fprintf(stderr, "accept error");
            goto closeClient;
        }
        puts("[Server]> New client accepted");
        if (!TcpClient_receive(client, &message)) {
            fprintf(stderr, "receive message error");
            goto closeClient;
        }

        // receive request
        in = NetMessage_data(&message);
        printf("[Server]> got request string:\n%s\n", in);
        Request req = Serialization_deserializeRequest(in);
        printf("[Server]> get request for function '%s'\n", FunctionName_toString(req.functionName));

        // handle request and create response
        Response res = {0};
        handler(&req, &res, context);

        // send response
        out = Serialization_serializeResponse(&res);
        Response_clear(&res);
        NetMessage_setDataString(&message, out);
        if (!TcpClient_send(client, &message)) {
            fprintf(stderr, "receive message error");
            goto closeClient;
        }
        printf("[Server]> sent response string:\n%s\n", out);

        // cleanup connection and memory
        closeClient:
        if (out != NULL) { free(out); }
        TcpClient_close(client);
        puts("[Server]> connection closed.");
    }
    TcpListener_close(&server);
    return 0;
}
