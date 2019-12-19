# собирает и подкладывает бинарник
cd ../src

bash compile.sh
cp main ../tests/solver
bash clean.sh

cd ../tests

# запускает тесты
g++ -fsanitize=address -std=c++11 tests.cpp -o tests
./tests

# чистит временные файлы
rm solver_output.txt
rm solver
rm tests
