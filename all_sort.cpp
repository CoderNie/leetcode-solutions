#include <iostream>
#include <vector>
using namespace std;
void printArr(vector<int> &nums);

// 冒泡
void propagate(vector<int> &nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        for (int j = 0; j < nums.size() - i - 1; j++) {
            if (nums[j] > nums[j + 1])
                swap(nums[j], nums[j + 1]);
        }
    }
}
// 选择
void selection(vector<int> &nums) {
    for (int i = 0; i < nums.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < nums.size(); j++) {
            minIndex = nums[j] < nums[minIndex] ? j : minIndex;
        }
        if (minIndex != i)
            swap(nums[minIndex], nums[i]);
    }
}
// 直接插入
void insert_direct(vector<int> &nums) {
    for (int i = 1; i < nums.size(); i++) {
        int j = i, temp = nums[j];
        while (temp < nums[j - 1]) {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = temp;
    }
}
// 希尔插入
void insert_shell(vector<int> &nums) {
    int gap = nums.size();
    while (gap > 1) {
        gap = gap / 3 + 1;
        for (int i = gap; i < nums.size(); i += gap) {
            int j = i, temp = nums[j];
            while (j - gap >= 0 & temp < nums[j - gap]) {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = temp;
        }
    }
}
// 堆排序
void heapify(vector<int> &nums, int i, int size) {
    int leftChild = i * 2 + 1;
    int rightChild = i * 2 + 2;
    int maxI = i;
    if (leftChild < size && nums[leftChild] > nums[maxI])
        maxI = leftChild;
    if (rightChild < size && nums[rightChild] > nums[maxI])
        maxI = rightChild;
    if (maxI != i) {
        swap(nums[maxI], nums[i]);
        heapify(nums, maxI, size);
    }
} 
void heap(vector<int> &nums) {
    // build heap
    for (int i = nums.size() / 2 - 1; i >= 0; i--)
        heapify(nums, i, nums.size());
    // heapify
    for (int i = nums.size() - 1; i > 0; i--) {
        swap(nums[i], nums[0]);
        heapify(nums, 0, i);
    }
}
// 归并排序
void merge(vector<int> &nums, int begin1, int end1, int begin2, int end2){ 
    vector<int> temp;
    int i = begin1, j = begin2;
    while (i <= end1 && j <= end2) {
        if (nums[i] < nums[j]) {
            temp.push_back(nums[i]);
            i++;
        } else {
            temp.push_back(nums[j]);
            j++;
        }
    }
    while (i <= end1)
        temp.push_back(nums[i++]);
    while (j <= end2)
        temp.push_back(nums[j++]);
    for (int i = begin1; i <= end2; i++) {
        nums[i] = temp[i - begin1];
    }

}
void merge_sort(vector<int> &nums, int begin, int end){
    int size = end - begin + 1;
    if (size > 1) {
        int begin1 = begin;
        int end1 = begin + size / 2 - 1;
        int begin2 = end1 + 1;
        int end2 = end;
        merge_sort(nums, begin1, end1);
        merge_sort(nums, begin2, end2);
        merge(nums, begin1, end1, begin2, end2);
    }
}
// 快速排序
void quick(vector<int> &nums, int begin, int end) {
    if (begin >= end) return;
    int i = begin, j = end, temp = nums[i];
    while (i < j) {
        while (i < j && nums[j] > temp)
            j--;
        if (i < j)
            nums[i++] = nums[j];
        while (i < j && nums[i] < temp)
            i++;
        if (i < j)
            nums[j--] = nums[i];
    }
    nums[i] = temp;
    quick(nums, begin, i - 1);
    quick(nums, i + 1, end);
}

void printArr(vector<int> &nums) {
    if (nums.size() == 0) return;
    cout << nums[0];
    for (int i = 1; i < nums.size(); i++)
        cout << ", " << nums[i];
    cout << endl;
}

int main() {
    vector<int> nums = {6, 3, 1, 5, 7, 2};
    printArr(nums);
    quick(nums, 0, nums.size() - 1);
    printArr(nums);
    return 0;
}