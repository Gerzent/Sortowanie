#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long long comparisons;
long long swaps;
long long merges;
#define MAX 1000

// SHELL SORT

void Shell(int arr[], int n) {
	int przyrost=1,kMax=1;
	while (przyrost<n) {
		przyrost=(pow(3,kMax)-1)/2;
		kMax++;
	}
	if (przyrost>=n) {
		przyrost=(pow(3,kMax--)-1)/2;
	}
	while (przyrost>0) {

		for (int i=przyrost; i<n; i++) {
			int key=arr[i];
			int j=i;

			while (j >= przyrost) {
				comparisons++;
				if (arr[j - przyrost]<key) {
					swaps++;
					arr[j]=arr[j-przyrost];
					j-=przyrost;
				} else {
					break;
				}
			}
			swaps++;
			arr[j]=key;

		}
		przyrost=(pow(3,kMax--)-1)/2;

	}
}

void ShellDemo(int arr[], int n) {
	int przyrost=1,kMax=1;
	while (przyrost<n) {
		przyrost=(pow(3,kMax)-1)/2;
		kMax++;
	}
	if (przyrost>=n) {
		przyrost=(pow(3,kMax--)-1)/2;
	}
	while (przyrost>0) {
	    
	    printf("Przyrost: %d\n", przyrost);

		for (int i=przyrost; i<n; i++) {
			int key=arr[i];
			int j=i;

			while (j >= przyrost) {
				comparisons++;
				if (arr[j - przyrost]<key) {
					swaps++;
					arr[j]=arr[j-przyrost];
					j-=przyrost;
				} else {
					break;
				}
			}
			swaps++;
			arr[j]=key;

		}
		przyrost=(pow(3,kMax--)-1)/2;

	}
}

// MERGE SORT

void merge(int arr[],int leftIndex,int midlle,int rightIndex) {
    
    merges++;
    
    int i=0,j=0,k=leftIndex;

    int lenghtOfLeft= midlle - leftIndex + 1;
    int lenghtOfRight= rightIndex - midlle;

    int *LeftSubArray=malloc(sizeof(int) * lenghtOfLeft);
    int *RightSubArray=malloc(sizeof(int) * lenghtOfRight);

    for (i=0;i<lenghtOfLeft;i++) {
        LeftSubArray[i]=arr[leftIndex+i];
    }

    for (j=0;j<lenghtOfRight;j++) {
        RightSubArray[j]=arr[midlle+j+1];
    }
    i = 0;
    j = 0;

    while (i < lenghtOfLeft && j < lenghtOfRight) {
        comparisons++;
        if (LeftSubArray[i] < RightSubArray[j]) {
            arr[k++] = LeftSubArray[i++];
        } else {
            arr[k++] = RightSubArray[j++];
        }
    }

    while (i < lenghtOfLeft) {
        arr[k++] = LeftSubArray[i++];
    }

    while (j < lenghtOfRight) {
        arr[k++] = RightSubArray[j++];
    }

    free(LeftSubArray);
    free(RightSubArray);

}

void mergeSort(int arr[], int leftIndex,int rightIndex){
    if (leftIndex < rightIndex) {
        int midlle=leftIndex+(rightIndex-leftIndex)/2;
        mergeSort(arr,leftIndex,midlle);
        mergeSort(arr,midlle+1,rightIndex);
        merge(arr,leftIndex,midlle,rightIndex);

    }

}

// HEAP SORT

void restoreHeap(int arr[], int length,int initialRoot) {
    int indexOfSmallest=initialRoot;
    int left=2*indexOfSmallest+1;
    int right=2*indexOfSmallest+2;
    if (left<length ) {
        comparisons++;
        if (arr[left] < arr[indexOfSmallest]) {
            indexOfSmallest = left;
        }
    }
    if (right<length) {
        comparisons++;
        if (arr[right] < arr[indexOfSmallest]) {
            indexOfSmallest = right;
        }
    }//szukanie najmniejszego
    if (indexOfSmallest !=initialRoot) {
        swaps++;
        int tmp = arr[initialRoot];
        arr[initialRoot] = arr[indexOfSmallest];
        arr[indexOfSmallest] = tmp;// jak był jakiś mniejszy to podmieniamy
        restoreHeap(arr, length, indexOfSmallest);//rekurencyjne wywoływanie
    }
}
void buildHeap(int arr[], int length) {
    for (int i=length/2-1;i>=0;i--) {
        restoreHeap(arr, length, i);//dla każdego nie liścia naprawamy stos
    }
}
void heapSort(int arr[], int length) {
    for (int i = length - 1; i > 0; i--) {//i robi za ostatni index nieprzesortowanej czesci i za to żeby wywołało się n razy
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        swaps++;

        restoreHeap(arr, i, 0);
    }

}

