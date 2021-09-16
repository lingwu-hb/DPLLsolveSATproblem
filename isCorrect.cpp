//isCorrect.cpp
#include"Global.h"
extern int FunNum;
bool verification(HeadNode* ordL, int* book);
//验证根据DPLL算法生成的文件是否正确
bool isCorrect(string& filename){
    HeadNode* L = CnfParser(filename);
    HeadNode* ordL = CopyList(L);

    int _FunNum = FunNum>1000? FunNum: 1000;
    int *book = new int[_FunNum];
    memset(book, 0, sizeof(int)*_FunNum);

    int isTrue = NewDPLL(L, book);
    if(!isTrue){cout << ".cnf文件不可满足"; exit(0);}
    else{
        if(verification(ordL, book)) return TRUE;
        else return FALSE;
    }
}
/*
解析文件，生成链表L，同时拷贝一份不会改变的ordL;（不会改变的L）
执行DPLL算法，生成.res文件
如果DPLL算法返回为假，直接退出就行，为真进行下一步
直接遍历ordL结构，访问book对应的文字的值
如果有一个子句的所有的文字都不会满足，那么该解就是有问题
*/
bool verification(HeadNode* ordL, int* book){
    HeadNode* _pH = ordL->down;
    while(_pH){
        DataNode* _p = _pH->right;
        while(_p){
            if(book[abs(_p->value)]*_p->value > 0) break;
            _p = _p->next;
        }
        if(!_p) return FALSE;
        _pH = _pH->down;
    }
    return TRUE;
}