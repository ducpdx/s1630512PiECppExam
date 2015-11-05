/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
*******************************************************************************/
include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
    
class City{
    int distance;
    bool visited;
    int cCity;
public:
    City(int distance, bool visited, int cCity){
        set_Values(distance,visited,cCity);
    };
    void set_Values(int& d, bool& v, int &p);
    void set_distance(int& d);
    void set_visited(bool& v);
    void set_cCity(int& p);
    int get_distance();
    bool get_visited();
    int get_cCity();
};

int lines_count (const std::string& fileName);
void input2vector (std::vector<std::vector<int>>& d, 
        const std::string& fileName);
int Dijkstra(int&nodes, int& s, int& t, std::vector<City>& city, 
    std::vector<std::vector<int>>& d);
void path_recon(int& s,int &t, int&nodes, std::vector<City>& city);

int main()
{
    std::string fileName ="cities_10.data";
    int nodes = lines_count(fileName); 
    std::vector<std::vector<int>> d;
    input2vector(d,fileName);
    for (int i = 1; i <= nodes; i++){
        for (int j = i+1; j <= nodes; j++){
            int INFINITY = 123456789;
            std::vector<City> city(nodes,City(INFINITY,false,0)); 
            int shortest = Dijkstra(nodes,i,j,city,d);
            path_recon(i, j, nodes, city);
            std::cout << "\t" << shortest;
            std::cout << std::endl;
        }           
    }
}

void City::set_Values(int& d, bool& v, int &p){
    distance = d;        
    visited = v;        
    cCity = p;            
}

void City::set_distance(int& d){
    distance = d;        
}

void City::set_visited(bool& v){
    visited = v;        
}

void City::set_cCity(int& p){
    cCity = p;        
}

int City::get_distance(){
    return distance;
}
bool City::get_visited(){
    return visited;
}
int City::get_cCity(){
    return cCity;
}
    
int Dijkstra(int&nodes, int& s, int& t, std::vector<City>& city, 
    std::vector<std::vector<int>>& d){   
    int INFINITY = 123456789;
    int i_distance = 0;
    bool i_visited = true;
    int i_cCity = 1;
    city[s-1].set_distance(i_distance);
    city[s-1].set_visited(i_visited);
    city[s-1].set_cCity(i_cCity);
    // Find shortest route
    int k = s;
    do{
        for (int j = 1; j <= nodes; j++){
            if((city[j-1].get_visited() == false) && (d[k-1][j-1]!= INFINITY)){
                if(city[j-1].get_distance() >= city[k-1].get_distance() 
                        + d[k-1][j-1]){
                    int n_distance = city[k-1].get_distance() + d[k-1][j-1];
                    city[j-1].set_distance(n_distance);
                    city[j-1].set_cCity(k);
                }        
            }           
        }
        int min = INFINITY;
        for (int i = 1; i <= nodes; i++){
            
            if((city[i-1].get_visited() == false) && 
                    (city[i-1].get_distance() < min)){
                min = city[i-1].get_distance();
                k = i;
            }
        }
        bool n_visited = true;
        city[k-1].set_visited(n_visited);
    }
    while (k != t);
    return city[t-1].get_distance();    
}

void path_recon(int& s, int& t, int& nodes, std::vector<City>& city){
    std::vector<int> path(nodes); 
    int l = 0;
    std::cout << s << " - ";
    for (int v = t; v != s; v = city[v-1].get_cCity()){
        path[l++] = v;
    }
    for (int i = l; i > 1; i--){
        std::cout << path[i-1] << " - ";
    }       
    std::cout << t;
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
