#include <cstdio>
#include <vector>
#include <cstring>
#define max(a, b) a>b?a:b
using namespace std;

void dfs(int node, int* depth, vector<int>* graph, int dpt, bool* visited, int** parents){
	depth[node] = dpt;
	visited[node] = true;
	int gsize = graph[node].size();
	
	int imax = 0;
	while(dpt - (1<<imax) >= 1){
		imax++;
	}
	
	for(int i = 1; i < imax; i++){
		parents[node][i] = parents[parents[node][i-1]][i-1];
	}
	
	for(int i = 0; i < gsize; i++){
		int nxt = graph[node][i];
		if(!visited[nxt]){
			parents[nxt][0] = node;
			dfs(nxt, depth, graph, dpt+1, visited, parents);	
		}
	}
}

int LCA(int a, int b, int** parents, int* depth){
	// guarantee b is deeper
	if(depth[a] > depth[b]){
		int tmp; tmp = a;
		a = b; b = tmp;
	}
	
	// to be the same depth
	int d = depth[a];
	while(d != depth[b]){
		int i = 1;
		int dpt = depth[b];
		while(1){
			if(dpt - (1 << i) < d){
				break;
			}
			i++;
		}
		b = parents[b][i-1];
	}
	
	// search
	while(a!=b){
		int i = 1;
		while(parents[a][i]){
			if(parents[a][i] == parents[b][i]) break;
			i++;
		}
		
		a = parents[a][i-1];
		b = parents[b][i-1];
		d = depth[a];
	}
	return a;
}

int main(void){
	int N; scanf("%d", &N);
	vector<int> *graph = new vector<int>[N+1];
	int** parents = new int*[N+1];
	bool* visited = new bool[N+1]; memset(visited, 0, sizeof(bool)*(N+1));
	int* depth = new int[N+1]; memset(depth, 0, sizeof(int)*(N+1));
	
	for(int i = 1; i <= N; i++){
		parents[i] = new int[20];
		memset(parents[i], 0, sizeof(int)*20);
	}
	
	// input
	for(int i = 0; i < N-1; i++){
		int a, b; scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	// root
	int root = 1;
	
	// check depth
	dfs(root, depth, graph, 1, visited, parents);
	
	// LCA
	int M; scanf("%d", &M);
	while(M--){
		int a, b; scanf("%d %d", &a, &b);
		printf("%d\n", LCA(a, b, parents, depth));	
	}
	delete[] graph;
}
