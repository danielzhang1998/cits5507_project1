#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double *generate_array(int value);
double *deep_copy(double *array, size_t size);
void print_array(double *array, int array_size);
double *enum_sort(double *array, int array_length);

double *deep_copy(double *array, size_t size){
    double *array_1 = malloc(sizeof(double) * size);
    for (size_t i = 0; i < size; i++){
        array_1[i] = array[i];
    }
    return array_1;
}

double *enum_sort(double *array, int value){
    double *array_1 = malloc(sizeof(double) * value);
    
    for (size_t i = 0; i < value; i++){
        double number = array[i];
        int count_smaller = 0;
        for (size_t j = 0; j < value; j++){
            if (array[j] < number){
                count_smaller += 1;
            }
        }
        array_1[count_smaller] = number;
    }
    
    //  if there have multi repeat values, all the value will be place at the same space by using this algorithm
    //  but there is a rule, the empty space value will be same with the space value of array[pos - 1]
    //  so loop the array and find the empty space, if exists, use the last space value instead it
    for (size_t i = 0; i < value; i++){
        if (array_1[i] == 0){
            array_1[i] = array_1[i - 1];
        }
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



void print_array(double *array, int array_size){
    for (size_t i = 0; i < array_size; i++)
    {
        printf("%lf\n", array[i]);
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
    array_copy = enum_sort(array_copy, array_length);
    print_array(array, array_length);
    printf("\n\n");
    print_array(array_copy, array_length);
    free(array);
    free(array_copy);
    return 0;
}