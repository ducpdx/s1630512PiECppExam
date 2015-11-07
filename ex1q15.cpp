#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<chrono>//measure time
#include<iomanip>//fix precision
#include<array>
#include <functional>

std::vector <unsigned long int> bruteForce (double &n);
std::vector <unsigned long int> modTestDiv (double &n);
std::vector <unsigned long int> bruteForceM (double &n);
void print_primes (double &n, std::vector <unsigned long int>& primes);
void rtime_to_file (const std::string& fileName, 
    std::function<std::vector <unsigned long int>(double &n)> &function);

int main( ){
    std::array<std::string,3> fileName = 
        {"bruteForce.txt", "modTestDiv.txt", "bruteForceM.txt"};   
    std::array<std::function<std::vector <unsigned long int>(double &n)>,3>
        function = {bruteForce, modTestDiv,bruteForceM};
    for (int i = 0; i < fileName.size()-2; i++) {
        rtime_to_file(fileName[i], function[i]);
        }
    return 0; 
}

std::vector<unsigned long int> bruteForce(double &n){
    unsigned long int  num = 3;  
    std::vector<unsigned long int> primes;
    if (n >= 1){
        primes.push_back(2);
        unsigned long int c;//need to be the type of primes for mode test
        for (int count = 1; count < n; ){//counter from 1; "2" included before
            for (c = 2; c < num; c++){
                if (num % c == 0) {//mod test from 2 to n
                    break;	
                }    
            }
            if (c == num) {//to this point means no divisor up to n, Prime!
                primes.push_back(num);//push to result vector of Prime
                count++;//increase counter   
            }
            num++;  
        }
    }
    return primes;
}  

std::vector <unsigned long int> bruteForceM (double &n){
    unsigned long int  num = 3;  
    std::vector<unsigned long int> primes;
    if (n >= 1){
        primes.push_back(2);
        unsigned long int c;//need to be the type of primes for mode test
        for (int count = 2; count <= n; ){//counter from 1; "2" included before
            for (c = 2; c <= sqrt(num); c++){//non prime has divisor lt sqrt
                if (num % c == 0) {//mod test from 2 to n
                    break;	
                }    
            }
            if (c > sqrt(num)) {//to this point means no divisor up to n, Prime!
                primes.push_back(num);//push to result vector of Prime
                count++;//increase counter   
            }
            num++;  
        }
    }
    return primes;
}    

std::vector<unsigned long int> modTestDiv(double &n){
    unsigned long int  num = 3;   
    std::vector<unsigned long int> primes;//result vector of Primes
    if (n >= 1){
        primes.push_back(2);  
        for (int count = 1; count < n; ) {//counter from 1; "2" included before 
            bool isPrime = true;
            for (int i = 0; i < primes.size(); i++){
                if (num % primes[i] ==0) {//non-primes  are products of primes
                  isPrime = false;
                  break;
                }    
            }
            if (isPrime == true) {
                primes.push_back(num);
                count++;//increase counter
            }
            num++;
        }
    }
    return primes;
}

void print_primes (double &n, std::vector <unsigned long int>& primes){
    //print after finding finished, not on-the-fly
    if(n >= 1){
        std::cout << "First " << n << " prime number(s) is(are):" << std::endl;
        for (int i = 0; i < primes.size(); i++) {
          std::cout << primes[i] <<std::endl;
        }
    }
    else{
        std::cerr << "Invalid Input" << std::endl;
    }
}

void rtime_to_file (const std::string& fileName, 
    std::function<std::vector <unsigned long int>(double &n)> &f){    
    std::ofstream fileOut;
    fileOut.open(fileName);
    fileOut << "%column 1: no of prime numbers" << std::endl;
    fileOut << "%column 2: run time (in second)"<<std::endl;
    std::array<double,4> v = {std::pow(10,3),std::pow(10,4),
          std::pow(10,5),std::pow(10,6)};
    //std::array<double,4> v = {100,1000,10000,20000};
    for (int i = 0; i < v.size(); i++) {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        std::vector<unsigned long int> primes = f(v[i]);
        //print_primes(v[i],primes);
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        fileOut << std::fixed << std::setprecision(0)<< v[i] << "\t";
        fileOut << std::fixed << std::setprecision(14)<<elapsed_seconds.count(); 
        fileOut << std::endl;
        std::cout << "elapsed time to find and print " <<std::fixed << std::setprecision(0) << v[i] << " prime numbers is: " << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
    }
}






