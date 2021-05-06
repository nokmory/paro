#include <thread>
#include <iostream>
#include "ThreadGuard.hpp"

void bar() { throw 1; }
void foo() {}

int main()
{
  try
  {
    std::thread t(&foo);
    bar();
    t.join();
  }
  catch (...)
  {
    std::cout << "Ups! Wyjatek! Na szczescie go zlapalismy... uff!" << std::endl;
  }
}
