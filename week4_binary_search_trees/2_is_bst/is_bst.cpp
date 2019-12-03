#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void inorder(int root, vector<Node> tree, vector<int> &result){
  if(root==-1) return;
  inorder(tree[root].left, tree, result);
  result.push_back(tree[root].key);
  inorder(tree[root].right, tree, result);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  vector<int> result;
  bool flag = true;
  inorder(0, tree, result);
  for(int i=0; i<result.size()-2; i++){
    int prev = result[i];
    if(result[i]>result[i+1]){
      flag =false; 
      break;
    }
  }
  return flag;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
