#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;
  int size = 0;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    size = n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int parent(int node){
    return (node/2);
  }

  int leftChild(int node){
    return (2*node);
  }

  int rightChild(int node){
    return (2*node)+1;
  }

  void shiftDown(int num){
    // int size = data_.size()-1;
    int minIndex = num;
    int l = leftChild(num);
    int r = rightChild(num);
    if(l<=size && data_[l-1]<data_[minIndex-1]){
      minIndex = l;
    }
    if(r<=size && data_[r-1]<data_[minIndex-1]){
      minIndex = r;
    }
    if(minIndex!=num){
      swap(data_[minIndex-1], data_[num-1]);
      swaps_.push_back(make_pair(num-1, minIndex-1));
      shiftDown(minIndex);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    // int size = data_.size()-1;
    cout<<"The size of array is: "<<size<<std::endl;
    for(int i=parent(size); i>=1; i--){
      shiftDown(i);
    }

  //   for (int i = 0; i < data_.size(); ++i)
  //     for (int j = i + 1; j < data_.size(); ++j) {
  //       if (data_[i] > data_[j]) {
  //         swap(data_[i], data_[j]);
  //         swaps_.push_back(make_pair(i, j));
  //       }
  //     }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
