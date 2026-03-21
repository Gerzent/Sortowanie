#include <stdio.h>
#include <time.h>
long long comparisons=0;
long long swaps=0;

int Partition(int A[], int p, int r) {
	int x = A[p];
	int i = p;
	int j = r;
	while(1) {
		while(A[i]>x){
		    comparisons++;
		    i++;
		}
		while(A[j]<x){
		    comparisons++;
		    j--;
		}
		if(i<j) {
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			swaps++;
			i++;
			j--;
		} else return j;
	}
}

void QsortIterative(int A[], int p, int r) {
	int stack[r-p+1];
	int top = -1;
	stack[++top] = p;
	stack[++top] = r;
	while(top>=0) {
		r = stack[top--];
		p = stack[top--];
		int q = Partition(A, p, r);
		if(q>p) {
			stack[++top]=p;
			stack[++top]=q;
		}
		if(q+1<r) {
			stack[++top]=q+1;
			stack[++top]=r;
		}
	}
}

int main()
{
    int n;
    scanf("%d", &n);
	int arr[n];
	for(int i=0; i<n; i++){
	    scanf("%d", &arr[i]);
	}
    // START TIMER
    clock_t start = clock();

    QsortIterative(arr, 0, n-1);

    // STOP TIMER
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
	
    printf("Posortowana tablica:\n");
	for(int i=0; i<n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
    printf("Liczba porównań: %lld \n",comparisons);
    printf("Liczba zamian: %lld",swaps);
    printf("Czas: %.10f\n", elapsed);
	return 0;
}
