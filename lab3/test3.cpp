#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

int main(){
    int s = socket(AF_INET, SOCK_DGRAM , IPPROTO_UDP);
    if (s < 0) return 1;

    string buf = "Hello World";

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(10000); 
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    int numBytes = sendto(s,buf.c_str(),buf.length(), 0, (struct sockaddr *) &sin, sizeof(sin));
    cout << "Sent: " << numBytes << endl;
    close(s);
    return 0;
}
