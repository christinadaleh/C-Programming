// Christina Holmes, Group 10
// Marshall McGarity, William Blake Smith
// assign03
// 2/11/15
// We spoke with Ms. Hundley about how to start the prompt.
/* The program allows the user to input an angle and calculates the height
   of the building using the given angle if it is between 27.0 and 33.0 degrees.
*/

#include <stdio.h>
#include <math.h>

//*****CONSTANT*****
#define MAX_ANGLE    33.0  // degrees
#define MIN_ANGLE    27.0  // degrees
#define DISTANCE    120.0  // meters
#define PI            3.14159

int main()
{
   double angle_degrees, angle_radians, height_meters;   // variables with units
   
//*****INPUT*****
// get the angle between the line of sight and
// the horizontal line connecting the measuring point and the building
   printf("Enter an angle between 27.0 and 33.0 degrees: \n");
   scanf ("%lf", &angle_degrees);
   
   

// if the angle is too small
   // print a message
   if (angle_degrees < 27.0)
   {
      printf ("%4.1lf is too small.\n", angle_degrees);
   } 
// else if the angle is too large
   // print a message
   else if (angle_degrees > 33.0)
   {
      printf ("%4.1lf is too large.\n", angle_degrees);
   }
// else compute and print height
   else
   {
   //*****COMPUTATION*****
   // convert degrees to radians
      angle_radians = angle_degrees * PI/180;
   //find the building height
      height_meters = DISTANCE * tan(angle_radians);
   //*****OUTPUT*****
   // print the degrees and building height
      printf ("Using %4.1lf degrees, the building height is %5.2lf meters.\n", angle_degrees, height_meters);
   }
   return 0;
}