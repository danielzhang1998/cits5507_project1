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
#include "merge.c"


double *start_omp_merge(double *array, size_t array_length);

void omp_merge(double *array, int start, int end);


/**
 * @brief run the merge algorithm with using omp
 * @param array the array to be sorted
 * @param start the start of the array
 * @param end the end of the array
 * 
 */
void omp_merge(double *array, int start, int end){
    if(start < end){
        if((end - start) > 100000){
            int middle = (start + end) / 2;
            #pragma omp parallel
            {
                #pragma omp single nowait
                {
                    #pragma omp task firstprivate(array, start, middle)
                    omp_merge(array, start, middle);    //array1 (left)
                    #pragma omp task firstprivate(array, middle, end)
                    omp_merge(array, middle + 1, end);  //array2 (right)
                }
            }
            //wait for the task finished, then sort the array
            #pragma omp taskwait
            merge_sort_looping(array, start, end);  
            
        }
        else{
            merge_sort(array, start, end);
        }
        }
}


/** 
 * @brief start running omp merge algorithm
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using omp merge algorithm
 */
double *start_omp_merge(double *array, size_t array_length){
    omp_merge(array, 0, array_length -1);
    //print_array(array, array_length);
    return array;
}