#include <thread>
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
#include <boost/lexical_cast.hpp>

std::string output;


void addLines(unsigned count)
{
  const auto id = boost::lexical_cast<std::string>( std::this_thread::get_id() );
  for(unsigned i=0; i<count; ++i)
  {
    output += id;
    output += ": #";
    output += std::to_string(i);
    output += "\n";
  }
}



int main()
{
  try
  {
    constexpr auto threadsCount = 3;
    constexpr auto iterations   = 40;

    std::vector<std::thread> threads;
    threads.reserve(threadsCount);
    for(auto i=0; i<threadsCount; ++i)
      threads.emplace_back(addLines, iterations);

    for(auto& th: threads)
      th.join();

    std::cout << output << std::endl;
  }
  catch(std::exception const &ex)
  {
    std::cerr << "Oops: " << ex.what() << " (" << typeid(ex).name() << ")" << std::endl;
    return 42;
  }
}
