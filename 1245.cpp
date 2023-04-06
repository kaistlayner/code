#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		int n, i;
		cin >> n;

		int x[10], w[10];
		for(i=0; i<n; i++){
			cin >> x[i];
		}
		for(i=0; i<n; i++){
			cin >> w[i];
		}



		cout << "#" << test_case << " " << 1 << endl;
	}
	return 0;
}