/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 17 Sep 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *start_quick(double *array, size_t array_length);

int quick_sort_looping(double *array, int left, int right);

void quicksort(double *array, int left, int right);


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
 * @brief start running quick algorithm
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using quick algorithm
 */
double *start_quick(double *array, size_t array_length)
{

    quicksort(array, 0, array_length - 1);
    // uncomment the line below to see the array after sorting
    //print_array(array_quick, array_length);

    return array;
}