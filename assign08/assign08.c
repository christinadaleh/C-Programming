// Christina Holmes, Group 11
// Marshall McGarity, Tiffany Pittman, Stewart Hawk
// assign08
// 4/8/15
// We spoke with Josh Jablonowski about the nested minimum, mean, and max integer arrays.
/* This program reads the file with AU's 2015 softball stats and using arrays, calculates the number of runs scored
   by Auburn and by the opponents (for all games and also specifically for SEC matchups). It then calculates the minimum,
   mean, and maximum value. Finally it scans and prints which games go into extra innings.
*/

#include <stdio.h>
// ******* CONSTANT *******
#define FILENAME "2015_AU_softball.txt"
#define MAXGAMES  50    // estimated number of games in season
#define NUMSEC    25    // estimated number of SEC games in season
#define SECDODE   '*'   // code for SEC games
#define NUMINNINGS 7    // number of innings in a game

// ******** FUNCTION PROTOTYPES *********
int getFileData (char code[], int auRuns[], int oppRuns[], int innings[], int attend[]);
void printSummary (char code[], int auRuns[], int oppRuns[], int innings[], int attend[], int numGames);
int getSecGames (char code[], int arrayAll[], int numGames, int arraySec[]);
int extraInnings (int innings[], int numGames, int extra[]);
int intMax (int x[], int n);
int intMin (int x[], int n);
double intMean (int x[], int n);

int main()
{
   int numGames = 0;
   char code[MAXGAMES];
   int auRuns[MAXGAMES], oppRuns[MAXGAMES], innings[MAXGAMES], attend[MAXGAMES]; 
   
   numGames = getFileData(code, auRuns, oppRuns, innings, attend);
   if (numGames > 0)
      printSummary(code, auRuns, oppRuns, innings, attend, numGames);
   else
      printf ("No data read. Program ending.");    
   //fclose(filePtr);
   return 0;
}

// ****** FUNCTION DEFINITIONS ******
int getFileData (char code[], int auRuns[], int oppRuns[], int innings[], int attend[])
{
   int t = 0;
   char cHold;
   int iHold;
   
   FILE * filePtr;
   filePtr = fopen(FILENAME, "r");
   if (filePtr == NULL)
      printf ("File open error.\n");
   else
   {
      while (fscanf(filePtr," %c %d%c%d%c%d%d%c%d%c%d%d%d%d%c%d", &code[t], &auRuns[t], &cHold, &iHold, &cHold, &iHold, 
      &oppRuns[t],&cHold, &iHold,&cHold, &iHold, &innings[t], &attend[t], &iHold, &cHold, &iHold) != EOF)
         t++;           
   }
   return t;
}
void printSummary (char code[], int auRuns[], int oppRuns[], int innings[], int attend[], int numGames)
{
   int arraySecAub[NUMSEC];
   int arraySecOpp[NUMSEC];
   int secGames = getSecGames(code, auRuns, numGames, arraySecAub);
   int oppSecGames = getSecGames(code, oppRuns, numGames, arraySecOpp);
   int count;
   int extra[MAXGAMES];
 
   
   printf("       2015 AU Softball Summary\n");
   printf("                #games  Min   Mean  Max\n");
   printf("Runs scored-all    %2d    %d    %.1f    %2d\n", numGames, intMin(auRuns, numGames), intMean(auRuns, numGames), intMax(auRuns, numGames));
   printf("Runs allowed-all         %d    %.1f    %2d\n", intMin(oppRuns, numGames), intMean(oppRuns, numGames), intMax(oppRuns, numGames));
   printf("Runs scored-SEC    %2d    %d    %.1f    %2d\n", secGames, intMin(arraySecAub, secGames),intMean(arraySecAub, secGames), intMax(arraySecAub, secGames)); 
   printf("Runs allowed-SEC         %d    %.1f    %2d\n\n",  intMin(arraySecOpp, secGames),intMean(arraySecOpp, oppSecGames), intMax(arraySecOpp, oppSecGames));      
   printf("Games with extra innings:\n");
   for (count = 0; count < extraInnings(innings, numGames, extra); count++)
   {
         printf(" %d ", extra[count]);
   }
   
}
int getSecGames (char code[], int arrayAll[], int numGames, int arraySec[])
{
   int k;
   int i=0;
   for (k=0; k<numGames; k++)
   {
      if (code[k] == SECDODE)
      {
         arraySec[i] = arrayAll[k];
         i++;
      }
   }
   return i;
}
int extraInnings (int innings[], int numGames, int extra[])
{
   int n, j=0;
   for (n=0; n<numGames; n++)
   {
      if (innings[n] > NUMINNINGS)
      {
         extra[j] = n + 1;
         j++;
      }
   }
   return j;
   
}
int intMax (int x[], int n)
{
   int k;
   int max_x;
   
   max_x = x[0];
   for (k=1; k<=n-1;k++)
   {
      if (x[k] > max_x)
         max_x = x[k];
         
   }
   return max_x;
}
int intMin (int x[], int n)
{
   int k;
   int min_x;
   
   min_x = x[0];
   for (k=1; k<n; k++)
   {
      if (x[k] < min_x)
         min_x = x[k];
   }
   return min_x;
}
double intMean (int x[], int n)
{
   int k;
   double sum = 0;
   
   for (k=0; k<n; k++)
   {
      sum += x[k];
   }
   return sum/n;
}

