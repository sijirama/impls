#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isAlphanumeric(char c) {
    return isalnum(c);
    ;
}
bool isPalindrome(string s) {
    string newstr = "";
    for (char i : s) {
        if (isAlphanumeric(i)) {
            newstr.push_back(tolower(i));
        }
    }
    string old = newstr;
    reverse(newstr.begin(), newstr.end());
    cout << old;
    cout << endl;
    cout << newstr;
    cout << endl;
    if (old == newstr) {
        return true;
    }

    return false;
}

int main() {
    string str = "A man, a plan, a canal: Panama";
    string strr = "race a car";
    if (isPalindrome(str)) {
        cout << "Is a palindrome";
    } else {
        cout << "Is not a palindrome";
    }
}
