#include <string>
using namespace std;

string toString(int n) {
    ;
    return to_string(n);
}

bool isHappy(int n) {
    if (n == 1 || n == 7) {
        return true;
    }

    string number = toString(n);

    int sum = 0;
    for (char i : number) {
        sum += (i - '0') * (i - '0');
    }
    if (sum == 1) {
        return true;
    }

    if (number.size() < 2) {
        return false;
    }

    return isHappy(sum);
}
