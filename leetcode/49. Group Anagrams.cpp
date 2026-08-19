#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string> &strs) {

    vector<vector<string>> Ans;
    vector<string> B = {strs.begin(), strs.end()};
    set<string> marked;

    for (int i = 0; i < strs.size(); i++) { // sort all strings
        sort(B[i].begin(), B[i].end());
    }

    for (int i = 0; i < strs.size(); i++) {
        vector<string> main;
        if (count(marked.begin(), marked.end(), B[i])) {
            continue;
        }
        marked.insert(B[i]);

        for (int j = 0; j < strs.size(); j++) {
            if (B[i] == B[j]) {
                main.push_back(strs[j]);
            }
        }
        Ans.push_back(main);
    }

    return Ans;
}
