#include<iostream>
#include<algorithm>

using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17};

double get_probability(double x, int n, int success, double p){
	if(n == 0){
		if(find(primes, primes + 7, success) != primes + 7)
			return p;
		else
			return 0;
	}

	double success_p = get_probability(x, n - 1, success + 1, p * x);
	double fail_p = get_probability(x, n - 1, success, p * (1-x));

	return success_p + fail_p;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;
	cout << fixed;
	cout.precision(6);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		double a, b, ans = 0;
		cin >> a >> b;

		a /= 100;
		b /= 100;
		
		
		double pa = get_probability(a, 18, 0, 1);
		double pb = get_probability(b, 18, 0, 1);

		ans += pa + pb - pa * pb;

		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;
}