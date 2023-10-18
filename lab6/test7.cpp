#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int sum = 0;

void f(){
    for(int i =0; i< 1000; ++i){
        ++sum;
    }
}

int main(){
    thread t(f);
    for(int i = 0; i< 1000; i++){
        ++sum;
    }
    t.join();
    cout<<"Sum: "<<sum << endl;
    /*1000으로 변경 시 2000이 뜬다. 1500이 뜨는 경우도 있다. 
    아무튼 다른 스레드에서 실행한 연산이 기대한 값과 같이 나올 수 있는 이유는 
    CPU 스케쥴링 관점에서 time slicing 시 한번에 처리 가능한 양이기 때문*/
}
