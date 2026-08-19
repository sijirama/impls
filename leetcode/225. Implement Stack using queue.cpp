#include <iostream>
#include <vector>

class MyStack {
  private:
    std::vector<int> queue;
    int ourtop = -1;

  public:
    MyStack() {}

    void push(int x) {
        this->ourtop = this->ourtop + 1;
        this->queue.emplace_back(x);
    }

    int pop() {
        // if (this->ourtop < 0) {
        //   return 0;
        // }
        int val = this->queue[this->ourtop];
        this->queue.pop_back();
        this->ourtop = this->ourtop - 1;
        return val;
    }

    int top() {
        // if (this->ourtop < 0) {
        //   return 0;
        // }
        int val = this->queue[this->ourtop];
        return val;
    }

    bool empty() {
        if (this->ourtop < 0) {
            return true;
        }
        return false;
    }
};
