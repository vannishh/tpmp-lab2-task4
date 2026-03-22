#include "data_processor.h"

int parse_csv_line(char* line, char* fields[], int max_fields) {
    int field_count = 0;
    char* token = strtok(line, ",");
    
    while (token != NULL && field_count < max_fields) {
        fields[field_count] = token;
        field_count++;
        token = strtok(NULL, ",");
    }
    
    return field_count;
}

int process_file_data(const char* input_file, const char* output_file) {
    FILE* fin = fopen(input_file, "r");
    FILE* fout = fopen(output_file, "w");
    
    if (fin == NULL || fout == NULL) {
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    char* fields[MAX_FIELDS];
    int brest_count = 0;
    
    // Читаем и пропускаем заголовок
    if (fgets(line, MAX_LINE_LENGTH, fin) == NULL) {
        fclose(fin);
        fclose(fout);
        return 0;
    }
    
    // Записываем заголовок в выходной файл
    fprintf(fout, "=== Покупатели из города Брест ===\n\n");
    fprintf(fout, "%-15s %-15s %-15s %-5s %-12s %-6s %-6s %-12s %-15s %-10s %-10s\n",
            "Фамилия", "Имя", "Отчество", "Пол", "Национальность", 
            "Рост", "Вес", "Дата_рождения", "Телефон", "Номер_карты", "Номер_счета");
    fprintf(fout, "--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    // Обрабатываем каждую строку
    while (fgets(line, MAX_LINE_LENGTH, fin) != NULL) {
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = 0;
        
        int field_count = parse_csv_line(line, fields, MAX_FIELDS);
        
        if (field_count >= 17) { // Проверяем что все поля присутствуют
            Customer c;
            
            // Заполняем структуру
            strcpy(c.surname, fields[0]);
            strcpy(c.name, fields[1]);
            strcpy(c.patronymic, fields[2]);
            strcpy(c.gender, fields[3]);
            strcpy(c.nationality, fields[4]);
            c.height = atoi(fields[5]);
            c.weight = atoi(fields[6]);
            strcpy(c.birth_date, fields[7]);
            strcpy(c.phone, fields[8]);
            strcpy(c.postal_code, fields[9]);
            strcpy(c.country, fields[10]);
            strcpy(c.region, fields[11]);
            strcpy(c.district, fields[12]);
            strcpy(c.city, fields[13]);
            strcpy(c.street, fields[14]);
            strcpy(c.house, fields[15]);
            strcpy(c.apartment, fields[16]);
            if (field_count > 17) strcpy(c.card_number, fields[17]);
            if (field_count > 18) strcpy(c.account_number, fields[18]);
            
            // Проверяем, проживает ли покупатель в Бресте
            if (strcmp(c.city, "Брест") == 0) {
                brest_count++;
                fprintf(fout, "%-15s %-15s %-15s %-5s %-12s %-6d %-6d %-12s %-15s %-20s %-20s\n",
                        c.surname, c.name, c.patronymic, c.gender, c.nationality,
                        c.height, c.weight, c.birth_date, c.phone, 
                        c.card_number, c.account_number);
            }
        }
    }
    
    // Добавляем статистику
    fprintf(fout, "\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fout, "Всего покупателей из Бреста: %d\n", brest_count);
    
    // Подсчитываем статистику по полу
    if (brest_count > 0) {
        fseek(fin, 0, SEEK_SET);
        // Пропускаем заголовок
        fgets(line, MAX_LINE_LENGTH, fin);
        
        int male_count = 0, female_count = 0;
        while (fgets(line, MAX_LINE_LENGTH, fin) != NULL) {
            line[strcspn(line, "\n")] = 0;
            int field_count = parse_csv_line(line, fields, MAX_FIELDS);
            
            if (field_count >= 17 && strcmp(fields[13], "Брест") == 0) {
                if (strcmp(fields[3], "М") == 0) male_count++;
                else if (strcmp(fields[3], "Ж") == 0) female_count++;
            }
        }
        
        fprintf(fout, "\nСтатистика по полу:\n");
        fprintf(fout, "  Мужчины: %d\n", male_count);
        fprintf(fout, "  Женщины: %d\n", female_count);
    }
    
    fclose(fin);
    fclose(fout);
    
    printf("   Found %d customers from Brest\n", brest_count);
    return 1;
}
