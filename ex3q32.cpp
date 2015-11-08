/*******************************************************************************
* Name: Duc Nguyen
* Student number: s1630512                                            
* Email address for correspondence: nguyenmanhduc@student.utwente.nl 
* or ngmaduc@gmail.com
* Dijkstra
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
    
class City{
    int distance;//store best distance
    bool visited;//visit or not
    int cCity;//other city which it connected to
public:
    City(int distance, bool visited, int cCity){
        set_Values(distance,visited,cCity);//initializer
    };
    void set_Values(int& d, bool& v, int &p);//initializer
    //set methods
    void set_distance(int& d);
    void set_visited(bool& v);
    void set_cCity(int& p);
    //get methods
    int get_distance();
    bool get_visited();
    int get_cCity();
};


int lines_count (const std::string& fileName);
std::vector<std::vector<int>> input2vector (const std::string& fileName);
int Dijkstra(int&nodes, int& s, int& t, std::vector<City>& city, 
    std::vector<std::vector<int>>& d);
void path_recon_to_file(std::ofstream& fileOut1,int& s,int &t, int&nodes, std::vector<City>& city);

int main()
{
    std::array<std::string,3> fileName = 
        {"cities_3.data", "cities_10.data", "cities_50.data"};
    std::array<std::string,3> filePathDistance = 
        {"shortest_3_DKT.txt", "shortest_10_DKT.txt", "shortest_50_DKT.txt"};
    for (int i = 0; i < fileName.size(); i++) {
        int nodes = lines_count(fileName[i]); 
        //distance matrix
        std::vector<std::vector<int>> d = input2vector(fileName[i]);
        std::ofstream fileOut1;
        fileOut1.open(filePathDistance[i]);
        std::ofstream fileOut2;
        fileOut2.open("timer_DKT.txt", std::ios_base::app);
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        for (int i = 1; i <= nodes; i++){
            for (int j = i+1; j <= nodes; j++){
                int infinity = 1234567;//know from the input file
                //set all to infinity
                std::vector<City> city(nodes,City(infinity,false,0)); 
                int shortest = Dijkstra(nodes,i,j,city,d);
                path_recon_to_file(fileOut1, i, j, nodes, city);
                fileOut1 << "\t\t" << shortest;
                fileOut1 << std::endl;
            }           
        }
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        fileOut2 << std::fixed << std::setprecision(0)<< fileName[i] << "\t";//fix precision
        fileOut2 << std::fixed << std::setprecision(14)<<elapsed_seconds.count(); 
        fileOut2 << std::endl;
        std::cout << "elapsed time to find shortest route with Dijkstra for " << fileName[i] << " is: " << std::fixed << std::setprecision(14)<<elapsed_seconds.count() << " seconds" << std::endl;
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
    int infinity = 1234567;
    //set distance for the first city to 0
    int i_distance = 0;
    bool i_visited = true;
    int i_cCity = 1;
    city[s-1].set_distance(i_distance);
    city[s-1].set_visited(i_visited);
    city[s-1].set_cCity(i_cCity);
    // Find shortest route, remember algorithm is from 1, vector is from 0.
    int k = s;//set k is the source point
    do{
        for (int j = 1; j <= nodes; j++){
            if((city[j-1].get_visited() == false) && (d[k-1][j-1]!= infinity)){
                if(city[j-1].get_distance() >= city[k-1].get_distance() 
                        + d[k-1][j-1]){
                    //adjacent city with lowest distance to the source
                    //updated from distance matrix
                    int n_distance = city[k-1].get_distance() + d[k-1][j-1];
                    city[j-1].set_distance(n_distance);//best distance so far
                    //path recon
                    city[j-1].set_cCity(k);//update connected city for shortest
                }        
            }           
        }
        int min = infinity;
        for (int i = 1; i <= nodes; i++){           
            //two loop looks the same but cannot combined because city[i] should
            //not updated on-the-fly. the second loop needs the first loop done
            if((city[i-1].get_visited() == false) && 
                    (city[i-1].get_distance() < min)){
                min = city[i-1].get_distance();
                k = i;
            }
        }
        bool n_visited = true;
        city[k-1].set_visited(n_visited);//mark as visited
    }
    while (k != t);//if the city is the endpoint, stop, molding completed! 
    return city[t-1].get_distance();    
}

void path_recon_to_file(std::ofstream& fileOut1, int& s, int& t, int& nodes, std::vector<City>& city){
    std::vector<int> path(nodes); 
    int l = 0;
    fileOut1 << s << " - ";
    for (int v = t; v != s; v = city[v-1].get_cCity()){//start at the last city
        path[l++] = v;//add to route
    }
    for (int i = l; i > 1; i--){//add until the first city i=1
        fileOut1 << path[i-1] << " - ";
    }       
    fileOut1 << t;
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
