/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
* RPN evaluator
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <array>
#include <stdexcept>

enum FSM_TRANSITIONS{//to deal with negative and multidigit integer
    RESTART = 0,
    INTEGER,
    NEGATIVE,
    OPERATOR,
    SPACE
};

std::array <std::array<int,5>, 5> stateTable= 
{{{0, INTEGER,  NEGATIVE, OPERATOR, SPACE},
  {INTEGER,  INTEGER,  RESTART,  RESTART,   RESTART},
  {NEGATIVE, INTEGER,  RESTART,  RESTART,   RESTART},
  {OPERATOR,  RESTART, RESTART,  RESTART,   RESTART},
  {SPACE,     RESTART, RESTART,  RESTART,   RESTART}}};

double RPN (const std::vector<std::string>& expr);
std::vector<std::string> parserPostFix(std::string& postfix);
int getFSMCol(char& currentChar);
std::vector<std::string> inputToPostfix (const std::string& fileName);

int main(){    
    std::string fileName ="postfix.data";
    std::vector<std::string> postfixFromFile = inputToPostfix(fileName);
    std::cout<< std::endl <<"Getting postfix expression from input file...";
    for (int i = 0; i < postfixFromFile.size(); i++){
        std::cout  << std::endl << postfixFromFile[i];
    }

    std::cout<< std::endl <<"Output:" << std::endl;
    for (int i = 0; i < postfixFromFile.size(); i++){
        std::vector<std::string>exprFromFile = parserPostFix(postfixFromFile[i]);      
        std::cout << postfixFromFile[i] << " = " << RPN(exprFromFile) << std::endl;
    }
}
    

bool isoperator(char arg){
    if(arg == '*' || arg == '/' || arg == '+' || arg == '-'){ 
        return(1);
    }
    else{ 
        return(0);
    }
}

double RPN (const std::vector<std::string>& expr){
    std::stack<double> s;
    double ans = 0;
    double answer = 0;
    for(unsigned int i = 0; i < expr.size(); ++i){
        // push numbers onto the stack
        if((std::isdigit(expr[i][0]))){
           s.push(atof(expr[i].c_str()));
        }
        else if((expr[i].length() > 1) && ((expr[i][0] == '-') &&
            (isdigit(expr[i][1]) || (expr[i][1] == '.')))){
           s.push(atof(expr[i].c_str()));//convert to integer
        }
        else if(isoperator(expr[i][0]) && (!s.empty())){   
            char token = expr[i][0];
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
                    if (secondOperand == 0){
                    }
                    ans = firstOperand / secondOperand;
                    break;
            }
            s.push(ans);
        }
    }
    if(!s.empty()){
        answer = s.top();
    }
    return answer;
}
 
std::vector<std::string> parserPostFix(std::string& postfix){
// this function parses a postfix string using an FSM to generate
//  each individual token in the infix expression
    std::vector<std::string> tokens;
    char currentChar = ' ';
    int col = RESTART;
    int currentState = RESTART;
    std::string currentToken = "";
    for(unsigned int i = 0; i < postfix.length();){
        currentChar = postfix[i];
        col = getFSMCol(currentChar);
        currentState = stateTable[currentState][col];
        if(currentState == RESTART){
            if(currentToken != " "){
                tokens.push_back(currentToken);//push to new cell
            }
            currentToken = "";
        }
        else{
            //recording multi digit and negative until next RESTART
            currentToken += currentChar;
            ++i;
        }
    }
    if(currentToken != " "){
        tokens.push_back(currentToken);
    }
    return tokens;
}
 
int getFSMCol(char& currentChar){
    if(std::isspace(currentChar)){
        return SPACE;
    }
    else if(std::isdigit(currentChar)){
        return INTEGER;
    }    
    else if(currentChar == '~'){// use ~ as a keyboard stroke for negative    
        currentChar = '-';//record negative value
        return NEGATIVE;
    }
    else if(isoperator(currentChar)){
        return OPERATOR;
    } 
    else{
        //avoid void return warning, this wont happen thanks to error checking 
        return -1;
    }
}

std::vector<std::string> inputToPostfix (const std::string& fileName){
    std::vector<std::string> postfix;
    std::ifstream fileIn(fileName);
    std::string line;
    while (std::getline(fileIn , line)){
        postfix.push_back(line);
    }
    return postfix;
}