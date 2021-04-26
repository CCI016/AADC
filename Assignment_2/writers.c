/* WRITERS Assignment from the Challenges of Week 1 of AADC */
/* Done by : Constantin Cainarean s4142152 and Garabajiu Denis */

#include <stdio.h>
#include <stdlib.h>

struct Writers {
  int identifier;
  int difficulty;
};

// Below is an implementation of the merge sort algorithm by Arnold Meijster.
// Which we have used and implemented during all the courses with C programming.
struct Writers *copySubArray(int left, int right, struct Writers arr[]) {
	int i;
	struct Writers *copy;
	copy = malloc((right - left)*sizeof(struct Writers));
	for (i=left; i < right; i++) {
		copy[i - left] = arr[i];
	}
	return copy;
}

void mergeSort(int length, struct Writers arr[]) {
	int l, r, mid, idx;
	struct Writers *left, *right;
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
		if (left[l].difficulty < right[r].difficulty) {
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

void findAssignments(struct Writers writers[], int m, int n) {
  struct Writers newWriter;

  for (int i = m; i < n; i++) {
    scanf("%d %d", &newWriter.identifier, &newWriter.difficulty);

    if (newWriter.difficulty > writers[0].difficulty) {
      writers[0] = newWriter;
      mergeSort(m, writers);
    }
  }

  for (int i = (m - 1); i >= 0; i--) {
    printf("%d %d\n", writers[i].identifier, writers[i].difficulty);
  }
}

int main(int argc, char* argv[]) {
	
	// We are scanning the input of the number of websites.
	int n, m;
	scanf("%d %d", &n, &m);

  struct Writers writers[m];

  for (int i = 0; i < m; i++) {
    scanf("%d %d", &writers[i].identifier, &writers[i].difficulty);
  }

  mergeSort(m, writers);

  findAssignments(writers, m ,n);

	return 0;
}
