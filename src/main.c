#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"
#include "data_processor.h"

int main() {
    const char* input_filename = "data/customers.txt";
    const char* output_filename = "data/brest_customers.txt";
    
    // Создаем директорию для данных если её нет
    system("mkdir -p data");
    
    printf("=== Customer Data Processor ===\n");
    printf("Program for processing customer information\n\n");
    
    // Создаем файл с данными покупателей
    printf("1. Creating input file with customer data...\n");
    if (create_input_file(input_filename)) {
        printf("   File created successfully: %s\n", input_filename);
    } else {
        printf("   Error creating file!\n");
        return 1;
    }
    
    // Просматриваем содержимое файла
    printf("\n2. Reading input file contents:\n");
    display_file_contents(input_filename);
    
    // Обрабатываем данные - выбираем покупателей из города Брест
    printf("\n3. Filtering customers from Brest city...\n");
    if (process_file_data(input_filename, output_filename)) {
        printf("   Data processed successfully!\n");
    } else {
        printf("   Error processing data!\n");
        return 1;
    }
    
    // Просматриваем результаты
    printf("\n4. Results saved to: %s\n", output_filename);
    printf("\n=== Customers from Brest ===\n");
    display_file_contents(output_filename);
    
    printf("\n=== Program completed successfully ===\n");
    return 0;
}
