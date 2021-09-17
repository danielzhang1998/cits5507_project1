/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 17 Sep 2021
*/
#include <omp.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "enum_omp.c"
#include "merge_omp.c"
#include "quick_omp.c"
#include "tools.c"

double *main_enum_and_omp_enum(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);
double *main_merge_and_omp_merge(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);
double *main_quick_and_omp_quick(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);

/**
 * @brief main function to call the enum function and omp enum function together
 * @param array the original array
 * @param arrag_length the size of array
 * @param start store start time of the enum function
 * @param middle store end time of the enum function
 * @param end store end time of the omp enum function
 * 
 * @return the result after sort
 */
double *main_enum_and_omp_enum(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end){
    double *array_enum = deep_copy(array, 0, array_length);
    double *array_enum_omp = deep_copy(array, 0, array_length);
    gettimeofday(&start, NULL);
    printf("enum:\n");
    double *array_enum_result = start_enum(array_enum, array_length);
    gettimeofday(&middle, NULL);
    
    double no_omp = print_time_distance(start, middle);
    double *omp_enum_result = start_omp_enum(array_enum_omp, array_length);

    gettimeofday(&end, NULL);
    printf("enum using omp:\n");
    double has_omp = print_time_distance(middle, end);
    //print_array(omp_enum_result, array_length);
    compare_result(array_enum_result, array_enum_result, omp_enum_result, array_length);
    print_ratio(no_omp, has_omp);

    return omp_enum_result;
}


/**
 * @brief main function to call the merge function and omp merge function together
 * @param array the original array
 * @param arrag_length the size of array
 * @param start store start time of the merge function
 * @param middle store end time of the merge function
 * @param end store end time of the omp merge function
 * 
 * @return the result after sort 
 */
double *main_merge_and_omp_merge(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end){
    double *array_merge = deep_copy(array, 0, array_length);
    double *array_merge_omp = deep_copy(array, 0, array_length);
    gettimeofday(&start, NULL);
    printf("merge:\n");
    double *array_merge_result = start_merge(array_merge, array_length);
    gettimeofday(&middle, NULL);
    
    double no_omp = print_time_distance(start, middle);
    double *omp_merge_result = start_omp_merge(array_merge_omp, array_length);

    gettimeofday(&end, NULL);
    printf("merge using omp:\n");
    double has_omp = print_time_distance(middle, end);
    //print_array(omp_merge_result, array_length);
    compare_result(array_merge_result, array_merge_result, omp_merge_result, array_length);
    print_ratio(no_omp, has_omp);

    return omp_merge_result;
}


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
    double *array_quick = deep_copy(array, 0, array_length);
    double *array_quick_omp = deep_copy(array, 0, array_length);
    gettimeofday(&start, NULL);
    printf("quick:\n");
    double *array_quick_result = start_quick(array_quick, array_length);
    gettimeofday(&middle, NULL);
    
    double no_omp = print_time_distance(start, middle);
    double *omp_quick_result = start_omp_quick(array_quick_omp, array_length);
    
    gettimeofday(&end, NULL);
    printf("quick using omp:\n");
    double has_omp = print_time_distance(middle, end);
    compare_result(array_quick_result, array_quick_result, omp_quick_result, array_length);
    print_ratio(no_omp, has_omp);

    return omp_quick_result;
}