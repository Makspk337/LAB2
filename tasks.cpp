#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include <random>
#include <chrono>
#include "array.h"
#include "tree.h"
#include "stack.h"
#include "set.h"
#include "hash_table.h"
#include "lfu.h"

using namespace std;

static int precedence(char op) {
    if (op == '!') {
        return 3;
    }
    if (op == '&') {
        return 2;
    }
    if (op == '|' || op == '^') {
        return 1;
    }
    return 0;
}

static int apply_unop(char op, int a) {
    if (op == '!') {
        return a ? 0 : 1;
    }
    return 0;
}

static int apply_binop(char op, int a, int b) {
    if (op == '&') {
        return a & b;
    }
    if (op == '|') {
        return a | b;
    }
    if (op == '^') {
        return a ^ b;
    }
    return 0;
}

int task1(const string& input) {
    string s;
    for (char c : input) {
        if (!isspace(c)) {
            s.push_back(c);
        }
    }

    Stack* vals = stack_create("vals");
    Stack* ops = stack_create("ops");
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (c == '0' || c == '1') {
            stack_push(vals, c == '1'); i++;
        } else if (c == '(') {
            stack_push(ops, (int)'('); i++;
        } else if (c == ')') {
            while (!stack_empty(ops) && stack_peek(ops) != '(') {
                char op = (char)stack_pop(ops);
                if (op == '!') {
                    int a = stack_pop(vals);
                    stack_push(vals, apply_unop(op, a));
                } else {
                    int b = stack_pop(vals), a = stack_pop(vals);
                    stack_push(vals, apply_binop(op, a, b));
                }
            }
            if (!stack_empty(ops) && stack_peek(ops) == '(') {
                stack_pop(ops);
            }
            i++;
        } else if (string("!&|^").find(c) != string::npos) {
            while (!stack_empty(ops)) {
                char topc = (char)stack_peek(ops);
                if (topc == '(') {
                    break;
                }
                int ptop = precedence(topc), pcur = precedence(c);
                if (pcur <= ptop) {
                    char op = (char)stack_pop(ops);
                    if (op == '!') {
                        int a = stack_pop(vals);
                        stack_push(vals, apply_unop(op, a));
                    } else {
                        int b = stack_pop(vals), a = stack_pop(vals);
                        stack_push(vals, apply_binop(op, a, b));
                    }
                } else {
                    break;
                }
            }
            stack_push(ops, (int)c); i++;
        } else {
            i++;
        }
    }

    while (!stack_empty(ops)) {
        char op = (char)stack_pop(ops);
        if (op == '!') {
            int a = stack_pop(vals);
            stack_push(vals, apply_unop(op, a));
        } else {
            int b = stack_pop(vals), a = stack_pop(vals);
            stack_push(vals, apply_binop(op, a, b));
        }
    }

    int result = stack_pop(vals);
    stack_free(vals);
    stack_free(ops);
    return result;
}

void task2(const string& file, const string& query) {
    Set* s = set_create(128);
    if (!file.empty()) {
        ifstream in(file);
        int x;
        while (in >> x) {
            set_add(s, x);
        }
        in.close();
    }
    if (!query.empty()) {
        string cmd, num;
        int pos = query.find(' ');
        if (pos != string::npos) {
            cmd = query.substr(0, pos);
            num = query.substr(pos + 1);
        } else {
            cmd = query;
        }
        int val = num.empty() ? 0 : stoi(num);
        if (cmd == "SETADD") {
            set_add(s, val);
        } else if (cmd == "SETDEL") {
            set_remove(s, val);
        } else if (cmd == "SET_AT") {
            cout << (set_contains(s, val) ? "YES\n" : "NO\n");
        }
    }
    if (!file.empty()) {
        set_save(s, file);
    }
    set_free(s);
}

void task3(const string& query) {
    string data = query;
    istringstream iss(data);
    Set* numSet = set_create(8);
    int x;
    
    while (iss >> x) {
        if (x == 0) {
            break;
        }
        set_add(numSet, x);
    }

    Set* setA = set_create(8);
    Set* setB = set_create(8);
    int sumA = 0, sumB = 0;

    Set* tempSet = set_create(numSet->table->capacity);
    
    HT* table = numSet->table;
    for (int i = 0; i < table->capacity; i++) {
        if (table->flags[i] == 1) {
            set_add(tempSet, table->keys[i]);
        }
    }

    while (tempSet->table->count > 0) {
        int maxElement = -1;
        for (int i = 0; i < tempSet->table->capacity; i++) {
            if (tempSet->table->flags[i] == 1) {
                int current = tempSet->table->keys[i];
                if (current > maxElement) {
                    maxElement = current;
                }
            }
        }
        
        if (maxElement == -1) {
            break;
        }

        set_remove(tempSet, maxElement);

        if (sumA <= sumB) {
            set_add(setA, maxElement);
            sumA += maxElement;
        } else {
            set_add(setB, maxElement);
            sumB += maxElement;
        }
    }

    cout << "{";
    bool firstA = true;
    for (int i = 0; i < setA->table->capacity; i++) {
        if (setA->table->flags[i] == 1) {
            if (!firstA) {
                cout << " ";
        }
            cout << setA->table->keys[i];
            firstA = false;
        }
    }
    cout << "} {";
    
    bool firstB = true;
    for (int i = 0; i < setB->table->capacity; i++) {
        if (setB->table->flags[i] == 1) {
            if (!firstB) {
                cout << " ";
        }
            cout << setB->table->keys[i];
            firstB = false;
        }
    }
    cout << "}\nРазница: " << abs(sumA - sumB) << "\n";

    set_free(numSet);
    set_free(tempSet);
    set_free(setA);
    set_free(setB);
}

