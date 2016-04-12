#include <chrono>
#include <future>
#include <thread>
#include <vector>
#include <iostream>
#include <cassert>
#include "isPrime.hpp"

void worker_thread(std::vector<std::promise<int>> &&q)
{
  unsigned lastPrime = 2;
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // TEGO NIE WOLNO USUWAC :)

    while( not isPrime(lastPrime) )
      lastPrime++;

    unsigned nextPrime = lastPrime;
    lastPrime++;

    // TODO: pobierz i wypelnij promise wartoscia nextPrime
  }
}


int main()
{
  std::vector<std::future<int>>  futures;       // moze sie przydac :)
  std::vector<std::promise<int>> promises(500);

  /*
   * TODO:
   * 1. Zachowac future odpowiadajace promise
   * 2. Utworzyc watek (moze byc detached)
   * Hint: std::promise::get_future()
   */

  while (true)
  {
    unsigned n;
    std::cout << "Ktora liczbe pierwsza chcesz uzyskac? Zakres 1-500. 0 konczy program" << std::endl;
    std::cin >> n;
    if (n == 0) break;

    /*
     * TODO: jesli wynik juz jest dostepny, wyswietl go. Jesli nie,
     * poinformuj o tym i popros o kolejne pytanie.
     *
     * HINTS: std::future::wait_for(), std::chrono::milliseconds(0),
     * std::future_status::ready
     */
  }
}
