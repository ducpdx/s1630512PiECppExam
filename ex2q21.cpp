#include <iostream>
#include <cmath>
#include <sstream>
#include <stack>
#include <vector>
#include <string>
double RPN (const std::string& expr);
  
int main(){
  std::cout << "Input an RPN expression:" << std::endl;
  std::string inputString;
  std::getline(std::cin, inputString);
  std::cout << "Output: " <<std::endl << RPN(inputString) << std::endl;
  return 0;
}

double RPN (const std::string& expr){
  std::stack<double> s;  
  std::istringstream iss(expr);
  std::string token;

  while(iss >> token) {
    double tokenNum;
    if (std::istringstream(token) >> tokenNum){
        double tokenNum;
        std::istringstream(token) >> tokenNum;
        s.push(tokenNum);
    }
    else{
        double secondOperand = s.top();
        s.pop();
        double firstOperand = s.top();
        s.pop();
        if (token == "+")
          s.push(firstOperand + secondOperand);  
        if (token == "-")
          s.push(firstOperand - secondOperand);
        if (token == "*")
          s.push(firstOperand * secondOperand);
        if (token == "/") 
          s.push(firstOperand / secondOperand);      
        if (token == "^")
          s.push(std::pow(firstOperand, secondOperand));
    }
  }
  return s.top();
}
    
    
  
