#include "quadstablo.h"
#include <iostream>

QuadStablo::QuadStablo(int sirina, int visina)
    : korijen(nullptr), sirinaStabla(sirina), visinaStabla(visina) {}

void QuadStablo::unesi(const Tocka& tocka) {
  unesiRekurzivno(&korijen, tocka, 0, 0, sirinaStabla, visinaStabla);
}

bool QuadStablo::sadrzi(const Tocka& tocka) {
  return sadrziRekurzivno(korijen, tocka);
}

void QuadStablo::ukloni(const Tocka& tocka) {
  ukloniRekurzivno(&korijen, tocka, 0, 0, sirinaStabla, visinaStabla);
}

void QuadStablo::unesiRekurzivno(QuadStabloCvor** cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax) {
  if (*cvor == nullptr) {
    *cvor = new QuadStabloCvor(tocka, xMin, yMin, xMax, yMax);
    std::cout << "Umetni: Tocka (" << tocka.x << ", " << tocka.y << ") je umetnuta u kvadrant s granicama od ("
              << xMin << ", " << yMin << ") do (" << xMax << ", " << yMax << ")." << std::endl;
    return;
  }
  
  int xMid = (xMin + xMax) / 2;
  int yMid = (yMin + yMax) / 2;
  
  if (tocka.x <= xMid) {
    if (tocka.y <= yMid) {
      unesiRekurzivno(&(*cvor)->SZ, tocka, xMin, yMin, xMid, yMid);
    } else {
      unesiRekurzivno(&(*cvor)->JZ, tocka, xMin, yMid + 1, xMid, yMax);
    }
  } else {
    if (tocka.y <= yMid) {
      unesiRekurzivno(&(*cvor)->SI, tocka, xMid + 1, yMin, xMax, yMid);
    } else {
      unesiRekurzivno(&(*cvor)->JI, tocka, xMid + 1, yMid + 1, xMax, yMax);
    }
  }
}

bool QuadStablo::sadrziRekurzivno(QuadStabloCvor* cvor, const Tocka& tocka) {
  if (cvor == nullptr) {
    return false;
  }
  
  if (cvor->tocka.x == tocka.x && cvor->tocka.y == tocka.y) {
    std::cout << "Sadrzi: Tocka (" << tocka.x << ", " << tocka.y << ") je u kvadrantu s granicama od ("
              << cvor->xMin << ", " << cvor->yMin << ") do (" << cvor->xMax << ", " << cvor->yMax << ")." << std::endl;
    return true;
  }
  
  int xMid = (cvor->xMin + cvor->xMax) / 2;
  int yMid = (cvor->yMin + cvor->yMax) / 2;
  
  if (tocka.x <= xMid) {
    if (tocka.y <= yMid) {
      return sadrziRekurzivno(cvor->SZ, tocka);
    } else {
      return sadrziRekurzivno(cvor->JZ, tocka);
    }
  } else {
    if (tocka.y <= yMid) {
      return sadrziRekurzivno(cvor->SI, tocka);
    } else {
      return sadrziRekurzivno(cvor->JI, tocka);
    }
  }
}

void QuadStablo::ukloniRekurzivno(QuadStabloCvor** cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax) {
  if (*cvor == nullptr) {
    return;
  }
  
  if ((*cvor)->tocka.x == tocka.x && (*cvor)->tocka.y == tocka.y) {
    delete *cvor;
    *cvor = nullptr;
    std::cout << "Ukloni: Tocka (" << tocka.x << ", " << tocka.y << ") je uklonjena iz kvadranta s granicama od ("
              << xMin << ", " << yMin << ") do (" << xMax << ", " << yMax << ")." << std::endl;
    return;
  }
  
  int xMid = (xMin + xMax) / 2;
  int yMid = (yMin + yMax) / 2;
  
  if (tocka.x <= xMid) {
    if (tocka.y <= yMid) {
      ukloniRekurzivno(&(*cvor)->SZ, tocka, xMin, yMin, xMid, yMid);
    } else {
      ukloniRekurzivno(&(*cvor)->JZ, tocka, xMin, yMid + 1, xMid, yMax);
    }
  } else {
    if (tocka.y <= yMid) {
      ukloniRekurzivno(&(*cvor)->SI, tocka, xMid + 1, yMin, xMax, yMid);
    } else {
      ukloniRekurzivno(&(*cvor)->JI, tocka, xMid + 1, yMid + 1, xMax, yMax);
    }
  }
}

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