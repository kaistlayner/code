#include<iostream>
#include<algorithm>

using namespace std;

struct point{
	int x, y;
};

int input_map[100][100], map_size, reach_time[100][100], ans, sort_value;
struct point default_point = {0, 0};

void reset_array(){
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

int distance(struct point p){
	return p.x + p.y;
}

bool is_near(struct point p){
	return distance(p) == (2 * (map_size - 1) - 1);
}

int min(int a, int b){
	if(a == -1) return b;
	if(b == -1) return a;
	return a < b ? a : b;
}

bool cmp(struct point a, struct point b){
	int v1 = min(reach_time[a.x][a.y], sort_value + input_map[a.x][a.y]);
	int v2 = min(reach_time[b.x][b.y], sort_value + input_map[b.x][b.y]);

	if(v1 == v2){
		return distance(a) > distance(b);
	}
	if(v1 == -1) return false;
	if(v2 == -1) return true;

	return v1 < v2;
}

void get_sample_answer(){
	ans = 0;

	for(int i=0; i<map_size; i++){
		ans += input_map[i][0];
		ans += input_map[map_size - 1][i];
	}

	ans -= input_map[map_size - 1][0];
}

void print_map(struct point p)
{
	int x= p.x, y = p.y;
	cout << x << ' ' << y << endl;

	for(int i=0; i<map_size; i++){
		for(int j=0; j<map_size; j++){
			if(i==x && j==y) cout << '*' << reach_time[i][j] << '*' << '\t';
			else cout << reach_time[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void fill_map(struct point p, int before_value, bool is_end = false){
	int x = p.x, y = p.y;
	int history = reach_time[x][y];
	int update = before_value + input_map[x][y];

	if(update >= ans && ans != -1){
		return;
	}

	if((history < 0) || (update < history)){
		reach_time[x][y] = update;

		// print_map(p);

		if(is_end){
			// cout << update << endl;
			ans = update;
			return;
		}

		struct point arrays[4];
		int path_count = 0;

		if(!is_near(p)){
			path_count += insert_path(arrays, x, y-1, path_count);
			path_count += insert_path(arrays, x, y+1, path_count);
			path_count += insert_path(arrays, x-1, y, path_count);
			path_count += insert_path(arrays, x+1, y, path_count);

			sort_value = update;
			sort(arrays, arrays + path_count, cmp);

			for(int i=0; i<path_count; i++){
				fill_map(arrays[i], update);
			}
		}
		else{
			struct point end_point = {map_size - 1, map_size - 1};
			fill_map(end_point, update, true);
		}
		
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &map_size);
		reset_array();

		for(int i=0; i<map_size; i++){
			for(int j=0; j<map_size; j++){
				scanf("%1d", &input_map[i][j]);
			}
		}

		get_sample_answer();

		fill_map(default_point, 0);

		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;
}