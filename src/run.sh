bison -d parser.y
lex lexer.lex
g++ -std=c++11 parser.tab.c lex.yy.c interpreter.cpp operation.cpp expression.cpp -o main

./main < in.txt