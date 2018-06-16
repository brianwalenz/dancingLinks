

#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include "utility.H"
#include "hexomino.H"

class boardFrame {
private:
  void   allocSpace(int32 maxX_, int32 maxY_) {
    _maxX = maxX_;
    _maxY = maxY_;

    _numOpen = 0;

    _idToX        = new int32   [_maxX * _maxY];
    _idToY        = new int32   [_maxX * _maxY];

    _boardAlloc   = new int32   [_maxX * _maxY];
    _board        = new int32 * [_maxX];

    memset(_boardAlloc, 0, sizeof(int32) * _maxX * _maxY);

    for (int32 x=0; x<_maxX; x++)
      _board[x]   = _boardAlloc + x * _maxY;

    _displayAlloc = new char    [(3 * _maxY + 1) * (3 * _maxX + 1)];
    _display      = new char  * [(3 * _maxY + 1)];

    for (int32 y=0; y<3 * _maxY + 1; y++)
      _display[y] = _displayAlloc + y * (3 * _maxX + 1);
  };

public:
  boardFrame(int32 maxX_, int32 maxY_) {
    allocSpace(maxX_, maxY_);

    setOpen();
  };

  boardFrame(char *infile);

  ~boardFrame() {
    delete [] _idToX;
    delete [] _idToY;

    delete [] _boardAlloc;
    delete [] _board;

    delete [] _displayAlloc;
    delete [] _display;
  };

private:
  void      check(int32 x, int32 y) {
    assert(0 <= x);
    assert(0 <= y);
    assert(x <  _maxX);
    assert(y <  _maxY);
  };

public:
  void      finalize(void) {
    _numOpen = 0;

    for (int32 y=0; y<_maxY; y++)
    for (int32 x=0; x<_maxX; x++)
      if (_board[x][y] < INT32_MAX) {
        _board[x][y] = _numOpen;

        _idToX[_numOpen] = x;
        _idToY[_numOpen] = y;

        _numOpen++;
      }

    fprintf(stdout, "BOARD: %d x %d with %d open spaces\n", _maxX, _maxY, _numOpen);
  };

  void      setBlocked(void) {
    for (int32 x=0; x<_maxX; x++)
    for (int32 y=0; y<_maxY; y++)
      _board[x][y] = INT32_MAX;
  };

  void      setOpen(void) {
    for (int32 x=0; x<_maxX; x++)
    for (int32 y=0; y<_maxY; y++)
      _board[x][y] = 0;
  };

  int32     getIndex  (int32 x, int32 y)   { check(x, y);  return(_board[x][y]);     };

  void      setBlocked(int32 x, int32 y)   { check(x, y);  _board[x][y] = INT32_MAX; };
  void      setOpen   (int32 x, int32 y)   { check(x, y);  _board[x][y] = 0;         };

  bool      isBlocked (int32 x, int32 y)   { return((x < 0) || (_maxX <= x) || (y < 0) || (_maxY <= y) || (_board[x][y] == INT32_MAX));  };
  bool      isOpen    (int32 x, int32 y)   { return((0 <= x) && (x < _maxX) && (0 <= y) && (y < _maxY) && (_board[x][y] <  INT32_MAX));  };

  bool      isBlocked (int32 x, int32 y, hexomino h) {
    for (int32 ii=0; ii<h.numOmino(); ii++)
      if (isBlocked(x + h.x[ii], y + h.y[ii]))
        return(true);

    return(false);
  };

  int32     Xsize(void)   { return(_maxX);    };
  int32     Ysize(void)   { return(_maxY);    };

  int32     numOpen(void) { return(_numOpen); };


  void      clearDisplay(void);
  void      display(FILE *F);
  void      addPiece(int32 *cells,
                     int32  cellsLen);

public:
  int32     _maxX;
  int32     _maxY;

  int32     _numOpen;

  int32    *_idToX;
  int32    *_idToY;

  int32    *_boardAlloc;
  int32   **_board;

  char     *_displayAlloc;
  char    **_display;
};



#endif  //  BOARDFRAME_H
