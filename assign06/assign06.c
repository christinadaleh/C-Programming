// Christina Holmes, Group 11
// Marshall McGarity, Tiffany Pittman 
// assign06
// 03/10/15
// We did assignment using only class material.
/* This program uses a while statement to read the variables from the file and uses user 
   defined functions to calculate the distance each balloon is thrown, the number and percent 
   that hits the pool, the number of balloons thrown, which balloon overflows the pool, and 
   how much water is spilled over the edge. */

#include <stdio.h>
#include <math.h>

//*****FUNCTION PROTOTYPES*****
double getBalloonVolume( int diameter );
double compDistance (double degrees, double velocity, double height_thrower);
void printResults ( int hit, int count, int balloonNum, double poolVolume);

//*****CONSTANTS*****
#define BALCONY_HT      12                   // balcony height in feet
#define G               32                   // gravitational acceleration
#define PI              3.14159
#define POOL_DIAMETER   2                    // diameter of pool in feet
#define POOL_CENTER     35                   // distance to the center of pool in feel
#define CAPACITY        7                    // pool capacity in gallons
#define FILENAME        "balloonValues.txt"   // input data file

int main()
{
   double degrees, velocity, height_thrower, distance, excessVolume, 
          volume, poolVolume, radians, yTotal, percent;
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
         count++;
      // calculate the volume
         volume = getBalloonVolume(diameter);
           // calculate distance
         distance = compDistance(degrees, velocity, height_thrower);
              // calculate the total volume of the water in the pool
         if ( distance <= ((POOL_CENTER + (POOL_DIAMETER/2))) && distance >= (POOL_CENTER - (POOL_DIAMETER/2))) 
         {
         // calculate the number of hits
            hit++;
         // calculate total volume of the pool when hit
            poolVolume += volume;
         
            if (poolVolume >= CAPACITY)
            {
               balloonNum = count;
            }
         }
                 
      }
   
   //*********OUTPUT**********
        
   printResults(hit, count, balloonNum, poolVolume);
   
      fclose(inp);
   
      
   
      return 0;
   }
}

//*****FUNCTION DEFINITIONS*****
double getBalloonVolume(int diameter)
{
   
   double volume;
   switch (diameter)
   {
      case 3:
         volume = 0.1;
         break;
      case 4:
         volume = 0.2;
         break;
      case 5:
         volume = 0.3;
         break;
      case 6:
         volume = 0.55;
         break;
      case 7:
         volume = 0.8;
         break;
      case 8:
         volume = 1.25;
         break;
      case 9:
         volume = 1.7;
         break;
   }
   return volume;
  
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

void printResults ( int hit, int count, int balloonNum, double poolVolume)
{
   double percent, excessVolume;
   // calculate the percent of hits
   percent = ((double) hit/(double) count) * 100;  
    // calculate how many gallons spilled over the edge of the pool
         if (poolVolume > CAPACITY)
         {
            excessVolume = poolVolume - CAPACITY;
         }
    

   printf("%.0d balloons hit the pool.\n", hit);
   printf("%.0d balloons were thrown.\n", count);
   printf("%4.2f%% balloons hit the pool.\n", percent);
   printf("Balloon #%d filled the pool.\n", balloonNum);
   printf("%.2f gallons of water spilled over the edge of the pool.\n", excessVolume);
   

}
