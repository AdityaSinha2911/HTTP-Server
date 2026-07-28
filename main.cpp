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

    int serverSocket=socket(AF_INET,SOCK_STREAM,0);

    if(serverSocket==-1){
        cerr<<"Not listening";
        return -1;
    }else{
        cout<<"Socket Created, socket FD: "<<serverSocket<<endl;
    };

    // sockaddr_in is a structure that stores an IPv4 address and a port number
    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Accept connections on all network interfaces.

    
    if (bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr)) == -1){
        cerr<<"Not binded"<<endl;
    }else{
        cout<<"Binding Succesfull"<<endl;
    }



    
    return 0;
}