#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

int main(){
    int listening=socket(AF_INET,SOCK_STREAM,0);

    if(listening==-1){
        cerr<<"Not listening";
        return -1;
    }else{
        cout<<"Socket Created, socket FD: "<<listening<<endl;
    }

    return 0;
}