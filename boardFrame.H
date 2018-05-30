

#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include "utility.H"
#include "hexomino.H"

class boardFrame {
public:
  boardFrame(int32 maxX_, int32 maxY_) {
    maxX = maxX_;
    maxY = maxY_;

    _numOpen = 0;

    boardAlloc = new int32   [maxX * maxY];
    board      = new int32 * [maxX];

    for (int32 x=0; x<maxX; x++)
      board[x] = boardAlloc + x * maxY;

    setOpen();
  };

  boardFrame(char *infile);

  ~boardFrame() {
    delete [] boardAlloc;
    delete [] board;
  };

  void      display(FILE *F, int32 offset=0) {
    for (int32 y=maxY; --y>=0; ) {
      for (int32 x=0; x<maxX; x++) {
        if (isBlocked(x, y))
          fprintf(F, " ****");
        else
          fprintf(F, "%5d", getIndex(x, y) + offset);
      }
      fprintf(F, "\n");
    }
  };

private:
  void      check(int32 x, int32 y) {
    assert(0 <= x);
    assert(0 <= y);
    assert(x <  maxX);
    assert(y <  maxY);
  };

public:
  void      finalize(void) {
    _numOpen = 0;

    for (int32 y=0; y<maxY; y++)
    for (int32 x=0; x<maxX; x++)
      if (board[x][y] < INT32_MAX)
        board[x][y] = _numOpen++;
  };

  void      setBlocked(void) {
    for (int32 x=0; x<maxX; x++)
    for (int32 y=0; y<maxY; y++)
      board[x][y] = INT32_MAX;
  };

  void      setOpen(void) {
    for (int32 x=0; x<maxX; x++)
    for (int32 y=0; y<maxY; y++)
      board[x][y] = 0;
  };

  int32     getIndex  (int32 x, int32 y)   { check(x, y);  return(board[x][y]);     };

  void      setBlocked(int32 x, int32 y)   { check(x, y);  board[x][y] = INT32_MAX; };
  void      setOpen   (int32 x, int32 y)   { check(x, y);  board[x][y] = 0;         };

  bool      isBlocked (int32 x, int32 y)   { return((x < 0) || (maxX <= x) || (y < 0) || (maxY <= y) || (board[x][y] == INT32_MAX));  };
  bool      isOpen    (int32 x, int32 y)   { return((0 <= x) && (x < maxX) && (0 <= y) && (y < maxY) && (board[x][y] <  INT32_MAX));  };

  bool      isBlocked (int32 x, int32 y, hexomino h) {
    for (int32 ii=0; ii<h.numOmino(); ii++) {
      //fprintf(stderr, "  at %d,%d -> %s\n",
      //        x + h.x[ii],
      //        y + h.y[ii],
      //        isBlocked(x + h.x[ii], y + h.y[ii]) ? "blocked" : "open");

      if (isBlocked(x + h.x[ii], y + h.y[ii]))
        return(true);
    }
    return(false);
  };

  int32     Xsize(void)   { return(maxX);    };
  int32     Ysize(void)   { return(maxY);    };

  int32     numOpen(void) { return(_numOpen); };

public:
  int32     maxX;
  int32     maxY;

  int32    _numOpen;

  int32    *boardAlloc;
  int32   **board;
};



#endif  //  BOARDFRAME_H
