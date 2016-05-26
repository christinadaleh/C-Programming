// Christina Holmes
// None
// assign04c
// 2/18/15
// I worked on the assignment alone using only course material.
/* The program allows the user to input the number of angles,  prompts the user
   to input an angle, and calculates the height of the building using the given angle 
   if it is between 27.0 and 33.0 degrees until the number of angles has been reached
   by using a do while embedded in a for loop.
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
   int num_angles, n; 
                                         
   //*****INPUT*****
   // get the angle between the line of sight and
   // the horizontal line connecting the measuring point and the building
       
   // ask the user to input number of angles  
   printf("Enter the number of angles to be entered: ");
   scanf("%d", &num_angles);
   
   // find angle in radians and height for given number of angles
   for (n = 1; n <= num_angles; n++)
   {
   // reprompts message until user inputs an angle within range   
      do
      {
         printf("Enter an angle in degrees (min=27.0, max=33.0): ");
         scanf ("%lf", &angle_degrees);
      }
      while (angle_degrees < MIN_ANGLE || angle_degrees > MAX_ANGLE);
      
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