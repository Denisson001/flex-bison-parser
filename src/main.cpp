#include <iostream>

#include "interpreter.h"

/*
 * Точка входа в интерпретатор
 * Передает имя файла с интерпретируемой программой в класс TInterpreter
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "wrong number of args\n";
        return 1;
    }
    TInterpreter interpreter;
    interpreter.run(argv[1]);
}
