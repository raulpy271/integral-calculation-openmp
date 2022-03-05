#include <stdio.h>
#include <math.h>

#include <omp.h>
 
float function_to_integrate(float x) {
    return pow(x, 3);
}

float integrate(float (*func)(float), float x_start, float x_end) {
    float result = 0;
    int total_steps = 10000;
    float increment_in_each_step = (x_end - x_start) / total_steps;
    for (
            float current_step = x_start + increment_in_each_step;
            current_step <= x_end; 
            current_step += increment_in_each_step) {
        result += (increment_in_each_step * func(current_step));
    }
    return result;
}

int main ()  
{
   int nthreads = 4;
   omp_set_num_threads(nthreads);

   float result = integrate(&function_to_integrate, 0, 10);

   printf("All done. Result: %f \n", result);

}

 

