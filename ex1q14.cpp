#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>

std::vector <unsigned long int> bruteForce (int &n);
std::vector <unsigned long int> modTestDiv (int &n);
void primes_to_file (int &n, const std::vector <unsigned long int>& primes,
        const std::string& fileName);

int main( ){
    int n;
    std::cout << "How many prime numbers (from the first one) are required?"; 
    std::cout<< std::endl;
    std::cin >> n;
    //std::vector<unsigned long int> primes = bruteForce(n);
    std::vector<unsigned long int> primes = modTestDiv(n);
    std::string fileName ="q14result.txt";
    primes_to_file(n,primes,fileName);
    return 0; 
}

void primes_to_file (int &n, const std::vector <unsigned long int>& primes,
        const std::string& fileName){
        if(n >= 1){
            std::ofstream fileOut;
            fileOut.open(fileName);
            for (int i = 0; i < primes.size(); i++) {
                fileOut << primes[i] << "\t";
                if ((i+1) % 8 == 0) {//Print eight numbers per line
                    fileOut<<std::endl;
                }	
            }
        }
        else{
            std::cerr << "Invalid Input" << std::endl;
        }
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
