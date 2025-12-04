#include "contract.h"
#include <math.h>

/**
 * РЕАЛИЗАЦИЯ 1: Наивный алгоритм проверки простоты
 * Проверяем делимость числа на все числа от 2 до sqrt(n)
 */
static int is_prime_naive(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    int sqrt_n = (int)sqrt(n);
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * Подсчёт простых чисел наивным методом
 */
int PrimeCount(int A, int B) {
    if (A < 1 || B < 1 || A > B) {
        return 0;
    }
    
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (is_prime_naive(i)) {
            count++;
        }
    }
    return count;
}

/**
 * РЕАЛИЗАЦИЯ 1: Площадь прямоугольника
 * S = A * B
 */
float Square(float A, float B) {
    if (A <= 0 || B <= 0) {
        return 0.0f;
    }
    return A * B;
}