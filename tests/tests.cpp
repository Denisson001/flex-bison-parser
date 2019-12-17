#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
 * Структура конфига тестов
 * dirs     - директории с тестами
 * test_cnt - число тестов в директории
 * */
struct TCfg {
    std::vector<std::string> dirs;
    std::vector<uint32_t>    test_cnt;
    std::string              solver_output;
    std::string              solver_name;
};

/*
 * Структура результата сравнения файлов
 * result - результат сравнения
 * В случае нахождения отличия в correct_line и solver_line будут лежать отличающиеся строки
 * */
struct TCompareResult {
    bool result;
    std::string correct_line;
    std::string solver_line;
};

/*
 * Считывает конфиг
 * */
TCfg readCfg() {
    std::ifstream cfg_file("tests.cfg");
    TCfg cfg;

    std::string line;
    while (getline(cfg_file, line)) {
        std::stringstream cfg_stream(line);
        std::string header;
        std::string item;
        cfg_stream >> header;
        if (!header.empty()) {
            header.pop_back();
        }
        while(cfg_stream >> item) {
            if (header == "dirs") {
                cfg.dirs.push_back(item);
            } else if (header == "solver_name") {
                cfg.solver_name = item;
            } else if (header == "solver_output") {
                cfg.solver_output = item;
            } else { // test_count:
                cfg.test_cnt.push_back(std::stoi(item));
            }
        }
    }

    cfg_file.close();
    return cfg;
}

/*
 * Создает путь до файла с тестом по директории и номеру теста
 * Например "base/01"
 * */
std::string createFileName(std::string dir, uint32_t test_num) {
    std::string result = dir + "/";
    if (test_num < 10) {
        result += "0";
    }
    result += std::to_string(test_num);
    return result;
}

/*
 * Запускает решение на тесте из test_file
 * Результат лежит в файле cfg.solver_output
 * */
void runTest(const std::string& program_file, const std::string& input_file, const TCfg& cfg) {
    pid_t pid = fork();
    if (pid == 0) {
        freopen(input_file.c_str(), "r", stdin);
        freopen(cfg.solver_output.c_str(), "w", stdout);
        freopen(cfg.solver_output.c_str(), "w", stderr);
        execl(cfg.solver_name.c_str(), cfg.solver_name.c_str(), program_file.c_str(), NULL);
        exit(1);
    } else {
        int status;
        wait(&status);
    }
}

/*
 * Выводит описание теста
 * */
void printDescription(const std::string& description_file) {
    std::ifstream file(description_file);
    std::string description;
    std::cout << "Description : ";
    while (getline(file, description)) {
        std::cout << description << "\n";
    }
    file.close();
}

/*
 * Сравнивает корректный ответ с ответом решения
 * */
TCompareResult compareFiles(const std::string& test_file, const std::string& solver_output) {
    std::ifstream correct_result(test_file);
    std::ifstream solver_result(solver_output);

    TCompareResult result;
    while (true) {
        getline(correct_result, result.correct_line);
        getline(solver_result, result.solver_line);
        if (result.correct_line == "" && result.solver_line == "") {
            result.result = true;
            break;
        }
        if (result.correct_line != result.solver_line) {
            result.result = false;
            break;
        }
    }

    correct_result.close();
    solver_result.close();
    return result;
}

/*
 * Запускает решение на всех тестах, описанных в конфиге.
 * */
void runTests(const TCfg& cfg) {
    uint32_t total_test_count = 0;
    uint32_t correct_tests    = 0;

    for (uint8_t dir_num = 0; dir_num < cfg.dirs.size(); ++dir_num) {
        const auto& dir = cfg.dirs[dir_num];
        for (uint32_t test_num = 1; test_num <= cfg.test_cnt[dir_num]; ++test_num) {
            const auto test_file = createFileName(dir, test_num);
            runTest(test_file + ".program", test_file + ".in", cfg);
            const auto compare_result = compareFiles(test_file + ".out", cfg.solver_output);

            if (compare_result.result) {
                ++correct_tests;
            }

            const std::string test_result = compare_result.result ? "OK" : "FAIL";
            std::cout << "Test " << test_file << ": " << test_result << "\n";
            printDescription(test_file + ".desc");
            if (!compare_result.result) {
                std::cout << "Correct line: " << compare_result.correct_line << "\n";
                std::cout << "Solver line : " << compare_result.solver_line  << "\n";
            }
            std::cout << "\n";
        }
        total_test_count += cfg.test_cnt[dir_num];
    }

    for (uint8_t i = 0; i < 25; ++i) {
        std::cout << '=';
    }
    std::cout << "\nTotal: " << correct_tests << "/" << total_test_count << "\n";
}

int main() {
    const auto cfg = readCfg();
    runTests(cfg);
}