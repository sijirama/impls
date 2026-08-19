/*
Write a function that reverses a string. The input string is given as an array
of characters s. You must do this by modifying the input array in-place with
O(1) extra memory.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

void reverseString(vector<char> &s) { reverse(s.begin(), s.end()); }

int main() {
    vector<char> que = {'H', 'a', 'n', 'n', 'a', 'h'};
    reverseString(que);
    for (auto i : que) {
        cout << i;
    }
}
