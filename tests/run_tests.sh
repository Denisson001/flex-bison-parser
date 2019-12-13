cd ../src

bash run.sh
cp main ../tests/solver
bash clean.sh

cd ../tests

g++ -std=c++11 tests.cpp -o tests
./tests

rm solver
rm tests