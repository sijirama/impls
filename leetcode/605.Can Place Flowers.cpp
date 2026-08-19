/*
You have a long flowerbed in which some of the plots are planted, and some are
not. However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and
1 means not empty, and an integer n, return true if n new flowers can be planted
in the flowerbed without violating the no-adjacent-flowers rule and false
otherwise. Example 1: Input: flowerbed = [1,0,0,0,1], n = 1 Output: true
*/

// Incomplete

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

bool canPlaceFlowers(vector<int> &flowerbed, int n) {
    bool answer = false;
    vector<int> ZeroVector;
    vector<int> OneVector;
    for (int num : flowerbed) {
        if (num == 0) {
            ZeroVector.push_back(num);
        } else {
            OneVector.push_back(num);
        }
    }
    if (n < 1) {
        return true;
    }
    if (OneVector.size() > ZeroVector.size() && n > 0) {
        return false;
    }
    int SizeofSpaceLeft = ZeroVector.size();
    double dubsize = SizeofSpaceLeft;
    if (n > SizeofSpaceLeft)
        return false;
    // if(SizeofSpaceLeft % 2 == 0 ) return false;
    if ((dubsize / 2) > n) {
        cout << dubsize;
        return true;
    } else {
        cout << dubsize;
        return false;
    }
}

int main() {
    vector<int> question = {1, 0, 0, 0, 1, 0, 1};
    int n = 1;
    if (canPlaceFlowers(question, n)) {
        cout << "True";
    } else {
        cout << "False";
    }
}
