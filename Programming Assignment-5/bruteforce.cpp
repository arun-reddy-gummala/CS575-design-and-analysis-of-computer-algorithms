#include <iostream>
#include <bits/stdc++.h>
#include <vector> // for 2D vector
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

#define ipair pair<int, int>

int num;

int max_profit;

vector<pair<string, ipair> > data;

// Data structure to store graph edges
struct Edge {
	int id, profit, weight;

  friend bool operator<(Edge a, Edge b){
        double r1 = (double)a.profit / a.weight;
        double r2 = (double)b.profit / b.weight;
        return r1 < r2;
    }
};

/*Function to compute knapsack using all possible subsets of given items.*/
void bruteforce(Edge * list, int W, int num){

	vector<int> max_subset;

	int max, kw, cw, cp;

	max = kw = 0;

	/*Creating all possible subsets and checking with previous max.*/
  int k;
  k = pow(2,num);
	for(int i = 0; i < k; i++){

		vector<int> subset;

		for(int j = 0; j < num; j++){
			if(i & (1<<j)){
        subset.push_back(j+1);
      }
		}

		//int cw, cp;
		cw = cp = 0;

		for(int i = 0; i < subset.size(); i++) {
      int z;
      z = cw + list[subset[i]-1].weight;
			if(z <= W) {
				cw += list[subset[i]-1].weight;
				cp += list[subset[i]-1].profit;
			}
		}

		if(cp > max){
			max = cp;
			kw = cw;
			max_subset = subset;
		}
	}

	cout<<"Total weight :"<<kw<<endl;
  cout<<"Total profit :"<<max<<endl;

  //Creating the Output File
  ofstream outfile ("output1.txt");
  
  outfile << max_subset.size() <<"\t"<<max<<"\t"<<kw<<endl;

	cout<<endl<<"Items selected :"<<endl;
	for(int i=0; i < max_subset.size(); i++){
		cout<<"Item"<<max_subset[i]<<"\t"<<list[max_subset[i]-1].weight<<"\t"<<list[max_subset[i]-1].profit<<endl;
    outfile<<"Item"<<max_subset[i]<<"\t"<<list[max_subset[i]-1].weight<<"\t"<<list[max_subset[i]-1].profit<<endl;
  }
}

int main(int argc, char *argv[]){

  int i=0;
	int p,w,W;

  string str, name;

	//Reading the knapsack file data
  ifstream knapsack01(argv[2]);

  //ifstream file("knapsack01.txt");

  getline(knapsack01, str);

  istringstream ss(str);

  ss >> num >> W;

	cout<<endl<<"Capacity:"<<W<<endl<<endl;

  while (getline(knapsack01, str)) {
    stringstream strs(str);
    strs >> name >> p >> w;
    data.push_back(make_pair(name, ipair(p, w)));
  }

  vector<Edge> vec;

  for(int i=0;i < num; i ++){
    Edge myedge = {i,data[i].second.first, data[i].second.second};
    vec.push_back(myedge);
  }

  vector<Edge> e = vec;

	cout<<"Items in sorted order"<<endl;
  for (Edge &vec: e){
    cout<<"Item"<<vec.id<<" : "<<vec.profit<<" "<<vec.weight<<endl;
  }

	cout<<endl;

  Edge item_list[num];

  for (Edge &vec: e){
		Edge it;
		it.id = vec.id;
		it.profit = vec.profit;
		it.weight = vec.weight;

		if( i < num){
			item_list[i] = it;
		}
		i++;
	}

  bruteforce(item_list, W, num);

  return 0;
}
