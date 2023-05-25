#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

struct elem{
	int x;
	int y;
	long long int distance;

	bool operator<(const elem a) const{
		return distance > a.distance;
	}
};
priority_queue<elem> costs;

struct point {
	int x;
	int y;
};
int vertex, roots[1000], connected;
struct point p[1000];
long long int ans;
double tax;

void get_cost(){
	for(int i=0; i<vertex; i++){
		roots[i] = i;

		for(int j=i+1; j<vertex; j++){
			long long int l, r;
			l = p[i].x - p[j].x;
			r = p[i].y - p[j].y;
			long long int tmp_cost = l*l + r*r;

			elem tmp = {i ,j, tmp_cost};
			costs.push(tmp);
		}
	}
}

void get_answer(){
	while(connected < vertex-1){
		elem tmp = costs.top();
		costs.pop();
		int x = tmp.x, y = tmp.y;

		if(roots[x] != roots[y]){
			ans += tmp.distance;
			connected++;
			int target = roots[y];

			for(int i=0; i<vertex; i++){
				if(roots[i] == target){
					roots[i] = roots[x];
				}
			}
		}
	}

	while(!costs.empty()){
		costs.pop();
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
		ans = 0;
		connected = 0;

		cin >> vertex;
		for(int i=0; i<vertex; i++){
			cin >> p[i].x;
		}
		for(int i=0; i<vertex; i++){
			cin >> p[i].y;
		}

		get_cost();
		get_answer();

		cin >> tax;
		cout << "#" << test_case << " " << (long long int)floor(tax*ans + 0.5) << endl;
	}
	return 0;
}