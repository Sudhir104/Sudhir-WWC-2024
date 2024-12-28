#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct T {
  int i;     // Index from nums1
  int j;     // Index from nums2
  int sum;   // Sum of nums1[i] and nums2[j]
};

class Solution {
 public:
  int kthSmallest(vector<vector<int>>& mat, int k) {
    vector<int> row = mat[0]; // Start with the first row

    // Iteratively merge each row with the accumulated result
    for (int i = 1; i < mat.size(); ++i)
      row = kSmallestPairSums(row, mat[i], k);

    return row[k - 1]; // Return the k-th smallest sum
  }

 private:
  vector<int> kSmallestPairSums(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<int> ans;
    auto compare = [&](const T& a, const T& b) { return a.sum > b.sum; };
    priority_queue<T, vector<T>, decltype(compare)> minHeap(compare);

    // Initialize the min-heap with the first k pairs
    for (int i = 0; i < min(k, static_cast<int>(nums1.size())); ++i)
      minHeap.push({i, 0, nums1[i] + nums2[0]});

    // Extract the smallest sums
    while (!minHeap.empty() && ans.size() < k) {
      T top = minHeap.top();
      minHeap.pop();
      int i = top.i;
      int j = top.j;
      int sum = top.sum;

      ans.push_back(sum);

      if (j + 1 < nums2.size()) // Push the next pair in the row
        minHeap.push({i, j + 1, nums1[i] + nums2[j + 1]});
    }

    return ans;
  }
};

int main() {
  Solution solution;
  vector<vector<int>> mat = {
      {1, 3, 11},
      {2, 4, 6},
  };
  int k = 5;

  int result = solution.kthSmallest(mat, k);
  cout << "The " << k << "-th smallest sum is: " << result << endl;

  return 0;
}
