// Christina Holmes
// None
// 02
// 2/4/15
// I worked on my assignment alone using only the course material.
/* The program uses trigonometry to find the height of the building, the angle you will tilt
   your head to see the top of the building, and the distance from the your head to the top
   of the building.
*/

#include <stdio.h>
#include <math.h>

//*****CONSTANT*****
#define MAX_ANGLE 33    // degrees
#define MIN_ANGLE 27    // degrees
#define DIST_A    120   // meters
#define DIST_B    20    // meters
#define HEIGHT_B  200   // meters
#define PI        3.14159

int main()
{
   double MAX_HEIGHT,      // variables with units
          MIN_HEIGHT,      
          radians_MAX,     // max angle in radians
          radians_MIN,     // min angle in radians
          angle_head,      // angle of head in radians
          angle_head_deg,  // angle of head in degrees
          hypotenuse;      // distance from head to top of building
   
//*****COMPUTATION*****
// a) convert degrees to radians
//    find the maximum and minimum heights the building can be.
   radians_MAX = MAX_ANGLE * PI / 180;
   radians_MIN = MIN_ANGLE * PI / 180;
   MAX_HEIGHT = DIST_A * tan(radians_MAX);
   MIN_HEIGHT = DIST_A * tan(radians_MIN);
// b) Find the angle that you will tilt your head to see the top of the building
//    Convert radians to degrees
   angle_head = atan2(HEIGHT_B , DIST_B);    // angle in radians
   angle_head_deg = angle_head * 180 / PI;  // angle in degrees
// c) Find how far it is from your head to the top of the building.
   hypotenuse = sqrt( (HEIGHT_B * HEIGHT_B) + (DIST_B * DIST_B) );
   
//*****OUTPUT*****
// a) print the minimum and maximum height the building can be
   printf("The minimum height is %5.2f meters.\n", MIN_HEIGHT);
   printf("The maximum height is %5.2f meters.\n", MAX_HEIGHT);
// b) print the angle that you will tilt your head to see the top of the building
   printf("The angle that you will tilt your head to see the top of the building is %5.2f degrees.\n", angle_head_deg);
// c) print the distance it is from the top of your head to the top of the building
   printf("The distance from your head to the top of the building is %6.2f meters.\n", hypotenuse);
   
   return 0;
}