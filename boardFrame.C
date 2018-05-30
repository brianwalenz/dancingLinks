

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

  _numOpen = 0;

  maxX = maxLineLen;
  maxY = linesLen;

  fprintf(stderr, "boardFrame()-- initialize to maxX = %d, maxY = %d\n",
          maxX, maxY);

  boardAlloc = new int32   [maxX * maxY];
  board      = new int32 * [maxX];

  for (int32 x=0; x<maxX; x++)
    board[x] = boardAlloc + x * maxY;

  setBlocked();

  //  Scan the lines, setting cells as specified.

  for (int32 jj=0; jj<linesLen; jj++)
    for (int32 ii=0; ii<lines[jj]._length; ii++)
      if (isspace(lines[jj]._line[ii]) == false)
        setOpen(ii, jj);

  //  Finish up.

  finalize();
}
