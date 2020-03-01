#include <stdlib.h>
#include <stdio.h>

/*This program asks the user to provide 2 numbers that denote a range of numbers. It tests these numbers against conditions and then runs the method to test and print the semiprime numbers (semiprime numbers are defined as having 2 prime numbers as factors).*/

//partner: asanag2, anudeep2


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b); //runs method print_semiprimes after tests for invalid  ranges
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  //loops through possible divisors
  for(int i = 2; i<number; i++){
  
    //tests is number is divisible by anything but itself and zero
    if(number%i==0){
      return 0;
    }
  }
  return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int flag = 0; //flag variable to denote whether or not the number is a semiprime
  int counter = 0; //counter variable for amount of semiprimes

  //loops through user-provided range
  for(int i = a; i<=b; i++){
    
    //loops through possible divisors
    for(int j=2; j<i; j++){
      
      //temporary variables that hold conditions for semi-primality
      int div1 = is_prime(i/j); 
      int div2 = is_prime(j); 
      int remainder = i%j;

      //tests for semi-primality
      if((div1==1)&&(div2==1)&&(remainder==0))
	flag = 1; 
      if(is_prime(i)==1)
	flag = 0;
    }
    
    //prints semiprime, increments amount of semiprimes, resets flag
    if(flag == 1){
      printf("%i", i); 
      printf(" ");
      counter++;
      flag = 0;
    }
  }
  
  //if we have encountered a semiprime, return 1, otherwise return 0
  if(counter > 0)
    return 1;
  else
    return 0;
}



