#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int num;

//to store profit and weight values
unordered_map<int, int> profit;
unordered_map<int, int> weight;

int main(int argc, char *argv[])
{
  int j;
  string str;

  //Using current time as a seed for random generator
  srand(time(0));

  //Generating a random number to take in as 'n' vertices
  num = (rand() % (8 - 4 + 1)) + 4;

  //display n value
  cout<<"Selected n value = "<<num<<endl;
  cout<<endl;

  //creating the random profit values in range 10 to 30
	for(int i = 0; i < num; i++){
		profit[i] = ((rand() % (30 - 10 + 1)) + 10);
	}

  //creating the random weight values in range 5 to 20
		for(int i = 0; i < num; i++){
			weight[i] = ((rand() % (20 - 5 + 1)) + 5);
		}

  int sum = 0;
  int W = 0;

	for(int i = 0; i < num; i++){
		sum = sum + weight[i];
	}

  //Calculating the knapsack capacity
  W = floor(0.6 * sum);

  string strn;

  strn = argv[2];

	//Creating the Output File
	ofstream outfile (strn);

	outfile << num <<"\t"<<W<<"\n";

		for(int i = 0; i < num; i++)
		  outfile<<"item"<<i + 1 <<"\t"<<weight[i]<<"\t"<<profit[i]<<"\n";

  return 0;
}
