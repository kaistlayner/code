#include<iostream>

using namespace std;

int len, LCS[501][501];
string a, b;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;
	cout << fixed;
	cout.precision(2);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> len;
		cin >> a >> b;

		for(int i = 1; i <= len; i++){
			for (int j = 1; j <= len; j++){
				if (a[i - 1] == b[j - 1]){
					LCS[i][j] = LCS[i - 1][j - 1] + 1;
				}
				else{
					LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
				}
			}
		}

		cout << "#" << test_case << " " << ((double)LCS[len][len] / len) * 100 << endl;
		for (int i = 0; i <= len; i++){
			for (int j = 0; j <= len; j++){
				LCS[i][j] = 0;
			}
		}
	}
	return 0;
}