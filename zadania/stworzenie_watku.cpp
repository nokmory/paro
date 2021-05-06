#include <iostream>
#include <chrono>
#include <thread>
#include <string>

void greeter(std::string who)
{
  for (size_t i = 0; i < 5; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Hi " << who << "!" << std::endl;
  }
}

int main()
{
  std::string name("Name");

  std::thread t(&greeter, name);
  t.join();
  return 0;

}
