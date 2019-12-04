#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ios_base;

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

void inorder_new(int root, vector<Node> tree, bool &flag, int lrange, int rrange){
  if(root==-1) return;
  if(tree[root].key<lrange || tree[root].key>rrange) flag = false;
  inorder_new(tree[root].left, tree, flag, lrange, tree[root].key);
  inorder_new(tree[root].right, tree, flag, tree[root].key, rrange);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  // vector<int> result;
  bool flag = true;
  if(tree.size()==0)  return flag;
  inorder_new(0, tree, flag, INT32_MIN, INT32_MAX);
  // inorder(0, tree, result);
  // for(int i=0; i<result.size()-1; i++){
  //   int prev = result[i];
  //   if(result[i]>result[i+1]){
  //     flag =false; 
  //     break;
  //   }
  // }
  return flag;
}



int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
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

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}




// int main() {
//   int nodes;
//   cin >> nodes;
//   vector<Node> tree;
//   for (int i = 0; i < nodes; ++i) {
//     int key, left, right;
//     cin >> key >> left >> right;
//     tree.push_back(Node(key, left, right));
//   }
//   if (IsBinarySearchTree(tree)) {
//     cout << "CORRECT" << endl;
//   } else {
//     cout << "INCORRECT" << endl;
//   }
//   return 0;
// }

