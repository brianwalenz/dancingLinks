
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
hexomino::display(FILE *F) {
  fprintf(F, "%3d -", id);

  for (int32 ii=0; ii<numOmino(); ii++)
    fprintf(F, " %d,%d", x[ii], y[ii]);

  fprintf(F, "\n");
}
