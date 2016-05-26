// Christina Holmes, Group 21
// Marshall McGarity, Tiffany Pittman, Stewart Hawk
// assign09
// 4/16/15
// We spoke with Ms. Hundley about our intColMax function and the hours[] array.
/* 
   This program reads the 2015 softball data file and, using 2D arrays, prints out the 
   max, min, and mean number of runs scored by Auburn and by the opponent for all games
   and specifically for SEC games. It also prints which games went into extra innings
   and how long the longest game played lasted.
*/

#include <stdio.h>
// ******* CONSTANT *******
#define FILENAME "2015_AU_softball09.txt"
#define MAXGAMES  50    // estimated number of games in season
#define NUMSEC    25    // estimated number of SEC games in season
#define SECDODE   '*'   // code for SEC games
#define NUMINNINGS 7    // number of innings in a game
#define NUMCOLS    4    // number of columns in game info array
#define AU_COL     0    // Auburn runs in 1st column of game info array
#define OPP_COL    1    // Opp runs in 2nd column of game info array
#define INN_COL    2    // no. of innings in 3rd column of game info array
#define ATT_COL    3    // attendance in 4th column of game info array
#define MIN_IN_HOUR 60  // number of minutes in an hour

// ******** FUNCTION PROTOTYPES *********
int getFileData (char code[], int gameStats[][NUMCOLS], double hours[]);
void printSummary (char code[], int gameStats[][NUMCOLS], double hours[], int numGames);
int getSecGames (char code[], int arrayAll[][NUMCOLS], int numGames, int arraySec[][NUMCOLS]);
int extraInnings (int gameStats[][NUMCOLS], int numGames, int extra[]);
int intColMax (int x[][NUMCOLS], int n, int colNum);
int intColMin (int x[][NUMCOLS], int n, int colNum);
double intColMean (int x[][NUMCOLS], int n, int colNum);
double doubleMax (double x[], int n);
int gameInfo[MAXGAMES][NUMCOLS];

int main()
{
   int numGames = 0;
   double hours[MIN_IN_HOUR];
   char code[MAXGAMES];
   double gameLength[MAXGAMES];
   int gameStats[MAXGAMES][NUMCOLS];
      numGames = getFileData(code, gameInfo, gameLength);
   if (numGames > 0)
      printSummary(code, gameInfo, gameLength, numGames);
   else
      printf ("No data read. Program ending.");    
   //fclose(filePtr);
   return 0;
}

// ****** FUNCTION DEFINITIONS ******
int getFileData (char code[], int gameStats[][NUMCOLS], double hours[])
{
   int t = 0;
   char cHold;
   int iHold;
   double gameMinutes, gameHours, maxHours;
   
   FILE * filePtr;
   filePtr = fopen(FILENAME, "r");
   if (filePtr == NULL)
      printf ("File open error.\n");
   else
   {
      while (fscanf(filePtr," %c %d%c%d%c%d%d%c%d%c%d%d%d%lf%c%lf", &code[t], &gameStats[t][AU_COL], &cHold, &iHold, &cHold, &iHold, 
      &gameStats[t][OPP_COL],&cHold, &iHold,&cHold, &iHold, &gameStats[t][INN_COL], &gameStats[t][ATT_COL], &gameHours, &cHold, &gameMinutes) != EOF)
        hours[t] = gameHours + ((double) gameMinutes/MIN_IN_HOUR);
       /* maxHours = hours[0];
        if (hours[t] > maxHours)
        {
            maxHours = hours[t];
        }*/
         t++;        
   }
   return t;
   //fclose(filePtr);
}
void printSummary (char code[], int gameStats[][NUMCOLS], double hours[], int numGames)
{
   //int arraySecAub[NUMSEC][NUMCOLS];
   //int arraySecOpp[NUMSEC][NUMCOLS];
   int arraySec[NUMSEC][NUMCOLS];
   int secGames = getSecGames(code, gameStats, numGames, arraySec);
   //int oppSecGames = getSecGames(code, gameStats, numGames, arraySec);
   int count, t;
   int extra[MAXGAMES];
   double intMax[MAXGAMES];
   double longestGame, maxHours;
   //maxHours = hours[0];
   //hours[t] = gameHours + ((double) gameMinutes/MIN_IN_HOUR);
 
   
   printf("       2015 AU Softball Summary\n");
   printf("                #games  Min   Mean  Max\n");
   printf("Runs scored-all    %2d    %d    %.1f    %2d\n", numGames, intColMin(gameStats, numGames, AU_COL), intColMean(gameStats, numGames, AU_COL), intColMax(gameStats, numGames, AU_COL));
   printf("Runs allowed-all         %d    %.1f    %2d\n", intColMin(gameStats, numGames, OPP_COL), intColMean(gameStats, numGames, OPP_COL), intColMax(gameStats, numGames, OPP_COL));
   printf("Runs scored-SEC    %2d    %d    %.1f    %2d\n", secGames, intColMin(arraySec, secGames, AU_COL),intColMean(arraySec, secGames, AU_COL), intColMax(arraySec, secGames, AU_COL)); 
   printf("Runs allowed-SEC         %d    %.1f    %2d\n\n",  intColMin(arraySec, secGames, OPP_COL),intColMean(arraySec, secGames, OPP_COL), intColMax(arraySec, secGames, OPP_COL));      
   printf("Games with extra innings:\n");
   for (count = 0; count < extraInnings(gameStats, numGames, extra); count++)
   {
         printf(" %d ", extra[count]);
   }
   /*for (t=0; t<MAXGAMES; t++)
   {
      if (hours[t] > maxHours)
      {
         maxHours = hours[t];
      }
   }*/
   printf("\nLongest game played: %.2f hours\n", doubleMax (hours, numGames));
  
   
}
   
int getSecGames (char code[], int arrayAll[][NUMCOLS], int numGames, int arraySec[][NUMCOLS])
{
   int k, j;
   int i=0;
   for (k=0; k<numGames; k++)
   {
      if (code[k] == SECDODE)
      {
         for (j=0; j<NUMCOLS; j++)
            arraySec[i][j] = arrayAll[k][j];
         //arraySec[i][AU_COL] = arrayAll[k][AU_COL];
         //arraySec[i][OPP_COL] = arrayAll[k][OPP_COL];
         i++;
      }
   }
   return i;
}
//int extraInnings (int gameStats[][NUMCOLS], int numGames, int extra[])
int extraInnings (int arrayAll[][NUMCOLS], int numGames, int extra[])
{
   int n, j=0;
   for (n=0; n<numGames; n++)
   {
      //if (gameStats[n][INN_COL] > NUMINNINGS)
      if (arrayAll[n][INN_COL] > NUMINNINGS)
      {
         extra[j] = n + 1;
         j++;
      }
   }
   return j;
   
}
int intColMax (int x[][NUMCOLS], int n, int colNum)
{
   int k, j;
   int max_x;
   
   max_x = x[0][colNum];
   for (k=1; k<n;k++)
   {
      
      if (x[k][colNum] > max_x)
         max_x = x[k][colNum];
      
         
   }
   return max_x;
}
int intColMin (int x[][NUMCOLS], int n, int colNum)
{
   int k,j;
   int min_x;
   
   min_x = x[0][colNum];
   for (k=1; k<n; k++)
   {
      if (x[k][colNum] < min_x)
         min_x = x[k][colNum];
   }
   return min_x;
}
double intColMean (int x[][NUMCOLS], int n, int colNum)
{
   int k, j;
   double sum = 0;
   
   for (k=0; k<n; k++)
   {
      sum += x[k][colNum];
   }
   return sum/n;
}
double doubleMax (double x[], int n)
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