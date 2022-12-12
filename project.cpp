#include <stdio.h> 
#include <limits.h> 
#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std; 

class BTreeNode 
{ 
	private:
		int *keys; // An array of keys 
		BTreeNode **childPointerArr;  
		int n;	 
		bool leaf; 
	public: 
		BTreeNode(bool _leaf)
		{
			leaf = _leaf; 

			// Allocate memory 
			keys = new int[5]; 
			childPointerArr = new BTreeNode *[6]; 

			n = 0; 
		};

		void insertNonFull(int k); 

		// i is the index of y in child array childpinterArr[].
		void split(int i, BTreeNode *y); 

		BTreeNode *search(int k);
		
		~BTreeNode();

// so that we can access private members of this class in BTree and dijkstraMain functions
friend class BTree;
friend class dijkstraMain; 
}; 

class BTree 
{ 
	private:
		BTreeNode *root;
	public: 
		BTree() 
		{ root = NULL; } 

		BTreeNode* search(int k) 
		{  return (root == NULL)? NULL : root->search(k); } 

		void insert(int k); 
		
friend class dijkstraMain;
};

class dijkstraMain
{
	private:
		int** maze;
		//we give each vertex an ID and ids is the array that contains them
		int** ids;
		int m,n,V;
		int count=0;
		int startX,startY,endX,endY;
		//we store the path here but in the inverse way
		vector<int> path;
	public:
		dijkstraMain();

        //finding the vertex with minimum distance
		int minDistance(int dist[] , BTree t) ;

        //a functon to find the path 
		void printPath(int parent[], int j) ;

        //dijkstra function 
		void dijkstra(int** graph, int srcX , int srcY, BTree t) ;

        //a function to print the output
		void makeOutput();
};

dijkstraMain ::dijkstraMain()
{
	cin>>m>>n;
	maze = new int*[m];
	ids = new int*[m];
	for(int i=0 ; i<m ; i++){
		maze[i] = new int[n];
		ids[i] = new int[n];
	}
	for(int i=0 ; i<m ; i++){
		for(int j=0 ; j<n ; j++){
			cin>>maze[i][j];
			ids[i][j]=count;
			count++;
			if(i==0 && maze[i][j]!=0){
				startX = i;
				startY = j;
			}
			if(i==m-1 && maze[i][j]!=0){
				endX = i;
				endY = j;
			}
		}
	}
	BTree t;
	V = m*n;
	dijkstra(maze , startX , startY, t);
	makeOutput();
}

