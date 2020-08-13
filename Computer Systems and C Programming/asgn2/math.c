#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>


double Sint(void);
double Cost(void);
double Tant(void);
double Expt(void);
double Sin(double x);
double Cos(double x);
double Tan(double x);
double Exp(double x);
double topower(double a, double b);
double fac(double a);

int main(int argc, char **argv) {
  
  int c;
  //Gets the flag from the command line to know which table to print
  while ((c= getopt(argc, argv, "sctea")) != -1) {
    switch (c) {

        //Prints the Sin table
        case 's':
          Sint();
          break;
            
        //Prints the Cos table
        case 'c':
          Cost();
          break;
            
        //Prints the Tan table
        case 't':
          Tant();
          break;
        
        //Prints the Exponential table
        case 'e':
          Expt();
          break;
                
            //Prints the sin, cos, tan, exponential table
        case 'a':
          Sint();
          Cost();
          Tant();
          Expt();
          break;
    }
    
  }
  return 0;
}

//Prints the table for Sin values and the difference for x in range (-2pi, 2pi)
//with increments of pi/16
double Sint(void) {
  
  // Code by DDEL
  printf("x\t\tSin\t\tLibrary\t\tDifference\n");
  printf("-\t\t---\t\t-------\t\t----------\n");
    
  for (double x = -(2)*(M_PI); x <= ((((2)*(M_PI))+(M_PI)/16));
       x += ((M_PI)/16)) {
    
    double ss = fabs(Sin(x) - sin(x));
    printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\n", x, Sin(x), sin(x), ss);
  }
  return 0;
}

//Prints the table for Cos values and the difference for x in range (-2pi, 2pi)
//with increments of pi/16
double Cost(void) {
    
  // Code by DDEL
  printf("x\t\tCos\t\tLibrary\t\tDifference\n");
  printf("-\t\t---\t\t-------\t\t----------\n");
    
  for (double x = -(2)*(M_PI); x <= ((((2)*(M_PI))+(M_PI)/16));
       x += ((M_PI)/16)) {
    double cc = fabs(Cos(x) - cos(x));
    printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\n", x, Cos(x), cos(x), cc);
  }
  return 0;
}

//Prints the table for Tan values and the difference for x in range of
//((-pi/2)-.001, (pi/2)+.001) with increments of pi/16
double Tant(void) {
  // Code by DDEL
  printf("x\t\tTan\t\tLibrary\t\tDifference\n");
  printf("-\t\t---\t\t-------\t\t----------\n");
    
  for (double x = -(M_PI/2)-.001; x <= (((M_PI/2)+.001+(M_PI)/16));
       x += ((M_PI)/16)) {
    double tt = fabs(Tan(x) - tan(x));
    printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\n", x, Tan(x), tan(x), tt);
  }
  return 0;
}

//Prints the table for Exponential values and the difference for x
//in range (0, 10) with increments of .1
double Expt(void) {
  // Code by DDEL
  printf("x\t\tExp\t\tLibrary\t\tDifference\n");
  printf("-\t\t---\t\t-------\t\t----------\n");
    
  for (double x = 0; x <= 10; x += .1) {
    double ee = fabs(Exp(x) - exp(x));
    printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\n", x, Exp(x), exp(x), ee);
  }
  return 0;
}

//Returns the value of Sin of x using Taylor Series approximation
double Sin(double x) {
  double s = 0;
  for (int i=0; i<100; i++) {
    s+= (topower(-1,i))*(topower(x, (2*i)+1))/fac((2*i)+1);
  }
  return s;
}

//Returns the value of Cos of x using Taylor Series approximation
double Cos(double x) {
  double c = 0;
  for (int i=0; i<100; i++) {
    c+= (topower(-1, i)*topower(x, 2*i))/(fac(2*i));
  }
  return c;
}

//Returns the value of Tan of x using Pade approximation
double Tan(double x) {
  double t = x*(topower(x,8)-(990*topower(x,6))+(135135*topower(x,4))-
                  (4729725*topower(x,2))+34459425);
  double td = 45*(topower(x,8)-(308*topower(x,6))+(21021*topower(x,4))-
                  (360360*topower(x,2))+765765);
  return t/td;
}

//Returns the exponential value to the power of x using
//Taylor Series approximation
double Exp(double x) {
  double e = 0;
  for (int i=0; i<100; i++) {
    e += topower(x, i)/fac(i);
  }
  return e;
}

//Returns the a to the power of b
double topower(double a, double b) {
  double result = 1;
  double exponent = b;
  for (int i = exponent; i>0; i--) {
    result *= a;
  }
  return result;
}

//Returns the a factorial (a!)
double fac(double a) {
  double fact= 1;
  for (double i =1; i<=a; i++) {
    fact = fact * i;
  }
  return fact;
}
