#include <vector>
#include <queue>
#include <functional>

int kth_largest(std::vector<int> values, int k) {

    if (k <= 0 || values.empty()) {
        return -1;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    for (int val : values) {
        min_heap.push(val);

        if (min_heap.size() > static_cast<size_t>(k)) {
            min_heap.pop();
        }
    }

    return min_heap.top();
}