// RECURSIVE QUICK SORT

int Partition(int A[], int p, int r){
    int x = A[p];
    int i = p;
    int j = r;
    while(1){
        while(A[i]>x){
		    comparisons++;
		    i++;
		}
        while(A[j]<x){
		    comparisons++;
		    j--;
		}
        if(i<j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
			swaps++;
            i++; j--;
        } else return j;
    }
}

void Qsort(int A[], int p, int r){
    if(p<r){
        int q = Partition(A, p, r);
        Qsort(A, p, q);
        Qsort(A, q+1, r);
    }
}

int PartitionDemo(int A[], int p, int r){
    int x = A[p];
    printf("Pivot: %d\n", x);
    int i = p;
    int j = r;
    while(1){
        while(A[i]>x){
		    comparisons++;
		    i++;
		}
        while(A[j]<x){
		    comparisons++;
		    j--;
		}
        if(i<j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
			swaps++;
            i++; j--;
        } else return j;
    }
}

void QsortDemo(int A[], int p, int r){
    if(p<r){
        int q = PartitionDemo(A, p, r);
        QsortDemo(A, p, q);
        QsortDemo(A, q+1, r);
    }
}

// ITERATIVE QUICK SORT (ALSO USES THE SAME Partition())

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

void QsortIterativeDemo(int A[], int p, int r) {
	int stack[r-p+1];
	int top = -1;
	stack[++top] = p;
	stack[++top] = r;
	while(top>=0) {
		r = stack[top--];
		p = stack[top--];
		int q = PartitionDemo(A, p, r);
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

// UTILS

void wypiszTablice(int tab[], int n)
{
    for(int i=0;i<n;i++)
        printf("%d ", tab[i]);
    printf("\n");
}

int main()
{
	int wyborAlg;
    int wyborDanych;
    int n;

    clock_t start, stop;
    double czas;

    printf("===== WYBOR ALGORYTMU =====\n");
    printf("1. Shell Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Heap Sort\n");
    printf("4. Quick Sort rekurencyjny\n");
    printf("5. Quick Sort iteracyjny\n");
    printf("Wybor: ");
    scanf("%d",&wyborAlg);

    printf("\n===== DANE =====\n");
    printf("1. Wprowadz recznie\n");
    printf("2. Generator losowy\n");
    printf("Wybor: ");
    scanf("%d",&wyborDanych);

    printf("\nPodaj liczbe elementow: ");
    scanf("%d",&n);

    int demo = 0;
    if(n <= 12)
        demo = 1;

    int tab[n];

    /* wczytywanie danych */

    if(wyborDanych == 1)
    {
        printf("\nPodaj liczby:\n");

        for(int i=0;i<n;i++)
        {
            printf("a[%d] = ", i);
            scanf("%d",&tab[i]);
        }
    }
    else
    {
        srand(time(NULL));

        for(int i=0;i<n;i++)
            tab[i] = rand()%1000;
    }

    if(demo)
    {
        printf("\nCIAG WEJSCIOWY:\n");
        wypiszTablice(tab,n);
    }

    /* zerowanie liczników */
    comparisons = 0;
    swaps = 0;

    /* pomiar czasu */
    start = clock();

    switch(wyborAlg)
    {
        case 1:
            if (demo)
            {
                ShellDemo(tab,n);
            }
            else
            {
                Shell(tab,n);
            }
            break;

        case 2:
            merges = 0;
            mergeSort(tab,0,n-1);
            if (demo) printf("Scaleń: %lld\n", merges);
            break;

        case 3:
            buildHeap(tab,n);
            heapSort(tab,n);
            break;

        case 4:
            if (demo)
            {
                QsortDemo(tab,0,n-1);
            }
            else
            {
                Qsort(tab,0,n-1);
            }
            break;

        case 5:
            if (demo)
            {
                QsortIterativeDemo(tab,0,n-1);
            }
            else
            {
                QsortIterative(tab,0,n-1);
            }
            break;

        default:
            printf("Bledny wybor\n");
            return 0;
    }

    stop = clock();

    czas = (double)(stop-start)/CLOCKS_PER_SEC;

    if(demo)
    {
        printf("\nCIAG WYJSCIOWY:\n");
        wypiszTablice(tab,n);
    }

    printf("\n===== STATYSTYKI =====\n");

    printf("Czas sortowania: %f s\n", czas);
    printf("Liczba porownan: %lld\n", comparisons);
    printf("Liczba zamian: %lld\n", swaps);


	return 0;
}