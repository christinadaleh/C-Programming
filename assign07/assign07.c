// Christina Holmes, Group 10
// Marshall McGarity, Tiffany Pittman, Stewart Hawk 
// assign07
// 03/18/15
// We asked the TA for help to get the number of balloons that hit the pool to print correctly.
/* This program uses a while statement to read the variables from the file and uses user 
   defined call by value and call by reference functions to calculate the distance 
   each balloon is thrown, the number and percent that hits the pool, the number of balloons 
   thrown, which balloon overflows the pool, and how much water is spilled over the edge. */

#include <stdio.h>
#include <math.h>

//*****FUNCTION PROTOTYPES*****
void isHit ( double *poolVolume, double balloonVolume, int *hit, 
             int *balloonNum , int count);
void addOne ( int *count );
double getBalloonVolume( int diameter );
double compDistance (double degrees, double velocity, double height_thrower);
void printResults ( int *hit, int *count, int balloonNum, double *poolVolume);

//*****CONSTANTS*****
#define BALCONY_HT      12                   // balcony height in feet
#define G               32                   // gravitational acceleration
#define PI              3.14159
#define POOL_DIAMETER   2                    // diameter of pool in feet
#define POOL_CENTER     35                   // distance to the center of pool in feel
#define CAPACITY        7                    // pool capacity in gallons
#define FILENAME        "balloonValues.txt"   // input data file

int main(void)
{
   double degrees, velocity, height_thrower, distance, excessVolume, 
          balloonVolume, poolVolume, radians, yTotal, percent;
   int  balloonNum, count, hit, diameter;
   FILE *inp;  // pointer to input file
        
   count = 0;
   hit = 0;
   poolVolume = 0;
   excessVolume = 0;
   balloonNum = 0;

   // open the input file     
   inp = fopen(FILENAME, "r");
   if (inp == NULL)
   {
      printf("Error opening input file.");
   }
   else
   {
   
      while ( fscanf( inp, "%lf %lf %lf %d", &degrees, &velocity, &height_thrower, &diameter) != EOF )
      {
      // count number of balloons
         addOne (&count);
      // calculate the volume
         balloonVolume = getBalloonVolume(diameter);
      // calculate distance
         distance = compDistance(degrees, velocity, height_thrower);
      // calculate the total volume of the water in the pool
         isHit(&poolVolume, balloonVolume, &hit, &balloonNum, count);           
      }
   
   //*********OUTPUT**********
      printResults(&hit, &count, balloonNum, &poolVolume);
      fclose(inp);
   
      return 0;
   }
}

//*****FUNCTION DEFINITIONS*****
void addOne ( int *count )
{
   *count = *count +1;
}

double getBalloonVolume(int diameter)
{
   
   double balloonVolume;
   switch (diameter)
   {
      case 3:
         balloonVolume = 0.1;
         break;
      case 4:
         balloonVolume = 0.2;
         break;
      case 5:
         balloonVolume = 0.3;
         break;
      case 6:
         balloonVolume = 0.55;
         break;
      case 7:
         balloonVolume = 0.8;
         break;
      case 8:
         balloonVolume = 1.25;
         break;
      case 9:
         balloonVolume = 1.7;
         break;
   }
   return balloonVolume;
}

double compDistance (double degrees, double velocity, double height_thrower)
{
   double radians, yTotal, distance;
   radians = degrees * PI/180;
   yTotal = height_thrower + BALCONY_HT;
   distance = (velocity * cos(radians) / G) * 
            ((velocity * sin(radians)) + sqrt( (pow((velocity * sin(radians)), 2)) + (2 * G * yTotal) ));
   return distance;
}

void isHit ( double *poolVolume, double balloonVolume, int *hit, 
             int *balloonNum , int count)
{
   double distance, velocity, height_thrower, degrees;
   int diameter;
   if ( distance <= ((POOL_CENTER + (POOL_DIAMETER/2))) && distance >= (POOL_CENTER - (POOL_DIAMETER/2))) 
   {
      // calculate the number of hits
      addOne (hit);
      // calculate total volume of the pool when hit
      *poolVolume = *poolVolume + balloonVolume;
            
      if (*poolVolume >= CAPACITY)
      {
         *balloonNum = count;         
      }                   
   }
}

void printResults ( int *hit, int *count, int balloonNum, double *poolVolume)
{
   double percent, excessVolume;
   // calculate the percent of hits
   percent = ((double) *hit/(double) *count) * 100;  
   // calculate how many gallons spilled over the edge of the pool
   if (*poolVolume > CAPACITY)
   {
      excessVolume = *poolVolume - CAPACITY;
   }
    

   printf("%.0d balloons hit the pool.\n", *hit);
   printf("%.0d balloons were thrown.\n", *count);
   printf("%4.2f%% balloons hit the pool.\n", percent);
   printf("Balloon #%d filled the pool.\n", balloonNum);
   printf("%.2f gallons of water spilled over the edge of the pool.\n", excessVolume);
}
