# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -std=c++17 -Wall -g -I src

# Имена исполняемых файлов
TARGET = build/DateBase
TEST_TARGET = build/test_database

# Цель по умолчанию: собрать основную программу
all: $(TARGET)

# Сборка основной программы
$(TARGET): src/DateBase.cpp src/main.cpp src/DateBase.h src/CommonHeaders.h
	$(CC) $(CFLAGS) src/DateBase.cpp src/main.cpp -o $(TARGET)

# Сборка юнит-тестов
$(TEST_TARGET): tests/unit/test_database.cpp src/DateBase.cpp src/DateBase.h src/CommonHeaders.h
	$(CC) $(CFLAGS) tests/unit/test_database.cpp src/DateBase.cpp -lgtest -lgtest_main -pthread -o $(TEST_TARGET)

# Очистка: удалить скомпилированные файлы и временные директории
clean:
	rm -rf build/* *.dSYM .pytest_cache

.PHONY: clean
