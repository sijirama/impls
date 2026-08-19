/*
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
Example 1:
Input: nums = [1,2,3,1]
Output: true
*/
#include <algorithm>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool containsDuplicate(vector<int>& nums);


int main(){
    vector <int> question = {1,1,1,3,3,4,3,2,4,2};
    auto ans =  containsDuplicate(question);
    if(ans){
        cout << "true";
    }else{
        cout << "False";
    }
}

bool containsDuplicate(vector<int>& nums) {
    bool flag = false;
    int count = 1;

    sort(nums.begin() , nums.end());
    for(int i = 0 ; i < nums.size() - 1 ; ++i){
        if(nums[i] == nums[i+1]){
            ++count;
        }
        if(count > 1){
            return true;
        }
    }

    if(count > 1){
        return true;
    }
       
    return flag;
};
