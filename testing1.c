#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double *generate_array(int value) {
    double *array = malloc(sizeof(double) * value);
    for (int i = 0; i < value; i++){
        array[i] = (double)rand() / RAND_MAX;
    }
    return array;
}

int main()
{
    srand(time(NULL));
    size_t array_length = 10;
    double *array = generate_array(array_length);
    for (size_t i = 0; i < array_length; i++){
        printf("%lf\n", array[i]);
    }
    free(array);
    return 0;
}
