

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
  hexominoIterator(hexominoIteratorType t, uint32 nSegments, uint32 nCopies) {

    //  Configure the omino size and number of copies allowed per piece.

    hexomino::configure(nSegments, nCopies);

    //  Free      - distinct when none is a transformation of other - pieces can be rotated or flipped
    //  One-sided - distinct when none is a rotation of an other    - pieces can be rotated
    //  Fixed     - distinct when none is exactly like it
    //
    //  But our iterator needs to return all the fixed ominoes, the distinction of 'free'
    //  or 'one-sided' or 'fixed' just changes the id of each omino.  In the 'free' set,
    //  there are still 216 hexominos iterated over, but only 35 different id's are assigned.
    //
    //  For free ominoes, variable 'hh' (the iterator index) is the ID.
    //
    //  For one-sided ominoes, both 'hh' and 'ho' are the IDs.  'ho' is for the one-sided variant,
    //  which starts after the 'free-omino' list.  This is incremented only as needed.
    //
    //  For fixed ominoes, the ID is just the ordinal in the piece list.

    _ominoPos    = 0;
    _ominoMax    = 1024;
    _maxOminoID  = 0;
    _omino       = new hexomino [_ominoMax];

    hexomino   omino;
    hexomino   r[8];

    for (int32 hh=0, ho=hexomino::numFree(); hh<hexomino::numFree(); hh++) {
      omino.initialize(hh);

      r[0] = omino;
      r[1] = r[0];  r[1].rotate();
      r[2] = r[1];  r[2].rotate();
      r[3] = r[2];  r[3].rotate();

      omino.flipX();

      r[4] = omino;
      r[5] = r[4];  r[5].rotate();
      r[6] = r[5];  r[6].rotate();
      r[7] = r[6];  r[7].rotate();

      //  This is a OneSided omino if none of the flipped rotations look like the native omino.
      //  When we add ominoes to the set, we add one for the 'forward' and one for the 'flipped'
      //  orientations.

      bool  oneSided = ((r[0] != r[4]) &&
                        (r[0] != r[5]) &&
                        (r[0] != r[6]) &&
                        (r[0] != r[7]));

      //  Decide if orientation 'b' looks like any other orientation.
      //
      //  Note that for the OneSided set, only the four rotations are allowed.  We've already
      //  decided if this omino needs to have only the 'forward' or both the 'forward' and 'flipped'
      //  ominoes added.

      int32  bMax = ((t == hexominoIteratorOneSided) ? 4 : 8);

      for (int32 b=0; b<bMax; b++) {
        bool  duplicate = false;

        for (int32 c=b+1; c<bMax; c++) {
          if (r[b] == r[c]) {
            duplicate = true;
            break;
          }
        }

        //  If omino 'h' in orientation 'b' is a the same as some later orientation, skip it.

        if (duplicate == true)
          continue;

        //  Otherwise, a distinct omino shape, so add it to our list.  Based on what set we've been
        //  asked to iterate over, set the id of this omino.
        //
        //  Free     -- all rotations and flips refer to the same piece.
        //  OneSided -- all rotations           refer to the same piece.
        //  Fixed    -- all rotations and flips refer to distinct pieces.

        if (t == hexominoIteratorFree) {
          fprintf(stderr, "piece %4d is omino %2d orientation %d\n", _ominoPos, hh, b);
          _omino[_ominoPos]    = r[b];
          _omino[_ominoPos].id = hh;
          _ominoPos++;
        }

        if (t == hexominoIteratorOneSided) {
          fprintf(stderr, "piece %4d is omino %2d orientation %d\n", _ominoPos, hh, b);
          _omino[_ominoPos]    = r[b];
          _omino[_ominoPos].id = hh;
          _ominoPos++;

          if (oneSided == true) {                //  Add one for the 'flipped' piece.
            fprintf(stderr, "piece %4d is omino %2d orientation %d (one sided)\n", _ominoPos, ho, b+4);
            _omino[_ominoPos]    = r[b+4];
            _omino[_ominoPos].id = ho;
            _ominoPos++;
          }
        }

        if (t == hexominoIteratorFixed) {
          fprintf(stderr, "piece %4d is omino %2d orientation %d\n", _ominoPos, hh, b);
          _omino[_ominoPos]    = r[b];
          _omino[_ominoPos].id = _ominoPos;
          _ominoPos++;
        }
      }

      if (oneSided)   //  Increment the one-sided ID.
        ho++;
    }

    assert(_ominoPos < _ominoMax);

    _ominoMax = _ominoPos;
    _ominoPos = 0;

    //  Find the largest ID we've assigned.  This is returned later.

    for (uint32 ii=0; ii<_ominoMax; ii++)
      _maxOminoID = max(_maxOminoID, _omino[ii].id);


    fprintf(stderr, "Assigned %d ominos to %d shapes.\n", _maxOminoID + 1, _ominoMax);
  };


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
