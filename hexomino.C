
#include "hexomino.H"

int32  hexomino::_numSegments = 0;
int32  hexomino::_numCopies   = 1;
int32  hexomino::_numFree     = 0;

void
hexomino::initialize(uint32 id_) {

  id = id_;

  if (_numSegments == 3) {
    switch (id_ % _numFree) {
      case  0:   init(x, y, { {0,0}, {0,1}, {0,2} });   break;
      case  1:   init(x, y, { {0,0}, {0,1}, {1,0} });   break;
      default:                                          break;
    }
  }

  if (_numSegments == 4) {
    switch (id_ % _numFree) {
      case  0:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3} });   break;
      case  1:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2} });   break;
      case  2:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,1} });   break;
      case  3:   init(x, y, { {0,0}, {0,1}, {1,0}, {1,1} });   break;
      case  4:   init(x, y, { {0,0}, {0,1}, {1,1}, {1,2} });   break;
      default:                                                 break;
    }
  }

  //  12 Free     - 63 shapes assigned to 12 ominoes --  60 cells used
  //  18 OneSided - 63 shapes assigned to 20 ominoes --  90 cells used
  //  63 Fixed    - 63 shapes assigned to 63 ominoes -- 315 cells used
  if (_numSegments == 5) {
    switch (id_ % _numFree) {
      case  0:   init(x, y, { {0,1}, {1,0}, {1,1}, {1,2}, {2,2} });   break;  //  0 = F, one-sided
      case  1:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {0,4} });   break;  //  1 = I
      case  2:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,0} });   break;  //  2 = L, one-sided
      case  3:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {1,3} });   break;  //  3 = N, one-sided
      case  4:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,1}, {1,2} });   break;  //  4 = P, one-sided
      case  5:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {2,2} });   break;  //  5 = T
      case  6:   init(x, y, { {0,0}, {0,1}, {1,0}, {2,0}, {2,1} });   break;  //  6 = U
      case  7:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {2,2} });   break;  //  7 = V
      case  8:   init(x, y, { {0,0}, {1,0}, {1,1}, {2,1}, {2,2} });   break;  //  8 = W
      case  9:   init(x, y, { {0,1}, {1,0}, {1,1}, {1,2}, {2,1} });   break;  //  9 = X
      case 10:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,2} });   break;  // 10 = Y, one-sided
      case 11:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {2,0} });   break;  // 11 = Z, one-sided
      default:                                                        break;
    }
  }

  //   35 Free     - 216 shapes assigned to  35 ominoes --  210 cells used
  //   60 OneSided - 216 shapes assigned to  60 ominoes --  360 cells used
  //  216 Fixed    - 216 shapes assigned to 216 ominoes -- 1296 cells used
  if (_numSegments == 6) {
    switch (id_ % _numFree) {
      case  0:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5} });   break;
      case  1:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {1,4} });   break;
      case  2:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {1,3} });   break;
      case  3:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {1,2} });   break;
      case  4:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,3}, {1,4} });   break;
      case  5:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,2}, {1,3} });   break;
      case  6:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,1}, {1,3} });   break;
      case  7:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,0}, {1,3} });   break;
      case  8:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,1}, {1,2} });   break;
      case  9:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,3}, {2,3} });   break;
      case 10:   init(x, y, { {0,0}, {0,1}, {0,2}, {0,3}, {1,2}, {2,2} });   break;
      case 11:   init(x, y, { {0,3}, {1,0}, {1,1}, {1,2}, {1,3}, {2,3} });   break;
      case 12:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {1,3}, {2,3} });   break;
      case 13:   init(x, y, { {0,1}, {1,0}, {1,1}, {1,2}, {1,3}, {2,3} });   break;
      case 14:   init(x, y, { {0,0}, {1,0}, {1,1}, {1,2}, {1,3}, {2,3} });   break;
      case 15:   init(x, y, { {0,1}, {1,0}, {1,1}, {1,2}, {1,3}, {2,2} });   break;
      case 16:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {1,3}, {2,2} });   break;
      case 17:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {1,3}, {2,2} });   break;
      case 18:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,0}, {1,2}, {1,3} });   break;
      case 19:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {1,3}, {1,4} });   break;
      case 20:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,1}, {1,2}, {1,3} });   break;
      case 21:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2} });   break;
      case 22:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {2,2}, {2,3} });   break;
      case 23:   init(x, y, { {0,2}, {1,0}, {1,1}, {1,2}, {2,1}, {2,2} });   break;
      case 24:   init(x, y, { {0,1}, {1,0}, {1,1}, {1,2}, {2,2}, {2,3} });   break;
      case 25:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {2,2}, {2,3} });   break;
      case 26:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {1,3}, {2,3} });   break;
      case 27:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,2}, {2,1}, {2,2} });   break;
      case 28:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,1}, {2,1}, {2,2} });   break;
      case 29:   init(x, y, { {0,1}, {0,2}, {1,0}, {1,1}, {2,1}, {2,2} });   break;
      case 30:   init(x, y, { {0,0}, {0,1}, {1,1}, {1,2}, {1,3}, {2,3} });   break;
      case 31:   init(x, y, { {0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {2,0} });   break;
      case 32:   init(x, y, { {0,0}, {0,1}, {1,0}, {1,1}, {1,2}, {2,1} });   break;
      case 33:   init(x, y, { {0,0}, {0,1}, {1,0}, {1,1}, {2,1}, {2,2} });   break;
      case 34:   init(x, y, { {0,0}, {0,1}, {1,1}, {1,2}, {2,2}, {2,3} });   break;
      default:                                                               break;
    }
  }

  normalize();
  sort();
};




