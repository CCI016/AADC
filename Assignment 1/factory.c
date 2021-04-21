/* FACTORY Assignment from the Challenges of Week 1 of AADC */
/* Done by : Constantin Cainarean and Garabajiu Denis */

#include <stdio.h>
#include <stdlib.h>


struct Factory {
   long int prod;
	 long int days;
};

struct Factory *copySubArray(long int left, long int right, struct Factory arr[]) {
	long int i;
	struct Factory *copy;
	copy = malloc((right - left)*sizeof(struct Factory));
	for (i=left; i < right; i++) {
		copy[i - left] = arr[i];
	}
	return copy;
}

void mergeSort(long int length, struct Factory arr[]) {
	long int l, r, mid, idx;
	struct Factory *left, *right;
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
		if (left[l].days < right[r].days) {
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


void findMinimalDays(long int p, long int n, struct Factory factories[]) {
	long int currentDay = 1;

	while (p > 1) {
		for (long int i = 0; i < n; i ++) {
			if (factories[i].days > currentDay) {
				break;
			} else if (currentDay % factories[i].days == 0) {
				p = p - factories[i].prod;
			}
		}
		currentDay++;
	}
	printf("%d\n", currentDay - 1); 
}


int main(int argc, char* argv[]) {
	
	// We are scanning the input of the number of gpu's.
	long int p;
	scanf("%ld", &p);

	// The number of factories
	long int n;
	scanf("%ld", &n);

	struct Factory factories[n];

	// Scanning the input and organizing it into the arrays.
	for (long int i = 0; i < n; i++) {
		scanf("%d %d", &factories[i].prod, &factories[i].days);
	}

	mergeSort(n, factories);

	findMinimalDays(p, n, factories);



	// printf("--------");

	// for (int i = 0; i < n; i++) {
	// 	printf("%d %d\n", factories[i].prod, factories[i].days);
	// }
	return 0;
}
