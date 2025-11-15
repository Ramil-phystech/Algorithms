#include <iostream>
#include <vector>

int get_elem(const std::vector<int> &arr, int target) {
    std::size_t left = 0;
    std::size_t right = arr.size() - 1;

    while (left <= right) {
        std::size_t middle = (left + right) / 2;

        if (arr[middle] == target)
            return middle;

        if (arr[left] <= arr[middle]) {
            if (arr[left] <= target && target < arr[middle])
                right = middle - 1;
            else
                left = middle + 1;
        } else
            if (arr[middle] < target && target <= arr[right])
                left = middle + 1;
            else
                right = middle - 1;
    }

    return -1;
}


int main() {
    std::vector<int> arr = {8, 8, 7, 1, 1, 2, 2, 3, 4, 5};

    std::cout << get_elem(arr, 4) << std::endl;

    return 0;
}