//  Rotate 90 degrees CW.
void
hexomino::rotate(void) {
  for (int32 ii=0; ii<numOmino(); ii++) {
    int32 xx =  y[ii];
    int32 yy = -x[ii];

    x[ii] = xx;
    y[ii] = yy;
  }

  normalize();
  sort();
}



//  Flip about the Y axis.
void
hexomino::flipY(void) {
  for (int32 ii=0; ii<numOmino(); ii++) {
    x[ii] = -x[ii];
    y[ii] =  y[ii];
  }

  normalize();
  sort();
}



//  Flip about the X axis.
void
hexomino::flipX(void) {
  for (int32 ii=0; ii<numOmino(); ii++) {
    x[ii] =  x[ii];
    y[ii] = -y[ii];
  }

  normalize();
  sort();
}



//  Adjust coords so omino is adjacent to both the X and Y axes.
void
hexomino::normalize(void) {
  int32  mx = numOmino();
  int32  my = numOmino();

  for (int32 ii=0; ii<numOmino(); ii++) {
    mx = min(mx, x[ii]);
    my = min(my, y[ii]);
  }

  for (int32 ii=0; ii<numOmino(); ii++) {
    x[ii] -= mx;
    y[ii] -= my;
  }
}



//  Arrange coordinates in a standard form.
void
hexomino::sort(void) {
  for (int32 ii=0;    ii<numOmino(); ii++) {
    for (int32 jj=ii+1; jj<numOmino(); jj++) {
      if (((x[jj] <  x[ii])) ||
          ((x[jj] == x[ii]) && (y[jj] < y[ii]))) {
        swap(x[ii], x[jj]);
        swap(y[ii], y[jj]);
      }
    }
  }
}



void
hexomino::display(FILE *F, int32 bx, int32 by) {
  fprintf(F, "%3d -", id);

  for (int32 ii=0; ii<numOmino(); ii++)
    fprintf(F, " %2d,%-2d", x[ii] + bx, y[ii] + by);

  fprintf(F, "\n");
}






hexominoIterator::hexominoIterator(hexominoIteratorType t, uint32 nSegments, uint32 nCopies) {

  fprintf(stdout, "\n");
  fprintf(stdout, "Configure %s %u-ominoes with %u cop%s.\n",
          toString(t), nSegments, nCopies, (nCopies == 1) ? "y" : "ies");
  fprintf(stdout, "\n");
  fprintf(stdout, "piece omino orient\n");
  fprintf(stdout, "   ID    ID     ID\n");
  fprintf(stdout, "----- ----- ------\n");

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
        fprintf(stdout, "%5d %5d %6d\n", _ominoPos, hh, b);
        _omino[_ominoPos]    = r[b];
        _omino[_ominoPos].id = hh;
        _ominoPos++;
      }

      if (t == hexominoIteratorOneSided) {
        fprintf(stdout, "%5d %5d %6d\n", _ominoPos, hh, b);
        _omino[_ominoPos]    = r[b];
        _omino[_ominoPos].id = hh;
        _ominoPos++;

        if (oneSided == true) {                //  Add one for the 'flipped' piece.
          fprintf(stdout, "%5d %5d %6d (one-sided)\n", _ominoPos, ho, b+4);
          _omino[_ominoPos]    = r[b+4];
          _omino[_ominoPos].id = ho;
          _ominoPos++;
        }
      }

      if (t == hexominoIteratorFixed) {
        fprintf(stdout, "%5d %5d %6d\n", _ominoPos, hh, b);
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


  fprintf(stdout, "Assigned %d ominos to %d shapes.\n", _maxOminoID + 1, _ominoMax);
}
