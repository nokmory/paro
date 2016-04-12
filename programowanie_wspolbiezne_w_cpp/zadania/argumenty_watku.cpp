#include <iostream>
#include <thread>

void foo(const std::string& s)
{
  std::cout << "Address of s: " << &s << std::endl;
}

void bar(std::string& ss)
{
  std::cout << "Address of ss: " << &ss << std::endl;
}

int main()
{
  std::string name("Bob");
  std::cout << "Address of name: " << &name << std::endl;

  std::thread t1(foo, name);
  t1.join();

  std::thread t2(foo, std::ref(name));
  t2.join();

  // std::thread t3(bar, name);
  // t3.join();
}
