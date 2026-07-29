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
        cerr << "Bind failed: " << strerror(errno) << endl;
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

    // client socket declared

    int clientSocket = accept(listenSocket,(sockaddr*)&clientAddr,&clientLen);

    if(clientSocket == -1){
        cerr<<"Client Not connected"<<endl;
        return -1;
    }else{
        cout<<"Client connected"<<endl;
    }

    // endlessly waiting until client connect



    // Buffer to store incoming data
    char buffer[4096];

    // Clear the buffer
    memset(buffer, 0, sizeof(buffer));


    // creating recving function to receive data
    ssize_t bytesReceived = recv(
        clientSocket,      // Connected socket
        buffer,            // Buffer to store data
        sizeof(buffer)-1,  // Maximum bytes to receive
        0                  // No special flags
    );
    
    if (bytesReceived > 0)
    {
        cout << "Received " << bytesReceived << " bytes\n";
        cout << buffer << endl;
    }
    else if (bytesReceived == 0)
    {
        cout << "Client disconnected." << endl;
    }
    else
    {
        perror("recv");
    }

    string body = "<h1>Hello from my HTTP Server!</h1>";

    string response ="HTTP/1.1 200 OK\r\n""Content-Type: text/html\r\n" "Content-Length: " + to_string(body.length()) + "\r\n""\r\n" +body;
    

    ssize_t bytesSent = send(clientSocket,response.c_str(),response.length(),0);

    
    if (bytesSent > 0)
    {
        cout << "Sent "<< bytesSent<< " bytes." << endl;
    }
    else if (bytesSent == 0)
    {
        cout << "No bytes were sent." << endl;
    }
    else
    {
        perror("send");
    }

    close(clientSocket);
    close(listenSocket);
    
    return 0;
}