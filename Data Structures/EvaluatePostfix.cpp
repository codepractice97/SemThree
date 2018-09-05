#include <iostream>
#include "StackByLL.cpp"
using namespace std;

int postfixEvaluation(char *exp){
    Stack<int> s;
    char ch; int n1, n2;
    for (int i=0; exp[i] != '\0'; i++){
        ch = exp[i];
        switch(ch){
            case '+':
                n2 = s.pop();
                n1 = s.pop();
                s.push(n1 + n2);
                break;
            case '-':
                n2 = s.pop();
                n1 = s.pop();
                s.push(n1 - n2);
                break;
            case '*':
                n2 = s.pop();
                n1 = s.pop();
                s.push(n1 * n2);
                break;
            case '/':
                n2 = s.pop();
                n1 = s.pop();
                s.push(n1 / n2);
                break;
            default:
                s.push(ch - 48);
                break;
        }
    }
    int result = s.pop();
    return result;
}

int main(){
    char exp[50];
    cout << "Enter the postfix expression to evaluate\n";
    cin >> exp;

    cout << "Result is: " << postfixEvaluation(exp) << endl;
    return 0;
}