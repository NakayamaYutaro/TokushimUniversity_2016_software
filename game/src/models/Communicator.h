
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Communicator{

 private :
	LinkedList <CustomizedRumba*>;
	RunawayRumba* runaway_runmba;
	pthread_mutex_t receiver_mutex ;
	pthread_mutex_t sender_mutex  ;
	
		
 public : 
	void sendData(vector<char> &data){
	   if(!isInit){
	   cout<<[Send] This object dosen't init<<endl;
	   return 0;
	 }
	
	   int ndata=data.size();
	   char sendBuf[ndata];
	   memcpy(sendBuf,&data[0],ndata);
	
	//送信
	   if(nWrite<=0){//Write失敗
	   cout<<"[Write] WriteFailed:"<<nWrite<<endl;
	   perror("Write");
	 }
	
	 return nWrite;
	}
	
	void receiveData(vector<char> &data){
	  
　　　　    int MAX_READ_BUF=22800;//MAXのバッファサイズ指定
	    char RecBuf=read[MAX_READ_BUF];
        
            //*データの受信*//
            int nRead=read(selfSock_,RecBuf,sizeof(RecBuf));
        
            //*受信データの診断*//
            if(nRead<=0){
            cout<<"[Read] cannot receive packet"<<end1;
            perror("Read");
            data.clear();
          return 0;
         }
        else if(nRead>=MAX_READ_BUF){//MAXバッファをnReadが超えていた場合
            cout<<"[Read] Buffer Overflow:"<<nRead<<end1;
            data.clear();
            return 0;
         }
         
         
            data.resize(nRead);//事前確保
         for(int ir= 0;ir<nRead;ir++){
         　 data[ir]=RecBuf[ir];
         }
         
            return nRead;//受信数を返す
         }
           
	void startCommunication(void){} 
	
	void handShake(){
	　selfSock_=socket(AF_INET,SOCK_STREAM,0);
	  if(selfsock_<0){//失敗の場合
	   cout<<"[CreateSocket] socket failed"<<endl;
	   perror("CreateSocket");
	  return false;
	 }
	 else{//成功の場合
	  cout<<"[CreateSocket] Create Socket"<<endl;
	  return true;
	  
	  }

	}
	　
	 sockaddr_in GetServerInfo(void){
          sockaddr_in server;
          server.sin_family =AF_INET;//TCP
          //ポート番号の指定 htonsはエンディアンの変換
          server.sin_port = htons(port_);
          return server;
	}　
	　
	void lockMutex(){}
	void unlockedMutex(){}
    

    
