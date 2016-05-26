// Christina Holmes
// assign01b.c
// 01/29/15
/*
   Compute the semester grade for COM1200
   assignments 40%, midterms 30%, final exam 30%,
   extra credit: syl quiz 1%, iclicker pts 2%
*/
#include <stdio.h>
// CONSTANTS
#define MAX_ICLICKER_POINTS 75
#define NUM_ASSIGNS         10

int main()
{
// INPUT - Get the student's assignment and exam grades
// Exam grades
   int exam01 = 86,
       exam02 = 94,
       final_exam = 92;
// Assignment grades
   int assignments[NUM_ASSIGNS] = { 0,0,95,92,69,54,61,62,70,68 };
// Extra credit
   int syllabusQuiz = 10,
       iclickPts    = 66;
// OUTPUT
   double grade,assignPerc;
   char   ltrGrade;
// OTHER variables
   int    a, assignTotal = 0;
   double gradePerc, extraPerc; 

// COMPUTE
// Compute the assignment percent
// Get total grades
   for ( a=0;a<NUM_ASSIGNS;a++ )
   {
      assignTotal += assignments[a];
   }
   assignPerc = assignTotal / NUM_ASSIGNS;
// Compute the grade percent
   gradePerc = exam01 * .15 + exam02 * .15 + final_exam * .3 + assignPerc * .4;
// Compute the extra credit percent
   extraPerc = syllabusQuiz/10 + (double)iclickPts/MAX_ICLICKER_POINTS * .02 * 100;
   grade     = gradePerc + extraPerc;
// Find the Banner letter grade
   if ( assignPerc < 60.0 ) ltrGrade = 'F'; // greater than 60% required to pass
   else if ( grade > 89.5 ) ltrGrade = 'A';
   else if ( grade > 79.5 ) ltrGrade = 'B';
   else if ( grade > 69.5 ) ltrGrade = 'C';
   else if ( grade > 59.5 ) ltrGrade = 'D';
   else ltrGrade = 'F';
      
// OUTPUT - Print the course grade, assignment grade, Banner letter grade
   printf( "Course grade:  %4.1f \nAssignment grade: %4.1f\n", grade,assignPerc );
   printf( "Banner grade:  %c\n", ltrGrade );
   return 0;
}