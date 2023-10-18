#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex m;
int sum = 0;

void f(){
    for(int i =0; i< 10*1000*1000; ++i){
        m.lock();
        ++sum;
        m.unlock();
    }
}

int main(){
    thread t(f);
    for(int i = 0; i< 10*1000*1000; i++){
        m.lock();
        ++sum;
        m.unlock();
    }
    t.join();
    cout<<"Sum: "<<sum << endl;
}
