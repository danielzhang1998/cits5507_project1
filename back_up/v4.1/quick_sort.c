#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *generate_array(int value);
void quicksort(double *array, int left, int right);
double *deep_copy(double *array, size_t size);
int looping(double *array, int left, int right);
void print_array(double *array, int array_size);

double *deep_copy(double *array, size_t size){
    double *array_1 = malloc(sizeof(double) * size);
    for (size_t i = 0; i < size; i++){
        array_1[i] = array[i];
    }
    return array_1;
}

double *generate_array(int value) {
    double *array = malloc(sizeof(double) * value);
    for (int i = 0; i < value; i++){
        array[i] = (double)rand() / RAND_MAX * 1000;
    }
    return array;
}

int looping(double *array, int left, int right){
    if(left > right){
        return 0;
    }
    double temp = array[left];
    while(left < right){
        while(left < right && array[right] >= temp){
            right--;
        }
        array[left] = array[right];
        while(left < right && array[left] <= temp){
            left++;
        }
        array[right] = array[left];
    }
    array[left] = temp;
    return left;
}

void print_array(double *array, int array_size){
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%lf\n", array[i]);
    }
}

void quicksort(double *array, int left, int right){
    if(left < right){
        int pointer = looping(array, left, right);
        quicksort(array, left, pointer - 1);
        quicksort(array, pointer + 1, right);
    }
}

int main()
{
    srand(time(NULL));
    size_t array_length = 10;
    double *array = generate_array(array_length);
    double *array_copy = deep_copy(array, array_length);
    print_array(array, array_length);
    printf("\n\n");
    quicksort(array_copy, 0, array_length - 1);
    print_array(array_copy, array_length);
    free(array);
    free(array_copy);
    return 0;
}