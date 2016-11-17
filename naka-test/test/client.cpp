
#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

 
int main(){
  int client,server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1"　//ここの値は変動する?//そもそも指定する必要がないのか　
    
    struct sockaddr_in server_addr;
    //init socket
    
    client = socket(AF_INIT, SOCK_STREAM,0);
    
    if(client < 0)
    {
        cout << "Error createing socket..." << endl;
        exit(1);
    }
    
    cout << "Client Socket created" << endl;
    
    server_addr.sin_family = AF_INIT;
    server_addr.sin_port = htons(portNum);
    
    
    if(connect(client,(struct sockaddr*)&server_addr, sizeof(server_addr))==1){
    
    cout << "Connecting to server..." << endl;
    }
    
    recv(client, bufsize, bufsize, 0);
    
    cout << "Connecting confirmed" << endl;
    cout << "Enter # to end the connection" << endl;

    
    do{
        cout << "Client: *;
        do{
            cin >> buffer;
            send(client,buffer,bufsize,0);
            if(*buffer == '#')
             {
             send(client, bufer,bufsize,0);
             *buffer = '*';
             isExit = true;
             }
       } while(*buffer != 42);
            cout << endl;
     }
     
     cout << "Connection terminated" << endl;
     cout << "Goodbye" <<endl;
     
     close(client);
     return 0;

}

      

