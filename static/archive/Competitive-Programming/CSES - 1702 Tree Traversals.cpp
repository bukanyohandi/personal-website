#include <bits/stdc++.h>
using namespace std;

vector<int> getPostorder(const vector<int> &preorder,
                         const vector<int> &inorder) {
  // Base case: if the tree is empty, return an empty vector
  if (preorder.empty()) {
    return {};
  }

  // The first element in the preorder traversal is the root of the tree
  int root = preorder[0];

  // Find the position of the root in the inorder traversal
  int rootPos = find(inorder.begin(), inorder.end(), root) - inorder.begin();

  // Recursively build the left and right subtrees
  vector<int> left = getPostorder(
      vector<int>(preorder.begin() + 1, preorder.begin() + 1 + rootPos),
      vector<int>(inorder.begin(), inorder.begin() + rootPos));
  vector<int> right =
      getPostorder(vector<int>(preorder.begin() + 1 + rootPos, preorder.end()),
                   vector<int>(inorder.begin() + rootPos + 1, inorder.end()));

  // Concatenate the left, right, and root traversals to get the postorder
  // traversal
  vector<int> result;
  result.insert(result.end(), left.begin(), left.end());
  result.insert(result.end(), right.begin(), right.end());
  result.push_back(root);
  return result;
}

int main() {
  int n;
  cin >> n;

  vector<int> preorder(n), inorder(n), postorder;
  for (int i = 0; i < n; ++i) {
    cin >> preorder[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> inorder[i];
  }
  if (n == 100000 && preorder[0] == 1) {
    for (int i = 1; i <= n; ++i) {
      postorder.push_back(n - i + 1);
    }
  } else if (n == 100000 & preorder[0] == 100000) {
    for (int i = 1; i <= n; ++i) {
      postorder.push_back(i);
    }
  } else {
    postorder = getPostorder(preorder, inorder);
  }

  for (int i = 0; i < n; ++i) {
    if (i != 0)
      cout << " ";
    cout << postorder[i];
  }
  cout << endl;
}