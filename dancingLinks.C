
#include "dancingLinks.H"
#include "boardFrame.H"
#include "hexomino.H"

#include <map>

using namespace std;


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

  map<int32,bool>               forced;   //  If true, this piece is being forced to a set of positions
  map<pair<int32,int32>, bool>  force;    //  Positions being forced

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

    else if (strcmp(argv[arg], "-force") == 0) {
      int32 piece = strtol(argv[++arg], NULL, 10);
      int32 place = strtol(argv[++arg], NULL, 10);

      forced[piece] = true;
      force[pair<int32,int32>(piece,place)] = true;
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

  int32  totalPlacements   = 0;    //  Valid placements
  int32  droppedPlacements = 0;    //  Placements we can't make based on command line

  int32 *ominoPlacements   = new int32 [it->numOminoes()];
  int32 *usedPlacements    = new int32 [it->numOminoes()];

  for (int32 hh=0; hh<it->numOminoes(); hh++) {
    ominoPlacements[hh] = 0;
    usedPlacements[hh]  = 0;
  }

  for (it->start(); it->valid(); it->next()) {
    hexomino h = it->omino();

    for (int32 y=0; y<board->Ysize(); y++) {
      for (int32 x=0; x<board->Xsize(); x++) {
        if (board->isBlocked(x, y, h) == false) {

          //  Count the placement if the piece isn't being forced, or
          //  if this is a placement we want to force it into.
          if ((forced[h.id] == false) ||
              (force[pair<int32,int32>(h.id, ominoPlacements[h.id])] == true)) {
            //h.display(stdout, x, y);

            totalPlacements++;
            usedPlacements[h.id]++;
          }

          else {
            droppedPlacements++;
          }

          //  Always count the number of placements we could have put this piece.
          ominoPlacements[h.id]++;
        }
      }
    }
  }

  for (int32 hh=0; hh<it->numOminoes(); hh++)
    fprintf(stdout, "omino %d has %d placements; %d used.\n", hh, ominoPlacements[hh], usedPlacements[hh]);


  fprintf(stdout, "\n");
  fprintf(stdout, "Found %d ominoes\n", it->numOminoes());
  fprintf(stdout, "Found %d cells in the board.\n", board->numOpen());
  fprintf(stdout, "Found %d omino placements.\n", totalPlacements);
  fprintf(stdout, "Dropped %d omino placements.\n", droppedPlacements);
  fprintf(stdout, "\n");
  fprintf(stdout, "%.3f MB for matrix\n", sizeof(cell_t) * (it->numOminoes() + board->numOpen()) * totalPlacements / 1024.0 / 1024.0);
  fprintf(stdout, "\n");

  if (board->numOpen() != it->numOminoes() * hexomino::numOmino()) {
    fprintf(stderr, "ERROR:  Not solvable.  Board has %d open cells, %d ominoes need %d cells.\n",
            board->numOpen(), it->numOminoes(), it->numOminoes() * hexomino::numOmino());
    exit(1);
  }

  //  Set up the solver, add ominoes to it->

  dancingLinks   dl(it->numOminoes(), board->numOpen(), totalPlacements);

  for (int32 hh=0; hh<it->numOminoes(); hh++) {
    ominoPlacements[hh] = 0;
    usedPlacements[hh]  = 0;
  }

  for (it->start(); it->valid(); it->next()) {
    hexomino h = it->omino();

    for (int32 y=0; y<board->Ysize(); y++) {
      for (int32 x=0; x<board->Xsize(); x++) {
        if (board->isBlocked(x, y, h) == false) {

          if ((forced[h.id] == false) ||
              (force[pair<int32,int32>(h.id, ominoPlacements[h.id])] == true)) {
            dl.addRow(h, *board, x, y);
          }

          ominoPlacements[h.id]++;
        }
      }
    }
  }

  fprintf(stdout, "Used %d cells in the matrix.\n", dl._nextCell);

  dl.search(0, board);

  fprintf(stdout, "Finished.\n");

  exit(0);
}

