#!/bin/bash

echo "==================================="
echo "Testing Customer Data Processor"
echo "==================================="

# Компилируем
echo "1. Compiling project..."
make clean
make

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi
echo "Compilation successful!"

# Запускаем программу
echo -e "\n2. Running program..."
./bin/customer_processor  # Исправлено: было file_processor

# Проверяем результаты
echo -e "\n3. Checking results..."
if [ -f "data/brest_customers.txt" ]; then
    echo "✓ Output file created successfully"
    
    # Проверяем количество покупателей из Бреста
    # Подсчитываем строки, содержащие информацию о покупателях (не заголовки и разделители)
    BREST_COUNT=$(grep -c "Брест" data/brest_customers.txt | head -1)
    if [ "$BREST_COUNT" -gt 0 ]; then
        echo "✓ Found customers from Brest"
        echo "  Number of customers: $BREST_COUNT"
    else
        echo "✗ No customers from Brest found"
        exit 1
    fi
else
    echo "✗ Output file not created"
    echo "Checking if data directory exists:"
    ls -la data/ 2>/dev/null || echo "data directory not found"
    exit 1
fi

echo -e "\n4. Sample of output:"
echo "-----------------------------------"
head -20 data/brest_customers.txt
echo "-----------------------------------"

echo -e "\n5. Statistics from output file:"
# Выводим последние строки со статистикой
tail -5 data/brest_customers.txt

echo -e "\n==================================="
echo "All tests passed successfully!"
echo "==================================="
