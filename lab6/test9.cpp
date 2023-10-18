#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex m;
mutex m2;
int sum = 0;

void f(){
    for(int i =0; i< 1000000; ++i){
        m.lock();
        m2.lock();
        ++sum;
        m.unlock();
        m2.lock();
    }
}

int main(){
    thread t(f);
    for(int i = 0; i< 1000000; i++){
        m.lock();
        ++sum;
        m.unlock();
    }
    t.join();
    cout<<"Sum: "<<sum << endl;

}
