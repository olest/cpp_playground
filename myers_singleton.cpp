// Very cool discussion of multithreading on C++
// https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton
// singletonMeyers.cpp

#include <chrono>
#include <iostream>
#include <future>

constexpr auto tenMill= 10000000;

class MyersSingleton{
public:
  static MyersSingleton& getInstance(){
    static MyersSingleton instance;
    volatile int dummy{};
    return instance;
  }
private:
  MyersSingleton()= default;
  ~MyersSingleton()= default;
  MyersSingleton(const MyersSingleton&)= delete;
  MyersSingleton& operator=(const MyersSingleton&)= delete;

};

std::chrono::duration<double> getTime(){

  auto begin= std::chrono::system_clock::now();
  for ( size_t i= 0; i <= tenMill; ++i){
      MyersSingleton::getInstance();
  }
  return std::chrono::system_clock::now() - begin;
  
};

int main(){
 
    auto fut1= std::async(std::launch::async,getTime);
    auto fut2= std::async(std::launch::async,getTime);
    auto fut3= std::async(std::launch::async,getTime);
    auto fut4= std::async(std::launch::async,getTime);
    
    auto total= fut1.get() + fut2.get() + fut3.get() + fut4.get();
    
    std::cout << total.count() << std::endl;

}

