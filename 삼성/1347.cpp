#include<iostream>

using namespace std;

int customer_count, pos[12][2], ans;
bool default_visited[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int abs(int a){
	return a > 0 ? a : -a;
}

int get_distance(int a, int b){
	return abs(pos[a][0] - pos[b][0]) + abs(pos[a][1] - pos[b][1]);
}

void get_answer(int position, int visited_count, int sum, bool* visited){
	// cout << position << ' ' << visited_count << ' ' << sum << "\t" << ans << '\t' << endl;
	if(visited_count == customer_count + 1){
		
		int new_sum = sum + get_distance(position, 0);
		ans = ans ? (new_sum < ans ? new_sum : ans) : new_sum;
		return;
	}

	for(int i=1; i<customer_count+2; i++){
		if(visited[i] == 0){
			bool new_visited[10];

			for(int j=0; j<customer_count+2; j++){
				new_visited[j] = visited[j];
			}
			new_visited[i] = 1;

			int new_sum = sum + get_distance(position, i);

			if(ans && new_sum > ans){
				continue;
			}
			get_answer(i, visited_count+1, new_sum, new_visited);
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
		cin >> customer_count;
		for(int i = 0; i < customer_count + 2; i++){
			cin >> pos[i][0] >> pos[i][1];
		}

		ans=0;
		get_answer(1, 1, 0, default_visited);

		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;
}