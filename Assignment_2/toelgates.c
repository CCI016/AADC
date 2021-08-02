/* WRITERS Assignment from the Challenges of Week 1 of AADC */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis */

#include <stdio.h>
#include <stdlib.h>

int summm(int arr[], int length) {
	int sum = 0;

	for (int i = 0; i < length; i++) {
		sum += arr[i];
	}

	return sum;
}

int min(int a, int b) {
	return a <= b ? a : b;
}

void findMinimalPrice(int h, int c, long int n) {
	int sum = 0, slidingWindow[h + c], currentStepAkaFrame[c], i1 = 0, i2 = 0, predecessor = 0, comparator = 0;
	
	for (int i = 0; i < (h + c); i++) {
		slidingWindow[i] = 0;
	}

	for (int i = 0; i < c; i++) {
		currentStepAkaFrame[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &currentStepAkaFrame[i % c]);

		if (i > 0) {
			predecessor = slidingWindow[((i - 1) % (h + c))];
		}

		if (i < (h + c)) {
			slidingWindow[(i % (h + c))] = currentStepAkaFrame[i % c] + predecessor;
		} else {
			slidingWindow[(i % (h + c))] = min(currentStepAkaFrame[i % c] + predecessor, slidingWindow[(i % (h + c))] + summm(currentStepAkaFrame, c));
		}
	}

	sum = slidingWindow[0];
	printf("%d\n", sum);
	comparator = currentStepAkaFrame[c - 1];

	for (int i = 0; i < (h + c); i++) {
		printf("%d ", slidingWindow[i]);
	}

	for (int i = 0; i < c; i++) {
		currentStepAkaFrame[i] = 0;
		slidingWindow[i] = min(comparator + predecessor, slidingWindow[i] + summm(currentStepAkaFrame, c));
		sum = min(sum, slidingWindow[i]);
	}
	
	printf("\n%d\n", sum);

}

void scan() {
	// We are scanning the input of the number of websites.
	int h, c;
	scanf("%d %d", &h, &c);
	long int n;
	scanf("%ld", &n);

	findMinimalPrice(h, c, n);
}

int main(int argc, char* argv[]) {
	scan();
	return 0;
}