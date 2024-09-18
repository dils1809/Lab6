//UVG
//Micro
//Dilary 231010

#include <iostream>
#include <pthread.h>
#include <vector>

struct ThreadData {
    int start;
    int end;
    int primeSum;
};

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

void* calculatePrimes(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->primeSum = 0;
    for (int i = data->start; i <= data->end; ++i) {
        if (isPrime(i)) {
            data->primeSum += i;
        }
    }
    return nullptr;
}

int main() {
    int maxValue, numThreads;

    std::cout << "Ingrese el valor maximo: ";
    std::cin >> maxValue;
    std::cout << "Ingrese la cantidad de hilos: ";
    std::cin >> numThreads;

    int rangePerThread = maxValue / numThreads;
    int remainder = maxValue % numThreads;

    std::vector<pthread_t> threads(numThreads);
    std::vector<ThreadData> threadData(numThreads);

    // Crear hilos
    for (int i = 0; i < numThreads; ++i) {
        threadData[i].start = i * rangePerThread;
        threadData[i].end = (i == numThreads - 1) ? maxValue : (i + 1) * rangePerThread - 1;
        pthread_create(&threads[i], nullptr, calculatePrimes, &threadData[i]);
    }

    // Join hilos y calcular la suma total de primos
    int totalPrimeSum = 0;
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
        totalPrimeSum += threadData[i].primeSum;
    }

    std::cout << "Suma total de numeros primos: " << totalPrimeSum << std::endl;
    return 0;
}

