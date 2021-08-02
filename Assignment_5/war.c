/* WAR Assignment from the Challenges of Week 5 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b) {
  return a > b ? a : b;
}

// Function to safely allocate memory.
void *safeMalloc(int n) {
	void *p = malloc(n);
	if (p == NULL) {
		printf("Error: calloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

void findBestPath(int n, int m, int *currentRow, int *result) {
  int currentCountryValue;


// Separate for to scan the first line and store the results if the path will be only east
  for (int i = 0; i < m; i++) {
    scanf("%d%*c", &currentCountryValue);

    if ((i != 0) && (currentCountryValue != 0) &&
      ((currentRow[i - 1] - 1 + currentCountryValue) > 0) && (currentRow[i - 1] != 0)) {
// if for calculating cost to a certain country based on the value of the prev one

      currentRow[i] = currentRow[i - 1] - 1 + currentCountryValue;

    } else if ((i != 0) &&
      ((currentCountryValue == 0) || ((currentRow[i - 1] - 1 + currentCountryValue) < 0) 
      || (currentRow[i - 1] == 0))) {
// If the user cannot go to a certain country, all other countries that are located 
//on east of this country will be not accesible, therefore we can mark them as ocean
      currentRow[i] = 0;
      i++;
      while (i < m) {
        scanf("%d%*c", &currentCountryValue);
        currentRow[i] = 0;
        i++;
      }

    } else {
      currentRow[i] = currentCountryValue;
    }
  }

  for (int r = 1; r < n; r++) {
    
    result = currentRow;

    for (int c = 0; c < m; c++) {
      scanf("%d%*c", &currentCountryValue);

      if (c > 0) {
        if (currentCountryValue == 0) {
          currentRow[c] = 0;
        } else {
          currentRow[c] = max(currentRow[c - 1] - 1 + currentCountryValue,
                                result[c] - 1 + currentCountryValue);
        }
      } else {
        if (((result[c] - 1 + currentCountryValue) > 0) && (result[c] != 0) && (currentCountryValue != 0)) {
          currentRow[c] = result[c] - 1 + currentCountryValue;
        } else {
          currentRow[c] = 0;
        }

      }
    }
  }

  printf("%d\n", currentRow[m - 1]);

}

int main(int argc, char* argv[]) {
  int n, m, *currentRow, *result;
  scanf("%d %d", &n, &m);

  currentRow = safeMalloc(m * sizeof(int));
  result = safeMalloc(m * sizeof(int));

  findBestPath(n, m, currentRow, result);

  free(currentRow);
  free(result);

  return 0;
}