#include "select.hpp"
#include "MyRandom.hpp"
#include <algorithm>
#include <assert.h>

using namespace std;

bool difftest(vector<int> vals){
    for(int i = 0;i < vals.size();i++){
        if(vals[i] == 50168){
            return true;
        }
    }
    return false;
}

int select(vector<int> vals,int k, int size){
    //assert(difftest(vals));
    //特殊情况
    if(vals.size() <= size){
        sort(vals.begin(),vals.end());
        return vals[k - 1];
    }
    //分组并补齐元素数量
    vector<int> nextVals;
    if(int a = vals.size() % size){
        for(int i = 0;i < a;i++){
            nextVals.push_back(vals[vals.size() - 1]);
            vals.pop_back();
        }
    }
    int n = vals.size() / size;
    //组内排序
    for(int i = 0;i < n;i++){
        sort(vals.begin() + i * size, vals.begin() + (i + 1) * size);
    }
    //找出中位数的中位数
    vector<int> mids;
    mids.resize(n);
    for(int i = 0;i < n;i++){
        mids[i] = vals[i * size + 2];
    }
    /*
    freopen("out2.txt", "w", stdout); 
    for(auto a : mids){
        cout << a << " ";
    }
    cout << endl;
    */
    auto res = randomizedSelect(mids, 0, n - 1, (n - 1) / 2 + 1);
    //difftest(mids, res, n);
    
    //统计abcd四个区域中的数量
    int a,b,c,d, big = 0, same = 0;
    for(int i = 0;i < n;i++){
        if(vals[i * size + 2] > res){
            big++;
        }else if(vals[i * size + 2] == res){
            same++;
        }
    }
    d = big * 3 + 2 * same;
    c = (n - big - same) * 2;
    b = big * 2;
    a = (n - big - same) * 3 + same * 2;
    vector<int> bigger, lowwer, sames;
    for(auto p : nextVals){
        collection(sames, bigger, lowwer, vals, a, d, p, res);
    }
    for(int i = 0;i < n;i++){
        //属于b
        if(vals[i * size + 2] > res){
            for(int j = 0;j < 2;j++){
                collection(sames, bigger, lowwer, vals, a, d, vals[i * size + j], res);
            }
        }else if(vals[i * size + 2] < res){
            for(int j = 3;j < size;j++){
                collection(sames, bigger, lowwer, vals, a, d, vals[i * size + j], res);
            }
        }
    }
    nextVals.clear();
    //分情况递归
    if(a + 1 > k){
        for(int i = 0;i < n;i++){
            if(res >= vals[size * i + 2]){
                for(int j = 0;j < 3;j++){
                    lowwer.push_back(vals[size * i + j]);
                }
            }
        }
        for(auto p : sames){
            lowwer.push_back(p);
        }
        return select(lowwer, k, size);
    }else if(a + 1 < k){
        for(int i = 0;i < n;i++){
            if(res <= vals[size * i + 2]){
                for(int j = 2;j < size;j++){
                    bigger.push_back(vals[size * i + j]);
                }
            }
        }
         for(auto p : sames){
            bigger.push_back(p);
        }
        return select(bigger, k - a, size);
    }else{
        return res;
    }

}

int randomizedSelect(vector<int> & vals, int begin, int end, int i){
    if(begin == end){
        return vals[begin];
    }
    int q = randomizedPartition(vals, begin, end);
    int k = q - begin + 1;
    if(i == k){
        return vals[q];
    }else if(i < k){
        return randomizedSelect(vals, begin, q - 1, i);
    }else{
        return randomizedSelect(vals, q + 1, end, i - k);
    }
}


int randomizedPartition(vector<int> & vals, int begin, int end){
    assert(begin <= end);
    auto r = MyRandom(begin,end);
    int i = r.getWord();
    assert(i >= begin && i <= end);
    swap(vals[end],vals[i]);
    return partition(vals, begin, end);
}

int partition(vector<int> & vals,int begin,int end){
    int x = vals[end];
    int i = begin;
    for(int j = begin; j < end; j++){
        if(vals[j] <= x){
            swap(vals[i], vals[j]);
            i = i + 1;
        }
    }
    swap(vals[i], vals[end]);
    return i;
}

void collection( vector<int>& sames, vector<int>& bigger, vector<int>& lowwer, vector<int>& vals, int &a, int &d, int val, int mid){
    if(val < mid){
        lowwer.push_back(val);
        a++;
    }else if(val > mid){
        bigger.push_back(val);
        d++;
    }else{
        sames.push_back(val);
    }
}


