#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

int lines_count (const std::string& fileName);
void print_vec(const std::vector<std::vector<int>>& vec);
void input2vector (std::vector<std::vector<int>>& d, 
        const std::string& fileName);
void WFI(int &nodes, std::vector<std::vector<int>>& d, 
        std::vector<std::vector<int>>& s);
void path_recon(int& n1,int& n2, std::vector<std::vector<int>>& s);

int main()
{
    std::string fileName ="cities_50.data";
    //init sequence square vector to zero
    int nodes = lines_count(fileName);    
    std::vector<std::vector<int>> s(nodes,std::vector<int>(nodes)); 
    //init adjacency 2D vector from input file
    std::vector<std::vector<int>> d;
    input2vector(d,fileName);
    //Implement Floyd-Warshall Algorithm
    WFI(nodes,d,s);
    for (int i = 1; i <= d.size(); i++){
        for (int j = i+1; j <= d[i].size(); j++){
            std::cout << i;
            path_recon(i,j,s);
            std::cout << " - " <<j; 
            std::cout << "\t" << d[i-1][j-1];
            std::cout << std::endl;
        }           
    }
}

int lines_count (const std::string& fileName){
    std::ifstream fileIn(fileName);
    int n =0;
    std::string line;
    while (std::getline(fileIn , line)){
        n++;
    }
    return n;
}

void print_vec(const std::vector<std::vector<int>>& vec)
{
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void input2vector (std::vector<std::vector<int>>& d, 
        const std::string& fileName){
    std::ifstream fileIn(fileName);
    std::string line;
    while (std::getline(fileIn , line)){
        std::vector<int> lineData;
        std::istringstream  lineStream(line);
        int value;
        // Read an integer at a time from the line
        while(lineStream >> value)
        {
            // Add the integers from a line to a 1D vector
            lineData.push_back(value);
        }
        // When all the integers have been read add the 1D array
        // into a 2D array (as one line in the 2D array)
        d.push_back(lineData);
    }
}

void WFI(int &nodes, std::vector<std::vector<int>>& d, 
        std::vector<std::vector<int>>& s){
    for (int k = 1; k <= nodes; k++){
        for (int i = 1; i <= nodes; i++){
            for (int j = 1; j <= nodes; j++){
                //If the path with two edges is less than the path with one edge
                if(i!=k && j!=k && i!=j){ 
                    if (d[i-1][j-1] >= (d[i-1][k-1] + d[k-1][j-1])){
                          //Set the cost of the edge to be the lesser cost.
                          d[i-1][j-1] = (d[i-1][k-1] + d[k-1][j-1]);
                          //This ensures proper path reconstruction.
                          s[i-1][j-1] = k;
                    }
                }
            }  	  
	}
    }    
}

void path_recon(int& n1,int& n2, std::vector<std::vector<int>>& s){
    int k;
    k = s[n1-1][n2-1];
    if (k != 0){
        path_recon(n1,k,s);
        std::cout<<" - "<< k;
        path_recon(k,n2,s);
    }
}    