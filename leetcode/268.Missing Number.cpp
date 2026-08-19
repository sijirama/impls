/*
Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
*/

#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;

int missingNumber(vector<int>& nums) {
    vector<int> RangeVect;
    int Bigger = 0;
    int Smaller = 0;

    for(int i = 0 ; i <= nums.size() ; ++i ){
        RangeVect.emplace_back(i);
    }

    for(int i : RangeVect){
        Bigger += i ;
    }
    for(int i : nums){
        Smaller += i;
    }

    return Bigger - Smaller;
}

int main(){
    vector<int>ques = {3,0,1};
    int ans = missingNumber(ques);
    cout <<"Final Answer is: "<< ans << endl;
}
