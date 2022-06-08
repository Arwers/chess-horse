#include <iostream>
#define CHESSBOARD_SIZE 7
typedef struct Points {
  int x;
  int y;
} Point;

int move( int** pChessBoard, int nDim, int move, int x, int y,
          int* px, int* py, Point* pHorseMoves );

int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves );

int** createChessboard( int nDim );

void freeChessboard( int*** pChessBoard );

void printChessBoard( int** pChessBoard, int nDim );

int main( int argc, char* argv[] ) {
  int** p = createChessboard( 7 );
  printChessBoard( p, 7 );
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

