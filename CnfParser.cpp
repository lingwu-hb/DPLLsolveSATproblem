//CnfParser.cpp
#include"Global.h"
int FunNum;//设置为全局变量，提供给main函数使用，用于记录cnf中变元个数
HeadNode* CnfParser(string& filename){//解析文件，返回头结点指针L
    string PATH = filename;
    ifstream fp(PATH);//注意：由于\符号本身为转义字符，所以需要两个此符号
    if(!fp){cout << "File can not open"; exit(0);}
    char ch;
    char exp[105];//exp:对cnf文件的解释explain
    fp >> ch;
    while(ch != 'p'){
        fp.getline(exp, 100);
        //注意：此处的exp只能是用c-string（数组），不能用string
        //详细解释:n:Pointer to an array of characters where extracted characters are stored as a c-string.
        fp >> ch;
    }
    string cnf; int ClauseNum;//分别存储CNF、变元个数、子句个数。
    fp >> cnf >> FunNum >> ClauseNum;
    //测试用例：cout << ClauseNum << " " << FunNum << endl;
    //下面循环将所有的子句读入到设计好的数据结构中
    HeadNode* L = new HeadNode;//L为HeadNode结点的头结点
    L->num = ClauseNum;//字句个数（也就是有多少行）
    HeadNode* pH = new HeadNode; L->down = pH; pH->down = nullptr;//L中num表示有多少行
    for(int i = 1; i <= ClauseNum; i++){
        int tep;
        fp >> tep;
        DataNode* p = new DataNode;
        p->value = tep; pH->right = p; pH->num++; p->next = nullptr;
        fp >> tep;
        while(tep){
            p = new DataNode;
            p->value = tep;//采用头插法建立链表
            p->next = pH->right;
            pH->right = p;
            pH->num++;
            fp >> tep;
        }
        if(i != ClauseNum){
            pH = new HeadNode;
            pH->down = L->down;
            L->down = pH;
        }
        //fp.get();//get掉换行符
    }
    fp.close();//关闭文件流
    
    //将解析后的cnf文件进行输出表示，用于进行代码块测试
    /*HeadNode* _pH = L->down;

    while(_pH){
        DataNode* _p = _pH->right;
        while(_p->next){
            cout << _p->value << " ";
            _p = _p->next;
        }
        cout << _p->value << endl;
        _pH = _pH->down;
    }
    */

    return L;
}