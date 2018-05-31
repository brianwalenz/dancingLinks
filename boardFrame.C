

#include "boardFrame.H"

class inLine {
public:
  inLine() {
    _line   = new char [1024 + 1];
    _length = 0;

    memset(_line, 0, sizeof(char) * (1024 + 1));
  };

  bool    readLine(FILE *F) {

    fgets(_line, 1024, F);

    if (feof(F))
      return(false);

    _length = strlen(_line);

    return(true);
  };

  ~inLine() {
    delete [] _line;
  };

  char   *_line;
  int32   _length;
};



boardFrame::boardFrame(char *inFileName) {
  int32     linesMax = 1024;
  int32     linesLen = 0;
  inLine   *lines    = new inLine [linesMax];

  //  Load the file into 'lines'.

  errno = 0;

  FILE *F = fopen(inFileName, "r");

  if (F == NULL)
    fprintf(stderr, "Failed to open board '%s' for reading: %s\n", inFileName, strerror(errno)), exit(1);

  while (lines[linesLen].readLine(F))
    linesLen++;
  
  fclose(F);

  //  Reverse the list, so we set up our array in the same orientation
  //  as the input picture.  We probably could have just done some
  //  index math when setOpen() is called...

  reverse(lines, lines+linesLen);

  //  Find the longest line.

  int32  maxLineLen = 0;

  for (int32 ii=0; ii<linesLen; ii++)
    maxLineLen = max(maxLineLen, lines[ii]._length);

  //  Allocate a board to fit those lines

  allocSpace(maxLineLen, linesLen);

  setBlocked();

  //  Scan the lines, setting cells as specified.

  for (int32 jj=0; jj<linesLen; jj++)
    for (int32 ii=0; ii<lines[jj]._length; ii++)
      if (isspace(lines[jj]._line[ii]) == false)
        setOpen(ii, jj);

  //  Finish up.

  finalize();
}




void
boardFrame::clearDisplay(void) {
  memset(_displayAlloc, '.', sizeof(char) * 9 * _maxY * (_maxX + 1));

  for (int32 y=0; y<3 * _maxY; y++)
    _display[y][3 * (_maxX + 1) - 1] = 0;
}



void
boardFrame::addPiece(int32 *cells,
                     int32  cellsLen) {

  int32  x[6];
  int32  y[6];

  for (int32 ii=0; ii<cellsLen; ii++) {
    x[ii] = _idToX[ cells[ii] ];
    y[ii] = _idToY[ cells[ii] ];
    //fprintf(stdout, "ii=%d  %d, %d\n", ii, x[ii], y[ii]);
  }

  //  We'll draw, in each cell, a * in the middle.
  //  Then, for each neighbor, a * towards the neighbor.

  for (int32 ii=0;    ii<cellsLen; ii++) {
    int32  dx = 3 * x[ii] + 1;
    int32  dy = 3 * y[ii] + 1;

    _display[dy-1][dx-1] = ' ';
    _display[dy-1][dx  ] = ' ';
    _display[dy-1][dx+1] = ' ';
    _display[dy  ][dx-1] = ' ';
    _display[dy  ][dx  ] = '+';
    _display[dy  ][dx+1] = ' ';
    _display[dy+1][dx-1] = ' ';
    _display[dy+1][dx  ] = ' ';
    _display[dy+1][dx+1] = ' ';

    for (int32 jj=0; jj<cellsLen; jj++) {
      //if (ii == 3)
      //  fprintf(stdout, "  TEST ii %d, %d  jj %d, %d\n", x[ii], y[ii], x[jj], y[jj]);

      if ((x[ii]-1 == x[jj]) && (y[ii]   == y[jj]))   _display[dy  ][dx-1] = '-';
      if ((x[ii]   == x[jj]) && (y[ii]-1 == y[jj]))   _display[dy-1][dx  ] = '|';
      if ((x[ii]   == x[jj]) && (y[ii]+1 == y[jj]))   _display[dy+1][dx  ] = '|';
      if ((x[ii]+1 == x[jj]) && (y[ii]   == y[jj]))   _display[dy  ][dx+1] = '-';
    }
  }
}



void
boardFrame::display(FILE *F) {

  for (int32 y=3*_maxY; --y>=0; )
    fprintf(F, "%s\n", _display[y]);
}
