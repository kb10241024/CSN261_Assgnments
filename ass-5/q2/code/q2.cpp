// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph

// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
#include <bits/stdc++.h>
using namespace std;
ofstream outdata;

// Creating shortcut for an integer pair
typedef pair<int, int> iPair;

// Structure to represent a graph
struct Graph
{
	int V, E;
	vector<pair<int, iPair>> edges;

	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	// Utility function to add an edge
	void addEdge(int u, int v, int w)
	{
		edges.push_back({w, {u, v}});
	}

	// Function to find MST using Kruskal's
	// MST algorithm
	int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	// Constructor.
	DisjointSets(int n)
	{
		// Allocate memory
		this->n = n;
		parent = new int[n + 1];
		rnk = new int[n + 1];

		// Initially, all vertices are in
		// different sets and have rank 0.
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//every element is parent of itself
			parent[i] = i;
		}
	}

	// Find the parent of a node 'u'
	// Path Compression
	int find(int u)
	{
		/* Make the parent of the nodes in the path 
		from u--> parent[u] point to parent[u] */
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union by rank
	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		/* Make tree with smaller height 
		a subtree of the other tree */
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y]
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
	int mst_wt = 0; // Initialize result

	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	DisjointSets ds(V);

	// Iterate through all sorted edges
	vector<pair<int, iPair>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u != set_v)
		{
			// Current edge will be in the MST
			// so print it
			outdata << (char)(u + 65) << "--" << (char)(v + 65) << "[label=\"" << (it->first) << "\"];" << endl;
			cout<< (char)(u + 65) << "--" << (char)(v + 65) << "[label=\"" << (it->first) << "\"];" << endl;
			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

void readGraph(Graph *g, string path)
{
	// filestream variable file
	fstream file;
	string word, t, q, filename;

	// filename of the file
	// filename = "2019_CSN_261_L5_P2.csv";
	filename = path;

	// opening file
	file.open(filename.c_str());
	string temp;
	// extracting words from the file
	while (file >> word)
	{
		string line = word;

		// Vector of string to save tokens
		vector<string> tokens;

		// stringstream class check1 ~
		stringstream check1(line);

		string intermediate;

		// Tokenizing w.r.t. space ' '
		int i = 0, v1 = 0, v2 = 0, w = 0;
		while (getline(check1, intermediate, ','))
		{
			// cout<<intermediate<<endl;
			if (i == 0)
			{
				v1 = (int)(intermediate[0] - 'A');
			}
			else if (i == 1)
			{
				v2 = (int)(intermediate[0] - 'A');
			}
			else
			{
				int w = stoi(intermediate);
				// cout<<v1<<" "<<v2<<" "<<w<<endl;
				(*g).addEdge(v1, v2, w);
			}
			tokens.push_back(intermediate);
			i = (i + 1) % 3;
		}
	}
}

// Driver program to test above functions
int main()
{
	outdata.open("out.dot");
	if (!outdata)
	{
		cerr << "error" << endl;
		exit(1);
	}
	/* Let us create above shown weighted 
	and unidrected graph */
	int V = 9, E = 14;
	Graph g(V, E);

	string path = "L5_Testcases_for_P2_and_P3.csv";
	readGraph(&g, path);

	// cout << "Edges of MST are \n";
	outdata << "graph{" << endl;
	int mst_wt = g.kruskalMST();
	outdata << "}";
	// cout << "\nWeight of MST is " << mst_wt << endl;

	return 0;
}
