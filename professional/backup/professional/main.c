/*
    Author: Hanlin Zhang
    Student id: 22541459
    Unit: CITS 5507
    Date: 2 Sep 2021
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

    //  the array_length should be larger than 60000
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
        free(array_quick);
        free(array_enum);
        free(array_merge);
    }

    if(argc == 4){
        if(strcmp(argv[2], "quick") == 0){
            main_quick_and_omp_quick(array, array_length, start, middle, end);
        }
        else if(strcmp(argv[2], "merge") == 0){
            main_merge_and_omp_merge(array, array_length, start, middle, end);
        }
        else if(strcmp(argv[2], "enum") == 0){
            main_enum_and_omp_enum(array, array_length, start, middle, end);
        }
        else{
            double *omp_quick_result = main_quick_and_omp_quick(array, array_length, start, middle, end);
            printf("\n");
            double *omp_merge_result = main_merge_and_omp_merge(array, array_length, start, middle, end);
            printf("\n");
            double *omp_enum_result = main_enum_and_omp_enum(array, array_length, start, middle, end);
            printf("\n");
            compare_result(omp_quick_result, omp_merge_result, omp_enum_result, array_length);
            free(omp_quick_result);
            free(omp_merge_result);
            free(omp_enum_result);
        }
    }

    free(array);
    
    return 0;
}