#ifndef QUADSTABLO_H
#define QUADSTABLO_H
#endif

#include <iostream>

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
  QuadStablo(int sirina, int visina);
  ~QuadStablo();
  void unesi(const Tocka& tocka);
  bool sadrzi(const Tocka& tocka);
  void ukloni(const Tocka& tocka);
  
private:
  QuadStabloCvor* korijen;
  int sirinaStabla;
  int visinaStabla;
  void unesiRekurzivno(QuadStabloCvor** cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax);
  bool sadrziRekurzivno(QuadStabloCvor* cvor, const Tocka& tocka);
  void ukloniRekurzivno(QuadStabloCvor** cvor, const Tocka& tocka, int xMin, int yMin, int xMax, int yMax);
};

QuadStablo::~QuadStablo() {
}
