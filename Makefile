# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -O2
CFLAGS_PIC = -fPIC
LDFLAGS_SHARED = -shared
LDFLAGS_MATH = -lm
LDFLAGS_DL = -ldl

# Цели
LIBS = libimpl1.so libimpl2.so
PROGRAMS = program1 program2

. PHONY: all clean run1 run2 test help

# Сборка всего проекта
all: $(LIBS) $(PROGRAMS)
	@echo ""
	@echo "✓ Сборка завершена успешно!"
	@echo ""
	@echo "Запуск:"
	@echo "  make run1  - запустить программу 1 (линковка)"
	@echo "  make run2  - запустить программу 2 (динамическая загрузка)"
	@echo "  make test  - запустить тесты"
	@echo ""

# Сборка библиотек
libimpl1.so: implementation1.c contract.h
	$(CC) $(CFLAGS) $(CFLAGS_PIC) $(LDFLAGS_SHARED) -o $@ implementation1.c $(LDFLAGS_MATH)
	@echo "✓ Библиотека libimpl1. so создана"

libimpl2.so: implementation2.c contract.h
	$(CC) $(CFLAGS) $(CFLAGS_PIC) $(LDFLAGS_SHARED) -o $@ implementation2.c $(LDFLAGS_MATH)
	@echo "✓ Библиотека libimpl2.so создана"

# Программа 1: линковка на этапе компиляции
program1: program1.c libimpl1.so contract.h
	$(CC) $(CFLAGS) -o $@ program1.c -L. -limpl1 $(LDFLAGS_MATH) -Wl,-rpath=. 
	@echo "✓ Программа program1 создана (linking)"

# Программа 2: динамическая загрузка
program2: program2.c contract.h
	$(CC) $(CFLAGS) -o $@ program2.c $(LDFLAGS_DL)
	@echo "✓ Программа program2 создана (dynamic loading)"

# Запуск программ
run1: program1
	@echo "=== Запуск программы 1 ==="
	./program1

run2: program2
	@echo "=== Запуск программы 2 ==="
	./program2

# Автоматическое тестирование
test: all
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║  АВТОМАТИЧЕСКОЕ ТЕСТИРОВАНИЕ                              ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Тест 1: PrimeCount(10, 50)"
	@echo "Ожидается: 11 простых чисел"
	@echo "1 10 50" | ./program1 | grep "Результат"
	@echo ""
	@echo "Тест 2: Square(5, 10) - Прямоугольник"
	@echo "Ожидается: 50. 00"
	@echo "2 5 10" | ./program1 | grep "Результат"
	@echo ""
	@echo "Тест 3: Square(5, 10) - Треугольник (через program2)"
	@echo "Ожидается: 25.00"
	@echo -e "0\n2 5 10" | ./program2 | grep "Результат"
	@echo ""
	@echo "✓ Тесты завершены"

# Очистка
clean:
	rm -f $(LIBS) $(PROGRAMS)
	@echo "✓ Проект очищен"

# Справка
help:
	@echo "Доступные команды:"
	@echo "  make         - собрать весь проект"
	@echo "  make run1    - запустить программу 1"
	@echo "  make run2    - запустить программу 2"
	@echo "  make test    - запустить автотесты"
	@echo "  make clean   - очистить проект"
	@echo "  make help    - показать эту справку"