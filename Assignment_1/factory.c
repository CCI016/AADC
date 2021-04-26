/* FACTORY Assignment from the Chalfactoriesges of Week 1 of AADC */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis s4142551*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


// That is the binary search algorithm, but it is adapted to the problem's requierments
// We make an assumption that the arrays are already sorted, but even if they are not, the totalRatio will fix this issue
// Refference: https://www.geeksforgeeks.org/binary-search/
long findLeastNumberOfDays(unsigned long long int limitR, unsigned long long int limitL, int factories, int days[], int products[], unsigned long long int total) {
  unsigned long long int totalRatio =  0;
	// the middled of our interval
	unsigned long long int middle = limitL + ((limitR-limitL) + 1) / 2;

	// We implemeted the idea of golden ratio for our binary search algorithm. 
	// somethin similar can be found in the knapsack problem.
	for (int i = 0; i < factories; i++) {
		totalRatio += (middle / days[i]) * products[i];
  }
  
  if (limitL == limitR) {
		return totalRatio < total ? limitL++ : limitL;
  } 
	
	return totalRatio < total ? findLeastNumberOfDays(limitR, middle + 1, factories, days, products, total) :
															findLeastNumberOfDays(middle, limitL, factories, days, products, total);

} 

void printResult(int factories, int days[], int products[], unsigned long long int total) {
	// maximal limit for our search algorithm
	unsigned long long int max = 18446744073709551615ULL;
	long int result = findLeastNumberOfDays(max, 0, factories, days, products, total);

  printf("%ld\n", result);
}

// A function for scanning the input of the problem
void scan() {
	//numebr of GPU's that needs to be produced
  unsigned long long int total;
  scanf("%llu", &total);

	// Total number of factories
  int factories;
  scanf("%d", &factories);
  
  int products[factories], days[factories];
  for (int i=0; i < factories; i++) {
		scanf("%d %d", &products[i], &days[i]);
  }

	printResult(factories, days, products, total);
}

int main(int argc, char *argv[]) {
  scan();
}
