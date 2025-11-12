#include <iostream>
#include <string>
#include "tasks.h"
using namespace std;

static bool has_flag(int argc, char** argv, const string& key) {
    for (int i = 1; i < argc; i++) {
        if (key == argv[i]) {
            return true;
        }
    }
    return false;
}

static string get_arg(int argc, char** argv, const string& key) {
    for (int i = 1; i < argc; i++) {
        if (key == argv[i] && i + 1 < argc) {
            return string(argv[i + 1]);
        }
    }
    return string("");
}

int main(int argc, char** argv) {
    string file = get_arg(argc, argv, "--file");
    string query = get_arg(argc, argv, "--query");

    if (has_flag(argc, argv, "--task1")) {
        cout << task1(query) << "\n";
        return 0;
    }
    if (has_flag(argc, argv, "--task2")) {
        task2(file, query);
        return 0;
    }
    if (has_flag(argc, argv, "--task3")) {
        task3(query);
        return 0;
    }
    if (has_flag(argc, argv, "--task4")) {
        task4(file, query);
        return 0;
    }
    if (has_flag(argc, argv, "--task5")) {
        task5(query);
        return 0;
    }
    if (has_flag(argc, argv, "--task6")) {
        task6(file, query);
        return 0;
    }
    if (has_flag(argc, argv, "--task7")) {
        task7(file, query);
        return 0;
    }
    return 0;
}
