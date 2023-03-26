#include "normalSelect.hpp"
#include "maxk.hpp"
#include "MyRandom.hpp"

#include <iostream>    //cin、cout
#include <string>      //string
#include <stdio.h>     //freopen
#include <vector>
#include <chrono>

using namespace std;

void make(int n);

int res1,res2,index;
long long int t1,t2, t3;
            

int main(){
    int n = 1e6,k = 5e5;
    //for(;n <= 10e9;n *= 10, k *= 10){
        make(n);
        freopen("in.txt", "r", stdin);
        vector<int> vals;
        vals.resize(n);
        for(int i = 0;i < n;i++){
            cin >> vals[i];
        }
        while(res1 == res2 && index < 100){
            auto start = std::chrono::system_clock::now();
            res1 = normalSelect(vals, k);
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            t1 += elapsed.count();
            //freopen("out.txt", "w", stdout); 
            //cout << res << endl;
            start = std::chrono::system_clock::now();
            res2 = select(vals, k, 5);
            end = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            t2 += elapsed.count();
            //cout << res2 << endl;
            start = std::chrono::system_clock::now();
            res2 = select(vals, k, 3);
            end = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            t3 += elapsed.count();
            index++;
        }
        freopen("out.txt", "a", stdout);
        cout << "级别:" << n << endl;
        cout << "普通方法:" << t1 << endl;
        cout << "改进方法5个一组:" << t2 << endl;
        cout << "改进方法3个一组:" << t3 << endl;
        t1 = 0;
        t2 = 0;
        t3 = 0;
        index = 0;
    //}
    /*
    
    return 0;
    */
}


void make(int n){
    auto r = MyRandom(1, 1e5);
    freopen("in.txt", "w", stdout); 
    for(int i = 0;i < n;i++){
        cout << r.getWord() << " ";
    }
}