void task4(const string& file, const string& query) {
    ifstream in(file);
    if (!in.is_open()) {
        cout << "Проблема с файлом\n";
        return;
    }
    Array* arr = array_create(8);
    int x;
    while (in >> x) {
        array_push_back(arr, x);
    }
    in.close();
    int target = query.empty() ? 0 : stoi(query);
    int n = array_size(arr);
    bool found = false;
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = i; j < n; j++) {
            s += array_get(arr, j);
            if (s == target) {
                found = true;
                for (int k = i; k <= j; k++) {
                    cout << array_get(arr, k) << (k < j ? " " : "");
                }
                cout << "\n";
            }
        }
    }
    if (!found) {
        cout << "Подмассивы не найдены\n";
    }
    array_free(arr);
}

void task5(const string& query) {
    string data = query;
    istringstream iss(data);
    Tree* t = create_tree("bst");
    int x;
    while (iss >> x) {
        if (x == 0) {
            break;
        }
        tree_insert(t, x);
    }
    Array* out = tree_nodes_with_two_children(t);
    for (int i = 0; i < array_size(out); i++) {
        if (i) {
            cout << " ";
        }
        cout << array_get(out, i);
    }
    cout << "\n";
    array_free(out);
    tree_free(t);
}

void task6(const string& file, const string& query) {
    Array* data = array_create(8);
    ifstream in(file);
    if (!in.is_open()) {
        cout << "Не удалось открыть файл " << file << "\n";
        return;
    }
    int x;
    while (in >> x) {
        array_push_back(data, x);
    }
    in.close();
    int N = array_size(data);
    int M = query.empty() ? 10000 : stoi(query);
    if (N == 0) {
        cout << "Файл пустой\n"; array_free(data);
        return;
    }
    cout << "Элементов: N=" << N << ", Запросов: M=" << M << "\n\n";
    HT* h_double = ht_create(N * 2 + 8);
    for (int i = 0; i < N; i++) {
        ht_insert(h_double, array_get(data, i), array_get(data, i));
    }
    mt19937 gen(12345);
    uniform_int_distribution<int> dist(0, N - 1);
    auto t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) {
        ht_contains(h_double, array_get(data, dist(gen)));
    }
    auto t1 = chrono::high_resolution_clock::now();
    double time_double = chrono::duration<double, milli>(t1 - t0).count();
    HTCuckoo* h_cuckoo = ht_cuckoo_create(N * 2 + 8);
    for (int i = 0; i < N; i++) {
        ht_cuckoo_insert(h_cuckoo, array_get(data, i), array_get(data, i));
    }
    t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; i++) {
        ht_cuckoo_contains(h_cuckoo, array_get(data, dist(gen)));
    }
    t1 = chrono::high_resolution_clock::now();
    double time_cuckoo = chrono::duration<double, milli>(t1 - t0).count();
    cout << "Двойное хеширование : " << time_double << " ms\n";
    cout << "Хеширование кукушки : " << time_cuckoo << " ms\n";
    double diff = time_cuckoo - time_double;
    double ratio = (time_cuckoo > 0 ? (time_double / time_cuckoo) : 0);
    if (diff < 0) {
        cout << "Хеширование кукушки быстрее на " << abs(diff) << " ms\n";
    } else if (diff > 0) {
        cout << "Двойное хеширование быстрее на " << diff << " ms\n";
    } else {
        cout << "Оба метода сработали одинаково по времени.\n";
    }
    cout << "Эффективность: " << ratio << "x\n";
    ht_free(h_double);
    ht_cuckoo_free(h_cuckoo);
    array_free(data);
}

void task7(const string& file, const string& query) {
    LFUCache* c = lfu_load(file);
    string cmd = query;
    
    if (cmd.find("cap=") == 0) {
        int cap = stoi(cmd.substr(4));
        lfu_free(c);
        c = lfu_create(cap);
    } else if (cmd.find("SET") == 0) {
        istringstream iss(cmd);
        string operation;
        int key, value;
        iss >> operation >> key >> value;
        lfu_set(c, key, value);
    } else if (cmd.find("GET") == 0) {
        istringstream iss(cmd);
        string operation;
        int key;
        iss >> operation >> key;
        int result = lfu_get(c, key);
        cout << result << "\n";
    }
    
    lfu_save(c, file);
    lfu_free(c);
}
