#include <stdio.h>
#include <time.h>

void subscriptFunction(){
	int arr[15][5] = { 0 };

	for (int jx = 0; jx < 5; jx++) {
		for (int iy = 0; iy < 15; iy++) {
			arr[iy][jx];
		}
	}
	return;
}

void pointersFunction(){
	int arr[15][5] = { 0 };

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 15; i++) {
			*(*(arr + i) + j);
		}
	}

	return;
}
int Q2() {
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	for (int i = 0; i < 20000; i++) {
		subscriptFunction();
	}
	end = clock();
	cpu_time_used = (((double)(end)) - ((double)(start))) / (CLOCKS_PER_SEC / 100);

	printf("Subscript Time taken:%f\n", cpu_time_used);

	start = clock();
	for (int i = 0; i < 20000; i++) {
		pointersFunction();
	}
	end = clock();

	cpu_time_used = (((double)(end))-((double)(start))) / (CLOCKS_PER_SEC / 100);

	printf("Pointers Time taken:%f\n", cpu_time_used);

	return 0;
}
