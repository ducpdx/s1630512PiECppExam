/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
* Ex1q16: Eratosthenes implementation
*******************************************************************************/
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<chrono>//measure time
#include<iomanip>//fix precision
#include<array>
#include <functional>


std::vector<unsigned long int> Eratosthenes(double& n);
void print_primes(double& n, const std::vector<unsigned long int>& primes);
void rtime_to_file (const std::string& fileName, 
    std::function<std::vector <unsigned long int>(double &n)> &function);

int main( ){
    std::array<std::string,1> fileName = 
        {"Eratosthenes.txt"};   
    std::array<std::function<std::vector <unsigned long int>(double &n)>,1>
        function = {Eratosthenes};
    for (int i = 0; i < fileName.size(); i++) {
        rtime_to_file(fileName[i], function[i]);
        }         
}

std::vector<unsigned long int> Eratosthenes(double& n){
    std::vector<bool> isPrime(max, true);
    std::vector<unsigned long int> primes; 
    unsigned long int max = n * std::log(n*std::log(n)); //Rosser's theorem
    for (unsigned long int p=2; p < max; p++){ // for all elements in array
        if (primes.size() > n-1){//keep track first n prime only, vector count from 0
            break;
        }
        else if(isPrime[p] == true){ // it is not multiple of any other prime
            primes.push_back(p);
        }
        // mark all multiples of prime selected above as non primes
        int c=2;
        int mul = p * c;
        while(mul <= max){
            isPrime[mul] = false;
            c++;
            mul = p*c;
        }        
    }
    return primes;    
}

void print_primes(double& n, const std::vector<unsigned long int>& primes)
{
    std::cout << "First " << n << " prime number are:" << std::endl;
    for (int i = 0; i < primes.size(); i++){
            std::cout << primes[i]<< std::endl;
    }
}

void rtime_to_file (const std::string& fileName, 
    std::function<std::vector <unsigned long int>(double &n)> &f){    
    std::ofstream fileOut;
    fileOut.open(fileName);
    fileOut << "%column 1: no of prime numbers" << std::endl;
    fileOut << "%column 2: run time (in second)"<<std::endl;
    std::array<double,4> v = {std::pow(10,3),std::pow(10,4),
          std::pow(10,5),std::pow(10,7)};
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
        std::cout << "elapsed time to find" <<std::fixed << std::setprecision(0) << v[i] << " prime numbers is: " << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
    }
}