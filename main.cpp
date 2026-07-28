#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <cerrno>
#include <cstring>

using namespace std;

int main(){

    // server socket created

    int listenSocket=socket(AF_INET,SOCK_STREAM,0);

    if(listenSocket==-1){
        cerr<<"Not listening";
        return -1;
    }else{
        cout<<"Socket Created, socket FD: "<<listenSocket<<endl;
    };

    // sockaddr_in is a structure that stores an IPv4 address and a port number
    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Accept connections on all network interfaces.

    
    if (bind(listenSocket,(sockaddr*)&serverAddr,sizeof(serverAddr)) == -1){
        cerr<<"Not binded"<<endl;
        return -1;
    }else{
        cout<<"Binding Succesfull"<<endl;
    }

    // listen 

    if(listen(listenSocket,10)== -1){
        cerr<<"Not listening"<<endl;
        return -1;
    }else{
        cout<<"Listening"<<endl;
    }


    // creating client address

    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    int clientSocket = accept(listenSocket,(sockaddr*)&clientAddr,&clientLen);

    if(clientSocket == -1){
        cerr<<"Client Not connected"<<endl;
        return -1;
    }else{
        cout<<"Client connected"<<endl;
    }

    // endlessly waiting until client connect

    return 0;
}