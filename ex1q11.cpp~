#include<iostream>
#include<math.h>
#include<vector>

void bruteForce(int &n);
std::vector<unsigned long int> modTestd(int &n);
void print_vec(int &n, const std::vector<unsigned long int>& vec);

int main( ){
  int n;
  std::cout << "How many prime numbers (from the first one) are required?" << std::endl;
  std::cin >> n;
  bruteForce(n);
  print_vec(n,modTestd(n));
  return 0; 
}

void print_vec(int &n, const std::vector<unsigned long int>& vec)
{
  int i;
  std::cout << "First " << n << " prime number are:" << std::endl;
  for (i = 0; i <= vec.size()-1; i++) {
    std::cout << vec[i] <<std::endl;
  }
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
  
std::vector<unsigned long int> modTestd(int &n){
  unsigned long int  num = 3, count = 1, i, j;
   
  std::vector<unsigned long int> vec;
  vec.push_back(2);
  std::cout << "Size of vector is: " << vec.size() <<std::endl  << "Prime numbers in the vector are:" << std::endl;
  for (j = 0; j <= vec.size()-1; j++) {
    std::cout << vec[j] <<std::endl;
  }
  
  for (count = 1; count < n; ) {
    bool isPrime = true;
    for (i = 0; i <= vec.size()-1; i++) {
      if (num%vec[i] ==0) {
	isPrime = false;
	break;
      }    
    }

    if (isPrime == true) {
      vec.push_back(num);
      count++;
      std::cout << "Size of vector is: " << vec.size() <<std::endl  << "Prime numbers in the vector are:" << std::endl;
      for (j = 0; j <= vec.size()-1; j++) {
	std::cout << vec[j] <<std::endl;
      }
    }
    num++;
  }
  return vec;
}





