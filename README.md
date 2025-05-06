# Импульс 2025
# Сборка проекта
```sh
mkdir build && cd build
cmake ..
cmake --build .
```
Запускаемый файл с именем test создается в директории build

# Тесты
Тестовые примеры находятся в папке /test_cases

[test_file.txt](test_cases/test_file.txt) - тест из примера в тексте задания

[test_all_events.txt](test_cases/test_all_events.txt) - проверка функционала программы

[invalid_command.txt](test_cases/invalid_command.txt) - несуществующий ID события

[invalid_cost.txt](test_cases/invalid_cost.txt) - недопустимая цена

[invalid_name.txt](test_cases/invalid_name.txt) - недопустимое имя пользователя

[invalid_num_of_tables.txt](test_cases/invalid_num_of_tables.txt) - недопустимое количество столов в клубе

[invalid_table.txt](test_cases/invalid_table.txt) - попытка занять несуществующий стол

[invalid_time.txt](test_cases/invalid_time.txt) - нарушение последовательности событий

[invalid_work_hours.txt](test_cases/invalid_work_hours.txt) - недопустимые время начала и/или время окончания работы
