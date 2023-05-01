#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int counter = 0; //number of comparisons
int swap = 0; //number of swaps

static long long randll(void) { //random long long int number generator (2)
    long long num = 0;
    for (int i = 0; i < 5; i++) {
        num = (num << 15) ^ (rand() & 0x7FFF);
    }
    return num;
}

static void rand_arr(int size, long long* arr, int type) { //filling the array according to the type
    long long edge = randll(), buf;
    int k = 1;
    if (type == 1 || type == 2) { //type 1 and 2
        for (int i = 0; i < size; i++) {
            buf = randll();
            if (type == 1) { //sorting by non-decreasing (straight order) (1)
                if (buf >= edge) arr[i] = buf;
                else arr[i] = edge + llabs(randll() % (0x7FFFFFFFFFFFFFFF - llabs(edge)) / k);
            }
            else if (type == 2) { //sorting by non-growth (in reversed order)
                if (buf <= edge) arr[i] = buf;
                else arr[i] = edge - llabs(randll() % (0x7FFFFFFFFFFFFFFF - llabs(edge)) / k);
            }
            edge = arr[i];
            if (k < 256) k *= 2;
        }
    }
    else if (type == 3 || type == 4) { //random array filling
        for (int i = 0; i < size; i++) {
            arr[i] = randll();
        }
    }
}

static int order(long long a1, long long a2) { //comparison of two ellements
    counter++;
    return a1 < a2;
}

static void selection_sort(long long* a, int size) { //selection sort (2)
    int min_index = 0; long long min_num = 0, tmp = 0;
    for (int i = 0; i < size; i++) {
        min_num = a[i];
        min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (order(a[j], min_num)) {
                min_num = a[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            tmp = a[i];
            a[i] = a[min_index];
            a[min_index] = tmp;
            swap++;
        }
    }
    printf("Selection sort:\n  Number of comparisons: %d\n  Number of swaps:       %d\n", counter, swap);
    counter = 0; swap = 0;
}

static void Shell_sort(long long* a, int size) { //Shell sort (3)
    long long buf = 0;
    for (int i = size / 2; i >= 1; i /= 2) {
        for (int j = i; j < size; j++) {
            buf = a[j];
            for (int q = j - i; (q >= 0) && order(buf, a[q]); q -= i) {
                a[q + i] = a[q];
                a[q] = buf;
                swap++;
            }
        }
    }
    printf("Shell method:\n  Number of comparisons: %d\n  Number of swaps:       %d\n", counter, swap);
    counter = 0; swap = 0;
}

static int compare(const void* i, const void* j) {
    long long a = *(long long*)i, b = *(long long*)j;
    if (a < b) return -1;
    else if (a == b) return 0;
    else return 1;
}

static void tester(long long* arr1, int size1, long long* arr2, int size2) { //testing function
    if (size1 != size2) {
        printf("    Sorting is incorrect! :(\n");
    }
    else {
        long long* tmp = (long long*)malloc(sizeof(long long) * size1);
        memcpy(tmp, arr1, sizeof(long long) * size1);
        qsort(tmp, size1, sizeof(long long), compare);
        for (int i = 0; i < size1; i++) {
            if (tmp[i] != arr2[i]) {
                printf("    Sorting is incorrect! :(\n");
                break;
            }
            if (i == size1 - 1) printf("    Sorting is correct +\n");
        }
        free(tmp);
    }
}

int main(void) {
    srand(time(NULL));
    long long* a, * sh, * ss; int n;
    if (scanf("%d", &n) != 1) {
        printf("Error: failed to read array size!\n");
        exit(-1);
    }
    a = (long long*)malloc(sizeof(long long) * n); //original array
    sh = (long long*)malloc(sizeof(long long) * n); //array for Shell sort
    ss = (long long*)malloc(sizeof(long long) * n); //array for Selection sort
    printf("\n______________________________\n");
    for (int i = 1; i <= 4; i++) {
        printf("Current array type is: %d\n", i);
        rand_arr(n, a, i);
        memcpy(sh, a, n * sizeof(long long));
        memcpy(ss, a, n * sizeof(long long));
        selection_sort(ss, n);
        tester(a, n, ss, n);
        Shell_sort(sh, n);
        tester(a, n, sh, n);
        printf("______________________________\n\n");
    }
    free(a); free(sh); free(ss);
    return 0;
}