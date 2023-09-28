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

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(10000+142);
    if(bind(s,(struct sockaddr *) &sin, sizeof(sin))< 0){
        cerr << strerror(errno) <<endl;
        return 0;
    } 
    memset(&sin, 0, sizeof(sin));
    socklen_t sin_size = sizeof(sin);
    int result = getsockname(s,(sockaddr *) &sin, &sin_size);
    if(result == 0){
        cout<< "My addr: "<< inet_ntoa(sin.sin_addr) <<endl;
        cout << "My port: "<< ntohs(sin.sin_port)<< endl;
    }

    close(s);
    return 0;
}
