#include<iostream>
#include<math.h>
#include<vector>
#include<iomanip>

void bruteForce(int &n);
void modTest(int &n);

int main( ){
  int n;
  std::cout << "How many prime numbers (from the first one) are required?" << std::endl;
  std::cin >> n;
  //bruteForce(n);
  modTest(n);
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

void modTest(int &n){
  unsigned long int  num = 3, count = 1, i, j;
   
  std::vector<unsigned long int> vec;
  
  std::cout << "n\t:\t p(n)\t:\t n*ln( p(n) )/p(n) " << std::endl;
  vec.push_back(2);
  std::cout << count << "\t:\t" << vec[count-1] <<"\t:\t" << std::fixed << std::setprecision(14) << double(count*log(vec[count-1])/vec[count-1])<< std::endl;
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
      std::cout << count << "\t:\t" << vec[count-1] <<"\t:\t" <<std::fixed << std::setprecision(14) << double(count*log(vec[count-1])/vec[count-1])<< std::endl;
    }
    num++;
  }
}





