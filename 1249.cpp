#include<iostream>
#include<algorithm>

using namespace std;

struct point{
	int x, y;
};

int input_map[100][100], map_size, reach_time[100][100];

void print_map(int a, int b){
	for(int i=0; i<map_size; i++){
		for(int j=0; j<map_size; j++){
			if(i==a && j==b) cout << '*' << reach_time[i][j] << '*' << '\t';
			else cout << reach_time[i][j] << '\t';
		}
		cout << endl;
	}
}

void reset_reach_time(){
	for(int i=0; i<map_size; i++){
		for(int j=0; j<map_size; j++){
			reach_time[i][j] = -1;
		}
	}
}

bool has_error(int x, int y){
	if(x < 0 || x >= map_size || y < 0 || y >= map_size) return true;
	return false;
}

bool insert_path(struct point arrays[4], int x, int y, int index){
	if(has_error(x, y)) return 0;

	int value = reach_time[x][y];
	arrays[index] = {x,y};
	return 1;
}

bool cmp(struct point a, struct point b){
	int v1 = reach_time[a.x][a.y];
	int v2 = reach_time[b.x][b.y];

	if(v1 == -1 && v2 == -1) return  input_map[a.x][a.y] < input_map[b.x][b.y];
	if(v1 == -1 && v2 != -1) return false;
	if(v2 == -1) return true;

	return v1 < v2;
}

void fill_map(int x, int y, int before_value){
	int history = reach_time[x][y];
	int update = before_value + input_map[x][y];

	if((history < 0) || (update < history)){
		reach_time[x][y] = update;
		

		struct point arrays[4];
		
		int path_count = 0;
		path_count += insert_path(arrays, x, y-1, path_count);
		path_count += insert_path(arrays, x, y+1, path_count);
		path_count += insert_path(arrays, x-1, y, path_count);
		path_count += insert_path(arrays, x+1, y, path_count);
		// sort(index, index + path_count, cmp);
		sort(arrays, arrays + path_count, cmp);

		for(int i=0; i<path_count; i++){
			// print_map(x, y);
 			fill_map(arrays[i].x, arrays[i].y, update);
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> map_size;
		reset_reach_time();

		for(int i=0; i<map_size; i++){
			getchar();
			for(int j=0; j<map_size; j++){
				input_map[i][j] = getchar() - '0';
			}
		}

		fill_map(0, 0, 0);

		cout << "#" << test_case << " " << reach_time[map_size-1][map_size-1] << endl;
	}
	return 0;
}