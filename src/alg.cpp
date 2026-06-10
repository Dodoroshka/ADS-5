// Copyright 2025 NNTU-CS
#include <cctype>
#include <map>
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
        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
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
int eval(const std::string& post) {
    TStack<int, 100> st;   
    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        if (c == ' ') continue;
        if (std::isdigit(c)) {
            int num = 0;
            while (i < post.length() && std::isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            st.push(num);
            --i;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = st.get(); st.pop();
            int a = st.get(); st.pop();
            if (c == '+') {
                st.push(a + b);
            } else if (c == '-') {
                st.push(a - b); 
            } else if (c == '*') {
                st.push(a * b);
            } else {
                st.push(a / b);
            }
        }
    }
    return st.get();
}
