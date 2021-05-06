#include <thread>
#include <typeinfo>
#include <iostream>
#include "Queue.hpp"
#include "external/isPrime.hpp"
#include <condition_variable>

constexpr auto range = 1000u*1000u;
Queue queue;

std::condition_variable cv;
std::mutex m;
using Lock = std::lock_guard<std::mutex>;

void producer()
{
  for (unsigned i=0; i<range; ++i)
  {
      Lock lock(m);
      queue.push( Queue::value_type{i, isPrime(i)} );
      cv.notify_one();
  }
}

void consumer()
{
  for(unsigned i=0; i<range; ++i)
  {
      std::unique_lock<std::mutex> lock(m);
      cv.wait(lock, [&]{ return not queue.empty(); });
      const auto e = queue.pop();
      std::cout << e.n_ << " is " << (e.isPrime_?"":"not ") << "a prime number" << std::endl;
  }
}

int main()
{
  try
  {
    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();
  }
  catch(std::exception const &ex)
  {
    std::cerr << "Oops: " << ex.what() << " (" << typeid(ex).name() << ")" << std::endl;
    return 42;
  }
}
