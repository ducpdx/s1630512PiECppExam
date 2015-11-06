/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
* Ex1q16: Eratosthenes implementation
*******************************************************************************/
#include<iostream>
#include<cmath>
#include<array>
#include<vector>

std::vector<unsigned long int> Eratosthenes(double& n , unsigned long int &max);
void print_primes(double& n, const std::vector<unsigned long int>& primes);

int main( ){
    std::array<double,4> a = {std::pow(10,3),std::pow(10,4),
        std::pow(10,5),std::pow(10,6)};
    //std::array<double,4> a = {100,1000,10000,
    //20000};
    for (int i = 0; i < a.size(); i++){
        unsigned long int max = a[i] * std::log(a[i]*std::log(a[i])); //for n geq 6 Rosser's theorem  
        std::vector<unsigned long int> primes = Eratosthenes(a[i],max);
        print_primes(a[i], primes);        
    }  
}

std::vector<unsigned long int> Eratosthenes(double& n , unsigned long int &max){
    std::vector<bool> isPrime(max, true);
    std::vector<unsigned long int> primes; 
    for (unsigned long int p=2; p < max; p++){ // for all elements in array
        if (primes.size() > n){//keep track first n prime only
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
