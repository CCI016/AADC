/* NOSTER Assignment from the Challenges of Week 3 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>

// Function to safely allocate memory.
void *safeMalloc(int n) {
	void *p = malloc(n);
	if (p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

// binary search algorithm that looks for an element such that happiness[end[middle]] < current element (happiness[i])
void binarySearch(int *lowerBound, int *upperBound, int *happiness, int *end, int i) {
  int middle;
  while (*upperBound >= *lowerBound) {
    middle = (*lowerBound + *upperBound) / 2;
    if (happiness[end[middle]] > happiness[i]) {
      *upperBound = middle - 1;
    } else {
      *lowerBound = middle + 1;
    }
  }
}

//Implementation of LIS algorithm
//Reference 1: https://ru.wikipedia.org/wiki/Задача_поиска_наибольшей_увеличивающейся_подпоследовательности
//Refference 2: https://www.youtube.com/watch?v=cjWnW0hdF1Y
void findLIS(int n, int *happiness) {
  // The end array will store the smallest element in which a sequence of length x ends
  // The pred array will store the preddecesor of the largest element in which a sequence of length x ends.
  int *end, *pred, *lis, length = 0, lowerBound, upperBound, ind;

  pred = safeMalloc(n * sizeof(int));
  end = safeMalloc((n + 1) * sizeof(int));

  for (int i = 0; i < n; i++) {
    lowerBound = 1;
    upperBound = length;

    binarySearch(&lowerBound, &upperBound, happiness, end, i);

    pred[i] = end[lowerBound - 1];
    end[lowerBound] = i;

    if (lowerBound > length) {
      length = lowerBound;
    }
    
  }

  //reconstructing the lis backwards
  lis = safeMalloc(length * sizeof(int));
  ind = end[length];

  for (int i = length - 1; i >= 0; i--) {
    
    lis[i] = happiness[ind];
    ind = pred[ind];
  }

  printf("%d %d\n", length, lis[length - 1] - lis[0]);
  free(end);
  free(pred);
  free(lis);
}

int main(int argc, char **argv) {
  int n, *happiness;

  scanf("%d", &n);
  happiness = safeMalloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    scanf("%d%*c", &happiness[i]);
  }

  findLIS(n, happiness);

  free(happiness);
}
