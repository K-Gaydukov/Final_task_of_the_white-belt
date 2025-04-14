# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -std=c++17 -Wall -g

# Имя исполняемого файла
TARGET = DateBase

# Цель по умолчанию: собрать программу
all: $(TARGET)

# Как собрать исполняемый файл
$(TARGET): DateBase.cpp
	$(CC) $(CFLAGS) DateBase.cpp -o $(TARGET)

# Очистка: удалить скомпилированные файлы
clean:
	rm -f $(TARGET)

# Указываем, что clean — не файл
.PHONY: clean