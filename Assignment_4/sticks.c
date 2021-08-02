/* Sticks Assignment from the Challenges of Week 4 of AADS */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis S4142551 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to safely allocate memory.
void *safeMalloc(int n) {
	void *p = calloc(n, sizeof(int));
	if (p == NULL) {
		printf("Error: calloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

int main(int argc, char* argv[]) {
	
	int s, f;
	int *submissions;

	scanf("%d %d", &s, &f);

	if (f == 0 || s == 0) {
		printf("0\n");
		return 0;
	}

	int size = (int) log2(s) + 1, value = 0, histoTotal = 0;
	submissions = safeMalloc(size);

	//Creating histograms for the submissions
	for (int i = 0; i < f; i++) {
    	scanf("%d%*c", &value);
		submissions[(int) log2(value)]++;
		histoTotal++;
	}

	int sticksNumber = 0, primaryIndex = (size - 1), secondaryIndex = 0, currentStick = 0;

	while(histoTotal > 0) {

		// This while loop will find the optimal combination of submissions for a stick
		while(1) {
			if ((primaryIndex - secondaryIndex) < 0) {
				break;
			}

			if ((submissions[primaryIndex - secondaryIndex] > 0) && 
				(currentStick + ((int) pow(2, primaryIndex - secondaryIndex)) <= s)) {

					currentStick += ((int) pow(2, primaryIndex - secondaryIndex));
					submissions[primaryIndex - secondaryIndex]--;
					histoTotal--;

			} else {
				secondaryIndex++;
			}
		}

		if (submissions[primaryIndex] == 0) {
			primaryIndex--;
		}

		secondaryIndex = 0;
		sticksNumber++;
		currentStick = 0;

	}
		printf("%d\n", sticksNumber);

	free(submissions);
	return 0;
}