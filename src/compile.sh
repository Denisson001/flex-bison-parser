# Скрипт, собирающий проект

bison -d  grammar.y
lex lexer.lex
g++ -std=c++17 grammar.tab.c lex.yy.c \
interpreter.cpp error_handler.cpp operation.cpp operator.cpp \
expression.cpp dictionary.cpp variable.cpp main.cpp -o main
