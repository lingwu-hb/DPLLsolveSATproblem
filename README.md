# 2020级课程设计DPLL算法解决SAT问题

## 计算机学院2020级数据结构课程设计任务项目

分为一下几个部分，详细内容见word文档
* 1.cnf解析
打开文件，逐行读入数据，将数据依次保存在链表中。
CnfParser()函数返回值为存储完毕的数据结构的头指针L

* 2.用户交互部分
用户进行选择1、2或者3，可以用if语句分部分进行处理。

* 3.算法执行部分，核心算法DPLL算法的实现
分为优化前的和优化（非递归）后的不同算例

* 4.数独部分
分为数独生成、随即挖洞、用户交互等部分

* 5.将结果输出到输出文件，完成整个项目代码部分

* 6.书写实验报告

## 预备知识了解
### 变元、文字、子句、CNF范式等概念
* 变元：布尔变元，可以取真假值
* 文字：布尔变元及其非称为文字
* 子句：若干个文字的或运算被称为子句
* CNF范式：若干个子句的合取被称为CNF范式，即合取范式
### DPLL算法
1）全称：Davis-Putnam-Logemann-Loveland

2）思想：基于树/二叉树的回溯搜索算法，主要基于两种策略。

* 单子句规则：如果一个CNF范式中存在单子句L（含有一个文字的子句），取L为真值。通过L的值，遍历其他的子句：

	如果某个子句中含有L，**则将这个子句从范式中去掉**（子句没了）

	如果某个子句中含有-L（L的非），**则将-L从这个子句中去掉**（文字没了）

	处理完之后，如果范式为空，则该范式为真；如果范式中含有空子句，则该范式为假。

* 分裂策略：如果一个范式S中不存在单子句。则按照某种方式选取一个变元v，假设v为真值和假值，然后重复单子句规则。（算法的复杂度和是否高效取决于选择变元的策略）

```cpp
//伪代码：
bool DPLL(范式S){
	while(S中有单子句L){
		for(子句P in S){
			if(P中有L) 去掉P;
			else if(P中有-L) 去掉-L;
		}
		for循环执行完毕之后，S化简为S1
		if(S1 为空) return TRUE;
		else if(S1 中含有空子句) return FLASE;
	}
	按照某种策略选择变元v;
	if(DPLL(S∪v)) return TRUE;
	//递归回溯部分
	else return DPLL(S∪-v);
}
```

注意：既然是递归算法，自然要注意几个重要的点。其中有一个就是要记得你写的递归是否需要回溯。如果需要回溯，那些中间变量以及标记变量都需要及时回溯。（在传指针的时候尤其需要注意！！！）

## 算法设计实现
### 程序编译
* 使用vsCode编译器作为代码的编译运行编辑器，然后在终端中用c++进行编译运行即可。

```cpp
命令部分：
g++ main.cpp main.exe
main.exe
```

* 编译多个文件时的命令为：

```cpp
g++ CnfParser.cpp display.cpp DPLL.cpp OutFile.cpp SudokuSover.cpp isCorrect.cpp main.cpp -o main
main.exe

//打开范例文件名：7cnf20_90000_90000_7.shuffled-20.cnf
Standard\functional_test\sat-20.cnf
```


### 数据结构部分
* 采用链表的形式存储。每个子句的第一个文字为链表的头节点，然后其他文字作为其他结点。
* 循环读入数据建立链表时一定要注意：头结点中不含有value，只有子句中文字的个数num。不要在头结点中也加入value，这样会让自己不好写循环的最终结束判断条件。

```cpp
//每个结点的数据类型，value表示文字的内容，next指向同一个子句中的下一个文字
typedef struct DataNode{
    int value = 0;
    struct DataNode* next;
}DataNode;

typedef struct HeadNode{
    int num = 0;
    struct HeadNode* down;//头结点向下
    struct DataNode* right;//同一个子句中结点向右指针
}HeadNode;

```

### 具体实现细节
* c++中的数组动态分配内存

```cpp
//由于不允许使用vector，所以可以尝试使用new[]为数组动态分配内存
int* a = new int[2000];

//用完之后也可以进行释放
delete [] a;
```

* 为了实现动态分配book数组的内存，采用在CnfParser.cpp文件中定义全局变量FunNum。然后在mian.cpp文件中使用extern int FunNum进行引用，从而实现在main.cpp中进行动态分配内存。

### 保存结果进行输出部分
目的：掌握ofstream中的常用方法，并能够熟练使用。

常用方法：

```cpp
ofstream op("Text.txt");
//或者采用open方法打开文件
ofstream op.open("Text.txt");
if(!op){cout << "文件无法打开" << endl;}

//常用输出方法
char ch = 'a';
op << ch;
op.put(ch);//与上面那个作用相同
```

### DPLL算法的优化策略
#### 时间复杂度优化
1）最短子句优先原则

从子句中选择最短的子句，选择最短子句中的文字进行赋值处理。以便更快得到单子句，从而快速进入单子句扩散策略。简化算法时间复杂度。

2）递归改为非递归

#### 空间复杂度优化策略
由于算法还未改成非递归，目前还是应用的递归算法。但是由于递归算法会额外生成很多空间用于递归函数的准备以及递归状态的保存，当输入规模比较大的时候，容易产生内存爆炸问题。

对于递归函数运行前的准备过程，除非改为非递归，用同一片地址运行函数。否则无法优化。

但是对于为了保存递归状态的变量来说，是可以即时释放内存的。例如第 i 层的函数保存了temL，用于记录状态。当函数从第 i+k 层（k未知）退回到第 i 层时，可以在退回到第 i-1 层之前即时将temL给释放掉，如此便能省下很多内存空间。代码如下

```cpp
bool DPLL(HeadNode* L, int* book){
    int SC;//存储单子句(SingleClause的缩写)
    //cout << ++TestNum << endl;
    //printList(L);
    while(SC = isHaveSingleClause(L)){
        //cout << "2-" << TestNum << " 本次循环要删除的为:" << SC << endl;
        if(SC > 0) book[SC] = 1;
        else if(SC < 0) book[0-SC] = -1;//例如：book[-(-2)] = -1表示2代表的变元取负值，即-2
        SimplifyCnf(L, SC);//根据单子句传播策略简化单子句
       //printList(L);
        if(isemptyCnf(L)) return TRUE;
        else if(isHaveEmptyClause(L)) return FALSE;
    }
    //int v = SelectWord(L);
    int v = SelectWord2(L);//采用最短子句优先选取规则进行选取变元
    //cout << "这次选取的变元为：" << v << endl;
    HeadNode* temL = CopyList(L);
    if(DPLL(merge(L, v), book)) return TRUE;
    bool result = DPLL(merge(temL, 0-v), book);
    //删除temL的内容空间
    FreeList(temL);
    return result;
}
```
