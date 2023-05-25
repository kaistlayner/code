#include<iostream>

using namespace std;

int vertex, edge, point1, point2;
int roots[10001], edges[10001][2], info[10001][2]; // info[0] = depth, info[1] = size

int get_vertex_info(int current_vertex = 1, int cur_depth = 1){
	int left = edges[current_vertex][0], right = edges[current_vertex][1], cur_size = 1;
	
	if(left){
		cur_size += get_vertex_info(left, cur_depth+1);
	}
	if(right){
		cur_size += get_vertex_info(right, cur_depth+1);
	}

	info[current_vertex][0] = cur_depth;
	info[current_vertex][1] = cur_size;

	return cur_size;
}

int get_root(int point1, int point2){
	int depth1 = info[point1][0], depth2 = info[point2][0];

	while(point1 != point2){
		if(depth1 > depth2){
			point1 = roots[point1];
			depth1--;
		}
		else if(depth1 < depth2){
			point2 = roots[point2];
			depth2--;
		}
		else if(depth1 == depth2){
			point1 = roots[point1];
			point2 = roots[point2];
			depth1--;
			depth2--;
		}
	}

	return point1;
}

void clear_array(){
	for(int i=0; i<vertex; i++){
		roots[i] = 0;
		edges[i][0] = 0;
		edges[i][1] = 0;
		info[i][0] = 0;
		info[i][1] = 0;
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
		cin >> vertex >> edge >> point1 >> point2;

		int parent, child;
		for(int i=0; i<edge; i++){
			cin >> parent >> child;
			if(edges[parent][0]){
				edges[parent][1] = child;
			}
			else{
				edges[parent][0] = child;
			}
			roots[child] = parent;
		}

		get_vertex_info();
		int root = get_root(point1, point2);

		cout << '#' << test_case << ' ' << root << ' ' << info[root][1] << endl;
		
		clear_array();
	}
	return 0;
}