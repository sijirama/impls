/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
Example 1:
Input: nums = [3,2,3]
Output: [3]
*/

#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;



vector<int> majorityElement(vector<int>& nums);

int main(){
    vector <int> question = {1 , 1, 1, 1,1};
    vector <int> num = majorityElement(question);

    for(int i : num){
        cout << i << endl;
    }
}

vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size()/3;
    vector <int> Result;
    int count = 0;

    sort(nums.begin() , nums.end());

    for(int i = 0; i < nums.size()-1; ++i){
       if(nums[i] == nums[i+1]){
            ++count; 
        }else{
            count = 0;
        }
        if(count >= n){
            Result.push_back(nums[i]);
        }
    }
    
    if (count >= n) {
        Result.push_back(nums[nums.size() - 1]);
    }

    auto u = unique(Result.begin() , Result.end());
    Result.resize(distance(Result.begin(), u));
    return Result;
}
