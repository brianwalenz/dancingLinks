

#ifndef DANCINGLINKS_H
#define DANCINGLINKS_H

#include "utility.H"
#include "hexomino.H"
#include "boardFrame.H"


//  A column object.
//
//  Includes one special object, the root.  Only L anr R are valid in the root.

class column_t {
public:
  char       N[16];
  uint32     C;      //  The column header for this column.
};


class cell_t {
public:
  uint32     id;

  uint32     L;      //  Left or right pointer
  uint32     R;

  uint32     U;      //  Up or down pointer
  uint32     D;

  uint32     col;    //  Points to the column header cell for this column.
  uint32     row;    //  Points to the row header cell (the omino id) for this row.
  uint32     sco;    //  Size, number of 1's in this column.
};



class dancingLinks {
public:
  dancingLinks(int32  nOminoes, int32 nCells, int32 nPositions) {
    _maxOminoes = nOminoes;
    _maxCells   = nCells;
    _maxRows    = nPositions;

    _columns    = new column_t   [ _maxOminoes + _maxCells + 1];
    _rows       = new cell_t   * [ _maxRows ];

    _cells      = new cell_t     [(_maxOminoes + _maxCells) * _maxRows];

    _solution   = new cell_t   * [ _maxRows ];

    _nextRow    = 0;
    _nextCell   = 0;

    //  Initialize cells.

    for (int32 cc=0; cc<(_maxOminoes + _maxCells) * _maxRows; cc++) {
      _cells[cc].id  = cc;
      _cells[cc].L   = UINT32_MAX;
      _cells[cc].R   = UINT32_MAX;
      _cells[cc].U   = UINT32_MAX;
      _cells[cc].D   = UINT32_MAX;
      _cells[cc].col = UINT32_MAX;
      _cells[cc].row = UINT32_MAX;
      _cells[cc].sco = 0;
    }

    //  Initialize columns, so they're first in the list.

    int32  nCols = 1 + _maxOminoes + _maxCells;

    for (int32 cc=0; cc<nCols; cc++) {
      _columns[cc].N[0] = 0;
      _columns[cc].C    = cc;

      _cells[cc].L      = (cc > 0)         ? cc - 1 : nCols - 1;
      _cells[cc].R      = (cc + 1 < nCols) ? cc + 1 : 0;

      _cells[cc].U      = cc;           //  So far, only us in the column list.
      _cells[cc].D      = cc;

      _cells[cc].col    = cc;           //  Column header is this cell
      _cells[cc].row    = UINT32_MAX;   //  Meaningless.
    }

    //fprintf(stderr, " %3u <- %3u -> %3u\n", _cells[0].L, 0, _cells[0].R);

    //  Set omino name.

    for (int32 cc=0; cc<_maxOminoes; cc++) {
      sprintf(_columns[1 + cc].N, "o%d", cc);
    }

    for (int32 cc=0; cc<_maxCells; cc++) {
      sprintf(_columns[1 + cc + _maxOminoes].N, "p%d", cc);
    }

    //  And move past the used cells.

    _nextCell = nCols;
  };

  ~dancingLinks() {
    delete [] _cells;
    delete [] _columns;
  };

public:
  void         addRow(hexomino &h, boardFrame &b, int32 x, int32 y) {

    //  For convenience, copy pointers to the cells we're going to be using to a small array.

    int32     nf = h.numOmino();
    int32     nc = h.numOmino() + 1;
    cell_t   *c[nc];

    //  Grab new cells for the omino and the six positions it is placed in.

    for (int32 ii=0; ii<nc; ii++) {
      c[ii]      = &_cells[_nextCell++];
      c[ii]->row = c[0]->id;
    }

    _rows[_nextRow++] = c[0];

    //  Set column pointers for all the cells we use here.
    //    1     -- because the first cell is a sentinal header cell
    //    h.id  -- the ident of the hexomino we're working with

    c[0]->col = 1 + h.id;

    for (int32 ii=0; ii<nf; ii++)
      c[1+ii]->col = 1 + _maxOminoes + b.getIndex(x + h.x[ii], y + h.y[ii]);

#if 0
    fprintf(stderr, "addRow()-- row starting at cell %4d is omino %4s -- ",
            c[0]->row,
            _columns[ c[0]->col ].N);
    for (int32 ii=0; ii<nf; ii++)
      fprintf(stderr, " %4s", _columns[ c[1+ii]->col ].N);
    fprintf(stderr, "\n");
#endif

    //  Add one to each column score.

    for (int32 ii=0; ii<nc; ii++)
      _cells[ c[ii]->col ].sco++;

    //  Set L/R pointers.

    c[0]->L = c[nf]->id;
    c[0]->R = c[ 1]->id;

    for (int32 ii=1; ii<nf; ii++) {
      c[ii]->L = c[ii-1]->id;
      c[ii]->R = c[ii+1]->id;
    }

    c[nf]->L = c[nf-1]->id;
    c[nf]->R = c[   0]->id;

    //  Set U/D pointers.

    for (uint32 ii=0; ii<nc; ii++) {
      cell_t  *header = &_cells[ c[ii]->col  ];
      cell_t  *last   = &_cells[ header->U   ];

      assert(last->D == header->id);

      c[ii]->U = header->U;
      c[ii]->D = header->id;

      header->U = c[ii]->id;
      last->D   = c[ii]->id;
    }
  };


