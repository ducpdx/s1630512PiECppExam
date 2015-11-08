/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
* Shunting-yard and RPN evaluator
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

enum FSM_TRANSITIONS{
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

std::vector<std::string> inputToInfix (const std::string& fileName);
std::string infixToPostfix(std::string& infix); 
bool isoperator(char arg);
int precendence(char& arg);
double RPN (const std::vector<std::string>& expr);
std::vector<std::string> parserPostFix(std::string& postfix);
int getFSMCol(char& currentChar); 

int main(){    
    try{
        std::string infix;
        std::cout<<"Enter an infix expression:"<<std::endl;
        std::getline(std::cin,infix);
        std::string postfix = infixToPostfix(infix);        
        std::vector<std::string> expr = parserPostFix(postfix);      
        std::cout << std::endl <<"Output:" << std::endl;
        std::cout<<infix<<" = "<< RPN(expr) << std::endl;
    }
    catch (std::exception& e){
        std::cout << std::endl <<"Error: " << std::endl<< e.what() << std::endl;
    }
    try{
        std::string fileName ="infix.data";
        std::vector<std::string> infixFromFile = inputToInfix(fileName);
        std::cout<< std::endl <<"Getting infix expression from input file:"; 
        for (int i = 0; i < infixFromFile.size(); i++){
            std::cout<< std::endl<< infixFromFile[i] << std::endl;   
        }        
        std::cout << std::endl <<"Output:" << std::endl;

        for (int i = 0; i < infixFromFile.size(); i++){
            std::cout  << std::endl << infixFromFile[i] << " = ";
            std::string postfixFromFile = infixToPostfix(infixFromFile[i]);        
            std::vector<std::string>exprFromFile=parserPostFix(postfixFromFile);      
            std::cout << RPN(exprFromFile) << std::endl;
        }
    }
    catch (std::exception& e){
        std::cout << std::endl <<"Error: " << std::endl<< e.what() << std::endl;
    }        
}

std::vector<std::string> inputToInfix (const std::string& fileName){
    std::vector<std::string> infix;
    std::ifstream fileIn(fileName);
    std::string line;
    while (std::getline(fileIn , line)){
        infix.push_back(line);
    }
    return infix;
}

std::string infixToPostfix(std::string &infix){
    bool expectingOperator = false;
    std::stack<char> s;//Declaring a stack for conversion purpose
    std::string postfix = "";//Initialize the output string as empty;
    for(int i = 0;i < infix.length(); i++){//Scan the infix string one by one                
        if((std::isdigit(infix[i])) || (infix[i] == '~')){
            postfix += infix[i];
            expectingOperator = true;    
        }
        else if(std::isspace(infix[i])){
                continue;
        }
        else if(isoperator(infix[i])){
            postfix+=" ";
            while((!s.empty())&&(precendence(infix[i]) <= precendence(s.top())))
            {
	      postfix+= s.top();
              s.pop();
            }
            s.push(infix[i]);
            expectingOperator = false;
        }
        else if(infix[i] == '('){
            if (expectingOperator == true){
                throw std::runtime_error("Operator Missing");
            }
            s.push(infix[i]);
        }
        else if(infix[i] == ')'){
            if (expectingOperator == false){
                throw std::runtime_error("Operand Missing");
            }
            while((!s.empty()) && (s.top() != '(')){
	        postfix += s.top();		
		s.pop();
            }
            if(s.empty()){
                throw std::runtime_error("Parentheses Mismatch");
            }
            s.pop();
            expectingOperator = true;
        }
        else{//no operator                        
            throw std::runtime_error("Only integers and +,-,*,/,^ are allowed");
        }
    }
    if (s.size() < 1 && expectingOperator == true){//one operand given
        throw std::runtime_error("Operator Missing");
    }         
    else if (expectingOperator == false){//one operator given
        throw std::runtime_error("Operand Missing");
    }
    else{
        while(!s.empty()){
            if (s.top() == '('){
                throw std::runtime_error("Parentheses Mismatch");
            }
            postfix+= s.top();
            s.pop();
        }
    }
    return postfix;
}

bool isoperator(char arg){
    if(arg == '*' || arg == '/' || arg == '+' || arg == '-' || arg == '^'){ 
        return(1);
    }
    else{ 
        return(0);
    }
}

int precendence(char& arg){//Add weight to the operator
    int weight = 0;
    switch(arg){
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
    for(unsigned int i = 0; i < expr.size(); ++i){
        // push numbers onto the stack
        if((std::isdigit(expr[i][0]))){
           s.push(atof(expr[i].c_str()));
        }
        else if((expr[i].length() > 1) && ((expr[i][0] == '-') &&
            (isdigit(expr[i][1]) || (expr[i][1] == '.')))){
           s.push(atof(expr[i].c_str()));
        }
        else if(isoperator(expr[i][0]) && (!s.empty())){
            if (s.size() < 2){
                throw std::runtime_error("Not enough operands"); 
            }
            else{
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
                            throw std::runtime_error
                                ("Attempt to divide by zero.");
                        }
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
    if (s.size() != 1){//error checking based on RPN eval stack
        throw std::runtime_error("Invalid Input");
    }
    if(!s.empty()){
        answer = s.top();
    }
    return answer;
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
