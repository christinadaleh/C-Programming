// Christina Holmes
// None
// assign04b
// 2/18/15
// I worked on the assignment alone using only course material.
/* The program allows the user to input an angle and calculates the height
   of the building using the given angle if it is between 27.0 and 33.0 degrees.
   It uses a while loop to reprompt the user to input an angle if the angle
   originally inputted isn't in the range.
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

// repromt if angle is outside range
  while (angle_degrees < MIN_ANGLE || angle_degrees > MAX_ANGLE)
  {
   printf("Enter an angle in degrees (min=27.0, max=33.0): ");
   scanf ("%lf", &angle_degrees);
   }   
   //*****COMPUTATION*****
   // convert degrees to radians
      angle_radians = angle_degrees * PI/180;
   //find the building height
      height_meters = DISTANCE * tan(angle_radians);
   //*****OUTPUT*****
   // print the degrees and building height
      printf ("Using %4.1lf degrees, the building height is %5.2lf meters.", angle_degrees, height_meters);
     
   return 0;
}