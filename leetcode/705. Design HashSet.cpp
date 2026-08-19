// Explanation
// MyHashSet myHashSet = new MyHashSet();
// myHashSet.add(1);      // set = [1]
// myHashSet.add(2);      // set = [1, 2]
// myHashSet.contains(1); // return True
// myHashSet.contains(3); // return False, (not found)
// myHashSet.add(2);      // set = [1, 2]
// myHashSet.contains(2); // return True
// myHashSet.remove(2);   // set = [1]
// myHashSet.contains(2); // return False, (already removed)

#include <algorithm>
#include <vector>
using namespace std;
class MyHashSet {
  public:
    vector<int> set;
    MyHashSet() {}

    void add(int key) {
        if (this->set.empty()) {
            this->set.emplace_back(key);
            return;
        }
        for (int i = 0; i < this->set.size(); ++i) {
            if (this->set[i] == key) {
                return;
            }
        }
        this->set.emplace_back(key);
    }

    void remove(int key) {
        if (this->contains(key)) {
            auto it = find(this->set.begin(), this->set.end(), key);
            if (it != this->set.end()) {
                this->set.erase(it);
            }
        }
    }

    bool contains(int key) {
        bool ans = false;
        for (int i = 0; i < this->set.size(); ++i) {
            if (this->set[i] == key) {
                ans = true;
            }
        }
        return ans;
    }
};
