/* SCALPERS Assignment from the Challenges of Week 1 of AADC */
/* Done by : Constantin Cainarean and Garabajiu Denis */

#include <stdio.h>
#include <stdlib.h>


// Below is an implementation of the merge sort algorithm by Arnold Meijster.
// Which we have used and implemented during all the courses with C programming.
int *copySubArray(int left, int right, int arr[]) {
	int i, *copy;
	copy = malloc((right - left)*sizeof(int));
	for (i=left; i < right; i++) {
		copy[i - left] = arr[i];
	}
	return copy;
}

void mergeSort(int length, int arr[]) {
	int l, r, mid, idx, *left, *right;
	if (length <= 1) {
		return;
	}
	mid = length/2;
	left = copySubArray(0, mid, arr);
	right = copySubArray(mid, length, arr);
	mergeSort(mid, left);
	mergeSort(length - mid, right);
	idx = 0;
	l = 0;
	r = 0;
	while ((l < mid) && (r < length - mid)) {
		if (left[l] < right[r]) {
			arr[idx] = left[l];
			l++;
		} else {
			arr[idx] = right[r];
			r++;
		}
		idx++;
	}
	while (l < mid) {
		arr[idx] = left[l];
		idx++;
		l++;
	}
	while (r < length - mid) {
		arr[idx] = right[r];
		idx++;
		r++;
	}
	free(left);
	free(right);
}


// Function that is computing the number of shops, where the PS5 is sold on the same exact day.
void findMaxNumbersOfShops(int start[], int end[], long int n) {

/* Since our input is organized into two arrays, as described in the main, we assign 3 variables in order to keep track of the earliest
	day, when the sales across all the websites are the most. From the start we assume that we have 1 shop,
	that starts selling on the day which is the first in the start-dates array. shopsInitial indicates the number
	of shops at a time, maxShops is the result we are looking for which indicates the maximum number of shops at a time,
	and the "day" variable is responsible for the exact day when the most number of websites are selling PS5. */

	int shopsInitial = 1, maxShops = 1, day = start[0];
	int i = 1, j = 0;
	// With this loop we are able to go through all arrays in a sorted manner.
	while (i < n && j < n) {

		/* Since i is in front of j by 1, we are looking if the next element is a selling date,
			we increment the current number of shops by 1 */
		if (start[i] <= end[j]) {
			shopsInitial++;

		/* Here we check if the current number of shops selling at a time is greater
			then the previously known maximum number, we update the maximum, and also the day which 
			has the most number of websites selling the PS5.*/

			if (shopsInitial > maxShops) {
				maxShops = shopsInitial;
				day = start[i];
			}
			i++;  // Traverse the array further.
		} else {    // In case if the next element is an end sale date, we decrement thecurrent number of shops and adjust the index of traversing the second array by +1.
			shopsInitial--;
			j++;
		}
	}

	printf("%d %d\n", day, maxShops);
}

int main(int argc, char* argv[]) {
	
	// We are scanning the input of the number of websites.
	int n;
	scanf("%d", &n);

	// Case described in the assignment, if the number of websites is 0, we print two zeros.
	if (n == 0) {
		printf("%d %d\n", 0, 0);
		return 0;
	}

	/* We initialize two arrays of the size n (which is the number of our websites).
		The start array containts all the dates when the sales start for all the websites.
		And the end array the dates when the sales end respectively. */
	int start[n], end[n];

	// Scanning the input and organizing it into the arrays.
	for ( int i = 0; i < n; i++) {
		scanf("%d %d", &start[i], &end[i]);
	}

	// Here we are sorting the two arrays, in order to make it possible for our algorithm to work.
	mergeSort(n, start);
	mergeSort(n, end);

	findMaxNumbersOfShops(start, end, n);
	return 0;
}