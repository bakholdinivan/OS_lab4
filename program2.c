#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

// Типы указателей на функции
typedef int (*PrimeCountFunc)(int, int);
typedef float (*SquareFunc)(float, float);

// Структура для работы с библиотекой
typedef struct {
    void *handle;
    PrimeCountFunc prime_count;
    SquareFunc square;
    const char *lib_path;
    int lib_number;
} Library;

/**
 * Загрузка библиотеки по номеру (1 или 2)
 */
int load_library(Library *lib, int lib_num) {
    const char *path = (lib_num == 1) ?  "./libimpl1.so" : "./libimpl2.so";
    
    // Закрываем предыдущую библиотеку
    if (lib->handle) {
        dlclose(lib->handle);
        lib->handle = NULL;
    }
    
    // Очищаем ошибки
    dlerror();
    
    // Загружаем библиотеку
    lib->handle = dlopen(path, RTLD_LAZY);
    if (!lib->handle) {
        fprintf(stderr, " Ошибка загрузки %s: %s\n", path, dlerror());
        return 0;
    }
    
    // Загружаем PrimeCount
    dlerror(); // Очищаем предыдущие ошибки
    lib->prime_count = (PrimeCountFunc)dlsym(lib->handle, "PrimeCount");
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, " Ошибка загрузки PrimeCount: %s\n", error);
        dlclose(lib->handle);
        lib->handle = NULL;
        return 0;
    }
    
    // Загружаем Square
    dlerror();
    lib->square = (SquareFunc)dlsym(lib->handle, "Square");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, " Ошибка загрузки Square: %s\n", error);
        dlclose(lib->handle);
        lib->handle = NULL;
        return 0;
    }
    
    lib->lib_path = path;
    lib->lib_number = lib_num;
    return 1;
}

void print_current_lib_info(int lib_num) {
    if (lib_num == 1) {
        printf(" Текущая библиотека: libimpl1.so (Реализация 1)\n");
        printf("   - PrimeCount: Наивный алгоритм O(n*sqrt(n))\n");
        printf("   - Square: Прямоугольник S = A * B\n\n");
    } else {
        printf(" Текущая библиотека: libimpl2.so (Реализация 2)\n");
        printf("   - PrimeCount: Решето Эратосфена O(n*log(log(n)))\n");
        printf("   - Square: Прямоугольный треугольник S = (A * B) / 2\n\n");
    }
}

int main() {
    Library lib = {NULL, NULL, NULL, NULL, 0};
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║  ПРОГРАММА 2: Динамическая загрузка библиотек             ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    // Загружаем первую библиотеку по умолчанию
    if (! load_library(&lib, 1)) {
        fprintf(stderr, "Не удалось загрузить начальную библиотеку.\n");
        return 1;
    }
    
    print_current_lib_info(1);
    
    printf("Команды:\n");
    printf("  0      - переключить библиотеку\n");
    printf("  1 A B  - PrimeCount(A, B) - количество простых чисел [A,B]\n");
    printf("  2 A B  - Square(A, B) - площадь фигуры\n");
    printf("  exit   - выход\n\n");
    
    char command[256];
    
    while (1) {
        printf(">>> ");
        fflush(stdout);
        
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }
        
        // Проверка на exit
        if (strncmp(command, "exit", 4) == 0) {
            printf("Выход из программы.\n");
            break;
        }
        
        int cmd;
        if (sscanf(command, "%d", &cmd) != 1) {
            printf(" Ошибка: неверная команда\n\n");
            continue;
        }
        
        if (cmd == 0) {
            // Переключение библиотеки
            int new_lib = (lib.lib_number == 1) ? 2 : 1;
            printf("\n Переключение библиотеки.. .\n");
            
            if (load_library(&lib, new_lib)) {
                printf("✓ Успешно переключено!\n\n");
                print_current_lib_info(new_lib);
            } else {
                fprintf(stderr, " Ошибка переключения.  Остаёмся на текущей библиотеке.\n\n");
            }
        } 
        else if (cmd == 1) {
            // PrimeCount
            int A, B;
            if (sscanf(command, "%d %d %d", &cmd, &A, &B) == 3) {
                if (lib.prime_count) {
                    printf("Вызов: PrimeCount(%d, %d) из %s\n", A, B, lib.lib_path);
                    int result = lib.prime_count(A, B);
                    printf(" Результат: %d\n\n", result);
                }
            } else {
                printf(" Ошибка: используйте '1 A B' (например: 1 10 50)\n\n");
            }
        } 
        else if (cmd == 2) {
            // Square
            float A, B;
            if (sscanf(command, "%d %f %f", &cmd, &A, &B) == 3) {
                if (lib.square) {
                    printf("Вызов: Square(%.2f, %.2f) из %s\n", A, B, lib.lib_path);
                    float result = lib. square(A, B);
                    printf("✓ Результат: %.2f\n\n", result);
                }
            } else {
                printf(" Ошибка: используйте '2 A B' (например: 2 5.5 10)\n\n");
            }
        } 
        else {
            printf(" Неизвестная команда: %d\n\n", cmd);
        }
    }
    
    // Закрываем библиотеку
    if (lib.handle) {
        dlclose(lib. handle);
    }
    
    return 0;
}