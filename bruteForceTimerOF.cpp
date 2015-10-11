#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<chrono>
#include<ctime>

void bruteForceTimerOF(int &n);

int main( ){
  int i;
  std::vector<int> v = {pow(10,3),pow(10,4),pow(10,5),pow(10,6)};
  std::chrono::time_point<std::chrono::system_clock> start, end;
  
  std::ofstream fileOut;
  for (i = 0; i < v.size(); i++) {
    
    fileOut << v[i] << "\t" << bruteForce(v[i]) << std::endl;    
  }  
  return 0; 
}

void bruteForce(int &n){
  unsigned long int  num = 3, count = 1, c;
  
  if (n >= 1) {
    std::cout << "First " << n << " prime number are:" << std::endl;
    std::cout << "2" << std::endl;
  }

  for (count = 2; count <= n; ) {
    for (c = 2; c <= num-1; c++) {
      if (num%c == 0) {
	break;	
      }    
    }
    if (c == num) {
      std::cout << num <<std::endl;
      count++;   
    }
    num++;  
  }
}    






