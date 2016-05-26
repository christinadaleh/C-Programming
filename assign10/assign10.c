// Christina Holmes, Group 10
// Tiffany Pittman, Marshall McGarity, Stewart Hawk
// assign10
// 4/23/15
// We worked on this alone with only the course material.
/* This program reads in the 2015 AU Softball stats and prints them in a chart
   using strings, 2D arrays, and 1D arrays, while marking games with high
   attendance, games with longer than average times, and prints those averages. */

#include <stdio.h>
#include <string.h>
//******CONSTANTS********
#define FILENAME "2015_AU_softball_SEC.txt"
#define MAXGAMES     25 // estimated number of SEC games in season
#define NUMINNINGS    7 // number of innings in a game
#define NUMCOLS       4 // numeber of columnds in game info array
#define AU_COL        0 // Auburn runs in 1st column of game info array
#define OPP_COL       1 // Opp runs in 2nd column of game info array
#define INN_COL       2 // no. of innings in 3rd column of game info arrray
#define ATT_COL       3 // attendance in 4th column of game info array
#define MIN_IN_HOUR  60 // number of minutes in an hour
#define TITLE_LEN    27 // title length
#define DATE_LEN     12 // max length of date
#define TEAM_LEN     15 // max length of opp team name\\
   
//*****FUNCTION PROTOTYPES*****
int getFileData (char title[], char date[][DATE_LEN], char team[][TEAM_LEN],
                 int gameStats[][NUMCOLS], double hours[]);
void printSummary (char title[], char date[][DATE_LEN], char team[][TEAM_LEN],
                   int gameStats[][NUMCOLS], double hours[], int numGames);
               
//*****MAIN*****
int main()
{
   char title[TITLE_LEN],
        date[MAXGAMES][DATE_LEN],
        team[MAXGAMES][TEAM_LEN];
   int gameStats[MAXGAMES][NUMCOLS],
       numGames;
   double hours[MAXGAMES];
   // calculate number of games
   numGames = getFileData(title, date, team, gameStats, hours);
   if (numGames < 1)
      printf ("No data available.\n");
   else
      printSummary (title, date, team, gameStats, hours, numGames);
}
                   
//*****FUNCTION DEFINITIONS*****
int getFileData (char title[], char date[][DATE_LEN], char team[][TEAM_LEN],
                 int gameStats[][NUMCOLS], double hours[])
{
   int n = 0;
   char letter[n];
   int gameHours,
       gameMinutes;
       
   // open file
   FILE *inp;
   inp = fopen("2015_AU_softball_SEC.txt", "r");
   if (inp == NULL)
      printf("Open file error.\n");
   else
   {
      // save title as string
      fgets(title, TITLE_LEN, inp);
      // scan info
      while (fscanf(inp, "%s %s%d%d%d%d%d%d", date[n], team[n], &gameStats[n][AU_COL], &gameStats[n][OPP_COL],
             &gameStats[n][INN_COL], &gameStats[n][ATT_COL], &gameHours, &gameMinutes) != EOF)
      {
                // calculate time of each game
         hours[n] = gameHours + (double)gameMinutes/MIN_IN_HOUR;
         n++;   
      }    
   }
   
   return n;
}


void printSummary (char title[], char date[][DATE_LEN], char team[][TEAM_LEN],
                   int gameStats[][NUMCOLS], double hours[], int numGames)
{
   int n, c;
   double sumAttend = 0,
          avgAttend,
          sumTime = 0,
          avgTime;
          
   // print header      
   printf("     %.16s Summary as of %s\n", title, date[numGames-1]);
   printf(" Game date   Opposing team    W/L  Score   Inns  Attend   Time(hours)\n");
   
   // calculate average attendance
   for (n=0; n<numGames; n++)
   {
      sumAttend += gameStats[n][ATT_COL];
   }
   avgAttend = sumAttend/numGames;
   
   // calculate average time
   for (n=0; n<numGames; n++)
   {
      sumTime += hours[n];
   }
   avgTime = sumTime/numGames;
   
   // print game info
   for (n=0; n<numGames; n++)
   {
      // print strings
      printf("%-s   %-15s", date[n], team[n]);
      // print win or loss
      if (gameStats[n][AU_COL] > gameStats[n][OPP_COL])
      {
         printf("  W  ");
      }
      else
      {
         printf("  L  ");
      }
      // print stats
      printf(" %02d-%02d %5d %7d", gameStats[n][AU_COL], gameStats[n][OPP_COL], 
            gameStats[n][INN_COL], gameStats[n][ATT_COL]);
      // specify high attendance
      if (gameStats[n][ATT_COL] > avgAttend)
      {
         printf("*");
      }
      else
      {
         printf(" ");
      }
      // specify long games
      printf("%9.2f", hours[n]);
      if (hours[n] > avgTime)
      {
         printf("**\n");
      }
      else
      {
         printf("  \n");
      }
                     
   }
      //print footers
   printf("* attendance above average:        %.2f\n", avgAttend); 
   printf("** games length longer than average: %.2f", avgTime);     
}
