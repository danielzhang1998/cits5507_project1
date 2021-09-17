/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 17 Sep 2021
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "quick.c"


double *start_omp_quick(double *array, size_t array_length);

void omp_quick(double *array, int left, int right);

/** 
 * @brief use omp to run the quick sort algorithm
 * @param array array to be sorted
 * @param left the pointer on the left hand side
 * @param right the pointer on the right hand side
 *
 */
void omp_quick(double *array, int left, int right){
    int pointer = quick_sort_looping(array, left, right - 1);
    #pragma omp parallel num_threads(2)
    {
        #pragma omp sections
        {
            #pragma omp section
            quicksort(array, 0, pointer - 1);
            #pragma omp section
            quicksort(array, pointer, right - 1);
        }
    }
}


/** 
 * @brief start running quick algorithm using omp
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using omp quick algorithm
 */
double *start_omp_quick(double *array, size_t array_length){
    //printf("array after omp quick sort:\n");
    omp_quick(array, 0, array_length);
    // uncomment the line below to see the array after sorting
    //print_array(array_omp_quick, array_length);

    return array;
}