#include<iostream>
#include<math.h>
#include<vector>
#include<iomanip>

std::vector <unsigned long int> bruteForce (int &n);
std::vector <unsigned long int> modTestDiv (int &n);
void print_ratio (int &n, const std::vector <unsigned long int>& primes);

int main( ){
    int n = 10000;
    //std::vector<unsigned long int> primes = bruteForce(n);
    std::vector<unsigned long int> primes = modTestDiv(n);
    print_ratio(n,primes);
    return 0; 
}

std::vector<unsigned long int> bruteForce(int &n){
    unsigned long int  num = 3;  
    std::vector<unsigned long int> primes;
    if (n >= 1){
        primes.push_back(2);
        unsigned long int c;//need to be the type of primes for mode test
        int count = 1;
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

std::vector<unsigned long int> modTestDiv(int &n){
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

void print_ratio (int &n, const std::vector <unsigned long int>& primes){
    std::cout << "n\t:\t p(n)\t:\t n*ln( p(n) )/p(n) " << std::endl;
    for (int i = 0; i < primes.size(); i++) {
        std::cout << i+1 << "\t:\t" << primes[i] <<"\t:\t" 
            <<std::fixed << std::setprecision(14) << 
                double((i+1)*log(primes[i])/primes[i])<< std::endl;
        }//set precision used for increase decimal displayed
}


