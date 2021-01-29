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

// Data structure to store node values
struct Edge {
	int id, profit, weight;

  friend bool operator<(Edge a, Edge b){
        double r1 = (double)a.profit / a.weight;
        double r2 = (double)b.profit / b.weight;
        return r1 > r2;
    }
};

//To define the direction
struct node{
    int profit, weight, level;
};

// Fractional knapsack problem is used to define bound per node.
int kwf2 (int depth, int v_profit, int v_weight, Edge list[], int W, int num);

// Calls kwf2 to decide if a node is promissing or not
bool promising (int level, int p, int w, Edge list[], int W, int num);

// Backtrack algorithm
void backtrack(Edge * list, int W, int num){

	//Queue to save the nodes
	vector <node> Q;

	//to store the number each nodes is visited
	vector <int> item_id;

	max_profit = 0;
	node u, v;

	u.level = -1;
	u.profit = u.weight = 0;

	Q.push_back(u);

  int bound, count = 0, weight = 0;

	//Creating the Output File
	ofstream enfile ("entries3.txt");

	cout<<"Nodes that are visited first: "<<endl;

	enfile << 0 << ": P-" << 0 << " W-" << 0 << " B-" << 0 <<endl;

	// Until we traverse all promissing nodes
	while (!Q.empty())
	{
		// Pop from front
		u = Q.front();
		Q.erase(Q.begin());

		//for the starting node
		if (u.level == -1){
			v.level = 0;
		}

		// if no nodes at next level
		if (u.level == num - 1){
			continue;
		}

		//increment level
		v.level = u.level + 1;

		v.weight = u.weight + list[v.level].weight;
		v.profit = u.profit + list[v.level].profit;

		// If we are under capacity and profit is more than the max profit update max profit
		if (v.weight <= W && v.profit > max_profit){

			// Calculating bond per node
			bound = kwf2(v.level, v.profit, v.weight, list, W, num);
			cout << "Node " << count << ": P-" << v.profit << " W-" << v.weight << " B-" << bound <<endl;

			enfile << count + 1 << ": P-" << v.profit << " W-" << v.weight << " B-" << bound <<endl;
			count++;

			// for the insertion of selected nodes
			item_id.push_back(list[v.level].id);
			max_profit = v.profit;
			weight = v.weight;
		}

		// If promissing take it for the consideration
		if (promising(v.level, v.profit, v.weight, list, W, num)){
				Q.push_back(v);
		}

		// If other node at the same level is also promising take it as consideration too
		v.weight = u.weight;
		v.profit = u.profit;
		if (promising(v.level, v.profit, v.weight, list, W, num)){
				Q.push_back(v);
		}
	}

	cout << "\nTotal Weight: " << weight <<endl;
	cout << "Total Profit: " << max_profit <<endl<<endl;
	cout << "Items in cosideration: " <<endl;

	for (int i = 0; i < num; i++){
		Edge it = list[i];

		for (int j = 0; j < item_id.size(); j++){
			if (it.id == item_id[j]) {
				cout << "Item" << it.id << ": P-" << it.profit << "  W-" << it.weight <<endl;
			}
		}
	}

	//Creating the Output File
	ofstream outfile ("output3.txt");

	outfile << item_id.size() <<"\t"<<max_profit<<"\t"<<weight<<endl;

		for(int i = 0; i < num; i++){
			Edge it = list[i];

			for (int j = 0; j < item_id.size(); j++)
				if (it.id == item_id[j]){
					outfile << "Item" << it.id << "\t" << it.profit << "\t" << it.weight <<endl;
				}
			}
	cout << "\n";
}

// Knapsack with fraction problem returns the upper bound for backtracing
int kwf2(int i, int v_profit, int v_weight, Edge list[], int W, int num){

	// If capacity is exceeded, just returns
	if (v_weight >= W) return 0;

	int bound = v_profit;

	// Until capacity is exceeded take items and increment the bound with their profit
  while (i < num && (v_weight + list[i].weight <= W)){
		v_weight += list[i].weight;
		bound += list[i].profit;
		i++;
	}

    if(i < num){
			int x,y,k;
			k = W - v_weight;
			x = list[i].profit;
			y = list[i].weight;
      bound += (k) * x / y;
    }
	return bound;
}

// Used for deceding if a node should be considered for benefit
bool promising(int level, int p, int w, Edge list[], int W, int num){

	if (w > W){
		return false;
	}

	// Bound is retrived
	int bound = kwf2(level, p, w, list, W, num);

	// If bound is more than max profit return true otherwise return false
	if (bound > max_profit){
		return true;
	}
	else{
		return false;
	}
}

int main(int argc, char *argv[]){

  int i=0;
	int p,w,W;

  string str, name;

	//Reading the knapsack file data
  ifstream knapsack01(argv[2]);

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
  sort(vec.begin(), vec.end());

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

  backtrack(item_list, W, num);

  return 0;
}
