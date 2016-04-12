#include <thread>
#include <typeinfo>
#include <iostream>
#include "Queue.hpp"
#include "isPrime.hpp"

constexpr auto range = 1000u*1000u;
Queue queue;


void producer()
{
  for(unsigned i=0; i<range; ++i)
    queue.push( Queue::value_type{i, isPrime(i)} );
}


void consumer()
{
  for(unsigned i=0; i<range; ++i)
  {
    while( queue.empty() )
    { }
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
