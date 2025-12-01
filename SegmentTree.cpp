#include <vector>
#include <iostream>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& vec) {
        size_t power_of_two = 1;
        while (power_of_two < vec.size()) {
            power_of_two *= 2;
        }
        n = power_of_two;
        segment_tree.assign(2 * n - 1, 0);

        for (size_t i = 0; i < vec.size(); ++i) {
            segment_tree[get_new_index(i)] = vec[i];
        }

        for (int i = n - 2; i >= 0; --i) {
            segment_tree[i] = segment_tree[2 * i + 1] + segment_tree[2 * i + 2];
        }
    }

    int Request(size_t left, size_t right) {
        if (left > right) return 0;
        
        size_t l = get_new_index(left);
        size_t r = get_new_index(right);
        int ans = 0;

        while (l <= r) {
            if (l % 2 == 0) {
                ans += segment_tree[l];
                l++;
            }
            if (r % 2 == 1) {
                ans += segment_tree[r];
                r--;
            }
            if (l > r) break;
            l = parent(l);
            r = parent(r);
        }
        return ans;
    }

    void Update(size_t index, int value) {
        size_t current = get_new_index(index);
        segment_tree[current] = value;

        while (current > 0) {
            current = parent(current);
            segment_tree[current] = segment_tree[2 * current + 1] + segment_tree[2 * current + 2];
        }
    }

private:
    std::vector<int> segment_tree;
    size_t n;

    size_t parent(size_t i) {
        return (i - 1) / 2;
    }

    size_t get_new_index(size_t i) {
        return n - 1 + i;
    }
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    SegmentTree st(data);

    std::cout << st.Request(0, 7) << std::endl;
    std::cout << st.Request(1, 3) << std::endl;

    st.Update(1, 10);

    std::cout << st.Request(1, 3) << std::endl;
    std::cout << st.Request(0, 7) << std::endl;

    return 0;
}