  void         dumpMatrix(FILE *F) {
    
  };


  //  Infinite loop in here

  void         cover(uint32 c) {
    //fprintf(stderr, "cover cell %u\n", c);

    _cells[ _cells[c].R ].L = _cells[c].L;
    _cells[ _cells[c].L ].R = _cells[c].R;

    for (uint32 i = _cells[c].D; i != c; i = _cells[i].D) {
      for (uint32 j = _cells[i].R; j != i; j = _cells[j].R) {
        _cells[ _cells[j].D ].U = _cells[j].U;
        _cells[ _cells[j].U ].D = _cells[j].D;

        _cells[ _cells[j].col ].sco--;
      }
    }
  };


  void         uncover(uint32 c) {
    //fprintf(stderr, "uncover cell %u\n", c);

    for (uint32 i = _cells[c].U; i != c; i = _cells[i].U) {
      for (uint32 j = _cells[i].L; j != i; j = _cells[j].L) {
        _cells[ _cells[j].col ].sco++;

        _cells[ _cells[j].D ].U = j;
        _cells[ _cells[j].U ].D = j;
      }
    }

    _cells[ _cells[c].R ].L = c;
    _cells[ _cells[c].L ].R = c;
  };


  void         printSolution(int32 k) {

    fprintf(stdout, "search(%d)-- SOLVED!\n", k);

    for (int32 ss=0; ss<k; ss++) {
      fprintf(stdout, "search(%d)-- placement %2d is omino %s at",
              k, ss,
              _columns[ _solution[ss]->col ].N);

      for (int32 oid = _cells[ _solution[ss]->row ].R; oid != _solution[ss]->row; oid = _cells[oid].R)
        fprintf(stdout, " %s", _columns[ _cells[oid].col ].N);

      fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
  };


  bool         search(int32 k) {

    if (_cells[0].R == 0) {
      printSolution(k);
      return(true);
    }

    //  Find the column with the smallest size

    uint32  c     = UINT32_MAX;
    uint32  cSize = UINT32_MAX;

    for (uint32 cc = _cells[0].R; cc != 0; cc = _cells[cc].R) {
      if (_cells[cc].sco < cSize) {
        c     = cc;
        cSize = _cells[cc].sco;
      }
    }

    //  Log something.

    //if (k < 20)
    //  fprintf(stderr, "search(%d)-- column c %u\n", k, c);

    //  Cover column c.  Remove c from the header list, then remove all rows in
    //  the column list of c from the other column lists they're in (and
    //  decrement the score of those columns too).

    cover(c);

    //  Now try each row r in the solution.

    for (uint32 r = _cells[c].D; r != c; r = _cells[r].D) {
      _solution[k] = &_cells[ _cells[r].row ];  //  Save the row we just placed

      //fprintf(stderr, "search(%d)-- column %u down %u\n", k, c, r);

      for (uint32 j = _cells[r].R; j != r; j = _cells[j].R)
        cover(_cells[j].col);

      if (search(k+1) == true) {
      //  fprintf(stderr, "search(%d)-- SOLVED - r %d\n", k, r);
      }

      //assert(r == _solution[k]);
      assert(c == _cells[r].col);

      for (uint32 j = _cells[r].L; j != r; j = _cells[j].L)
        uncover(_cells[j].col);
    }

    uncover(c);

    //fprintf(stderr, "search(%d)-- no solution\n", k);
    return(false);    
  };


public:
  int32       _maxOminoes;
  int32       _maxCells;
  int32       _maxRows;

  column_t   *_columns;    //  Object at the top of each row; the header cell
  cell_t    **_rows;       //  Pointer to the first cell in each row; this is the omino cell

  cell_t     *_cells;      //  Array data.

  cell_t    **_solution;   //  Pointer to the first cell in a solution; depth k

  int32       _nextRow;
  int32       _nextCell;
};



bool testFlipRotate(void);
void countOneSided(void);
void countFixed(void);


#endif  //  DANCINGLINKS_H
