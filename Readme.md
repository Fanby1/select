# select
## 目录
* [原始算法](#原始算法)
  * [算法的细节](#算法的细节)
  * [算法的时间复杂度](#算法的时间复杂度)
* [关于原始算法的讨论](#原始算法讨论)
* [对原始算法的改进](#对原始算法的改进)
* [关于改进算法的讨论](#对改进算法的讨论)
  * [为何不使用随机选则算法](#为何不使用随机选则算法)

### 原始算法
  原始算法将原始数组五个一组分配并递归的调用其伪代码如下
  ```
  Select(S, k)
    将S划分为5个一组，共n/5个组
    每组分别排序并将每组中位数放入集合M中
    m* = Select(M, |M| / 2 + 1)
    将AD中的每个元素与m*进行比较，小的加入S1，大的加入S2
    S1 += c, S2 += B
    if k == |S1| + 1
      return m*
    else if k <= |S1|
      Select(S1, k)
    else 
      Select(S2, k - |S1| - 1)
  ``` 
#### 算法的细节
  这之中有几个小细节
  * 对于不清楚与m*大小关系的a与d区域并非不管不顾，而是进行了比较 
  * 对于每一组内部不光要找中位数还要排序
  * 元素分类的操作可以在统计个数并决定下一次递归分支时进行，这样可以有效减少常数大小。
  * 对于余项（n模5不为0时）的处理。
  * 中位数不唯一时取下中位数
#### 算法的时间复杂度
  这个算法是![][O(n)]复杂度的下面给出具体的推导  
  对于其中的非递归部分可以简单的算出其时间复杂度为![][O(n)]  
  而算法中出现了两个递归部分它们的代价分别为![][T(n/5)]与![][T(7n/10)]  
  有递推公式![][递推1]  
  推导：  
  ![][推导1]  
  
  可以看到推导中最重要的部分是这个等比数列的和是否收敛。
  而有高数知识q < 1时收敛因此3个不行7个可以
### 原始算法讨论
  可以注意到在算法递归的两支中有一支单纯的求中位数但是却白白浪费了0.2的递归权重。  
  对此我联想到了算法导论中给出的一个时间复杂度![][O(n)]的随机选则算法。  
  我使用这一算法对其进行优化，将求中位数的部分化为![][O(n)]进一步减小时间复杂度。  
  我利用到的这一算法伪代码如下
  ```
  randomized-select(A,p,r,i)
    if(p == r)
      return A[p]
    q = randomized-partition(A,p,r)
    k = q - p + 1
    if(i == k)
      return A[q]
    else if(i < k)
      return randomized-select(A,p,q - 1,i)
    else
      return randomized-select(A,q + 1,r,i - k)
  ```
  这一算法是![][O(n)]的，证明如下：  
  这个算法是一个随机算法，首先考虑最坏情况，即partition部分每一次都作出了最坏选择的情况：
    此时在每一轮递归中只有一个元素被排除在外而partition则消耗了![][O(n)]的时间对数组原址重排  
    有递推公式：  
    ![][递推2]  
    推导：  
    ![][推导2]  
  其次考虑期望情况：  
  我们设该算法在一个含有n个元素的输入数组[p...r]上的运行时间是一个随机变量，记为T(n)  
  对于子过程Randomized-partition 等可能的返回任何元素作为住院。  
  不妨设主元是互异的，因此对于任意元素作为主元的概率为1/n。  
  因为目标元素位于主元的左侧与右侧在代码中的处理的对称的，我们不妨假设目标总是在主元的较大一侧即A[q + 1,r]一侧。
  定义一个指示器![][指示器]方便书写，其含义为：  
  ![][含义]  
  则  
  ![][推导3]  
  两边取期望  
  ![][推导4]  
  上一部中运用了指示器与T(max(k - 1,n - k))独立  
  又![][定义1]  
  ![][结论1]  
  下面考虑T(max(k - 1,n - k))  
  由于k - 1 + n - k = n -1 因此不论n为奇数还是偶数，绝大部分的T(k)会成对出现  
  ![][结论2]  
  接下来利用归纳法
  假设T(n) < cn 而余项O(n) < an  
  ![][推导5]   
  把取整放缩掉   
  ![][推导6]  
  把负项放缩掉  
  ![][推导7]  
  得证（其实还有一些细节但太麻烦了就不写了）
### 对原始算法的改进
  这一部分的改进十分简单就是把找中位数的部分替换为前文中的randomized-selection  
  但是实现起来异常困难，细节很多具体可以看select.cpp。（里面写了注释） 
  为了保证算法的正确性我还写了一个单纯的排序后选第k个的算法并在main中做difftest。  
### 对改进算法的讨论
  这一改进最大的用处就是可以在每组三个的情况下获得线性复杂度的结果！（震声）  
  具体可以自己试运行一下。  
  这之中randomized-partition的伪代码如下
  ```
  randomiezd-partition(A,p,r)
    i = random(p,r)
    swap(A[i],A[r])
    return partition(A,p,r)
  ```
  partition的伪代码如下
  ```
  partition(A,p,r)
    x = A[r]
    i = p
    for j = p to r - 1
      if A[j] <= x
        swap(A[i],A[j])
        i = i + 1
    swap(A[i],A[r])
    return i
  ```
#### 为何不使用随机选则算法
  那么问题来了，为什么教科书没有用这种方法而要固执的5个一组分类呢？  
  这是由于在前一部分的讨论中我们分析出随机算法的最坏时间复杂度为O(n^{2})  
  如果触发了最坏情况整个算法将不能再保持O(n)  
  但是这里还有一个问题。  
  由于我们使用的是随机算法，最坏情况实际上没有意义。  
  毕竟每一次都抽签抽到最坏情况的几率实在是太小了。  
  所以我认为我得改进还是有效的。

[O(n)]:https://latex.codecogs.com/svg.image?O(n)
[T(n/5)]:https://latex.codecogs.com/svg.image?T(\left&space;\lceil&space;\frac{n}{5}\right&space;\rceil)
[T(7n/10)]:https://latex.codecogs.com/svg.image?T(\frac{7n}{10})
[递推1]:https://latex.codecogs.com/svg.image?T(n)&space;=&space;T(\frac{7n}{10})&space;&plus;&space;T(\left&space;\lceil&space;\frac{n}{5}\right&space;\rceil)
[推导1]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant&space;&space;tn&space;&plus;&space;0.9tn&space;&plus;&space;0.9^{2}tn&space;&plus;&space;...\newline&space;=tn(1&space;&plus;&space;0.9&space;&plus;&space;0.9^{2}&space;&plus;&space;...)\newline&space;=\displaystyle&space;\lim_{i&space;\to&space;\infty&space;}&space;(tn&space;\times&space;1&space;\times&space;\frac{1&space;-&space;0.9^{i}}{1&space;-&space;0.9})\newline&space;=&space;10tn&space;\times&space;\displaystyle&space;\lim_{i&space;\to&space;\infty&space;}&space;(1&space;-&space;0.9^{i})\newline&space;=&space;10tn\newline&space;=&space;O(n)&space;
[递推2]:https://latex.codecogs.com/svg.image?T(n)&space;=&space;T(n&space;-&space;1)&space;&plus;&space;O(n)
[推导2]:https://latex.codecogs.com/svg.image?T(n)&space;=&space;T(1)&space;&plus;&space;n&space;\times&space;O(n)\newline&space;=&space;O(n^{2})&space;
[指示器]:https://latex.codecogs.com/svg.image?X_{k}
[含义]:https://latex.codecogs.com/svg.image?I\left\\{&space;A\left&space;[&space;p...q&space;\right&space;]\right\\}&space;
[推导3]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant&space;\sum_{k&space;=&space;1}^{n}X_{k}&space;\cdot&space;(T(max(k&space;-&space;1,n&space;-&space;k))&space;&plus;&space;O(n))\newline&space;=&space;\sum_{k&space;=&space;1}^{n}X_{k}&space;\cdot&space;T(max(k&space;-&space;1,n&space;-&space;k))&space;&plus;&space;O(n)&space;
[推导4]:https://latex.codecogs.com/svg.image?E\left&space;[&space;T(n)&space;\right&space;]&space;=&space;E\left&space;[&space;\sum_{k&space;=&space;1}^{n}X_{k}&space;\cdot&space;T(max(k&space;-&space;1,n&space;-&space;k))&space;&plus;&space;O(n)&space;\right&space;]\newline&space;=&space;\sum_{k&space;=&space;1}^{n}&space;E\left[&space;X_{k}&space;\cdot&space;T(max(k&space;-&space;1,&space;n-&space;k))\right]&space;&plus;&space;O(n)&space;\newline&space;=&space;\sum_{k&space;=&space;1}^{n}&space;E\left[&space;X_{k}&space;\right&space;]&space;\cdot&space;E\left&space;[&space;T(max(k&space;-&space;1,&space;n&space;-&space;k))&space;\right&space;]&space;&plus;&space;O(n)&space;
[定义1]:https://latex.codecogs.com/svg.image?E\left[&space;X_{k}\right]&space;=&space;\frac{1}{n}
[结论1]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant&space;\sum_{k&space;=&space;1}^{n}&space;\frac{1}{n}&space;\cdot&space;E\left[&space;T(max(k&space;-&space;1,&space;n&space;-&space;k))\right]&space;&plus;&space;O(n)
[结论2]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant\frac{2}{n}&space;\sum_{k&space;=&space;\left&space;\lfloor&space;n&space;/&space;2\right&space;\rfloor}^{n&space;-&space;1}&space;\cdot&space;E\left[&space;T(k)\right]&space;&plus;&space;O(n)
[推导5]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant\frac{2}{n}&space;\sum_{k&space;=&space;\left&space;\lfloor&space;n&space;/&space;2\right&space;\rfloor}^{n&space;-&space;1}&space;\cdot&space;E\left[&space;T(k)\right]&space;&plus;&space;O(n)\newline&space;\leqslant&space;\frac{2}{n}&space;\cdot&space;\sum_{k&space;=&space;\left&space;\lfloor&space;n&space;/&space;2\right&space;\rfloor}^{n&space;-&space;1}ck&space;&plus;&space;an\newline&space;=&space;\frac{2c}{n}&space;\cdot&space;(\sum_{k&space;=&space;1}^{n&space;-&space;1}ck&space;-&space;\sum_{k&space;=&space;1}^{\left&space;\lfloor&space;n&space;/&space;2\right&space;\rfloor})&space;&plus;&space;an&space;
[推导6]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant&space;\frac{2c}{n}&space;\cdot&space;(\frac{(n&space;-&space;1)n}{2}&space;-&space;\frac{(\frac{n}{2}&space;-&space;2)(\frac{n}{2}&space;-&space;1)}{2})&space;&plus;&space;an\newline&space;=&space;c(\frac{3n}{4}&space;&plus;&space;\frac{1}{2}&space;-&space;\frac{n}{2})&space;&plus;&space;an&space;
[推导7]:https://latex.codecogs.com/svg.image?T(n)&space;\leqslant&space;\frac{3cn}{4}&space;&plus;&space;\frac{c}{2}&space;&plus;&space;an\newline&space;=&space;cn&space;-&space;(\frac{cn}{4}&space;-&space;\frac{c}{2}&space;-&space;an)&space;
