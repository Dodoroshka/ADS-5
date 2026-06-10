// Copyright 2025 NNTU-CS
#include <cctype>
#include <map>
#include <string>
#include <functional>
#include "tstack.h"
std::string infx2pstfx(const std::string& inf) {
    std::map<char, int> priority;
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['('] = 0;
    TStack<char, 100> st;
    std::string res;
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (c == ' ') continue;
        if (c >= '0' && c <= '9') {
            while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
                res += inf[i];
                ++i;
            }
            res += ' ';
            --i;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.get() != '(') {
                res += st.get();
                res += ' ';
                st.pop();
            }
            if (!st.isEmpty() && st.get() == '(') {
                st.pop();
            }
        } else if (priority.find(c) != priority.end()) {
            while (!st.isEmpty() && priority[st.get()] >= priority[c]) {
                res += st.get();
                res += ' ';
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        if (st.get() != '(') {
            res += st.get();
            res += ' ';
        }
        st.pop();
    }
    if (res.length() > 0 && res[res.length() - 1] == ' ') {
        res.resize(res.length() - 1);
    }
    return res;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divv(int a, int b) { return a / b; }

int eval(const std::string& post) {
    std::map<char, int(*)(int, int)> operations;
    operations['+'] = add;
    operations['-'] = sub;
    operations['*'] = mul;
    operations['/'] = divv;
    TStack<int, 100> st;
    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        if (c == ' ') continue;

        if (c >= '0' && c <= '9') {
            int num = 0;
            while (i < post.length() && post[i] >= '0' && post[i] <= '9') {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            st.push(num);
            --i;
        } else if (operations.find(c) != operations.end()) {
            int b = st.get(); st.pop();
            int a = st.get(); st.pop();
            int result = operations[c](a, b);
            st.push(result);
        }
    }
    return st.get();
}