int dijkstraMain :: minDistance(int dist[], BTree t) 
{ 
	
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (!t.search(v) && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

void dijkstraMain :: printPath(int parent[], int j) 
{ 
	if (parent[j] == - 1) 
		return; 

	path.push_back(j);
	
	printPath(parent, parent[j]); 

} 

void dijkstraMain :: dijkstra(int** maze, int srcX , int srcY, BTree t) 
{ 
	int u;
	int uX;
	int uY;
	//dist[i] shortest distance from src to i 
	int dist[V]; 


	// Parent array
	int parent[V]; 

	// Initialize all distances as infinite
	for (int i = 0; i < V; i++) 
	{ 
		parent[ids [srcX][srcY]] = -1; 
		dist[i] = INT_MAX; 
	} 

	dist[ ids[srcX][srcY] ] = 0; 
	
	while (!t.search(ids[endX][endY]))
	{ 
		// Pick the minimum distance 
		u = minDistance(dist, t);

		t.insert(u); 

		if(u%n != 0){
			uY = (u % n) ;
			uX = ((u - uY) / n);
		}

		if(u%n == 0){
			uY = 0;
			uX = u/n;
		}

		if(uX>0 && !t.search(ids[uX-1][uY]) && maze[uX-1][uY] && dist[u]+maze[uX-1][uY] < dist[ ids[uX-1][uY] ]){
			parent[ ids[uX-1][uY] ] = u;
			dist[ids[uX-1][uY] ] = dist[u]+maze[uX-1][uY];
		}

		if(uY>0 && !t.search(ids[uX][uY-1]) && maze[uX][uY-1] && dist[u]+maze[uX][uY-1] < dist[ ids[uX][uY-1] ]){
			parent[ ids[uX][uY-1] ] = u;
			dist[ ids[uX][uY-1] ] = dist[u]+maze[uX][uY-1];
		}

		if(uX < m-1 && !t.search(ids[uX+1][uY]) && maze[uX+1][uY] && dist[u]+maze[uX+1][uY] < dist[ ids[uX+1][uY] ]){
			parent[ ids[uX+1][uY] ] = u;
			dist[ ids[uX+1][uY] ] = dist[u]+maze[uX+1][uY];
		}

		if(uY < n-1 && !t.search(ids[uX][uY+1]) && maze[uX][uY+1] && dist[u]+maze[uX][uY+1] < dist[ ids[uX][uY+1] ]){
			parent[ ids[uX][uY+1] ] = u;
			dist[ ids[uX][uY+1] ] = dist[u]+maze[uX][uY+1];
		}

	} 
	printPath(parent , u);

	path.push_back( parent[path[path.size()-1]] );
} 

void dijkstraMain :: makeOutput()
{
	int u, uX, uY;
	for(int i=0 ; i<path.size() ; i++){
		u = path[i];
		if(u%n != 0){
			uY = (u % n) ;
			uX = ((u - uY) / n);
		}
		if(u%n == 0){
			uY = 0;
			uX = u/n;
		}	
		maze[uX][uY] = -1 ;

	}
	for(int i = 0 ; i< m ; i++){
		for(int j=0 ; j<n ; j++){
			cout<<maze[i][j]<<" ";
		}
		cout<<endl;
	}
} 

BTreeNode *BTreeNode::search(int k) 
{ 
    // Find the first key greater than or equal to k 
    int i = 0; 
    while (i < n && k > keys[i]) 
        i++; 
   
    if (keys[i] == k) 
        return this; 
  
    if (leaf == true) 
        return NULL; 
   
    return childPointerArr[i]->search(k); 
} 

void BTree::insert(int k) 
{ 
	if (root == NULL) 
	{  
		root = new BTreeNode(true); 
		root->keys[0] = k; 
		root->n = 1; 
	} 
	else // If tree is not empty 
	{ 
		if (root->n == 5) 
		{ 
			BTreeNode *s = new BTreeNode( false); 

			s->childPointerArr[0] = root; 

			s->split(0, root); 

			int i = 0; 
			if (s->keys[0] < k) 
				i++; 
			s->childPointerArr[i]->insertNonFull(k); 

			root = s; 
		} 
		else
			root->insertNonFull(k); 
	} 
} 

void BTreeNode::insertNonFull(int k) 
{ 
	int i = n-1; 

	if (leaf == true) 
	{ 
		while (i >= 0 && keys[i] > k) 
		{ 
			keys[i+1] = keys[i]; 
			i--; 
		} 

		keys[i+1] = k; 
		n = n+1; 
	} 
	else 
	{ 
		while (i >= 0 && keys[i] > k) 
			i--; 

		if (childPointerArr[i+1]->n == 5) 
		{ 
			split(i+1, childPointerArr[i+1]); 

			if (keys[i+1] < k) 
				i++; 
		} 
		childPointerArr[i+1]->insertNonFull(k); 
	} 
} 

void BTreeNode::split(int i, BTreeNode *y) 
{ 
	BTreeNode *z = new BTreeNode(y->leaf); 
	z->n = 2; 

	for (int j = 0; j < 2; j++) 
		z->keys[j] = y->keys[j+3]; 

	if (y->leaf == false) 
	{ 
		for (int j = 0; j < 3; j++) 
			z->childPointerArr[j] = y->childPointerArr[j+3]; 
	} 
 
	y->n = 2; 

	for (int j = n; j >= i+1; j--) 
		childPointerArr[j+1] = childPointerArr[j]; 

	childPointerArr[i+1] = z; 

	for (int j = n-1; j >= i; j--) 
		keys[j+1] = keys[j]; 

	keys[i] = y->keys[2]; 

	n = n + 1; 
} 

int main() 
{ 
	dijkstraMain inp;

	return 0; 
} 
BTreeNode ::~BTreeNode(){
	delete[] keys;
	delete[] childPointerArr;
}