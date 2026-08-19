/*
78. Subsets
Given an integer array nums of unique elements, return all possible
subsets
(the power set).
The solution set must not contain duplicate subsets. Return the solution in any
order. Example 1: Input: nums = [1,2,3] Output:
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> pascals(int num) {
  vector<int> Result;

  for (int i = 0; i < num; ++i) {
  }

  return Result;
}

vector<vector<int>> generate(int numRows) {
  vector<vector<int>> Result;

  return Result;
}

int main() {

  vector<vector<int>> result = generate(5);
  // for(vector<int> i : result){
  //    for(int j : i){
  //        cout << j << " ";
  //    }
  //    cout << endl;
  // }
}
