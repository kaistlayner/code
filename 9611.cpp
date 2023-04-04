#include<iostream>

using namespace std;

int find_answer(){
	int count;
	cin >> count;

  int answer[10] = {0};
  int yes_count = 0;

	for(int i = 0; i < count; i++){
		int tmp[4];
		char result;
		cin >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> result;
    cin.ignore(3, '\n');
    cin.clear();

    if(result == 'Y'){
      for(int value : tmp){
        // cout << "testing: " << value << endl;;
        if(answer[value] > -1){
          answer[value]++;
        }
      } 
      yes_count++;
    }
    else{
      for(int value : tmp){
        answer[value] = -1;
      }
    }

    // for(int num : answer) cout << num << ' ';
    // cout << endl;
	}


  for(int i = 0; i < 10; i++){
    if(answer[i] == yes_count) return i;
  }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cout << '#' << test_case << ' ' << find_answer() << endl;
	}
	return 0;
}