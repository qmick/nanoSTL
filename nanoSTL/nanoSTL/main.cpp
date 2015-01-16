#include <vector>
#include <deque>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <climits>
#include "algo.hpp"

using namespace std;


int main(int argc, char* argv[])
{
	
	double sumt = 0;
	const int arr_size = 10;
	std::vector<int> arr(arr_size);
	std::vector<int> brr(arr_size);

	std::default_random_engine gen;
	std::uniform_int_distribution<int> dis(0, 100);

	for(size_t i = 0; i < arr_size; i++)
		arr[i] = dis(gen);

	memcpy(&brr[0], &arr[0], arr_size * sizeof(int));
	cout<<"ori is: ";
	for(int i = 0; i < 10; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	clock_t t = GetTickCount();
	//insertionSort(arr.begin(), arr.end());
	//selectionSort(arr.begin(), arr.end());
	//heapSort(arr.begin(), arr.end());
	//std::sort(arr.begin(), arr.end());
	
	cout<< "heap sort time is: "<<(GetTickCount() - t) / 1000.0<<"\n";
	cout<<"result is: ";
	for(int i = 0; i < 10; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	t = GetTickCount();

	esort(brr.begin(), brr.end());	

	cout<< "quick sort time is: "<<(GetTickCount() - t) / 1000.0<<"\n";
	for(int i = 0; i < arr_size; i++)
		if(arr[i] != brr[i]) 
		{
			cout<<"check error\n";
			break;
		}
	return 0;



	int array_int[1000];
	double array_double[1000];
	vector<double> vector_double(1000);

	esort(array_int, array_int + 1000);
	esort(array_double, array_double + 1000);
	esort(vector_double.begin(), vector_double.end());
}