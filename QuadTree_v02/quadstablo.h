#ifndef QUADSTABLO_H
#define QUADSTABLO_H

#include <iostream>
#include <limits>

struct Tocka {
  int x;
  int y;
};

struct QuadStabloCvor {
  Tocka tocka;
  int xMin;
  int yMin;
  int xMax;
  int yMax;
  QuadStabloCvor* SZ;
  QuadStabloCvor* SI;
  QuadStabloCvor* JZ;
  QuadStabloCvor* JI;
  
  QuadStabloCvor(const Tocka& p, int xMin, int yMin, int xMax, int yMax)
    : tocka(p), xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax), SZ(nullptr), SI(nullptr), JZ(nullptr), JI(nullptr) {}
};

class QuadStablo {
public:
  QuadStablo(int sirina, int visina)
    : korijen(nullptr), sirinaStabla(sirina), visinaStabla(visina) {}
  ~QuadStablo() {}
  
  void unesi(const Tocka& tocka) {
    unesiRekurzivno(&korijen, tocka, 0, 0, sirinaStabla, visinaStabla);
  }
  
  bool sadrzi(const Tocka& tocka) {
    return sadrziRekurzivno(korijen, tocka);
  }
  
  void ukloni(const Tocka& tocka) {
    ukloniRekurzivno(korijen, tocka, 0, 0, sirinaStabla, visinaStabla);
  }

private:
  QuadStabloCvor* korijen;
  int sirinaStabla;
  int visinaStabla;
  
  void unesiRekurzivno(QuadStabloCvor** cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax) {
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
  
  bool sadrziRekurzivno(QuadStabloCvor* cvor, const Tocka& tocka) {
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
  
void ukloniRekurzivno(QuadStabloCvor*& cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax) {
  if (cvor == nullptr) {
    return;
  }

  if (cvor->tocka.x == tocka.x && cvor->tocka.y == tocka.y) {
    cvor->tocka.x = std::numeric_limits<int>::min();  // Postavi x koordinatu na minimalnu vrijednost kao oznaku uklonjenog čvora
    cvor->tocka.y = std::numeric_limits<int>::min();  // Postavi y koordinatu na minimalnu vrijednost kao oznaku uklonjenog čvora
    std::cout << "Ukloni: Tocka (" << tocka.x << ", " << tocka.y << ") je uklonjena iz kvadranta s granicama od ("
              << xMin << ", " << yMin << ") do (" << xMax << ", " << yMax << ")." << std::endl;
    return;
  }

  int xMid = (xMin + xMax) / 2;
  int yMid = (yMin + yMax) / 2;

  if (tocka.x < xMid) {
    if (tocka.y < yMid) {
      ukloniRekurzivno(cvor->SZ, tocka, xMin, yMin, xMid, yMid);
    } else {
      ukloniRekurzivno(cvor->JZ, tocka, xMin, yMid + 1, xMid, yMax);
    }
  } else {
    if (tocka.y < yMid) {
      ukloniRekurzivno(cvor->SI, tocka, xMid + 1, yMin, xMax, yMid);
    } else {
      ukloniRekurzivno(cvor->JI, tocka, xMid + 1, yMid + 1, xMax, yMax);
    }
  }
}
};

#endif