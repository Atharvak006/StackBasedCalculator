#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

int precedence(char op) {
    switch (op) 
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

string infixToPostfix(const string& exp) {
    stack<char> ops;
    string postfix;

    for (size_t i = 0; i < exp.length(); ++i) {
        char ch = exp[i];

        if (isdigit(ch)) 
        {
            postfix += ch;
        } 
        else if (ch == '(') 
        {
            ops.push(ch);
        } 
        else if (ch == ')') 
        {
            while (!ops.empty() && ops.top() != '(') 
            {
                postfix += ops.top();
                ops.pop();
            }
            ops.pop(); 
        } 
        else 
        { 
            while (!ops.empty() && precedence(ops.top()) >= precedence(ch)) 
            {
                postfix += ops.top();
                ops.pop();
            }
            ops.push(ch);
        }
    }

    while (!ops.empty()) 
    {
        postfix += ops.top();
        ops.pop();
    }

    return postfix;
}

int evaluatePostfix(const string& postfix) 
{
    stack<int> values;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            values.push(ch - '0');
        } else {

            int val2 = values.top(); 
            values.pop();

            int val1 = values.top(); 
            values.pop();
            
            values.push(applyOp(val1, val2, ch));
        }
    }

    return values.top();
}

int main() {
    string infix;

    cout << "Enter infix expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}