#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

using pii = pair<int , int>;

struct Result {
	int mCost;
	int mContent; 
};

int mShipFee;

struct E{
	int mineID, cost, content;

	bool operator <(const E& other) const{
		if (cost != other.cost)
				return cost < other.cost;
		return content > other.content;   
	}
};

// mineID, type
set<E> mines[3][3]; 

struct Combo{
	int cost, content;
	vector<E> history;

	bool operator <(const Combo& other) const{
		if (content != other.content)
				return content > other.content; // content 높은 순 (내림차순)
		return cost < other.cost;           // cost 낮은 순 (오름차순)
	}
};

set<int> mix_budgets;
unordered_map<int, set<Combo>> mix_records; // budget, which_combo

void print_hists(vector<E> history){
	for(int i = 0; i < 3; i++){
		E hist = history[i];
		cout << "\t\t" << hist.mineID << ' ' << hist.cost << ' ' << hist.content << '\n';
	}
}

void init(int mShipFee) {
  ::mShipFee = mShipFee;
	
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			mines[i][j].clear();

	mix_budgets.clear();
	mix_records.clear();
}

void insert_combo(int mineID, int shipCost, int budget, set<Combo> &which_combo){
	for(E elem_0 : mines[mineID][0]){
		int cost_0 = shipCost + elem_0.cost;
		int content_0 = elem_0.content;
		if(cost_0 > budget) break;

		for(E elem_1 : mines[mineID][1]){
			int cost_1 = cost_0 + elem_1.cost;
			int content_1 = min(content_0, elem_1.content);
			if(cost_1 > budget) break;

			for(E elem_2 : mines[mineID][2]){
				int cost_2 = cost_1 + elem_2.cost;
				int content_2 = min(content_1, elem_2.content);
				if(cost_2 > budget) break;

				Combo new_combo = {cost_2, content_2};
				new_combo.history = {elem_0, elem_1, elem_2};
				which_combo.insert(new_combo);
			}
		}
	}
}

int gather(int mMineId, int mType, int mCost, int mContent) {
	E new_elem = {mMineId, mCost, mContent};
  mines[mMineId][mType].insert(new_elem);
	mines[2][mType].insert(new_elem);

  return mines[mMineId][mType].size();
}

int last_budget;
Result mix(int mBudget) {
	Result ans = {0, 0};

	// mix_budgets에서 mBudget 이하의 값 찾기
	set<Combo> which_combo;
	auto iter1 = mix_budgets.upper_bound(mBudget);
	if (iter1 == mix_budgets.begin()) {
    // 이전 조합 없음: 빈 상태로 시작
	} else {
			--iter1;
			int hist_budget = *iter1;
			which_combo = mix_records[hist_budget];
	}

	for(int mineID = 0; mineID < 3; mineID++){
		int shipCost = mineID == 2 ? 2 * mShipFee : mShipFee;
		insert_combo(mineID, shipCost, mBudget, which_combo);
	}

	auto iter2 = which_combo.begin();
	while(iter2 != which_combo.end()){
		bool isExist = true;
		for(int type = 0; type < 3; type++){
			E elem = iter2->history[type];
			bool found = mines[elem.mineID][type].find({elem.mineID, elem.cost, elem.content}) != mines[elem.mineID][type].end();
			if(!found){
				isExist = false;
				break;
			}
		}

		if(!isExist){
			// which_combo 에서 해당 elem 지우기
			iter2 = which_combo.erase(iter2);
		}
		else{
			// ans update 및 history 지우기
			ans = { iter2->cost, iter2->content };
			for(int type = 0; type < 3; type++){
				E hist = iter2->history[type];
				mines[hist.mineID][type].erase({hist.mineID, hist.cost, hist.content});
				mines[2][type].erase({hist.mineID, hist.cost, hist.content});
			}
			which_combo.erase(iter2);
			break;
		}
	}

	mix_budgets.insert(mBudget);
	mix_records[mBudget] = which_combo;

	// cout << ans.mCost << ' ' << ans.mContent << '\n';
	return ans;
}
