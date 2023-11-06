#include <thread>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <vector>
#include <algorithm>
#include <condition_variable>
#include <memory>

using namespace std::chrono_literals;
using std::vector;
using std::thread;
using std::unique_lock;
using std::mutex;
using std::condition_variable;
using std::queue;


class WorkQueue
{
	std::condition_variable work_available;
	std::mutex work_mutex;
	std::queue<int> work;

public:
  void push_work(int item)
  {
    unique_lock<mutex> lock(work_mutex);

    bool was_empty = work.empty();
    work.push(item);

    lock.unlock();

    if (was_empty)
    {
		work_available.notify_one();
    }    
  }

  int wait_and_pop()
  {
    unique_lock<mutex> lock(work_mutex);
    while (work.empty())
    {
      work_available.wait(lock);
    }

    int tmp = work.front();
    work.pop();
    return tmp;
  }
};

WorkQueue work_queue;

int main(int argc, char** argv) {
    WorkQueue work_queue;

    auto producer = [&]() {
    while (true) {
      int work = 10;
      std::cout << "PRODUCER: Push some work: " << work << std::endl;
      work_queue.push_work(work);
      std::this_thread::sleep_for(5s);
    }
    };

    vector<thread> producers;
    for(int i=0;i<5;i++)
    {
        producers.push_back( std::thread(producer ) );
    }

	std::cout << "Got here " << "\n";
    std::thread consumer([&]() {        
    while (true)
    {
        int i = work_queue.wait_and_pop();
        std::cout << "CONSUMER: Got some work: " << i << std::endl;
    }
    });

    std::for_each(producers.begin(), producers.end(), [](thread &p) {
        p.join();
    });    

    consumer.join();  
}


