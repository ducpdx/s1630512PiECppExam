#include <iostream>
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
int Dijkstra(int&nodes, int& s, int& t, std::vector<City>& city, 
    std::vector<std::vector<int>>& d);
void path_recon(int& t, std::vector<City>& city);
void print_vec(const std::vector<std::vector<int>>& vec);
void input2vector (std::vector<std::vector<int>>& d, 
        const std::string& fileName);


int main()
{
    std::string fileName ="cities_3.data";
    //init adjacency 2D vector from input file
    int nodes = lines_count(fileName);    
    std::vector<std::vector<int>> d;
    input2vector(d,fileName);
    //init route vectot
    //Implement Dijkstra Algorithm
    //print_vec(d);
    int s = 1;
    int t = 2;
    //std::vector<City>& city;    
    path_recon(t,city);
    Dijkstra(nodes,s,t,city,d);
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
    //Initialize
    int INFINITY = 123456789;
    for (int j = 1; j <= nodes; j++){
        city[j] = City(INFINITY,false,0);             
    }
    int i_distance = 0;
    bool i_visited = false;
    int i_cCity = 0;
    city[s].set_distance(i_distance);
    city[s].set_visited(i_visited);
    city[s].set_cCity(i_cCity);
    // Find shortest route
    int k = s;
    while (k != t){
        for (int j = 1; j <= nodes; j++){
            if((city[j].get_visited() == false) && (d[k-1][j-1]!= INFINITY)){
                if(city[j].get_distance() >= city[k].get_distance() 
                        + d[k-1][j-1]){
                    int n_distance = city[k].get_distance() + d[k-1][j-1];
                    city[j].set_distance(n_distance);
                    city[j].set_cCity(k);
                }        
            }           
        }
        
        int min = INFINITY;
        int k = 1;
        for (int i = 1; i <= nodes; i++){
            if((city[i].get_visited() == false) && 
                    (city[i].get_distance() < min)){
                min = city[i].get_distance();
                k = i;
            }
            bool n_visited = true;
            city[k].set_visited(n_visited);
            if(k == 1){
                return 0;
            }
        }        
    }
    return city[t].get_distance();    
}

void path_recon(int& t, int&nodes, std::vector<City>& city){
    std::vector<int> path(nodes); 
    int l = 0;
    for (int s = t; s != 1; s = city[s].get_cCity()){
        path[l++] = s;
    }
    for (int i = l; i > 1; i--){
        std::cout << path[i-1] << " - ";
        std::cout << t;
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