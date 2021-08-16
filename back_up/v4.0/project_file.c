/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 17 Aug 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare_result(double *array_1, double *array_2, double *array_3, size_t array_length);
double *copy_array_to_array(double *target, double *source, int start, int end);
double *deep_copy(double *array, size_t start, size_t size);
double *enum_sort(double *array, size_t array_length);
double *generate_array(size_t value);
void merge_sort(double *array, size_t size);
void merge_sort_looping(double *array, double *array_new, int left, int right);
void print_array(double *array, int array_size);
void quicksort(double *array, int left, int right);
int quick_sort_looping(double *array, int left, int right);


int compare_result(double *array_1, double *array_2, double *array_3, size_t array_length){
    for (int i = 0; i < array_length; i++){
        if(array_1[i] == array_2[i] && array_2[i] == array_3[i]){
            //printf("%lf\n", array_1[i]);
            continue;
        }
        else{
            if(array_1[i] == array_2[i])
                printf("array 3 is different with others!");
            else if(array_2[i] == array_3[i])
                printf("array 1 is different with others!");
            else if(array_1[i] == array_3[i])
                printf("array 2 is different with others!");           
            else
                printf("the results are different!");
            return -1;
        }
    }

    printf("all correct!\n");
    return 0;
}

double *copy_array_to_array(double *target, double *source, int start, int end){
    for (int i = start; i <= end; i++){
        target[i] = source[i];
    }
    return target;
}

/** 
 * @brief deep copy the content from original array to target array
 * @param array the original array need to be copied 
 * @param size the size to be copied
 *
 * @return the new array that copy from original array
*/
double *deep_copy(double *array, size_t start, size_t size){
    double *array_1 = malloc(sizeof(double) * size);
    for (size_t i = 0; i < size; i++)
        array_1[i] = array[i];
    return array_1;
}


/** 
 * @brief use enumeration algorithm to sort the list
 * loop the array, compare each elements with others
 * count the number of element x that smaller than it
 * then put it at position x of the empty array
 * repeat the step above until loop to the end of array
 * @param array the array to be sorted
 * @param value length of the input array
 *
 * @return the new array after sorted
*/
double *enum_sort(double *array, size_t value){
    double *array_1 = malloc(sizeof(double) * value);
    
    for (size_t i = 0; i < value; i++){
        double number = array[i];
        int count_smaller = 0;
        for (size_t j = 0; j < value; j++){
            if (array[j] < number)
                count_smaller += 1;
        }
        array_1[count_smaller] = number;
    }
    
    //  if there have multi repeat values, all the value will be place at the same space by using this algorithm
    //  but there is a rule, the empty space value will be same with the space value of array[pos - 1]
    //  so loop the array and find the empty space, if exists, use the last space value instead it
    for (size_t i = 0; i < value; i++){
        if (array_1[i] == 0)
            array_1[i] = array_1[i - 1];
    }
    return array_1;
}


/** 
 * @brief generate a random double-precision floating-point array
 * @param value length of the array need to be generate
 *
 * @return return new array
*/
double *generate_array(size_t value) {
    double *array = malloc(sizeof(double) * value);
    for (int i = 0; i < value; i++)
        array[i] = (double)rand() / RAND_MAX * 1000;
    return array;
}


void merge_sort(double *array, size_t array_length){
    double *array_new = generate_array(array_length);
    merge_sort_looping(array, array_new, 0, array_length - 1);
}


void merge_sort_looping(double *array, double *array_new, int left, int right){
    if(left >= right)
        return;

    int pointer = left;
    int distance = right - left;
    int half = (distance / 2) + left;
    
    //  the array split into two part
    //  both array all have left pointer and right pointer
    //  left_l and right_l are the left pointer and right pointer for left hand side array
    //  left_r and right_r are the left pointer and right pointer for right hand side array

    int left_l = left;
    int right_l = half;

    int left_r = half + 1;
    int right_r = right;

    merge_sort_looping(array, array_new, left_l, right_l);
    merge_sort_looping(array, array_new, left_r, right_r);

    while(left_l <= right_l && left_r <= right_r){
        if(array[left_l] < array[left_r]){
            array_new[pointer] = array[left_l];
            left_l++;
        }
        else{
            array_new[pointer] = array[left_r];
            left_r++;
        }
        pointer++;
    }

    while(left_l <= right_l){
        array_new[pointer] = array[left_l];
        pointer++;
        left_l++;
    }

    while(left_r <= right_r){
        array_new[pointer] = array[left_r];
        pointer++;
        left_r++;
    }

    array = copy_array_to_array(array, array_new, left, right);
}


/** 
 * @brief print the array
 * @param array array to be printed
 * @param array_size length to be printed
 *
*/
void print_array(double *array, int array_size){
    for (size_t i = 0; i < array_size; i++)
        printf("%lf\n", array[i]);
    
}


/** 
 * @brief loop the array. In general, quick sort pick the first element, then compare each element with it
 * if element less than it, put at the left hand side. otherwise put at the right hand side
 * repeat the step above to sort the left array and right array by using recursion
 * @param left the pointer on the left
 * @param right the pointer on the right
 *
 * @return the pointer to be moved
*/
int quick_sort_looping(double *array, int left, int right){
    if(left > right)
        return 0;
    double temp = array[left];
    while(left < right){
        while(left < right && array[right] >= temp)
            right--;
        array[left] = array[right];
        while(left < right && array[left] <= temp)
            left++;
        array[right] = array[left];
    }
    array[left] = temp;
    return left;
}



/** 
 * @brief quick sort algorithm
 * see the description in looping function 
 * @param array array to be sorted 
 * @param left the left pointer
 * @param right the right pointer
*/
void quicksort(double *array, int left, int right){
    if(left < right){
        int pointer = quick_sort_looping(array, left, right);
        quicksort(array, left, pointer - 1);
        quicksort(array, pointer + 1, right);
    }
}


int main()
{
    srand(time(NULL));
    size_t array_length = 10;
    double *array = generate_array(array_length);

    double *array_quick = deep_copy(array, 0, array_length);
    double *array_enum = deep_copy(array, 0, array_length);
    double *array_merge = deep_copy(array, 0, array_length);

    printf("original array:\n");
    print_array(array, array_length);
    printf("\n\n");

    printf("array after quick sort:\n");
    quicksort(array_quick, 0, array_length - 1);
    print_array(array_quick, array_length);
    printf("\n\n");

    printf("array after enum sort:\n");
    array_enum = enum_sort(array_enum, array_length);
    print_array(array_enum, array_length);
    printf("\n\n");
    
    printf("array after enum sort:\n");
    merge_sort(array_merge, array_length);
    print_array(array_merge, array_length);
    printf("\n\n");

    compare_result(array_quick, array_enum, array_merge, array_length);

    free(array);
    free(array_quick);
    free(array_enum);
    free(array_merge);
    return 0;
}