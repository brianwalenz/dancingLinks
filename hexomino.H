

#ifndef HEXOMINO_H
#define HEXOMINO_H

#include "utility.H"


enum hexominoIteratorType {
  hexominoIteratorFree     = 0,   //   35 "front-only" ominoes
  hexominoIteratorOneSided = 1,   //   60 "front" and "back" ominoes
  hexominoIteratorFixed    = 2    //  216 ominoes pre-rotated and flipped
};



class hexomino {
public:
  hexomino(int32 id=0) {
    initialize(id);
  };
  ~hexomino() {
  };

private:
  void   init(int32 *x, int32 *y, vector<pair<int32,int32> > p) {
    for (int32 ii=0; ii<numOmino(); ii++) {
      x[ii] = p[ii].first;
      y[ii] = p[ii].second;
    }
  };

public:
  static
  void     configure(int32 numSegments, int32 numCopies=1) {

    _numSegments = numSegments;
    _numCopies   = numCopies;
    _numFree     = 0;

    switch (numSegments) {
      case  3:   _numFree =  2 * _numCopies;   break;
      case  4:   _numFree =  5 * _numCopies;   break;
      case  5:   _numFree = 12 * _numCopies;   break; 
      case  6:   _numFree = 35 * _numCopies;   break; 
      default:   _numFree =  0 * _numCopies;   break;
    }

    if (_numFree == 0) {
      fprintf(stderr, "unsupported numSegments %d.\n", numSegments);
      exit(1);
    }
  };

  void   initialize(uint32 id_);


  void   rotate(void);       //  Rotate 90 degrees CW.
  void   flipY(void);        //  Flip about the Y axis.
  void   flipX(void);        //  Flip about the X axis.
  void   normalize(void);    //  Adjust coords so omino is adjacent to both the X and Y axes.
  void   sort(void);         //  Arrange coordinates in a standard form.
  void   display(FILE *F);


  bool  operator==(const hexomino &h) {
    for (int32 ii=0; ii<numOmino(); ii++) {
      if ((x[ii] != h.x[ii]) ||
          (y[ii] != h.y[ii]))
        return(false);
    }
    return(true);
  };

  bool  operator!=(const hexomino &h) {
    for (int32 ii=0; ii<numOmino(); ii++) {
      if ((x[ii] != h.x[ii]) ||
          (y[ii] != h.y[ii]))
        return(true);
    }
    return(false);
  };

public:
  static
  int32   numOmino(void)  { return(_numSegments); };

  static
  int32   numFree(void)   { return(_numFree);     };

public:
  int32  id;
  int32  x[6];
  int32  y[6];

  static  int32  _numSegments;
  static  int32  _numCopies;
  static  int32  _numFree;
};





class hexominoIterator {
public:
  hexominoIterator(hexominoIteratorType t, uint32 nSegments, uint32 nCopies);

public:
  hexomino &operator*(void)   { return(_omino[_ominoPos]);     };
  hexomino &omino(void)       { return(_omino[_ominoPos]);     };

  void      start(void)       { _ominoPos = 0;                 };
  bool      valid(void)       { return(_ominoPos < _ominoMax); };
  void      next(void)        { _ominoPos++;                   };

  int32     numOminoes(void)  { return(_maxOminoID + 1);       };
  int32     numPieces(void)   { return(_ominoMax);             };

private:
  int32      _ominoPos;
  int32      _ominoMax;
  int32      _maxOminoID;
  hexomino  *_omino;
};

#endif  //  HEXOMINO_H
