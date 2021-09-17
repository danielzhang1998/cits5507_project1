#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "quick.c"

double *main_quick_and_omp_quick(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);
double *start_omp_quick(double *array, size_t array_length);

void omp_quick(double *array, int left, int right);


/**
 * @brief main function to call the quick function and omp quick function together
 * @param array the original array
 * @param arrag_length the size of array
 * @param start store start time of the quick function
 * @param middle store end time of the quick function
 * @param end store end time of the omp quick function
 * 
 * @return the result after sort 
 */
double *main_quick_and_omp_quick(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end){
    gettimeofday(&start, NULL);
    double *array_quick = start_quick(array, array_length);
    gettimeofday(&middle, NULL);
    printf("quick:\n");
    double no_omp = print_time_distance(start, middle);
    double *omp_quick_result = start_omp_quick(array, array_length);
    
    gettimeofday(&end, NULL);
    printf("quick using omp:\n");
    double has_omp = print_time_distance(middle, end);
    compare_result(array_quick, array_quick, omp_quick_result, array_length);
    print_ratio(no_omp, has_omp);

    return omp_quick_result;
}


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
    double *array_omp_quick = deep_copy(array, 0, array_length);
    //printf("array after omp quick sort:\n");
    omp_quick(array_omp_quick, 0, array_length);
    // uncomment the line below to see the array after sorting
    //print_array(array_omp_quick, array_length);

    return array_omp_quick;
}