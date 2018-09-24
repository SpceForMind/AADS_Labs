
#include <iostream>
using namespace std;

#define PAIR 2

struct City
{	
	//defaut constructor
	City() : visited(false)
	{}
	bool visited;
};


struct Graph
{
	//default constructor
	Graph() : cities(NULL), relations(NULL)
	{}
	Graph(int count_cities, int count_rel) : count_cities(count_cities), count_rel(count_rel)
	{
		cities = new City[count_cities];
		relations = new int *[count_rel];
		for(int i = 0; i < count_rel; ++i)
			relations[i] = new int[PAIR];
	}
	~Graph()
	{
		delete[] cities;
		for(int i = 0; i < count_rel; ++i)
			delete[] relations[i];
		delete[] relations;
	}
	City *cities;
	int **relations;
	int count_cities;
	int count_rel;
};


void bc(Graph &graph, int cur_city, int arrival, bool * exists)
{
	if(cur_city == arrival)
		*exists = true;
	else
	{
		for(int i = 0; i < graph.count_rel; ++i)
			if(graph.relations[i][0] == cur_city && !graph.cities[graph.relations[i][1]].visited)
			{	
				graph.cities[graph.relations[i][1]].visited = true;
				cout << graph.relations[i][0] << "-->" << graph.relations[i][1] << endl; //log informations
				bc(graph, graph.relations[i][1], arrival, exists);
			}
			else if(graph.relations[i][1] == cur_city && !graph.cities[graph.relations[i][0]].visited)
			{
				graph.cities[graph.relations[i][0]].visited = true;
				cout << graph.relations[i][1] << "-->" << graph.relations[i][0] << endl; //log informations
				bc(graph, graph.relations[i][0], arrival, exists);
			}	
	}
}


int main()
{
	int count_cities;
	int count_rel;
	cout << "Enter count cities: ";
	cin >> count_cities;
	cout << "Enter count roads between cities: ";
	cin >> count_rel;
	Graph graph(count_cities, count_rel);	
	//input pairs
	cout << "Enter pairs in format <city1> <city2>" << endl;
	for(int i = 0; i < count_rel; ++i)
		for(int j = 0; j < PAIR; ++j)
			cin >> graph.relations[i][j];
	cout << "Relations: " << endl;	
	for(int i = 0; i < count_rel; ++i)
		cout << "[" << graph.relations[i][0] << ", " << graph.relations[i][1] << "]" << endl;
	bool exists = false; //variable which will be true after bypassing relations between cities if road exists
	int cur_city;
	int arrival;
	cout << "Enter current city with wich stating searching: ";
	cin >> cur_city;
	cout << "Enter arrival city: ";
	cin >> arrival;
	graph.cities[cur_city].visited = true;
	bc(graph, cur_city, arrival, &exists);
	if(exists)
		cout << "Way exists!" << endl;
	else
		cout << "Way doesn't exist!" << endl;
	
	return 0;
}
