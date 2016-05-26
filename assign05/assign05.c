// Christina Holmes, Group 8
// Marshall McGarity, Stewart Hawk 
// assign05
// 03/4/15
// We asked Christopher Lewis and the TA about the embedded if statements that determine which balloon fills the pool.
/* This program uses a while statement to read the variables from the file and 
   calculate the distance each balloon is thrown, the number and percent that hits the pool, 
   the number of balloons thrown, which balloon overflows the pool, and how much water is spilled over the edge. */

#include <stdio.h>
#include <math.h>

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
          volume, poolVolume, radians, yTotal, percent, count, hit;
   int diameter, balloonNum;
   FILE *inp;  // pointer to input file
        
   count = 0;
   hit = 0;
   poolVolume = 0;
   excessVolume = 0;
   balloonNum = 0;

   // open the input file     
   inp = fopen("balloonValues.txt", "r");
   
   while ( fscanf( inp, "%lf %lf %lf %d", &degrees, &velocity, &height_thrower, &diameter) != EOF )
   {
      // count number of balloons
      count++;
      // calculate the volume
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
      // calculate distance
      radians = degrees * PI/180;
      yTotal = height_thrower + BALCONY_HT;
      distance = (velocity * cos(radians) / G) * 
         ((velocity * sin(radians)) + sqrt( (pow((velocity * sin(radians)), 2)) + (2 * G * yTotal) ));
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
      // calculate how many gallons spilled over the edge of the pool
      if (poolVolume > CAPACITY)
      {
         excessVolume = poolVolume - CAPACITY;
      }
      // calculate the percent of hits
      percent = (hit/count) * 100;      
   
   }
   
   //*********OUTPUT**********
      printf("%.0f balloons hit the pool.\n", hit);
      printf("%.0f balloons were thrown.\n", count);
      printf("%4.2f%% balloons hit the pool.\n", percent);
      printf("Balloon #%d filled the pool.\n", balloonNum);
      printf("%.2f gallons of water spilled over the edge of the pool.\n", excessVolume);
   

   
   fclose(inp);
   
      
   
   return 0;
}