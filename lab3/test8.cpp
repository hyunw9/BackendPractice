#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

int main(){
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(s < 0){
        return 1;
    }

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(20000+142);
    if(bind(s,(struct sockaddr *) &sin, sizeof(sin)) < 0){
        cerr << strerror(errno) << endl;
        return 0;
    }

    char buf2[65536];
    memset(&sin, 0, sizeof(sin));
    socklen_t sin_size = sizeof(sin);

    while(true){
        cout << ("Receiving Datagrams...");
        int numBytes = recvfrom(s, buf2, sizeof(buf2), 0,  (struct sockaddr *) &sin, &sin_size);
        buf2[numBytes] = '\0';

        cout << "Received: " << numBytes << endl;
        cout << "Data: " << buf2 << endl;
        cout << "From " << inet_ntoa(sin.sin_addr) << endl;

        string str(buf2);
        numBytes = sendto(s,str.c_str(),str.length(), 0, (struct sockaddr *) &sin, sizeof(sin));

        if(numBytes < 0 )  {
            cerr << strerror(errno) <<endl;
            return -1;
        }

        cout << "Sent:" << numBytes << endl;
    }
    close(s);
    return 0;

}