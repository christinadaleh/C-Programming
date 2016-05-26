#include <stdio.h> 
//*****CONSTANT***** 
#define FILENAME "2015_AU_softball09.txt" 
#define MAXGAMES 50 // estimated number of games in season 
#define NUMSEC 25 // estimated number of SEC games in season 
#define SECCODE '*' // code for SEC games 
#define NUMINNINGS 7 // number of innings in a game 
#define NUMCOLS 4 // number of columns in game info array 
#define AU_COL 0 // Auburn runs in 1st column of game info array 
#define OPP_COL 1 // Opp runs in 2nd column of game info array 
#define INN_COL 2 // no. of innings in 3rd column of game info array 
#define ATT_COL 3 // attendance in 4th column of game info array 
#define MIN_IN_HOUR 60 // number of minutes in an hour 
// FUNCTION PROTOTYPES ============================================================================ 
int getFileData ( char code[], int gameStats[][NUMCOLS], double hours[] ); 
void printSummary( char code[], int gameStats[][NUMCOLS], double hours[], int numGames ); 
int getSecGames ( char code[], int arrayAll[][NUMCOLS], int numGames, int arraySec[][NUMCOLS] ); 
int extraInnings( int gameStats[][NUMCOLS], int numGames, int extra[] ); 
int intColMax ( int x[][NUMCOLS], int n, int colNum ); 
int intColMin ( int x[][NUMCOLS], int n, int colNum ); 
double intColMean( int x[][NUMCOLS], int n, int colNum ); 
double doubleMax ( double x[], int n ); 
// MAIN PROTOTYPES ===============================================================================
int main() 
{
    char code[MAXGAMES]; 
    int gameInfo[MAXGAMES][NUMCOLS]; 
    double gameLength[MAXGAMES]; 
    int numGames = 0; 
    // INPUT 
    numGames = getFileData( code, gameInfo, gameLength ); 
    if (numGames > 0) 
    { 
      // OUTPUT 
      printSummary( code, gameInfo, gameLength, numGames ); 
    }
    else 
    { 
      printf("No data read. Program ending."); 
    }
    return 0; 
}
// FUNCTION DEFINITIONS ========================================================================== 
// read file. store selected data in 1D integer arrays =========================================== 
int getFileData ( char code[], int gameStats[][NUMCOLS], double hours[] ) 
{ int g = 0, // counter 
      hour, min, // game time 
      iHold; // hold integers not saved 
 char cHold; // hold characters not saved 
 FILE * filePtr; // file pointer 
 //*****INPUT***** 
 //open input data file 
 filePtr = fopen(FILENAME,"r"); 
 // check for good file open 
 if (filePtr == NULL) 
   printf("File open error.\n"); 
 else {
   while( fscanf( filePtr, " %c %d%c%d%c%d %d%c%d%c%d %d %d %d%c%d", &code[g], &gameStats[g][AU_COL],&cHold,&iHold,&cHold,&iHold, // Auburn stats
    &gameStats[g][OPP_COL],&cHold,&iHold,&cHold,&iHold, // opp stats
     &gameStats[g][INN_COL],&gameStats[g][ATT_COL],&hour,&cHold,&min ) != EOF ) 
     { 
         hours[g] = hour + (double)min/MIN_IN_HOUR; g++; } // while 
     } // else
      return g; 
}
// print statistics summary report ========================================================== 
void printSummary( char code[], int gameStats[][NUMCOLS], double hours[], int numGames ) 
{ 
   int g; 
   int arraySec[NUMSEC][NUMCOLS], extra[MAXGAMES]; 
   int numSecGames, numExtra; 
   int minRuns, maxRuns; 
   double aveRuns; 
   
   printf( "       2015 AU Softall Summary\n" ); 
   printf( "                 #games Min Mean Max\n" ); 
   
   // all games runs 
   // max/mean/min AU runs scored: all, with # of games
    
   printf( "Runs scored-all    %2d  %2d  %4.1f  %2d\n", numGames,intColMin(gameStats,numGames,AU_COL), 
         intColMean(gameStats,numGames,AU_COL),intColMax(gameStats,numGames,AU_COL) );
         
    // max/mean/min runs allowed: all 
    
   printf( "Runs allowed-all       %2d  %4.1f  %2d\n", intColMin(gameStats,numGames,OPP_COL),
       intColMean(gameStats,numGames,OPP_COL),intColMax(gameStats,numGames,OPP_COL) ); 
       
  // SEC games runs 
  // get the Auburn runs for the SEC game 
  
  numSecGames = getSecGames( code, gameStats, numGames, arraySec ); 
  
  // max/mean/min AU runs scored: SEC, with # of games 
  
  printf( "Runs scored-SEC    %2d  %2d  %4.1f  %2d\n", numSecGames,intColMin(arraySec,numSecGames,AU_COL), 
      intColMean(arraySec,numSecGames,AU_COL), intColMax(arraySec,numSecGames,AU_COL) );
      
 // max/mean/min runs allowed: SEC 
 printf( "Runs allowed-SEC       %2d  %4.1f  %2d\n", intColMin(arraySec,numSecGames,OPP_COL), 
      intColMean(arraySec,numSecGames,OPP_COL),intColMax(arraySec,numSecGames,OPP_COL) );
      
// game(s) with extra innings; regular game 7 innings 
numExtra = extraInnings( gameStats, numGames, extra ); 
printf( "\nGames with extra innings:\n"); 
if (numExtra > 0 ) 
{ 
   for ( g=0; g<numExtra; g++ ) 
   { 
      printf( " %d", extra[g] );
   } 
   // end for g 
   printf( "\n" );
 } // if numExtra 
 else 
 {
    printf( "none\n" ); 
} // end else 
// longest game for all and SEC 
printf( "\nLongest game played: %.2f hours\n", doubleMax( hours, numGames ) );
} // end printSummary

