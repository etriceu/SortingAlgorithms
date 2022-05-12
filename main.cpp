#include <iostream>
#include "sort.hpp"

using namespace std;

int main()
{
	const int size = 5;
	int tab[size] = {5, 4, 3, 2, 1};
	
	//sort::bubble(tab, tab+size);
	//sort::selection(tab, tab+size);
	//sort::merge(tab, tab+size);
	//sort::insertion(tab, tab+size);
	//sort::counting(tab, tab+size, 5, 1);
	//sort::heap(tab, size);
	//sort::bucket(tab, tab+size);
	//sort::quick(tab, tab+size-1);
	
	for(auto a : tab)
		cout<<a<<endl;
}
