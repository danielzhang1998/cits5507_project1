#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "merge.cpp"

double *main_merge_and_omp_merge(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);
double *start_omp_merge(double *array, size_t array_length);

void omp_merge(double *array, int start, int end);

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
double *main_merge_and_omp_merge(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end)
{
    gettimeofday(&start, NULL);
    double *array_merge = start_merge(array, array_length);
    gettimeofday(&middle, NULL);
    printf("merge:\n");
    double no_omp = common_merge::print_time_distance(start, middle);
    double *omp_merge_result = start_omp_merge(array, array_length);

    gettimeofday(&end, NULL);
    printf("merge using omp:\n");
    double has_omp = common_merge::print_time_distance(middle, end);
    //print_array(omp_merge_result, array_length);
    common_merge::compare_result(array_merge, array_merge, omp_merge_result, array_length);
    common_merge::print_ratio(no_omp, has_omp);

    return omp_merge_result;
}

/**
 * @brief run the merge algorithm with using omp
 * @param array the array to be sorted
 * @param start the start of the array
 * @param end the end of the array
 * 
 */
void omp_merge(double *array, int start, int end)
{
    if (start < end)
    {
        if ((end - start) > 100000)
        {
            int middle = (start + end) / 2;
#pragma omp parallel
            {
#pragma omp single nowait
                {
#pragma omp task firstprivate(array, start, middle)
                    omp_merge(array, start, middle); //array1 (left)
#pragma omp task firstprivate(array, middle, end)
                    omp_merge(array, middle + 1, end); //array2 (right)
                }
            }
//wait for the task finished, then sort the array
#pragma omp taskwait
            merge_sort_looping(array, start, end);
        }
        else
        {
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
double *start_omp_merge(double *array, size_t array_length)
{
    double *array_omp_merge = common_merge::deep_copy(array, 0, array_length);

    omp_merge(array_omp_merge, 0, array_length - 1);

    //print_array(array, array_length);
    return array_omp_merge;
}