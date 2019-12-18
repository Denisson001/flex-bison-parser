#pragma once

#include "operation.h"
#include "node.h"

/*
 * Класс интерпретатора
 */
class TInterpreter {
public:
    /*
     * Запустить парсер и интерпретатор на программе из файла program_filename
     * Успешный код возврата 0
     */
    int run(char* program_filename);

private:
    /*
     * Строит абстрактное дерево разбора программы
     * Используется Bison и Flex
     * Успешный код возврата 0
     */
    int _buildAST(char* program_filename);

    /*
     * Запускает интерпретатор
     */
    void _interpret();

    /*
     * Вся интерпретируемая программа представляется как набор операций
     */
    TOperations _operations;

    /*
     * Словарь всех переменных интерпретируемой программы
     */
    TDictionary _dictionary;
};
