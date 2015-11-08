/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
 * Floyd-Warshall’s Algorithm
*******************************************************************************/
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<sstream>
#include<chrono>//measure time
#include<iomanip>//fix precision
#include<array>
#include <functional>

int lines_count (const std::string& fileName);
std::vector<std::vector<int>> input2vector (const std::string& fileName);
void WFI(int &nodes, std::vector<std::vector<int>>& d, 
        std::vector<std::vector<int>>& s);
void path_recon_to_file(std::ofstream& fileOut1, int& n1,int& n2, std::vector<std::vector<int>>& s);

int main()
{  
    std::array<std::string,3> fileName = 
        {"cities_3.data", "cities_10.data", "cities_50.data"};
    std::array<std::string,3> filePathDistance = 
        {"shortest_3_WFI.txt", "shortest_10_WFI.txt", "shortest_50_WFI.txt"};
    //std::string fileName ="cities_3.data";
    //init sequence square vector to zero
    for (int i = 0; i < fileName.size(); i++) {
        int nodes = lines_count(fileName[i]);    
        std::ofstream fileOut1;
        fileOut1.open(filePathDistance[i]);
        std::ofstream fileOut2;
        fileOut2.open("timer_WFI.txt", std::ios_base::app);
        std::vector<std::vector<int>> s(nodes,std::vector<int>(nodes, 0)); 
        //init adjacency 2D vector from input file
        std::vector<std::vector<int>> d = input2vector(fileName[i]);
        //Implement Floyd-Warshall Algorithm
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        WFI(nodes,d,s);
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        fileOut2 << std::fixed << std::setprecision(0)<< fileName[i] << "\t";//fix precision
        fileOut2 << std::fixed << std::setprecision(14)<<elapsed_seconds.count(); 
        fileOut2 << std::endl;
        std::cout << "elapsed time to find shortest route with WFI for " << fileName[i] << " is: " << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
        for (int i = 1; i <= d.size(); i++){
            for (int j = i+1; j <= d[i].size(); j++){
                //i,j is correspond to algorithm so start from 1
                //j will start from i+1 because we move to other cities
                fileOut1 << i;
                path_recon_to_file(fileOut1,i,j,s);//path reconstruction  
                fileOut1 << " - " <<j; 
                fileOut1 << "\t\t" << d[i-1][j-1];// print distance
                fileOut1 << std::endl;
            }           
        }
    }
}

int lines_count (const std::string& fileName){
    std::ifstream fileIn(fileName);
    int n =0;
    std::string line;
    while (std::getline(fileIn , line)){
        n++;//increase n after each line
    }
    return n;
}

std::vector<std::vector<int>> input2vector (const std::string& fileName){
    std::vector<std::vector<int>> d;
    std::ifstream fileIn(fileName);
    std::string line;
    while (std::getline(fileIn , line)){
        std::vector<int> lineData;
        std::istringstream lineStream(line);
        int value;
        // Read an integer at a time from the line
        while(lineStream >> value){
            // Add the integers from a line to a 1D vector
            lineData.push_back(value);
        }
        // When all the integers have been read add the 1D array
        // into a 2D array (as one line in the 2D array)
        d.push_back(lineData);
    }
    return d;
}

void WFI(int &nodes, std::vector<std::vector<int>>& d, 
        std::vector<std::vector<int>>& s){
    for (int k = 1; k <= nodes; k++){
        for (int i = 1; i <= nodes; i++){
            for (int j = 1; j <= nodes; j++){
                //If the path with two edges is less than the path with one edge
                //node that algorithm is from 1 but vector is from 0
                if(i!=k && j!=k && i!=j){ 
                    if (d[i-1][j-1] >= (d[i-1][k-1] + d[k-1][j-1])){
                        //choose the one with more nodes
                        //Set the cost of the edge to be the lesser cost.
                        d[i-1][j-1] = (d[i-1][k-1] + d[k-1][j-1]);
                        //This ensures proper path reconstruction. 
                        //at this point increase to k+1 to continue algorithm
                        s[i-1][j-1] = k;
                    }
                }
            }  	  
	}
    }    
}

void path_recon_to_file(std::ofstream& fileOut1, int& n1,int& n2, 
        std::vector<std::vector<int>>& s){
    int k;
    k = s[n1-1][n2-1];//start and destination, remember to -1 in the index
    if (k != 0){
        path_recon_to_file(fileOut1,n1,k,s);//recursive
        fileOut1 << " - "<< k;//add - to separate new nodes
        path_recon_to_file(fileOut1,k,n2,s);//recursive
    }
}    