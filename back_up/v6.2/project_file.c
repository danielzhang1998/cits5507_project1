/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 1 Sep 2021
*/

#include <ctype.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


double *copy_array_to_array(double *target, double *source, int start, int end);
double *deep_copy(double *array, int start, int size);
double *enum_sort(double *array, size_t array_length);
double *generate_array(size_t value);
double *start_enum(double *array, size_t array_length);
double *start_merge(double *array, size_t array_length);
double *start_omp_merge(double *array, size_t array_length);
double *start_omp_quick(double *array, size_t array_length);
double *start_quick(double *array, size_t array_length);

int compare_result(double *array_1, double *array_2, double *array_3, size_t array_length);
int quick_sort_looping(double *array, int left, int right);

void merge_sort(double *array, int start, int end);
void merge_sort_looping(double *array, int start, int end);
void omp_merge(double *array, int start, int end);
void omp_quick(double *array, int left, int right);
void print_array(double *array, int array_size);
void print_time_distance(struct timeval time1, struct timeval time2);
void quicksort(double *array, int left, int right);


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
 * @brief copy array A to array B (can decide copy from position x to y)
 * @param target the target array to copy data into it
 * @param source the source array to get the copied data
 * @param start the position of source array to start copy
 * @param end the position of source array to stop copy
 *
 * @return return the new array after copy data in
*/
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
double *deep_copy(double *array, int start, int size){
    double *array_1 = malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++)
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
            int half = (start + end) / 2;
            merge_sort(array, start, half);
            merge_sort(array, half + 1, end);
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
    int pointer = 0;
    double *temp = malloc(sizeof(double) * (end - start + 1));

    int left = start;
    int right = half + 1;

    while((left <= half) && (right <= end)) {
        if (array[left] < array[right]) 
            temp[pointer++] = array[left++];
        else 
            temp[pointer++] = array[right++];
    }

    while(left <= half) 
        temp[pointer++] = array[left++];
    
    while(right <= end) 
        temp[pointer++] = array[right++];

    for(int i = start; i <= end; i++) 
        array[i] = temp[i - start];

    free(temp);
}

void omp_merge(double *array, int start, int end){
    if(start < end){
        if((end - start) > 100000){
            int middle = (start + end) / 2;
            #pragma omp parallel num_threads(2)
            {
                #pragma omp single
                {
                    #pragma omp task firstprivate(array, start, middle)
                    omp_merge(array, start, middle);
                    #pragma omp task firstprivate(array, middle, end)
                    omp_merge(array, middle + 1, end);
                }
            }

            #pragma omp taskwait
            merge_sort_looping(array, start, end);  
            
        }
        else{
            merge_sort(array, start, end);
        }
        }
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
 * @brief print the time distance of two time point
 * @param time1 the earlier time point
 * @param time2 the later time point
 *
*/
void print_time_distance(struct timeval time1, struct timeval time2){
    double distance = ((time2.tv_sec  - time1.tv_sec) * 1000000u + time2.tv_usec - time1.tv_usec) / 1.e6;
    printf("time spent = %12.10f\n",distance);
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


/** 
 * @brief start running enum algorithm
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using enum algorithm
*/
double *start_enum(double *array, size_t array_length){
    double *array_enum = deep_copy(array, 0, array_length);
    //printf("array after enum sort:\n");
    array_enum = enum_sort(array_enum, array_length);
    // uncomment the line below to see the array after sorting
    //print_array(array_enum, array_length);

    return array_enum;
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


double *start_omp_merge(double *array, size_t array_length){
    double *array_omp_merge = deep_copy(array, 0, array_length);

    omp_merge(array, 0, array_length -1);
    
    
    //print_array(array, array_length);
    return array;
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


/** 
 * @brief start running quick algorithm
 * @param array array to be copied
 * @param array_length the length to be copied
 *
 * @return return the result after using quick algorithm
*/
double *start_quick(double *array, size_t array_length){
    double *array_quick = deep_copy(array, 0, array_length);
    //printf("array after quick sort:\n");
    quicksort(array_quick, 0, array_length - 1);
    // uncomment the line below to see the array after sorting
    //print_array(array_quick, array_length);
    
    return array_quick;
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    struct timeval start, middle, end;
    if ((argc != 3 && argc != 4) || atoi(argv[1]) <= 0 || (argc == 4 && strcmp(argv[3], "-omp") != 0))
    {
        printf("To run the specific sorting algorithm without using omp: ./OUT_FILE SEED_NUMBER SORTING_ALGORITHM\n");
        printf("To run the specific sorting algorithm with using omp: ./OUT_FILE SEED_NUMBER SORTING_ALGORITHM -omp\n");
        printf("Sorting algorithm include: enum, quick, merge and all(run all three sorting algorithms)\n");
        return -1;
    }

    //  the array_length should be larger than 40000
    size_t array_length = atoi(argv[1]);    //  convert char type to int type
    double *array = generate_array(array_length);

    // uncomment two lines below to see the original array before sorting
    //printf("original array:\n");
    //print_array(array, array_length);

    if(strcmp(argv[2], "enum") == 0 && argc == 3){
        start_enum(array, array_length);
    }
    else if(strcmp(argv[2], "quick") == 0 && argc == 3){
        start_quick(array, array_length);
    }
    else if(strcmp(argv[2], "merge") == 0 && argc == 3){
        start_merge(array, array_length);
    }
    else if(argc == 3){
        double *array_quick = start_quick(array, array_length);
        double *array_enum = start_enum(array, array_length);
        double *array_merge = start_merge(array, array_length);

        compare_result(array_quick, array_enum, array_merge, array_length);
    }

    if(argc == 4){
        if(strcmp(argv[2], "quick") == 0){
            gettimeofday(&start, NULL);
            double *array_quick = start_quick(array, array_length);
            gettimeofday(&middle, NULL);
            print_time_distance(start, middle);
            double *omp_quick_result = start_omp_quick(array, array_length);
            
            gettimeofday(&end, NULL);
            print_time_distance(middle, end);
            compare_result(array_quick, array_quick, omp_quick_result, array_length);
        }
        else if(strcmp(argv[2], "merge") == 0){
            gettimeofday(&start, NULL);
            double *array_merge = start_merge(array, array_length);
            gettimeofday(&middle, NULL);
            print_time_distance(start, middle);
            double *omp_merge_result = start_omp_merge(array, array_length);

            gettimeofday(&end, NULL);
            print_time_distance(middle, end);
            //print_array(omp_merge_result, array_length);
            compare_result(array_merge, array_merge, omp_merge_result, array_length);
        }
    }

    free(array);
    
    return 0;
}