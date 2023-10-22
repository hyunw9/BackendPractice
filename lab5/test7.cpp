#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>

#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    
    int s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(s<0){
        cerr <<"socket() failed: "<< s <<" "<< strerror(errno) <<endl;
        return 1;
    }
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port= htons(10001);
    if(connect(s,(struct sockaddr*) &sin, sizeof(sin))<0){
        cerr<< "connect() failed: "<<strerror(errno) << endl;
        return 1;
    }

    char buf[65535];
    int r = send(s,buf,sizeof(buf),0);
    if(r<0){
        cerr<<"send() failed: "<< strerror(errno) <<endl;
    }else{
        cout<< "Sent: " <<r<< "bytes"<< endl;
    }
    r = recv(s,buf,sizeof(buf),0);
    if(r<0){
        cerr<<"recv() failed: "<< strerror(errno) <<endl;
    }else{
        cout<< "Received: " << r << endl;
    }

    /*
    * 반복을 돌며 recv, send 하는 것이 올바른 방법 (tcp) 
    왜 ? TCP 는 전송 보장을 하기 때문이다. Ethernet 프레임의 MTU 는 약 1500byte고, 
    그 위의 UDP는 최대 64KB 까지 전송이 가능하기 때문에, 약 1472 byte 이상의 데이터는 fragmentation 이 일어난다.
    (IP 헤더에 필드 존재) UDP는 Best Effort 기 때문에, 받은 패킷을 조합 시 일부가 손실되었다면 복구가 어렵다. 
    반면 TCP는 Sequence number, ACK 를 이용해 stateful 하게 전송하기 때문에, 전송 보장이 가능하다. 
    값을 받게 되면 커널 레벨에서 ACK를 전송하기 때문에 사용자는 신경쓰지 않아도 된다. 
    하지만 개발자는 recv() 를 반복적으로 호출해서 데이터를 읽어야 한다. TCP 스트림은 바운더리가 없으므로,
    전송된 모든 데이터를 한번에 받아오지 않고 여러 번에 걸쳐서 받아올 수 있다.
    int offset= 0;
    while( offset < r){
        int numRecv = recv(s,buf+offset,r-offset,0);
        if(numRecv<0){
            cerr << "Recv() failed: "<< strerror(errno)<<endl;
            break;
        }else if( numRecv ==0){
            cout << "Connection closed " <<endl;
        }
        else{
            cout<< "recv: "<<numRecv << endl;
            offset += numRecv;
        }
        */
    
    
    close(s);
    return 0;
}
