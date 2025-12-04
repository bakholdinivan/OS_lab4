#include "contract.h"
#include <stdlib.h>
#include <string.h>

/**
 * РЕАЛИЗАЦИЯ 2: Решето Эратосфена
 * Более эффективный алгоритм для нахождения всех простых чисел до N
 */
int PrimeCount(int A, int B) {
    if (A < 1 || B < 1 || A > B) {
        return 0;
    }
    
    // Создаём массив для решета
    int size = B + 1;
    char *is_prime = (char*)malloc(size * sizeof(char));
    if (!is_prime) {
        return 0;
    }
    
    // Инициализация: все числа считаем простыми
    memset(is_prime, 1, size);
    is_prime[0] = is_prime[1] = 0; // 0 и 1 не простые
    
    // Решето Эратосфена
    for (int i = 2; i * i <= B; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= B; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    
    // Подсчёт простых чисел на отрезке [A, B]
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (is_prime[i]) {
            count++;
        }
    }
    
    free(is_prime);
    return count;
}

/**
 * РЕАЛИЗАЦИЯ 2: Площадь прямоугольного треугольника
 * S = (A * B) / 2
 */
float Square(float A, float B) {
    if (A <= 0 || B <= 0) {
        return 0.0f;
    }
    return (A * B) / 2.0f;
}