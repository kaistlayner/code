#include<iostream>
#include<cmath>

using namespace std;

double ALLOW = 1.0e-12;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		int n, i;
		cin >> n;

		double x[10], w[10];
		for(i=0; i<n; i++){
			cin >> x[i];
		}
		for(i=0; i<n; i++){
			cin >> w[i];
		}

		cout << fixed;
		cout.precision(10);
		cout << "#" << test_case;

		for(int i=0; i<n-1; i++){
			double l = x[i], r = x[i+1];

			while(1){
				double sum = 0, last_sum = 0;
				double point = (l + r) / 2;

				for(int j=0; j<n; j++){
					double force =  w[j] / pow(point - x[j], 2);
					if(x[j] < point){
						sum -= force;
					}else{
						sum += force;
					}
				}

				if(last_sum && pow(last_sum, 2) < pow(sum, 2)){
					break;
				}

				// cout << ' ' << i << ' ' << l << ' ' << point << ' '<< r <<  ' ' << sum << endl;
	
				if(sum == 0 || r - l < ALLOW){
					cout << " " << point;
					break;
				}
				else if(sum > 0){
					r = point;
				}
				else{
					l = point;
				}

				last_sum = sum;
			}
		}

		cout << endl;
	}
	return 0;
}