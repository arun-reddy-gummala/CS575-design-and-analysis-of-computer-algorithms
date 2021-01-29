#include <iostream>
#include <vector> // for 2D vector
#include <bits/stdc++.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define Pair pair<int, int>

int num;
vector<vector<int> > vec(num);

//for kruskals
unordered_map<int, int> parent;
unordered_map<int, int> height;

//for prims
unordered_map<int, int> key;

//Print function for the D- Matrix
void printBoard(vector<vector<int>> vec){
  for (int i = 0; i < num; i++) {
      for (int j = 0; j < num; j++)
          cout << vec[i][j] << "\t";
      cout << endl;
  }
}

//Creating the graph
vector<vector<int> > createGraph(vector<vector<int> > v,int num){
  int x=0;
  x = num;
  vector<vector<int> > d( num , vector<int> (x  , 0));
  for( int i = 0; i < x;i++){
   	 	for( int j = 0; j < x; j++){
      if(i==j){
         d[i][j] = 0; //Assigning the weight to each edge
      }
      else{
        int w = (rand() % (10)) + 1;
        d[i][j] = w; //Assigning the weight to each edge
        d[j][i] = d[i][j];
      }
	}
}
 return d;
}

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
  friend bool operator<(Edge a, Edge b){
        return a.weight > b.weight;
    }
};

//find function used in kruskals
int find3(int x){
  int node, p, root = 0;
  root = x;
  while(root != parent[root]){
    root = parent[root];
  }
  node = x;
  while(node!= root){
    p = parent[node];
    parent[node] = root;
    node = p;
}
return root;
}

//union function used in kruskals
void union3(int repx, int repy){
  if(height[repx] == height[repy]){
    height[repx]++;
    parent[repy] = repx;
  }
  else if(height[repx] > height[repy]){
    parent[repy] = repx;
  }
  else{
    parent[repx] = repy;
  }
}

// construct MST using Kruskal's algorithm
vector<Edge> Kruskal(vector<Edge> edges, int num){
	// stores edges present in MST
	vector<Edge> MST;

	for (int i = 0; i < num; i++)
		parent[i] = i;

  for (int j = 0; j < num; j++)
    height[j] = j;

	// MST contains exactly V-1 edges
	while (MST.size() != num - 1){
		Edge next = edges.back();
		edges.pop_back();

		int x = find3(next.src);
		int y = find3(next.dest);

		if (x != y){
			MST.push_back(next);
			union3(x, y);
		}
	}
	return MST;
}

//prims algorithm
vector<Edge> prims(vector<Edge> edges, int num, vector<vector<int> > vec){

  int x,y,z,src;
  src = 0;

  vector<Edge> MST;
  priority_queue< Pair, vector <Pair> , greater<Pair> > pq;

  vector <Pair > adj[num];

  vector<Edge> e = edges;

  for (Edge &edge: e){
    x = edge.src;
    y = edge.dest;
    z = edge.weight;
    adj[x].push_back(make_pair(y, z));
    adj[y].push_back(make_pair(y, z));
  }

  unordered_map<int, bool> inMST;

  for (int i = 0; i < num; i++)
    inMST[i] = false;

  for (int j = 0; j < num; j++)
    key[j] = 999;

  for (int k = 0; k < num; k++)
    parent[k] = -1;

  pq.push(make_pair(0, src));
  key[src] = 0;

  while(!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    inMST[u] = true;

        for (auto k : adj[u]){
            int v = k.first;
            int weight = k.second;

            if (inMST[v] == false && key[v] > weight){
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
  }

  for (int i = 1; i < num; ++i)
        cout<<"V"<<parent[i]<<" - "<<"V"<<i<<": "<<vec[i][parent[i]]<<endl;

  return MST;
}

int main()
{
  int i,j;
  string str;
  //Using current time as a seed for random generator
  srand(time(0));
  //Generating a random number to take in as 'n' vertices
  num = (rand() % (6)) + 5;

  cout<<"Selected n value = "<<num<<endl;
  cout<<endl;

  vector<vector<int> > vec( num , vector<int> (num, 0));

  //Creting the afjancency matrix
  vec = createGraph(vec,num);

  cout<<"Random Matrix: "<<endl;
  printBoard(vec); //printing the matrix

  cout<<"Enter the type of Algorithm (prims/kruskals): ";
  cin>>str;

  if(str == "kruskals"){

    vector<Edge> edges;

    for( i = 0; i < num;i++){
     	 	for( j = 0; j < num; j++){
            Edge myedge = {i, j, vec[i][j]};
            edges.push_back(myedge);
        }
    }

    // sort edges by increasing weight
  	sort(edges.begin(), edges.end());

    vector<Edge> e = Kruskal(edges, num);

    cout<<"Edges in MST using Kruskals: "<<endl;

    //printing the edges
  	for (Edge &edge: e)
      cout<<"V"<<edge.src<<" - V"<<edge.dest<<": "<<edge.weight<<endl;
  }

  else if(str == "prims"){
    vector<Edge> edges;

    for( i = 0; i < num;i++){
     	 	for( j = 0; j < num; j++){
            Edge myedge = {i, j, vec[i][j]};
            edges.push_back(myedge);
        }
    }

    // sort edges by increasing weight
  	sort(edges.begin(), edges.end());

    cout<<"Edges in MST using Prims: "<<endl;

    prims(edges, num, vec);
  }
  else{
    cout<<"The given algorithm is not present in this program."<<endl;
  }

  return 0;
}
