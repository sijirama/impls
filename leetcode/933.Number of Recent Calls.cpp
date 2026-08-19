#include <vector>
using namespace std;

class RecentCounter {
    vector<int> request;

  public:
    RecentCounter() { request.clear(); }

    int ping(int t) {
        this->request.emplace_back(t);
        return this->getThosRanges(t);
    }

    int getThosRanges(int t) {
        int lower = t - 3000;
        int higher = t;
        int count = 0;

        for (int i = 0; i < this->request.size(); ++i) {
            if (this->request[i] >= lower && this->request[i] <= higher) {
                ++count;
            }
        }
        return count;
    }
};
