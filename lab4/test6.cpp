#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "person.pb.h"

using namespace std;
using namespace mju;

int main(){
    int s = socket(AF_INET, SOCK_DGRAM , IPPROTO_UDP);
    if (s < 0) return 1;

    Person *person = new Person; 
    person -> set_name("홍길동");
    person -> set_id(60192159);

    Person::PhoneNumber *phoneNum = person->add_phones();
    phoneNum -> set_number("010-2222-1321");
    phoneNum -> set_type(Person::MOBILE);

    const string buf = person->SerializeAsString();

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(10001); 
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int numBytes = sendto(s,buf.c_str(),buf.length(), 0, (struct sockaddr *) &sin, sizeof(sin));
    cout << "Sent: " << numBytes << endl;

    char buf2[65536];    
    memset(&sin, 0, sizeof(sin));
    socklen_t sin_size = sizeof(sin);

    buf2[numBytes] = '\0'; 
    numBytes = recvfrom(s, buf2, sizeof(buf2), 0,  (struct sockaddr *) &sin, &sin_size);

    Person *p2 = new Person;
    p2 -> ParseFromString(buf2);
    cout<< p2->name()<<endl;
    cout<< p2->id()<<endl;
    for (int i = 0; i < p2->phones_size(); i++){
        cout<<p2 -> phones(i).type()<<endl;
        cout<<p2-> phones(i).number()<<endl;
    }
    
    close(s);
    return 0;
}
