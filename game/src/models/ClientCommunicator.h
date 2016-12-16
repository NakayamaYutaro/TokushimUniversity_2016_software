#ifndef ClientCommunicator_H
#define ClientCommunicator_H

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>

class ClientCommunicator {
	private:
        string server_ip_addr;
        int client_id;
	public:
        bool connect2Server();
}

ClientCommunicator::bool connect2Server(){
        connect(csock, (struct sockaddr *)&server, sizeof(server));
}


#endif
