#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

// Создание входного файла с данными покупателей
int create_input_file(const char* filename);

// Отображение содержимого файла
void display_file_contents(const char* filename);

#endif
