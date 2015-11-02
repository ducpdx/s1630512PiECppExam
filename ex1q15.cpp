#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<chrono>
#include<iomanip>


void bruteForce(double &n);
void bruteForceM(double &n);
void modTest(double &n);

int main( ){
  int i;
  //std::vector<double> v = {5,1000};
  //std::vector<double> v = {pow(10,3),pow(10,4)};
  std::vector<double> v = {pow(10,3),pow(10,4),pow(10,5),pow(10,6)};
  //v.push_back(pow(10,3)); use this if compiler does not support c++11 and above
  
  std::ofstream fileOutbF, fileOutbFM, fileOutmT;
  fileOutbF.open("bFtimer.txt");
  //fileOutbFM.open("bFMtimer.txt");
  //fileOutmT.open("mTtimer.txt");
  fileOutbF << "%column 1: no of prime numbers" << std::endl << "%column 2: run time (in second)"<<std::endl;
  //fileOutbFM << "%column 1: no of prime numbers" << std::endl << "%column 2: run time (in second)"<<std::endl;
  //fileOutmT << "%column 1: no of prime numbers" << std::endl << "%column 2: run time (in second)"<<std::endl;
  
  for (i = 0; i < v.size(); i++) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    bruteForce(v[i]);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    fileOutbF <<std::fixed << std::setprecision(0)<< v[i] << "\t" << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << std::endl;
    std::cout << "elapsed time to find and print " <<std::fixed << std::setprecision(0) << v[i] << " prime numbers is: " << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
  }
  /*
  for (i = 0; i < v.size(); i++) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    bruteForceM(v[i]);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    fileOutbFM <<std::fixed << std::setprecision(0)<< v[i] << "\t" << std::fixed << std::setprecision(14)<< elapsed_seconds.count() << std::endl;
    std::cout << "elapsed time to find and print " <<std::fixed << std::setprecision(0)<< v[i] << " prime numbers is: " <<std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
  }

  for (i = 0; i < v.size(); i++) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    modTest(v[i]);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    fileOutmT <<std::fixed << std::setprecision(0)<< v[i] << "\t" << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << std::endl;
    std::cout << "elapsed time to find and print " <<std::fixed << std::setprecision(0)<< v[i] << " prime numbers is: " <<std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
  }
  */
  return 0; 
}

void bruteForce(double &n){
  unsigned long int  num = 3, count = 1, c;
  
  std::cout << "First " << n << " prime number are:" << std::endl;
  std::cout << count << "\t" << "2" << std::endl;

  for (count = 2; count <= n; ) {
    for (c = 2; c <= num-1; c++) {
      if (num%c == 0) {
	break;	
      }    
    }
    if (c == num) {
      std::cout << count << "\t" << num <<std::endl;
      count++;   
    }
    num++;  
  }
}    


void bruteForceM(double &n){
  unsigned long int  num = 3, count = 1, c;

  std::cout << "First " << n << " prime number are:" << std::endl;
  std::cout << count << "\t" << "2" << std::endl;  

  for (count = 2; count <= n; ) {
    for (c = 2; c <= sqrt(num); c++) {
      if (num%c == 0) {
	break;	
      }    
    }
    if (c > sqrt(num)) {
      std::cout << count << "\t" << num <<std::endl;
      count++;   
    }
    num++;  
  }
}    

void modTest(double &n){
  unsigned long int  num = 3, count = 1, i, j;

  std::vector<unsigned long int> vec;
  vec.push_back(2);

  std::cout << "First " << n << " prime number are:" << std::endl;
  std::cout << count << "\t" << "2" << std::endl;

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
      std::cout << count << "\t" << vec[count-1] <<std::endl;
    }
    num++;
  }
}






