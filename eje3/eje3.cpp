//UVG
//Micro
//Dilary 231010

#include <iostream>
#include <pthread.h>

void* printHello(void* arg) {
    int threadNumber = *(int*)arg;
    std::cout << "Hello world thread No. " << threadNumber << std::endl;
    return nullptr;
}

int main() {
    const int numThreads = 5;
    pthread_t threads[numThreads];
    int threadIds[numThreads];

    // Primer programa: Crear hilos y luego join en un ciclo separado
    for (int i = 0; i < numThreads; ++i) {
        threadIds[i] = i + 1;
        pthread_create(&threads[i], nullptr, printHello, &threadIds[i]);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Segundo programa: Crear hilo y hacer join dentro del mismo ciclo
    std::cout << "\nSegundo ciclo con join inmediato:" << std::endl;
    for (int i = 0; i < numThreads; ++i) {
        threadIds[i] = i + 1;
        pthread_create(&threads[i], nullptr, printHello, &threadIds[i]);
        pthread_join(threads[i], nullptr);
    }

    return 0;
}

