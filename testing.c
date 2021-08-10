#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double *generate_array(int value) {
    double *array = malloc(sizeof(double) * (value + 1));
    for (int i = 0; i < value; i++){
        array[i] = (double)rand() / RAND_MAX;
    }
    array[value] = NAN;
    return array;
}

int main()
{
    srand(time(NULL));
    double *array = generate_array(10);
    for (size_t i = 0; !isnan(array[i]); i++){
        printf("%lf\n", array[i]);
    }
    free(array);
    return 0;
}
