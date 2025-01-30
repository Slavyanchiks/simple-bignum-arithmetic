# Лабораторная работа 2

## Задача

  Реализовать пользовательский тип для целого знакового числа фиксированной длины **int2023_t**.
  Размер получившегося типа не должен превышать 253 байтa.

  Для вышеуказанного типа требуется реализовать следующий набор функций и операторов

     1. Конвертация из типа int32_t
     2. Конвертация из строки
     3. Сложение
     4. Вычитание
     5. Умножение
     6. Деление
     7. Вывод числа в поток (не обязательно в 10й системе счисления)

## Инструкция по выполнению

Вам дан шаблон проекта, состоящие из трех директорий:
- **bin**
- **lib**
- **tests**

Менять стуктуру проекта, добавлять новый файлы запрещается.

Требуется:
  1. Реализовать тип **int2023_t**, описав его в заголовочном файле **lib/number.h** (!Обратите внимание что такая структура там уже есть, требуется дополнить ее описание)
  2. Реализовать вышеуказанные функции и операторы, написав реализацию в **lib/number.cpp**

### Тесты

Проект содержит базовый набор тестов, который позволит убедится, что реализация функций выполненна без явных ошибок.
Для запуска тестов в командной строке можно выполнить след операцию:

***cmake --build . --target number_tests && ctest -V***  или воспользоваться средствами вашей IDE

Пока все тесты не будут проходить показывать лабораторную - нельзя.
Тесты при желании можно дополнять, но это не обязательно.

### Если этого не хватило

В директории **bin** находится консольное приложение, которые вы также можете использовать по вашему усмотрению, что бы проверить свой код.
Для запуска выполнить след команду:

***cmake --build . --target labwork2 && bin/labwork2*** или воспользоваться IDE

## Примечание
 - Переполнение - Undefined Behavior

## Ограничения
 - Запрещается использование стандартных контейнеров (std::vector, std::list и тд)
 - Запрещается использование std::bitset

