
#include "dancingLinks.H"
#include "boardFrame.H"
#include "hexomino.H"



int
main(int argc, char **argv) {
  boardFrame           *board     = NULL;
  char                 *boardName = NULL;
  uint32                boardX    = 3;
  uint32                boardY    = 20;

  hexominoIterator     *it        = NULL;
  hexominoIteratorType  itType    = hexominoIteratorFree;

  uint32                nSegments = 5;
  uint32                nCopies   = 1;

  int arg = 1;
  while (arg < argc) {
    if      (strcmp(argv[arg], "-board") == 0) {
      boardName = argv[++arg];
      boardX    = 0;
      boardY    = 0;
    }

    else if (strcmp(argv[arg], "-rectangle") == 0) {
      boardName = NULL;
      boardX    = strtoul(argv[++arg], NULL, 10);
      boardY    = strtoul(argv[++arg], NULL, 10);
    }

    else if (strcmp(argv[arg], "-omino") == 0) {
      nSegments = strtoul(argv[++arg], NULL, 10);
    }

    else if (strcmp(argv[arg], "-copies") == 0) {
      nCopies = strtoul(argv[++arg], NULL, 10);
    }

    else if (strcmp(argv[arg], "-free") == 0) {
      itType = hexominoIteratorFree;
    }

    else if (strcmp(argv[arg], "-onesided") == 0) {
      itType = hexominoIteratorOneSided;
    }

    else if (strcmp(argv[arg], "-fixed") == 0) {
      itType = hexominoIteratorFixed;
    }

    else {
      fprintf(stderr, "ERROR: unknown option '%s'\n", argv[arg]);
      exit(1);
    }

    arg++;
  }

  //  Configure the omino and iterator.

  it = new hexominoIterator(itType, nSegments, nCopies);

  //  Create the board.

  if (boardName) {
    board = new boardFrame(boardName);
    board->finalize();
    board->clearDisplay();
    board->display(stdout);
  }

  else {
    board = new boardFrame(boardX, boardY);
    board->finalize();
    board->clearDisplay();
    board->display(stdout);
  }

  //  Count how many placements we can make.

  int32  ominoPlacements = 0;

  for (it->start(); it->valid(); it->next()) {
    hexomino h = it->omino();

    for (int32 y=0; y<board->Ysize(); y++)
      for (int32 x=0; x<board->Xsize(); x++)
        if (board->isBlocked(x, y, h) == false) {
          //h.display(stdout, x, y);
          ominoPlacements++;
        }
  }

  fprintf(stderr, "\n");
  fprintf(stderr, "Found %d ominoes\n", it->numOminoes());
  fprintf(stderr, "Found %d cells in the board.\n", board->numOpen());
  fprintf(stderr, "Found %d omino placements.\n", ominoPlacements);
  fprintf(stderr, "\n");
  fprintf(stderr, "%.3f MB for matrix\n", sizeof(cell_t) * (it->numOminoes() + board->numOpen()) * ominoPlacements / 1024.0 / 1024.0);
  fprintf(stderr, "\n");

  if (board->numOpen() != it->numOminoes() * hexomino::numOmino()) {
    fprintf(stderr, "ERROR:  Not solvable.  Board has %d open cells, %d ominoes need %d cells.\n",
            board->numOpen(), it->numOminoes(), it->numOminoes() * hexomino::numOmino());
    exit(1);
  }

  //  Set up the solver, add ominoes to it->

  dancingLinks   dl(it->numOminoes(), board->numOpen(), ominoPlacements);

  for (it->start(); it->valid(); it->next()) {
    hexomino h = it->omino();

    for (int32 y=0; y<board->Ysize(); y++)
      for (int32 x=0; x<board->Xsize(); x++)
        if (board->isBlocked(x, y, h) == false) {
          dl.addRow(h, *board, x, y);
        }
  }

  fprintf(stderr, "Used %d cells in the matrix.\n", dl._nextCell);

  dl.search(0, board);

  fprintf(stderr, "Finished.\n");

  exit(0);
}

