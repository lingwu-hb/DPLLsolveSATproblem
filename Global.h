//Global.cpp
#ifndef Global_H
#define Global_H
#include<iostream>
#include<fstream>
#include<ctime>
#include<cmath>
#include<stack>
#include<string>
#include<cstring>
#define TRUE 1
#define FALSE 0
#define NOMAL -1
#define ROW 9
#define COL 9
#define NoAnwser -1
typedef int status;
using namespace std;

static int TestNum = 0;//用于测试变量

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

HeadNode* CnfParser(string& filename);
void display();
bool DPLL(HeadNode* L, int* book);//核心算法部分
bool NewDPLL(HeadNode* L, int* book);
int SingleSpread(HeadNode* L, int* book);
int isHaveSingleClause(HeadNode* L);
void SimplifyCnf(HeadNode* L, int SC);
bool isemptyCnf(HeadNode* L);
bool isHaveEmptyClause(HeadNode* L);
HeadNode* merge(HeadNode* L, int v);
int SelectWord(HeadNode* L);
int SelectWord2(HeadNode* L);
void OutFileFun1(string _PATH, bool suc, int* book, int _Ctime, int FunNum, int cod);
void printList(HeadNode* L);
HeadNode* CopyList(HeadNode* L);
void FreeList(HeadNode* L);

int Digit(int a[][COL], int i, int j);
void randomFirstRow(int a0[], int n);
void createSudoku(int a[][COL]);
void createStartinggrid(const int a[][COL], int b[][COL], int numDigits);
void print(const int a[][COL]);
string ToCnf(int a[][COL],int holes);
string createSudokuToFile(int holes, int array[ROW][COL]);

void CoreFun(HeadNode* L, string& filename, int FunNum, int cod, int array[ROW][COL]);
bool isCorrect(string& filename);

#endif