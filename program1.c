#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contract.h"

int main() {
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║  ПРОГРАММА 1: Линковка на этапе компиляции                ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    printf("Используется: libimpl1.so (через linking)\n");
    printf("  - PrimeCount: Наивный алгоритм O(n*sqrt(n))\n");
    printf("  - Square: Прямоугольник S = A * B\n\n");
    
    printf("Команды:\n");
    printf("  1 A B  - PrimeCount(A, B) - количество простых чисел [A,B]\n");
    printf("  2 A B  - Square(A, B) - площадь фигуры\n");
    printf("  exit   - выход\n\n");
    
    char command[256];
    
    while (1) {
        printf(">>> ");
        fflush(stdout);
        
        if (! fgets(command, sizeof(command), stdin)) {
            break;
        }
        
        // Проверка на exit
        if (strncmp(command, "exit", 4) == 0) {
            printf("Выход из программы.\n");
            break;
        }
        
        int cmd;
        if (sscanf(command, "%d", &cmd) != 1) {
            printf("❌ Ошибка: неверная команда\n\n");
            continue;
        }
        
        if (cmd == 1) {
            // PrimeCount
            int A, B;
            if (sscanf(command, "%d %d %d", &cmd, &A, &B) == 3) {
                printf("Вызов: PrimeCount(%d, %d)\n", A, B);
                int result = PrimeCount(A, B);
                printf("✓ Результат: %d\n\n", result);
            } else {
                printf(" Ошибка: используйте '1 A B' (например: 1 10 50)\n\n");
            }
        } 
        else if (cmd == 2) {
            // Square
            float A, B;
            if (sscanf(command, "%d %f %f", &cmd, &A, &B) == 3) {
                printf("Вызов: Square(%.2f, %.2f)\n", A, B);
                float result = Square(A, B);
                printf("✓ Результат: %.2f\n\n", result);
            } else {
                printf(" Ошибка: используйте '2 A B' (например: 2 5. 5 10)\n\n");
            }
        } 
        else {
            printf(" Неизвестная команда: %d\n\n", cmd);
        }
    }
    
    return 0;
}