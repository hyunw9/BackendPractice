#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>

#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    for (int i = 0; i < 1024; i++){
        int s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(s<0){
            cerr <<"socket() failed: "<< i <<" "<< strerror(errno) <<endl;
            return 1;
        }
    char buf[1024];
    int r = send(s,buf,sizeof(buf),MSG_NOSIGNAL);
    if(r<0){
        cerr<< "send() failed: "<< r << " "<<strerror(errno)<<endl;
    }else{
        cout<< "Sent: " << r << "bytes"<< endl;
    }
    close(s);
    return 0;
}
}