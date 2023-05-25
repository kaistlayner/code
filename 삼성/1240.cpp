#include<iostream>

using namespace std;


int get_start_point(char* raw_codes){
	for (int i = 99; i >= 0; i--){
		if(raw_codes[i] == '1'){
			return i - 56 + 1;
		}
	}

	return -1;
}

int decode_value(int value){
	//   168421
	// 0: 00110 => 6
	// 1: 01100 => 12
	// 2: 01001 => 9
	// 3: 11110 => 30
	// 4: 10001 => 17
	// 5: 11000 => 24
	// 6: 10111 => 23
	// 7: 11101 => 29
	// 8: 11011 => 27
	// 9: 00101 => 5

	int ans;
	switch (value)
	{
	case 6:
		ans = 0;
		break;
	case 12:
		ans = 1;
		break;
	case 9:
		ans = 2;
		break;
	case 30:
		ans = 3;
		break;
	case 17:
		ans = 4;
		break;
	case 24:
		ans = 5;
		break;
	case 23:
		ans = 6;
		break;
	case 29:
		ans = 7;
		break;
	case 27:
		ans = 8;
		break;
	case 5:
		ans = 9;
		break;
	default:
		ans = -1;
		break;
	}

	return ans;
}

int get_code(char* src){
	int sum = 0, digit = 1 << 4;

	for (int i = 1; i <= 5; i++){
		sum += (src[i] - '0') * digit;
		digit = digit >> 1;
	}

	return decode_value(sum);
}

int save_codes(char* src, int* dst){
	int start_point = 0;

	for (int i = 0; i < 8; i++){
		dst[i] = get_code(&src[7*i]);
	}
}

int decode_barcode(){
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; i++){
		char line[101];
		cin >> line;
		int start_point = get_start_point(line);

		if(start_point != -1){
			int codes[8];
			save_codes(&line[start_point], codes);
			// for(int code : codes)
			// 	cout << code << ' ';
			// cout << endl;

			int odd_sum = codes[0] + codes[2] + codes[4] + codes[6];
			int even_sum = codes[1] + codes[3] + codes[5] + codes[7];

			if(((odd_sum)*3 + even_sum) % 10 == 0){
				cin.ignore((N - i) * (M + 1));
				return odd_sum + even_sum;
			}
			else{
				cin.ignore((N - i) * (M + 1));
				return 0;
			}
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cout << '#' << test_case << ' ' << decode_barcode() << endl;
	}
	return 0;
}