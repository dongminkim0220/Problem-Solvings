#include <cstdio>
#include <cstring>
#include <iostream>
#define INF (1<<31)-1 

using namespace std;
int TSP(int** graph, int** dp, int N, int cur, int start, int visited){
	printf("cur %d visited %x \n", cur, visited);
	// check dp
	if(dp[cur][visited]){
		printf("DP: cur %d visited %x  => returns %d \n\n", cur, visited,  dp[cur][visited]);
		return dp[cur][visited];
	}
	
	// check in
	visited |= (1 << (cur-1));
	
	// destination?
	if(visited == (1<<N)-1){
		//dp[cur][visited] = graph[cur][start]? cost + graph[cur][start]: INF;
		dp[cur][visited] = graph[cur][start]? graph[cur][start]: INF;
		printf("visited all: cur %d visited %x => return cost : %d\n ", cur, visited, dp[cur][visited]);
		return dp[cur][visited];
	}
	
	// iterate
	int min_cost = INF;
	for(int nxt = 1; nxt <= N; nxt++){
		if(visited & (1<<(nxt-1))) continue;
		
		int cost_to_nxt = graph[cur][nxt];
		// can we go?
		if(cost_to_nxt){
			int tsp = TSP(graph, dp, N, nxt, start, visited);
			printf("loop: cur %d nxt %d tsp: %d\n", cur, nxt, tsp);
			//min_cost = min(min_cost, TSP(graph, dp, N, nxt, start, visited, cost + cost_to_nxt));
			int result = (tsp==INF)? INF: tsp + cost_to_nxt;
			min_cost = min(min_cost, result);
		}
	}
	
	// check out
	visited &= ~(1 << (cur-1));
	
	// answer
	
	printf("func finished: cur %d visited %x min_cost %d\n\n", cur, visited, min_cost);
	//dp[cur][visited] = (min_cost == INF)? INF: min_cost+cost;
	return dp[cur][visited] = min_cost;
}

int main(void){
	int N;
	scanf("%d", &N);
	int** graph = new int*[N+1];
	int** dp = new int*[N+1];
 	int visited= 0;
	for(int r = 1; r <= N; r++){
		graph[r] = new int[N+1];
		dp[r] = new int[(1<<N)-1];
		memset(dp[r], 0, sizeof(int) * (1<<N)-1);
		for(int c = 1; c <= N; c++){
			scanf("%d", &graph[r][c]);
		}
	}
	
	printf("%d", TSP(graph, dp, N, 1, 1, visited));
}
