/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
#include <array>

enum FSM_TRANSITIONS
{
    RESTART = 0,
    INTEGER,
    NEGATIVE,
    OPERATOR,
    UNKNOWN,
    SPACE
};

std::array <std::array<int, 6>, 6>stateTable = 
{{{0, INTEGER,  NEGATIVE, OPERATOR,  UNKNOWN,  SPACE},
  {INTEGER,  INTEGER,  RESTART,  RESTART,   RESTART,  RESTART},
  {NEGATIVE, INTEGER,  RESTART,  RESTART,   RESTART,  RESTART},
  {OPERATOR,  RESTART, RESTART,  RESTART,   RESTART,  RESTART},
  {UNKNOWN,   RESTART, RESTART,  RESTART,   UNKNOWN, RESTART},
  {SPACE,     RESTART, RESTART,  RESTART,   RESTART,  RESTART}}};

std::string infixToPostfix(std::string& infix); 
bool isoperator(char arg);
int precendence(char& arg);
double RPN (const std::vector<std::string>& expr);
std::vector<std::string> parserPostFix(std::string& postfix);
int getFSMCol(char& currentChar); 

int main()
{
    std::string infix;
    std::cout<<"Enter an infix infix expression:"<<std::endl;
    std::getline(std::cin,infix);
    std::string postfix = infixToPostfix(infix);
    std::cout<<postfix<<std::endl;
    std::vector<std::string> expr = parserPostFix(postfix);

    //display the found tokens to the screen
    for(unsigned x = 0; x < expr.size(); ++x)
    {
        std::cout<<expr.at(x)<<std::endl;
    }       
    std::cout<<"Output:"<<std::endl<<infix<<" = "<< RPN(expr) << std::endl;
}

std::string infixToPostfix(std::string &infix){
    std::stack<char> s;//Declaring a stack for conversion purpose
    std::string postfix = "";//Initialize the output string as empty;
    for(int i = 0;i < infix.length(); i++){//Scan the infix string one by one
        if((std::isdigit(infix[i])) || (infix[i] == '~'))
        {
            postfix += infix[i];
        }
        else if(std::isspace(infix[i]))
        {
            continue;
        }
        
        else if(isoperator(infix[i]))
        {
            postfix+=" ";
            while((!s.empty())&&(precendence(infix[i]) <= precendence(s.top())))
            {
	      postfix+= s.top();
              s.pop();
            }
            s.push(infix[i]);
        }
        else if(infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if(infix[i] == ')')
        {
            while((!s.empty()) && (s.top() != '('))
            {
	        postfix += s.top();		
		s.pop();
            }
            if(!s.empty()) 
            {
                s.pop();
            }
        }
    }
    while(!s.empty())
    {
        postfix+= s.top();
        s.pop();
    }
    return postfix;
}

bool isoperator(char arg)
{
    if(arg == '*' || arg == '/' || arg == '+' || arg == '-' || arg == '^') 
        return(1);
    else 
        return(0);
}

int precendence(char& arg)//Add weight to the operator
{
    int weight = 0;
    switch(arg)
    {
    case '^':
        weight = 3;
        break;
    case '*':
    case '/':
        weight = 2;
        break;
    case '+':
    case '-':
        weight = 1;
        break;
    }
    return(weight);
}

double RPN (const std::vector<std::string>& expr){
    std::stack<double> s;
    double ans = 0;
    double answer = 0;
    for(unsigned int i = 0; i < expr.size(); ++i)
    {
        // push numbers onto the stack
        if((std::isdigit(expr[i][0])))
        {
           s.push(atof(expr[i].c_str()));
        }
        else if((expr[i].length() > 1) && ((expr[i][0] == '-') &&
            (isdigit(expr[i][1]) || (expr[i][1] == '.')))){
           s.push(atof(expr[i].c_str()));
        }
        else if(isoperator(expr[i][0]) && (!s.empty()))
        {
            char token = expr[i][0];
            if(s.size() > 1)
            {
                double secondOperand = s.top();
                s.pop();
                double firstOperand = s.top();
                s.pop();
                switch(token){
                    case ('+'):
                        ans = firstOperand + secondOperand; 
                        break;
                    case ('-'):
                        ans = firstOperand - secondOperand;
                        break;
                    case ('*'):
                        ans = firstOperand * secondOperand;
                        break;
                    case ('/'):
                        ans = firstOperand / secondOperand;
                        break;
                    case ('^'):
                        ans = std::pow(firstOperand, secondOperand);
                        break;
                }
                s.push(ans);
            }    
        }
    }
    // pop the final answer from the stack, and return to main
    if(!s.empty())
    {
        answer = s.top();
    }
    return answer;
}
 
int getFSMCol(char& currentChar)
{
    if(std::isspace(currentChar))
    {
        return SPACE;
    }
    else if(std::isdigit(currentChar))
    {
        return INTEGER;
    }    
    else if(currentChar == '~')// use ~ as a keyboard stroke for negative
    {
        currentChar = '-';//record negative value
        return NEGATIVE;
    }
    else if(isoperator(currentChar))
    {
        return OPERATOR;
    }
    return UNKNOWN;
}
//parser and error checking
std::vector<std::string> parserPostFix(std::string& postfix)
{// this function parses a postfix string using an FSM to generate
 //  each individual token in the infix expression
    std::vector<std::string> tokens;
    char currentChar = ' ';
    int col = RESTART;
    int currentState = RESTART;
    std::string currentToken = "";
    for(unsigned int i = 0; i < postfix.length();)
    {
        currentChar = postfix[i];
        col = getFSMCol(currentChar);
        currentState = stateTable[currentState][col];
        if(currentState == RESTART)
        {
            if(currentToken != " ")
            {
                tokens.push_back(currentToken);
            }
            currentToken = "";
        }
        else
        {
            //recording multi digit and negative until next RESTART
            currentToken += currentChar;
            ++i;
        }
    }
    if(currentToken != " ")
    {
        tokens.push_back(currentToken);
    }
    return tokens;
}