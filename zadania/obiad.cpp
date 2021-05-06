#include <future>
#include <iostream>
#include "external/obiad.hpp"

Herbata                zrob_herbate(Woda, TorebkaHerbaty);
PokrojonySurowyKurczak pokroj_kurczaka(SurowyKurczak);
GotowyKurczak          usmaz_kurczaka(PokrojonySurowyKurczak);
UgotowaneZiemniaki     ugotuj_ziemniaki(Woda, SuroweZiemniaki);
Obiad                  zrob_obiad(UgotowaneZiemniaki, GotowyKurczak, Herbata);


Obiad ugotuj()
{
  // To dostajecie
  Woda            woda;
  SuroweZiemniaki suroweZiemniaki;
  SurowyKurczak   surowyKurczak;
  TorebkaHerbaty  torebkaHerbaty;

  auto herbata = std::async(std::launch::async, zrob_herbate, woda, torebkaHerbaty);
  auto ziemniaki = std::async(std::launch::async, ugotuj_ziemniaki, woda, suroweZiemniaki);
  auto kurczak = std::async(std::launch::async,  pokroj_kurczaka, surowyKurczak);
  auto usmazonyKurczak = std::async(std::launch::async,  usmaz_kurczaka, kurczak.get());
  std::async(std::launch::async, zrob_obiad, ziemniaki.get(), usmazonyKurczak.get(), herbata.get());

}

int main()
{
  auto  start  = Clock::now();
  Obiad obiad1 = synchroniczneGotowanie();
  auto  stop  = Clock::now();
  std::cout << "Synchronicznie: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << "[ms]" << std::endl;

  start        = Clock::now();
  Obiad obiad2 = ugotuj();
  stop         = Clock::now();
  std::cout << "Twoja implementacja: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << "[ms]" << std::endl;
}
