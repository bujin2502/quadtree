#include "quadstablo.h"
#include <iostream>

int main() {
  int sirina, visina;
  std::cout << "Unesite sirinu QuadStabla: ";
  std::cin >> sirina;
  std::cout << "Unesite visinu QuadStabla: ";
  std::cin >> visina;
  
  QuadStablo quadTree(sirina, visina);
  
  int option;
  do {
    std::cout << "\n-------- Izbornik --------\n";
    std::cout << "1. Unesi tocku\n";
    std::cout << "2. Provjeri tocku\n";
    std::cout << "3. Ukloni tocku\n";
    std::cout << "4. Izlaz\n";
    std::cout << "Odabir: ";
    std::cin >> option;
    
    switch(option) {
      case 1: {
        Tocka tocka;
        std::cout << "Unesite x koordinatu: ";
        std::cin >> tocka.x;
        std::cout << "Unesite y koordinatu: ";
        std::cin >> tocka.y;
        quadTree.unesi(tocka);
        std::cout << "Tocka unesena.\n";
        break;
      }
      case 2: {
        Tocka tocka;
        std::cout << "Unesite x koordinatu za provjeru: ";
        std::cin >> tocka.x;
        std::cout << "Unesite y koordinatu za provjeru: ";
        std::cin >> tocka.y;
        if (quadTree.sadrzi(tocka)) {
          std::cout << "Tocka se nalazi unutar QuadStabla.\n";
        } else {
          std::cout << "Tocka se ne nalazi unutar QuadStabla.\n";
        }
        break;
      }
      case 3: {
        Tocka tocka;
        std::cout << "Unesite x koordinatu za uklanjanje: ";
        std::cin >> tocka.x;
        std::cout << "Unesite y koordinatu za uklanjanje: ";
        std::cin >> tocka.y;
        quadTree.ukloni(tocka);
        std::cout << "Tocka uklonjena.\n";
        break;
      }
      case 4:
        std::cout << "Izlaz iz programa.\n";
        break;
      default:
        std::cout << "Neispravan odabir, molimo odaberite ponovno.\n";
    }
    
  } while (option != 4);
  
  return 0;
}
