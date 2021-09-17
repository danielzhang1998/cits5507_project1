/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 17 Sep 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *deep_copy(double *array, int start, int size);
double *generate_array(size_t value);
double print_ratio(double no_omp, double has_omp);
double print_time_distance(struct timeval time1, struct timeval time2);

int compare_result(double *array_1, double *array_2, double *array_3, size_t array_length);

void print_array(double *array, int array_size);

/** 
 * @brief compare the element in the array_1 to see all the elements is in order or not, then 
 * compare the values in each array to see the arrays are same or difference
 * @param array_1 the array 1 to compare
 * @param array_2 the array 2 to compare
 * @param array_3 the array 3 to compare
 *
 * @return return 0 if all same, -1 if difference
 */
int compare_result(double *array_1, double *array_2, double *array_3, size_t array_length){
    int first_element = array_1[0];

    for (int i = 1; i < array_length; i++){
        if (i == 1){
            if (array_1[i] < first_element){
                printf("The array is not ordered!\n");
                return -1;
            }
        }
        else{
            if(array_1[i] < array_1[i - 1]){
                printf("The array is not ordered!\n");
                return -1;
            }
        }
    }

    for (int i = 0; i < array_length; i++)
    {
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


/** 
 * @brief deep copy the content from original array to target array
 * @param array the original array need to be copied 
 * @param size the size to be copied
 *
 * @return the new array that copy from original array
 */
double *deep_copy(double *array, int start, int size){
    double *array_1 = malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++)
        array_1[i] = array[i];
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


/** 
 * @brief print the array
 * @param array array to be printed
 * @param array_size length to be printed
 *
 */
void print_array(double *array, int array_size){
    for (size_t i = 0; i < array_size; i++)
        printf("%lf\n", array[i]);
    
    printf("\n\n");
}


/** 
 * @brief print ratio of two running time
 * @param no_omp time using with no omp
 * @param has_omp time using with omp
 *
 */
double print_ratio(double no_omp, double has_omp){
    double ratio = has_omp / no_omp;
    printf("ratio (has_omp / no_omp) = %12.10f\n", ratio);
    return ratio;
}


/** 
 * @brief print the time distance of two time point
 * @param time1 the earlier time point
 * @param time2 the later time point
 *
 */
double print_time_distance(struct timeval time1, struct timeval time2){
    double distance = ((time2.tv_sec  - time1.tv_sec) * 1000000u + time2.tv_usec - time1.tv_usec) / 1.e6;
    printf("time spent = %12.10f\n",distance);

    return distance;
}