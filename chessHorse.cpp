#include <iostream>
#define CHESSBOARD_SIZE 7
typedef struct Points {
  int x;
  int y;
} Point;

typedef enum { FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH, EIGHTH };

int move( int** pChessBoard, int nDim, int move, int x, int y,
          int* px, int* py, Point* pHorseMoves );

int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves );

int** createChessboard( int nDim );

void freeChessboard( int*** pChessBoard );

void printChessBoard( int** pChessBoard, int nDim );

int main( int argc, char* argv[] ) {
  int** p = createChessboard( 7 );
  printChessBoard( p, 7 );
  freeChessboard( &p );
}

int** createChessboard( int nDim ) {
  
  int** pTab2D = ( int** ) calloc ( nDim, sizeof( int* ) );
  if( !pTab2D ) {
    printf( "ERROR - createChessboard() - 1" );
    return 0;
  }
  int** pTemp = pTab2D;

  for( int row = 0; row < nDim; row++ ) {
    
    *pTemp = ( int* ) calloc ( nDim, sizeof( int ) );
    if( !*pTemp ) {
      printf( "ERROR - createChessboard() - 2" );
      return 0;
    }
    pTemp++;
  }
  return pTab2D;
}

void printChessBoard( int** pChessBoard, int nDim ) {

  for( int row = 0; row < nDim; row++ ) {
    int* pRows = *pChessBoard;
    
    for( int element = 0; element < nDim; element++ ) {
      if( element==( nDim-1 ) ) printf( "%d\n", *pRows );
      else printf( "%d ", *pRows );
      pRows++;
    }
  }
}

void freeChessboard( int*** pChessBoard ) {
  
  int** pRows = *pChessBoard;
  
  for( int i = 0; i < CHESSBOARD_SIZE; i++ ) {
    free( *pRows );
    pRows++;
  }
  free( *pChessBoard );
  pChessBoard = NULL;
}

int move( int** pChessBoard, int nDim, int move, int x, int y,
          int* px, int* py, Point* pHorseMoves ) {
  
  // nowe współrzędne
  *px = x + pHorseMoves[ move ].x;
  *py = y + pHorseMoves[ move ].y;

  if( *px >= 0 && *px < nDim && *py >= 0 && *py < nDim ) { // sprawdzamy czy ruch jest poprawny
    if( pChessBoard[ *px ][ *py ] == 0 ) return 1; // sprawdzamy czy byliśmy już w tym miejscu
  }

  return 0;
}

int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves ) {

  // wstawic kolejny numer ruchu
  pChessBoard[ x ][ y ] = moveNo;
  // jesli koniec to zwracamy 1  (ilosc ruchow porownac z iloscia pozycji na szachownicy)
  if( moveNo<=nDim*nDim ) return 1;
  else {
    // zdefiniowac nowe pozycje x i y
    int xNew = 0;
    int yNew = 0;
    // sprawadzic wszystkie mozliwosci ruchu (petla od FIRST do EIGHTH)
    for( int i = FIRST; i<=EIGHTH; i++ ) {
      // jesli ruch do nowej poycji mozliwy
      if( move( pChessBoard, CHESSBOARD_SIZE, i, x, y, &xNew, &yNew, pHorseMoves ) ) {
        // to rekurencyjnie wykonac ruch moveNo+1
        // jesli zwrocono 1 z rekurencji to zwrocic 1;
        if( root( pChessBoard, CHESSBOARD_SIZE, moveNo+1, xNew, yNew, pHorseMoves ) ) return 1;
      }
    }
  }
  // jezeli wracamy to ustawiamy w pChessBoard[x][y] na 0 bo ten ruch byl zly
  pChessBoard[ x ][ y ] = 0;
  return 0;
}




