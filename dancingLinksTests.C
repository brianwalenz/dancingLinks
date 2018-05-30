
#include "dancingLinks.H"
#include "boardFrame.H"
#include "hexomino.H"



bool
testFlipRotate(void) {
  hexomino  a(3);
  hexomino  b(3);

  ;            if (a == b)  fprintf(stderr, "0n true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "1n true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "2n true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "3n true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "4n true\n");  b.report(stderr);
  b.flipY();   if (a == b)  fprintf(stderr, "0f true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "1f true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "2f true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "3f true\n");  b.report(stderr);
  b.rotate();  if (a == b)  fprintf(stderr, "4f true\n");  b.report(stderr);

  return(true);
}


  //  Count one-sided.
  //
  //  The one-sided set includes the normal free set, and the set of the free ominoes flipped,
  //  excluding the ones that are the same.
  //
void
countOneSided(void) {
  int32   oneSided = 0;

  for (int32 ii=0; ii<35; ii++) {
    hexomino a(ii);

    hexomino b(ii);
    hexomino c(ii);
    hexomino d(ii);
    hexomino e(ii);

    b.flipY();
    c.flipY();  c.rotate();
    d.flipY();  d.rotate();  d.rotate();
    e.flipY();  e.rotate();  e.rotate();  e.rotate();

    if ((a == b) ||
        (a == c) ||
        (a == d) ||
        (a == e)) {
      fprintf(stderr, "%02d 1  ", ii);
      oneSided += 1;
    } else {
      fprintf(stderr, "%02d 2  ", ii);
      oneSided += 2;
    }

    if ((ii % 7) == 6) {
      fprintf(stderr, "\n");
    }
  }

  fprintf(stderr, "one sided %d\n", oneSided);
}



//  Any of the 8 flips/rotations are counted, as long as they are distinct.
//
void
countFixed(void) {
  int32   fixed = 0;

  for (int32 ii=0; ii<35; ii++) {
    hexomino h[8];

    h[0].initialize(ii);
    h[1].initialize(ii);  h[1].rotate();
    h[2].initialize(ii);  h[2].rotate();  h[2].rotate();
    h[3].initialize(ii);  h[3].rotate();  h[3].rotate();  h[3].rotate();
    h[4].initialize(ii);  h[4].flipX();
    h[5].initialize(ii);  h[5].flipX();   h[5].rotate();
    h[6].initialize(ii);  h[6].flipX();   h[6].rotate();  h[6].rotate();
    h[7].initialize(ii);  h[7].flipX();   h[7].rotate();  h[7].rotate();  h[7].rotate();

    //  Add one assuming it's different under rotations and flips.

    for (int32 b=0; b<8; b++) {
      fixed++;

      //  But if we find a rotation of flip that is the same after us,
      //  do not count this one.  Wait until the last to count.

      for (int32 c=b+1; c<8; c++) {
        if (h[b] == h[c]) {
          fixed--;
          break;
        }
      }
    }
  }

  fprintf(stderr, "fixed %d\n", fixed);
}




