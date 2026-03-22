#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 20

// Структура для хранения данных о покупателе
typedef struct {
    char surname[50];
    char name[50];
    char patronymic[50];
    char gender[10];
    char nationality[30];
    int height;
    int weight;
    char birth_date[20];
    char phone[20];
    char postal_code[10];
    char country[30];
    char region[30];
    char district[30];
    char city[50];
    char street[50];
    char house[10];
    char apartment[10];
    char card_number[20];
    char account_number[30];
} Customer;

// Обработка данных из файла - выборка покупателей из Бреста
int process_file_data(const char* input_file, const char* output_file);

// Функция для парсинга строки CSV
int parse_csv_line(char* line, char* fields[], int max_fields);

#endif
