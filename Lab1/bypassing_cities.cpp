
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


void bc(int cur_city, int arrival, City *cities, int count_cities, int **relations, int count_relations, bool * exists)
{
	if(cur_city == arrival)
		*exists = true;
	for(int i = 0; i < count_relations; ++i)
		if(relations[i][0] == cur_city && !cities[relations[i][1]].visited)
		{	
			cities[relations[i][1]].visited = true;
			cout << relations[i][0] << "-->" << relations[i][1] << endl; //log informations
			bc(relations[i][1], arrival, cities, count_cities, relations, count_relations, exists);
		}
		else if(relations[i][1] == cur_city && !cities[relations[i][0]].visited)
		{
			cities[relations[i][0]].visited = true;
			cout << relations[i][1] << "-->" << relations[i][0] << endl; //log informations
			bc(relations[i][0], arrival, cities, count_cities, relations, count_relations, exists);
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
	City *cities = new City[count_cities];
	for(int i = 0; i < count_cities; ++i)
		cout << cities[i].visited << endl;
	int **relations = new int *[count_rel];
	for(int i = 0; i < count_rel; ++i)
		relations[i] = new int[PAIR];
	//input pairs
	cout << "Enter pairs in format <city1> <city2>" << endl;
	for(int i = 0; i < count_rel; ++i)
		for(int j = 0; j < PAIR; ++j)
			cin >> relations[i][j];
	cout << "Relations: " << endl;	
	for(int i = 0; i < count_rel; ++i)
		cout << "[" << relations[i][0] << ", " << relations[i][1] << "]" << endl;
	bool exists = false; //variable which will be true after bypassing relations between cities if road exists
	int cur_city;
	int arrival;
	cout << "Enter current city with wich stating searching: ";
	cin >> cur_city;
	cout << "Enter arrival city: ";
	cin >> arrival;
	cities[cur_city].visited = true;
	bc(cur_city, arrival, cities, count_cities, relations, count_rel, &exists);
	if(exists)
		cout << "Way exists!" << endl;
	else
		cout << "Way doesn't exist!" << endl;

	return 0;
}
