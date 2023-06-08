#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

struct stack {
    char data;
    stack* tail;
};

stack* push(stack* str, char c) {
    stack* next = new stack;
    next->data = c;
    next->tail = str;
    return next;
}

bool empty(stack* str) {
    if (!str) return 1;
    else return 0;
}

stack* pop(stack* str) {
    stack* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

char top(stack* str) {
    return str->data;
}

struct stack_i {
    double data;
    stack_i* tail;
};

stack_i* push(stack_i* s, double num) {
    stack_i* next = new stack_i;
    next->data = num;
    next->tail = s;
    return next;
}

bool empty(stack_i* str) {
    if (!str) return 1;
    else return 0;
}

stack_i* pop(stack_i* str) {
    stack_i* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

double top(stack_i* str) {
    return str->data;
}

int operators(char c) {
    switch (c) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return -1;
    }
}

void output_stack(stack* s) {
    while (!empty(s)) {
        cout << s->data << ' ';
        s = s->tail;
    }
}

bool correction(string& s) {
    stack* par = NULL;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == ' ' && operators(s[i - 1]) == -1 && operators(s[i + 1]) == -1) return 0;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') s.erase(i, 1);
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') par = push(par, s[i]);
        else if (s[i] == ')')
            if (!empty(par)) par = pop(par);
            else return 0;
    }
    if (!empty(par)) return 0;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == '(' && (operators(s[i - 1]) == -1 || s[i - 1] == ')')) {
            s.insert(i, "*");
        }
        else if (s[i] == ')' && (operators(s[i + 1]) == -1 || s[i + 1] == '(')) {
            s.insert(i + 1, "*");
        }
    }
    for (int i = 1; i < s.length(); i++) {
        if (s[i - 1] == '+' && s[i] == '-') s.erase(i - 1, 1);
        else if (s[i - 1] == '-' && s[i] == '-') {
            s.insert(i - 1, "+");
            s.erase(i, 2);
        }
        else if (operators(s[i - 1]) > 0 && operators(s[i]) > 0 && s[i] != '-') return 0;
    }
    for (int i = 0, k = 0; i < s.length(); i++) {
        if (operators(s[i]) > 0) k++;
        if (i == 1 && s[i - 1] != '-' && operators(s[i - 1]) > 0) return 0;
        else if (i == s.length() - 1 && operators(s[i]) > 0 || i == s.length() - 1 && !k) return 0;
    }
    return 1;
}

string reverse_notation(string str) {
    cout << "\n";
    string n;
    stack* stack = NULL;
    string num = "";
    int k = 1;
    for (int i = 0, flag; i < str.length(); i++) {
        if (str[i] == '-') {
            if (i == 0 && operators(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
            else if (operators(str[i - 1]) > 1 && operators(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
        }
        flag = operators(str[i]);
        if (flag == 0) {
            if (str[i] == '(') {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". стек: ";
                    output_stack(stack);
                    cout << "\t\tстрока: " << n << "\n";
                    k++;
                }
                stack = push(stack, str[i]);
                cout << k << ". стек: ";
                output_stack(stack);
                cout << "\t\tстрока: " << n << "\n";
                k++;
            }
            else {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". стек: ";
                    output_stack(stack);
                    cout << "\t\tстрока: " << n << "\n";
                    k++;
                }
                while (!empty(stack)) {
                    if (top(stack) != '(') {
                        n += top(stack);
                        stack = pop(stack);
                        n += ' ';
                    }
                    else {
                        stack = pop(stack);
                        break;
                    }
                }
                cout << k << ". стек: ";
                output_stack(stack);
                cout << "\t\tстрока: " << n << "\n";
                k++;
            }
        }
        else if (flag == 1) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". стек: ";
                output_stack(stack);
                cout << "\t\tстрока: " << n << "\n";
                k++;
            }
            if (empty(stack) || operators(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && operators(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". стек: ";
            output_stack(stack);
            cout << "\t\tстрока: " << n << "\n";
            k++;
        }
        else if (flag == 2) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". стек: ";
                output_stack(stack);
                cout << "\t\tстрока: " << n << "\n";
                k++;
            }
            if (empty(stack) || operators(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && operators(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". стек: ";
            output_stack(stack);
            cout << "\t\tстрока: " << n << "\n";
            k++;
        }
        else num += str[i];
    }
    if (num != "") {
        n += num;
        n += ' ';
        cout << k << ". стек: ";
        output_stack(stack);
        cout << "\t\tстрока: " << n << "\n";
        k++;
    }
    while (!empty(stack)) {
        n += top(stack);
        stack = pop(stack);
        n += ' ';
    }
    cout << k << ". стек: ";
    output_stack(stack);
    cout << "\t\tстрока: " << n << "\n";
    return n;
}

double calculate(string s) {
    string num = "";
    double num_1, num_2;
    stack_i* stack = NULL;
    for (int i = 0, k = 1; i < s.length(); i++) {
        if (operators(s[i]) == -1 && s[i] != ' ') {
            while (s[i] != ' ') {
                num += s[i];
                i++;
            }
            stack = push(stack, stoi(num));
            cout << k << ". записываем в стек " << num << '\n';
            k++;
            num = "";
        }
        else if (operators(s[i]) == 1) {
            if (s[i] == '+') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 + num_1);
                cout << k << ". выносим из стека " << num_2 << " и " << num_1 << ", складываем и возвращаем в стек " << num_1 + num_2 << '\n';
                k++;
            }
            if (s[i] == '-' && i < s.length() - 1 && s[i + 1] == ' ') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 - num_1);
                cout << k << ". выносим из стека " << num_2 << " и " << num_1 << ", вычитаем и возвращаем в стек " << num_2 - num_1 << '\n';
                k++;
            }
            else if (s[i] == '-' && i < s.length() - 1 && operators(s[i + 1]) == -1) {
                while (s[i] != ' ') {
                    num += s[i];
                    i++;
                }
                stack = push(stack, stoi(num));
                cout << k << ". записываем в стек " << num << '\n';
                k++;
                num = "";
            }
        }
        else if (operators(s[i]) == 2) {
            if (s[i] == '*') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 * num_1);
                cout << k << ". выносим из стека " << num_2 << " и " << num_1 << ", умножаем и возвращаем в стек " << num_1 * num_2 << '\n';
                k++;
            }
            if (s[i] == '/') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 / num_1);
                cout << k << ". выносим из стека " << num_2 << " и " << num_1 << ", делим и возвращаем в стек " << num_2 / num_1 << '\n';
                k++;
            }
        }
    }
    cout << "возвращаем верхний элемент стека\n\nответ: ";
    return top(stack);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    string str, str_out;
    char choice;
    do{

        cout << "введите выражение: ";
        getline(cin, str);
        while (str == "" || !correction(str)) {
            cout << "некорректный ввод\n\nвведите выражение: ";
            getline(cin, str);
        }
        str_out = reverse_notation(str);
        cout << "\nобратная польская нотация: " << str_out << '\n';
        cout << "\n\tвычисления: \n";
        cout << "\n" << calculate(str_out) << "\n\n";
        cin >> choice;
    } while(choice != 0);

    return 0;
}