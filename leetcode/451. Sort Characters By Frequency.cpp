#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string frequencySort(string s) {
    string ans = "";

    map<char, int>
        M; // create a map to store all the characters and their frequencies
    for (int i = 0; i < s.size(); i++) {
        M[s[i]] += 1;
    }
    vector<pair<char, int>> vec(
        M.begin(), M.end()); // create a vector to store every pair in the map
    auto cmp = [](pair<char, int> a,
                  pair<char, int>
                      b) { // create a function to change the sort method to
                           // arrange the pairs if the frequency is higher
        return a.second > b.second;
    };
    sort(vec.begin(), vec.end(), cmp); // sort with our cmp functor
    for (auto it :
         vec) { // for loop to concat the chars accoriding to their freq
        for (int i = 0; i < it.second; i++) {
            ans += it.first;
        }
    }
    cout << ans;
    return ans;
}
