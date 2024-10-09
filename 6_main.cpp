#include <iostream>                
#include "arithmeticExpression.h"  // Including the header file for arithmetic expressions

using namespace std;

int main(){
    // Defining infix expressions
    string expr1 = "a+b*c";
    string expr2 = "(a+b)*(c-d)";
    string expr3 = "a + b * c - ( d * e + f ) * g";

    // Creating arithmeticExpression objects and initializing them with infix expressions
    arithmeticExpression ex1(expr1);
    arithmeticExpression ex2(expr2);
    arithmeticExpression ex3(expr3);

    // Building expression trees for each arithmeticExpression object
    ex1.buildTree();
    ex2.buildTree();
    ex3.buildTree();

    // Printing expression details for each arithmeticExpression object
    cout<<"expression 1: "<<expr1<<endl;
    cout<<"infix: "; ex1.infix(); cout<<endl;    // Printing infix expression
    cout<<"prefix: "; ex1.prefix(); cout<<endl;  // Printing prefix expression
    cout<<"postfix: "; ex1.postfix(); cout<<endl; // Printing postfix expression
    cout<<endl;

    cout<<"expression 2: "<<expr2<<endl;
    cout<<"infix: "; ex2.infix(); cout<<endl;
    cout<<"prefix: "; ex2.prefix(); cout<<endl;
    cout<<"postfix: "; ex2.postfix(); cout<<endl;
    cout<<endl;

    cout<<"expression 3: "<<expr3<<endl;
    cout<<"infix: "; ex3.infix(); cout<<endl;
    cout<<"prefix: "; ex3.prefix(); cout<<endl;
    cout<<"postfix: "; ex3.postfix(); cout<<endl;
    cout<<endl;

    return 0;
}
