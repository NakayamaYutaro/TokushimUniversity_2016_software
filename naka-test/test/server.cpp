
#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
 
using namespace std;

int main(/*戻り値の必要性*/)
{ 



    int client,server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];


    /* ソケットの生成 */
    client = socket(AF_INET,SOCK_STREAM,0);
    if(client<0)
    {
        cout<< "Error establishing connection." <<endl;
        exit(1);
    }
    cout << "Server Socket connection created..." <<endl;
 
    /* 通信ポート・アドレスの設定 */
    server_addr.sin_family = AF_INET;
    server.addr.sin_addr.s_addr = htons(INADDER_ANY);
    server.addr.sin_port = htons(portNum);
 
    /* ソケットにアドレスを結びつける */
    if(bind(client,(struct sockaddr*)&server_addr,size(server_addr) < 0)
    {
        cout << "Error binding socket..."<< endl;
        exit(1);
    }

        size = sizeof(server_addr);
        cout << "Looking for clients..." << endl;

    /* コネクト要求をいくつまで待つかを設定 */
    if(listen(client, 2) < 0)
    {
        perror("reader: accept");
        exit(1);
    }
 
    /* コネクト要求を待つ */
    server = accept(client, (struct sockaddr*)&server_addr,&size);
    /*ある程度時間が立ったら強制終了する-まだ書いてない*/
 
    if(server < 0)
    {
        cout << "Error on accepting..." << endl;
        exit(1);
    }　　
    return 0;
}
    
    while(server > 0)
    {
        strcpy(buffer,"Server connected...\n");
        send(server, buffer, bufsize,0);

        cout << "Connected with client..." << endl;
        cout << "Enter # to end the connection\n" <<endl;
        cout << "Client: ";

    }

do{
  recv(server,buffer,bufsize,0);
  cout << "buffer" << "";
   if(*buffer == '#')
   {
       *buffer = "*";
        isExit = true;
   }
  }while (*bufer != '*');
    
    do{
    cout << "\nServer:";
        do{　
            cin >> buffer;
            send(server,buer,bufsize,0);　//クライアントに情報を送る
            *buffer = '*';
            isExit = true;
        }while (buffer != "*");
      
          cout << "Client: ";
          
           do{
                recv(server,buffer,bufsize,0);//データを受け取る操作
                cout << buffer << "";
               if(*buffer == '#')
                  {
                  *buffer == "*";
                   isExit = true;
                   }
              } while (buffer != '*');         
        }while(!isExit);
             
          cout << "Connection terminated..."<< endl;
          cout << "Goodbye..." << endl;
          isExit = false;
          exit(1);
   }
   close(client);
 return 0;
}
