#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

class thread{
  private:
    int index;
    long long freeTime;

  public:
    thread(){}
    thread(int index, long long freeTime){
      this->index = index;
      this->freeTime = freeTime;
    }

    int get_index(){
      return this->index;
    }
    void set_index(int index){
      this->index = index;
    }
    long long get_free_time(){
      return this->freeTime;
    }
    void set_free_time(long long time){
      this->freeTime = time;
    }
};

class PriorityQueue{
  private:
    int maxSize;
    int size{0};
    vector<thread> arr;

    void sift_up(int nodeNum){
      while(true){
        int parentNode = parent(nodeNum);
        if(nodeNum>1){
          if(arr[parentNode-1].get_free_time() > arr[nodeNum-1].get_free_time()){
            thread temp = arr[parentNode-1];
            arr[parentNode-1] = arr[nodeNum-1];
            arr[nodeNum-1] = temp;
          }
          else if(arr[parentNode-1].get_free_time() == arr[nodeNum-1].get_free_time()){
            if(arr[parentNode-1].get_index() > arr[nodeNum-1].get_index()){
              thread temp = arr[parentNode-1];
              arr[parentNode-1] = arr[nodeNum-1];
              arr[nodeNum-1] = temp;
            }
            else break;
          }
          else{
            break;
          }
          nodeNum = parentNode;
        }
        else{
          break;
        }
      }
      
    }
    void sift_down(int num){
      int minIndex = num;
      int l = left_child(num);
      int r = right_child(num);
      if(l<=size && arr[l-1].get_free_time() < arr[minIndex-1].get_free_time()){
        minIndex = l;
      }
      if(r<=size && arr[r-1].get_free_time() < arr[minIndex-1].get_free_time()){
        minIndex = r;
      }
      if(l<=size && r<=size && arr[l-1].get_free_time() == arr[r-1].get_free_time()){
        if(arr[l-1].get_index() < arr[r-1].get_index()) minIndex = l;
        else minIndex = r;
      }
      if(minIndex!=num){
        thread temp = arr[minIndex-1];
        arr[minIndex-1] = arr[num-1];
        arr[num-1] = temp;
        sift_down(minIndex);
      }
    }

    int parent(int node){
      return node/2;
    }

    int left_child(int node){
      return 2 * node;
    }

    int right_child(int node){
      return left_child(node) + 1;
    }

  public:
    PriorityQueue(int maxSize): maxSize(maxSize) {arr.resize(maxSize);}

    void insert(thread th){
      arr[size] = th;
      size++;
      sift_up(size);
    }

    thread extract_min(){
      thread min = arr[0];
      arr[0] = arr[size-1];
      size--;
      sift_down(1);
      return min;
    }
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    // vector<long long> next_free_time(num_workers_, 0);
    // for (int i = 0; i < jobs_.size(); ++i) {
    //   int duration = jobs_[i];
    //   int next_worker = 0;
    //   for (int j = 0; j < num_workers_; ++j) {
    //     if (next_free_time[j] < next_free_time[next_worker])
    //       next_worker = j;
    //   }
    //   assigned_workers_[i] = next_worker;
    //   start_times_[i] = next_free_time[next_worker];
    //   next_free_time[next_worker] += duration;
    // }
    PriorityQueue pq(num_workers_);
    for(int i=0; i<num_workers_; i++){  // Creating the thread object and inserting them in the priority queue for the first time
      long long x = 0;
      thread th(i, x);
      pq.insert(th);
    }
    for(int j=0; j<jobs_.size(); j++){  // Iterating over the jobs array and for each job extracting a thread from the priority queue and storing the results
      thread th = pq.extract_min();       // and calculating the new free time then updating it in the thread object and again pushing it into the priority queue.
      assigned_workers_[j] = th.get_index();
      start_times_[j] = th.get_free_time();
      th.set_free_time(th.get_free_time() + jobs_[j]);
      pq.insert(th);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
