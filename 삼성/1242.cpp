#include<iostream>
#include<cstring>

using namespace std;

int char_to_number(char c){
	if(c >= 'A' && c <= 'F'){
		return c - 'A' + 10;
	}

	return c - '0';
}

void save_line(char* raw, char* dst){
	int i = -1;

	while(raw[++i] != '\0'){
		int n = char_to_number(raw[i]);
		int digit = 0;

		while(digit < 4){
			dst[4 * i + 3 - digit] = n % 2 ? '1' : '0';
			digit++;
			n = n >> 1;
		}
	}
	
}

int get_last_point(char* raw_codes, size_t len){
	for (int i = len - 1; i >= 0; i--){
		if(raw_codes[i] == '1'){
			return i;
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

int get_width(char* src, int last_point){
	int sum = 0;
	int cnt = 0;

	for (int i = 0; i < 4; i++){
		char current_digit = i % 2 == 0 ? '1' : '0';

		while(src[last_point--] == current_digit){
			cnt++;
		}

		sum += cnt;
		cnt = 1;
	}

	return (sum + 6) / 7;
}

void strip_code(char* src, int width, char* buffer){
	for (int i = 0; i < 7; i++){
		buffer[i] = src[i * width];
	}
}

int get_code(char* src){
	int sum = 0, digit = 1 << 4;

	for (int i = 1; i <= 5; i++){
		sum += (src[i] - '0') * digit;
		digit = digit >> 1;
	}

	return decode_value(sum);
}

void save_codes(char* src, int* dst, int width){
	int start_point = 0;
	char code[7];

	for (int i = 0; i < 9; i++){
		strip_code(&src[7 * i * width], width, code);
		dst[i] = get_code(code);
	}
}

int decode_barcode(){
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; i++){
		char hex_line[501] = { 0 }, line[2001] = { 0 };
		cin >> hex_line;

		save_line(hex_line, line);

		int last_point = get_last_point(line, M * 4);
		line[last_point + 1] = '\0';

		if(last_point != -1){
			int codes[8];
			int width = get_width(line, last_point);
			save_codes(&line[last_point - 7*8*width + 1], codes, width);
			// for(int code : codes)
			// 	cout << code << ' ';
			// cout << endl;

			for(int code : codes){
				if(code == -1){
					continue;
				}
			}

			int odd_sum = codes[0] + codes[2] + codes[4] + codes[6];
			int even_sum = codes[1] + codes[3] + codes[5] + codes[7];

			if(((odd_sum)*3 + even_sum) % 10 == 0){
				cin.ignore((N - i) * (M + 1));
				return odd_sum + even_sum;
			}
			else{
				continue;
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