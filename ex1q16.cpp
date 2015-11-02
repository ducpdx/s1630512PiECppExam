#include<iostream>
#include<cmath>
#include<vector>

void modTest(int &n);

int main( ){
  int i;
  unsigned long int max = n * log(nlog(n)); //for n geq 6 Rosser's theorem  
  std::vector<double> v = {pow(10,3),pow(10,4),pow(10,5),pow(10,6)};
}

void modTest(int &n){
  unsigned long int  num = 3, count = 1, i, j;

  std::vector<unsigned long int> vec;

  std::cout << "n\t:\t p(n)\t:\t n*ln( p(n) )/p(n) " << std::endl;
  vec.push_back(2);
  std::cout << count << "\t:\t" << vec[count-1] <<"\t:\t" << std::fixed << std:\
    :setprecision(14) << double(count*log(vec[count-1])/vec[count-1])<< std::endl;
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
      std::cout << count << "\t:\t" << vec[count-1] <<"\t:\t" <<std::fixed << s\
	td::setprecision(14) << double(count*log(vec[count-1])/vec[count-1])<< std::end\
	l;
    }
    num++;
  }
}
