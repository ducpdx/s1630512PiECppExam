#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>

void bruteForceOF(int &n);
void modTestOF(int &n);

int main( ){
  int n;
  std::cout << "How many prime numbers (consecutively from the first one) are required?" << std::endl;
  std::cin >> n;
  //bruteForceOF(n);
  modTestOF(n);
  return 0; 
}

void bruteForceOF(int &n){
  unsigned long int  num = 3, count = 1, c;
  
  if (n >= 1) {
    std::cout << "First " << n << " prime number are:" << std::endl;
    std::cout << "2" << std::endl;
  }

  for (int count = 2; count <= n; ) {
    for (int c = 2; c <= num-1; c++) {
      if (num%c == 0) {
	break;	
      }    
    }
    if (int c == num) {
      std::cout << num <<std::endl;
      count++;   
    }
    num++;  
  }
}  
  
void modTestOF(int &n){
  unsigned long int  num = 3, count = 1, i, j;
   
  std::vector<unsigned long int> vec;
  std::ofstream fileOut;
  vec.push_back(2);
  fileOut.open("q14result.txt");
  fileOut << vec[count-1] << "\t"; 
   
  for (count = 1; count < n; ) {
    bool isPrime = true;
    for (i = 0; i <= vec.size()-1; i++) {
      if (num % vec[i] == 0) {
	isPrime = false;
	break;
      }    
    }

    if (isPrime == true) {
      vec.push_back(num);
      count++;
      fileOut << vec[count-1] << "\t";
      if (count % 8 == 0) {
        fileOut<<std::endl;
      }	      
    }
    num++;
  }
}





