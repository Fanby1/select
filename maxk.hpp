#include <vector>

using namespace std;
int select(vector<int> vals,int k, int size);
int randomizedSelect(vector<int> & vals, int begin, int end, int k);
int randomizedPartition(vector<int> & vals, int begin, int end);
int partition(vector<int> & vals,int begin,int end);
void collection( vector<int>& sames, vector<int>& bigger, vector<int>& lowwer, vector<int>& vals, int &a, int &d, int val, int mid);