//-*-c++-*-
#ifndef _Filter_h_
#define _Filter_h_

using namespace std;

class Filter {
  int divisor;
  int dim;
  int *data;

public:
  inline Filter(int _dim){divisor = 1;dim = _dim;data = new int[dim * dim];};
  inline int get(int r, int c){return data[ r * dim + c ];};
  inline void set(int r, int c, int value){data[ r * dim + c ] = value;};

  inline int getDivisor(){  return divisor;};
  inline void setDivisor(int value){divisor = value;};

  inline int getSize(){  return dim;};
  void info();
};


#endif
