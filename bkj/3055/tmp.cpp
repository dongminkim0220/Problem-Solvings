#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

struct coord{
	int row;
	int col;
	int t;
};

int main(void){
	int R, C;
	scanf("%d %d", &R, &C);

	// map
	char** map = new char*[R];
	queue<coord> q;
	coord start;
	for(int r = 0; r < R; r++){
		string s;
		cin >> s;
		map[r] = new char[C];
		for(int c = 0; c < C; c++){
			char data = s[c];
			if(data == 'S'){
				start = {r, c, 0};
			} 
			map[r][c] = s[c];
		}
	}
	
	// queue init
	q.push(start);
	for(int r = 0; r < R; r++){
		for(int c = 0; c < C; c++){
			if(map[r][c] == '*'){
				q.push({r, c, -1});
			} 
		}
	}
	
	// stick           W   N  E   S  
	int rowstick[4] = {0, 1, 0, -1};
	int colstick[4] = {-1, 0, 1, 0};
	
	int answer = 0;
	while(!q.empty()){	
		for(int r = 0; r < R; r++){
			for(int c = 0; c < C; c++){
				printf("%c", map[r][c]);	
			}
			printf("\n");
		}
		printf("\n");
		coord pos = q.front(); q.pop();
		char pos_info = map[pos.row][pos.col];
		
		if(pos_info == 'D'){
			answer = pos.t;
			break;
		}
		// water
		if(pos.t == -1){
			for(int i = 0; i < 4; i++){
				int nr = pos.row + rowstick[i];
				int nc = pos.col + colstick[i];
				bool out_of_bound = nr < 0 || nr >= R || nc < 0 || nc >= C;
				if(out_of_bound) continue;
				else {
					char new_pos_info = map[nr][nc];
					if(new_pos_info == 'X' || new_pos_info == 'D' || new_pos_info == '*'){
						continue;
					} else {
						map[nr][nc] = '*';
						q.push({nr, nc, -1});
					}
				}
			} 
		}
		// path find
		else{
			if(pos_info == '*') {
				continue;	
			}
			map[pos.row][pos.col] = 'S';
			for(int i = 0; i < 4; i++){
				int nr = pos.row + rowstick[i];
				int nc = pos.col + colstick[i];
				bool out_of_bound = nr < 0 || nr >= R || nc < 0 || nc >= C;
				if(out_of_bound) continue;
				else {
					char new_pos_info = map[nr][nc];
					if(new_pos_info == 'X' || new_pos_info == '*' || new_pos_info == 'S'){
						continue;
					} else {
						q.push({nr, nc, pos.t + 1});
					}
				}
			}
		}
	}
	
	if(!answer){
		printf("KAKTUS\n");
	} else {
		printf("%d", answer);
	}
	
	delete[] map;
}
