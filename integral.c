#include <stdio.h>
#include <math.h>

#include <omp.h>

#define MAX_THREADS 4
 
double function_to_integrate(float x) {
    return pow(x, 3) / 3;
}

double integrate(double (*func)(float), float x_start, float x_end) {
    double result = 0;
    int total_steps = 10000;
    float increment_in_each_step = (x_end - x_start) / total_steps;
    for (
            double current_step = x_start + increment_in_each_step;
            current_step <= x_end; 
            current_step += increment_in_each_step) {
        result += (increment_in_each_step * func(current_step));
    }
    return result;
}

double integrate_parallel(double (*func)(float), float x_start, float x_end) {
    double result_of_each_thread[MAX_THREADS] = {0.0};
    double total_result = 0;
    #pragma omp parallel 
    {
        int current_threads_number = omp_get_num_threads();
        int id = omp_get_thread_num();
        float length = (x_end - x_start) / current_threads_number;
        float relative_x_start = x_start + (length * id);
        double partial_result = integrate(func, relative_x_start, relative_x_start + length); 
        result_of_each_thread[id] = partial_result;
        printf("relative result: id: %d, len: %f, x: %f, result: %f\n", id, length, relative_x_start, partial_result);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        total_result += result_of_each_thread[i];
    }
    return total_result;

}

int main ()  
{
   int nthreads = MAX_THREADS;
   omp_set_num_threads(nthreads);

   double result = integrate_parallel(&function_to_integrate, 0, 10);

   printf("All done. Result: %f \n", result);

}

 