// copy information for SEC games to another array ================================================ 
int getSecGames( char code[], int arrayAll[][NUMCOLS], int numGames, int arraySec[][NUMCOLS] )
{ 
   int g, c, count = 0; 
   for ( g=0; g<numGames; g++ ) 
   {
       if( code[g] == SECCODE ) 
       { 
         for ( c=0; c<NUMCOLS; c++ ) 
         { 
            arraySec[count][c] = arrayAll[g][c]; 
         } // end for c count ++
       } // end if code 
   } // end for g 
   return count;
}
// return the maximum value in the array x with n elements ======================================== 
int intColMax ( int x[][NUMCOLS], int n, int colNum ) 
{
    int k; 
    double max_x; 
    max_x = x[0][colNum];
    for ( k=1; k<n; k++ ) 
    {
       if ( x[k][colNum] > max_x ) 
       {
          max_x = x[k][colNum]; 
       } // end if x 
    } // for k 
    return max_x;
}
// return the minimum value in the array x with n elements ======================================== 
int intColMin ( int x[][NUMCOLS], int n, int colNum ) 
{
 int k; 
 double min_x; 
 min_x = x[0][colNum]; 
 for ( k=1; k<n; k++ ) 
 {
    if ( x[k][colNum] < min_x ) 
    {
       min_x = x[k][colNum]; 
    } 
 }
 return min_x;
} 
// return the average value of the array x with n elements ======================================== 
double intColMean ( int x[][NUMCOLS], int n, int colNum ) 
{
   int k; 
   int sum=0; 
   for ( k=0; k<n; k++ ) 
   { 
      sum += x[k][colNum]; 
   }
   return (double)sum/n; 
}
// return a list of the games with extra innings ================================================== 
int extraInnings( int arrayAll[][NUMCOLS], int numGames, int extra[] ) 
{
    int g, count=0; 
    for ( g=0; g<numGames; g++ ) 
    { 
      if ( arrayAll[g][INN_COL] > NUMINNINGS ) 
      {
          extra[count] = g+1;
          count++; 
      } // end if arrayAll 
    } // end g return count; 
    return count;
}

// return the maximum value in the array x with n elements ======================================== 
double doubleMax( double x[], int n )
{
    int k; 
    double max_x; 
    max_x = x[0]; 
    for ( k=1; k<n; k++ ) 
    { 
      if ( x[k] > max_x ) 
         max_x = x[k]; 
    }
    return max_x; 
}