#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "enum.cpp"

double *main_enum_and_omp_enum(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end);
void omp_enum(double *array, double *array_new, size_t value);
double *start_omp_enum(double *array, size_t array_length);

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
double *main_enum_and_omp_enum(double *array, size_t array_length, struct timeval start, struct timeval middle, struct timeval end)
{
    gettimeofday(&start, NULL);
    double *array_enum = start_enum(array, array_length);
    gettimeofday(&middle, NULL);
    printf("enum:\n");

    double no_omp = common_enum::print_time_distance(start, middle);
    double *omp_enum_result = start_omp_enum(array, array_length);

    gettimeofday(&end, NULL);
    printf("enum using omp:\n");
    double has_omp = common_enum::print_time_distance(middle, end);
    //print_array(omp_enum_result, array_length);
    common_enum::compare_result(array_enum, array_enum, omp_enum_result, array_length);
    common_enum::print_ratio(no_omp, has_omp);

    return omp_enum_result;
}

/** 
 * @brief use enumeration algorithm to sort the list
 * loop the array, compare each elements with others
 * count the number of element x that smaller than it
 * then put it at position x of the empty array
 * repeat the step above until loop to the end of array
 * @param array the array to be sorted
 * @param array_new the empty array to save the sort result
 * @param value length of the input array
 *
 * @return the new array after sorted
 */
void omp_enum(double *array, double *array_new, size_t value)
{
    //int i, j, count_smaller;
    int count_smaller;
#pragma omp parallel
    {
#pragma omp for reduction(+ \
                          : count_smaller)
        for (int i = 0; i < value; i++)
        {
            count_smaller = 0;
            for (int j = 0; j < value; j++)
            {
                if (array[j] < array[i])
                    count_smaller += 1;
            }
            array_new[count_smaller] = array[i];
        }

//  if there have multi repeat values, all the value will be place at the same space by using this algorithm
//  but there is a rule, the empty space value will be same with the space value of array[pos - 1]
//  so loop the array and find the empty space, if exists, use the last space value instead it
#pragma omp for
        for (size_t i = 0; i < value; i++)
        {
            if (array_new[i] == 0)
                array_new[i] = array_new[i - 1];
        }
    }
}

/** 
 * @brief start running enum algorithm using omp
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using omp enum algorithm
 */
double *start_omp_enum(double *array, size_t array_length)
{
    double *array_enum = common_enum::deep_copy(array, 0, array_length);
    double *array_new = (double *)malloc(sizeof(double) * array_length);
    //printf("array after enum sort:\n");
    omp_enum(array_enum, array_new, array_length);
    // uncomment the line below to see the array after sorting
    //print_array(array_enum, array_length);

    return array_new;
}