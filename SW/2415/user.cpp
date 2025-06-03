#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
using namespace std;

using pii = pair<int , int>;

struct Result {
	int mCost;
	int mContent; 
};

// mineId, type 별로 저장
set<pii> mines[3][3]; // cost 절댓값 작은 순, content 많은 순

int mShipFee; // 1 ~ 40000


void init(int mShipFee) {
  ::mShipFee = mShipFee;
}

int gather(int mMineId, int mType, int mCost, int mContent) {
  mines[mMineId][mType].insert(make_pair(mCost, -mContent));
	mines[2][mType].insert(make_pair(mCost, -mContent));
	cout << mines[mMineId][mType].size() << '\n';
  return mines[mMineId][mType].size();
}

Result get_answer(int mineID, int mBudget, int shipCost){
	int budget = mBudget - shipCost;
	set<pii>& elems_0 = mines[mineID][0];
	set<pii>& elems_1 = mines[mineID][1];
	set<pii>& elems_2 = mines[mineID][2];
	priority_queue<pii> pq;

	for(auto iter = elems_0.begin(); iter != elems_0.end(); ++iter){
		pii elem_0 = *iter;
		int budget_1 = budget - elem_0.first;
		if(budget_1 < 0) break;
		for(auto iter = elems_1.begin(); iter != elems_1.end(); ++iter){
			pii elem_1 = *iter;
			int budget_2 = budget_1 - elem_1.first;
			if(budget_2 < 0) break;
			for(auto iter = elems_2.begin(); iter != elems_2.end(); ++iter){
				pii elem_2 = *iter;
				int budget_3 = budget_2 - elem_2.first;
				if(budget_3 < 0) break;

				// 타입별로 하나씩 꺼내서 pq에 넣기
				int cost = mBudget - budget_3;
				int minContent = min(min(-elem_0.second, -elem_1.second), -elem_2.second);
				pq.push({-cost, minContent});
			}
		}
	}
	
	Result ans = { 0, 0 };
	if(pq.size() > 0){
		ans.mCost = -pq.top().first;
		ans.mContent = pq.top().second;
	}

	return ans;
}

Result mix(int mBudget) {
	Result ans = { 0, 0 };

	for(int mineID = 0; mineID < 3; mineID++){
		int shipCost = mineID == 2 ? 2 * mShipFee : mShipFee;
		Result cur = get_answer(mineID, mBudget, shipCost);

		if(cur.mContent > ans.mContent || (cur.mContent == ans.mContent) && (cur.mCost < ans.mCost)){
			ans.mContent = cur.mContent;
			ans.mCost = cur.mCost;
		}
	}

	cout << ans.mCost << ' ' << ans.mContent << '\n';
	return ans;
}
