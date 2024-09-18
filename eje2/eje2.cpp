//UVG
//Micro
//Dilary 231010

#include <iostream>
#include <pthread.h>
#include <cmath>

struct ThreadData {
    int n;
    double term;
};

void* calculateTerm(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->term = 1.0 / pow(2, data->n);
    return nullptr;
}

int main() {
    int maxN;

    std::cout << "Ingrese el valor maximo de n: ";
    std::cin >> maxN;

    pthread_t threads[maxN];
    ThreadData threadData[maxN];

    // Crear hilos para cada valor de n
    for (int i = 0; i < maxN; ++i) {
        threadData[i].n = i + 1;
        pthread_create(&threads[i], nullptr, calculateTerm, &threadData[i]);
    }

    // Join hilos y acumular la sumatoria
    double sum = 0.0;
    for (int i = 0; i < maxN; ++i) {
        pthread_join(threads[i], nullptr);
        sum += threadData[i].term;
    }

    std::cout << "Valor de la sumatoria: " << sum << std::endl;
    return 0;
}

