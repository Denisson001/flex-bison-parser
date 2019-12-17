# Flex-bison-parser

## Usage example

- Собрать проект
  - Скриптом под Linux
    ```
    ../src$ bash compile.sh
    ```
  - Пошагово
    ```
    ../src$ bison -d grammar.y
    ../src$ lex lexer.lex
    ../src$ g++ -std=c++17 grammar.tab.c lex.yy.c interpreter.cpp \ 
            operation.cpp operator.cpp expression.cpp dictionary.cpp \
            variable.cpp main.cpp -o main
    ```
- Запустить интерпретатор
  - Интерпретатор принимает единственный параметр - путь до файла с интерпретируемой программой.
  - ```
    ../src$ ./main program.txt
    ```
  - Из *stdin* читает интерпретируемая программа. 
- Запустить тесты
  - Скриптом под Linux
  - ```
    ../tests$ bash run_tests.sh
    ```
  - Пошагово
    - Подложить собранный бинарник из директории `../src` в директорию `../tests`
    - Собрать и запустить тесты под Linux (изпользуется стандарт POSIX)
      ```
      ../tests$ g++ -std=c++11 tests.cpp -o tests
      ../tests$ ./tests
      ```
    - Или самостоятельно запустить конкретный тест, например:
      ```
      ../tests$ ./main algo/01.program <algo/01.in
      ```
  
## Project

## Tests

- Директория `../tests`
- `../tests/description.md` - описание всех тестов
- `../tests/tests.cpp` - точка входа в тесты
- `../tests/tests.cfg` - конфиг тестов
- `../tests/run_tests.sh` - скрипт для запуска тестов
- Структура теста
  - Например, поддиректория `../tests/algo`
  - `01.in` - ввод интерпретируемой программы
  - `01.out` - ожидаемый ввывод программы
  - `01.program` - код интерпретируемой программы
  - `01.desc` - описание теста

## TODO

- вынести error catchers
- унарный минус в грамматику
- ридинги все
  - описание кода
- ошибки компиляции
- кидать рантайм ошибки

