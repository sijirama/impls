#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
111
 11
---

*/

string addBinary(string a, string b) {
    int carry = 0;
    string answer;
    string word = a.size() > b.size() ? a : b;
    auto myint = [](char i) { return i - '0'; };
    for (int i = word.size() - 1; i >= 0; i--) {
        int ans;
        if (a[i] && b[i]) {
            ans = myint(a[i]) + myint(b[i]) + carry;
        } else if (a[i]) {
            ans = myint(a[i]) + carry;
        } else {
            ans = myint(b[i]) + carry;
        }

        if (ans > 1) {
            carry = 1;
            ans = 0;
        }
        answer += to_string(ans);
    }
    if (carry) {
        answer += to_string(carry);
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

int main() { cout << addBinary("11", "1"); }
