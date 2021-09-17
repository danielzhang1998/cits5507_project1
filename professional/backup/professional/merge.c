#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_func.c"

double *start_merge(double *array, size_t array_length);

void merge_sort(double *array, int start, int end);
void merge_sort_looping(double *array, int start, int end);

/** 
 * @brief generate a new array to get the result after sorting
 * split the array to be two parts which called A and B
 * split A and B seperately by using recursion
 * repeat the step, until only 1 element inside, then compare each
 * put the smallest in two elements at the left, the biggest on the right
 * now repeat the step above, we get multiple arrays which contains 2 elements inside
 * then re-compare each array from left to right, sort them and merge two arrays
 * finally, we will get a sorted array
 * @param array the array need to be sorted
 * @param start the start of the current array
 * @param end the end of the current array
 * 
 */
void merge_sort(double *array, int start, int end){
        if(start < end) {
            int half = (start + end) / 2;   //middle of the array
            merge_sort(array, start, half); //array1 (left)
            merge_sort(array, half + 1, end);   //array2 (right)
            merge_sort_looping(array, start, end);
    }
}


/** 
 * @brief see description in function merge_sort
 * @param array the array need to be sorted
 * @param start the start of the current array
 * @param end the end of the current array
 * 
 */
void merge_sort_looping(double *array, int start, int end){
    int half = (start + end) / 2;
    int pointer = 0;    //  pointer move in the temp array
    double *temp = malloc(sizeof(double) * (end - start + 1));  //  save the values after sorting

    int left = start;   //  initialize the pointer at the top of array1
    int right = half + 1;   //  initialize the pointer at the top of array2 (middle + 1 of the parent array)

    //  compare the value in array1 and array2 from left to right
    //  if value1 < value2, put value1 into the temp array
    //  otherwise, put value2 in
    while((left <= half) && (right <= end)) {
        if (array[left] < array[right]) 
            temp[pointer++] = array[left++];
        else 
            temp[pointer++] = array[right++];
    }

    //  if still value(s) in array1 or array2
    while(left <= half) 
        temp[pointer++] = array[left++];
    
    while(right <= end) 
        temp[pointer++] = array[right++];
        
    //  copy temp array to original array
    //  tried to use copy_array_to_array function, but failed (the element number on two side (array) is different)
    for (int i = start; i <= end; i++)
        array[i] = temp[i - start];

    free(temp); //free the temp array
}


/** 
 * @brief start running merge algorithm
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using merge algorithm
 */
double *start_merge(double *array, size_t array_length){
    double *array_merge = deep_copy(array, 0, array_length);
    //print_array(array_merge, array_length);
    //printf("array after merge sort:\n");
    merge_sort(array_merge, 0, array_length - 1);
    // uncomment the line below to see the array after sorting
    //print_array(array_merge, array_length);
    
    return array_merge;
}