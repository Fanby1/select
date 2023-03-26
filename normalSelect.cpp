#include <algorithm>
#include <vector>

using namespace std;


int normalSelect(vector<int> vals, int k){
    sort(vals.begin(), vals.end());
    return vals[k - 1];
}