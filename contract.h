#ifndef CONTRACT_H
#define CONTRACT_H

/**
 * Подсчёт количества простых чисел на отрезке [A, B]
 * @param A - начало отрезка (натуральное число)
 * @param B - конец отрезка (натуральное число)
 * @return количество простых чисел на отрезке
 */
int PrimeCount(int A, int B);

/**
 * Подсчет площади плоской геометрической фигуры по двум сторонам
 * @param A - первая сторона
 * @param B - вторая сторона
 * @return площадь фигуры
 */
float Square(float A, float B);

#endif // CONTRACT_H