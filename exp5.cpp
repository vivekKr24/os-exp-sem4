#include <stdlib.h>
#include <iostream>
#include <pthread.h>

int* fib = new int[100];
int* n_val = new int[100];

void* F(void* arguments) {
    int n = *((int*)arguments);
    if (n <= 2) return (void*)nullptr;
    if(fib[n] != -1) return (void*)nullptr;

    pthread_t thread_1;
    pthread_create(&thread_1, NULL, F, (void*)(n_val + n - 1));

    pthread_t thread_2;
    pthread_create(&thread_2, NULL, F, (void*)(n_val + n - 2));
    
    pthread_join(thread_1,  NULL);
    pthread_join(thread_2,  NULL);

    fib[n] = fib[n - 1] + fib[n - 2];
    return (void*)nullptr;
}

int main() {
    for (int i = 0; i < 100; i++) {
        fib[i] = -1;
        n_val[i] = i;
    }

    fib[1] = fib[2] = 1;
    std::cin >> fib[0];

    F((void*)(n_val + fib[0]));
    for (int i = 1; i <= fib[0]; i++) {
        std::cout << fib[i] << ' ';
    }
}