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

int max(int a, int b) {
  if (a > b){
    return a;
  }
  else{
    return b;
  }
}

// Data structure to store graph edges
struct Edge {
	int id, profit, weight;

  friend bool operator<(Edge a, Edge b){
        double r1 = (double)a.profit / a.weight;
        double r2 = (double)b.profit / b.weight;
        return r1 < r2;
    }
};

//To define the direction
struct node{
    int profit, weight, level;
};

struct t{
	int value;
	int flag;
};

// Knapsack for storing the selected nodes
struct knapsack{
	Edge items[8];

	int num_item;
	int total_weight;
	int total_profit;
};

// Refined Dynamic Approach
void dynamic(Edge * list, int W, int num){

	t mat[num + 1][W + 1];

	int datas[999], tmp[999], count = 0, range = 1;

	datas[0] = W;

	// Initialize table
	for (int i = 0; i < num + 1; i++){
		for (int j = 0; j < W + 1; j++){
			mat[i][j].value = 0;
			mat[i][j].flag = -1;
		}
	}

	// Decide which cells are needed for final result,
	for (int i = num; i > 0; i--){
		for (int j = 0; j < range; j++){
			mat[i][datas[j]].flag = 0;
		}

    int wi1, wi2;

		for (int k = 0; k < range; k++){
			wi1 = datas[k];
			wi2 = datas[k] - list[i - 1].weight;

			tmp[k * 2] = wi1;
			tmp[(k * 2) + 1] = wi2;
			count = k * 2 + 1;
		}

		for (int k = 0; k <= count; k++){
			datas[k] = tmp[k];
		}
		range = range * 2;
	}

	//Creating the Output File
	ofstream enfile ("entries2.txt");

	// Dynamic programming takes place here
	for (int i = 0; i <= num; i++){
		for (int j = 0; j <= W; j++){
			if (i == 0 || j == 0){
				mat[i][j].value = 0;
			}
			// Only consider the previously true marked cells for final result
			else if(mat[i][j].flag == 0){
				int k;
				k = list[i-1].weight;
				if (k <= j){
					int a,b;
					Edge it = list[i - 1];

					a = it.profit + mat[i - 1][j - it.weight].value;
					b = mat[i - 1][j].value;

					mat[i][j].value = max(a, b);
				}
				else{
					mat[i][j].value = mat[i-1][j].value;
				}
			}
		}

		for (int j = 0; j <= W; j++){
			if(mat[i][j].value != 0){
			cout<<mat[i][j].value <<setw(3);
			enfile<<mat[i][j].value <<setw(3);
		}
		}
		enfile<<endl;
		cout <<endl;
	}

	int j = W;
	int i = num;
	int w, total_weight = 0;

	knapsack thali;
	thali.num_item = 0;
	thali.total_weight = 0;
	thali.total_profit = 0;

	// This is for finding the items used.
	while (i > 0){
		Edge it = list[i - 1];
		w = it.weight;

		int x,y;

		x=mat[i][j].value - mat[i - 1][j - w].value;
		y=it.profit;

		if (x == y){
			thali.items[thali.num_item] = it;
			thali.num_item++;
			total_weight += w;

			i--;
			j = j - w;
		}
		else{
			i--;
		}
	}

	//Creating the Output File
	ofstream outfile ("output2.txt");

	outfile << thali.num_item <<"\t"<<mat[num][W].value<<"\t"<<total_weight<<endl;

	cout << "\nTotal Weight: " << total_weight <<endl;
	cout << "Total Profit: " << mat[num][W].value <<endl<<endl;

	for (i = 0; i < thali.num_item; i++){
		Edge it = thali.items[i];
		cout<<"row"<<it.id<<": P-"<<it.profit<<" W-"<<it.weight<<endl;
		outfile<<"row"<<it.id<<"\t"<<it.profit<<"\t"<< it.weight <<endl;
	}
	cout <<endl;
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

  // sort edges by increasing weight
  //sort(vec.begin(), vec.end());

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

  dynamic(item_list, W, num);

  return 0;
}
