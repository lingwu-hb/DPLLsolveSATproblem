#include "Global.h"
extern int FunNum;
int zeroNum;
int isBetter;
int main() {
    display();
    int cod = 0;
    string filename;
    cin >> cod;
    while (cod){
        if(cod == 1){//cnf解析求解
            cout << "请输入需要解析的.cnf文件。（例如：.\\src\\Sat\\S\\problem1-20.cnf）" <<endl;
            cin >> filename;
            cout << "请选择是否使用优化的算法" << endl;
            cout << "0--未优化" << endl; cout << "1--优化" << endl;
            cin >> isBetter;
            HeadNode* L = CnfParser(filename);
            int temp[9][9];
            CoreFun(L, filename, FunNum, cod, temp);
        }
        else if(cod == 2){//数独问题求解
            cout << "请输入数独初盘中设定数字的个数：（不少于17，不大于81）" << endl;
            int preNum; cin >> preNum; zeroNum = 81-preNum;
            int array[ROW][COL] = {0};
            filename = createSudokuToFile(zeroNum, array);
            HeadNode* L = CnfParser(filename);
            //printList(L);
            CoreFun(L, filename, 1000, cod, array);
            /*
            设计用户交互的部分
            请求用户输入填一个空，并指明填写的数字格式以及对应意义
                读入的数字为零，直接退出程序
                将用户输入的数字与book中的数进行比对，查看是否正确
                如果不正确的话，显示错误重新输入
                正确的话，就读入数字，然后把用户输入的地方的那个数字修改之后把数独表打印出来显示给用户
            如果数独中空元的个数为零，通知用户成功过关，并询问是否可以再次重新开始游戏
            */
        }
        else if(cod == 3){
            cout << "请输入待检验的文件名（例如：.\\src\\Sat\\S\\problem1-20.cnf）" << endl;
            cin >> filename;
            if(isCorrect(filename)) {cout << "输出的结果没问题" << endl;}
            else {cout << "输出的结果不对" << endl;}
        }
        display();
        TestNum = 0;
        cin >> cod;
    }
}

void CoreFun(HeadNode* L, string& filename, int FunNum, int cod, int array[ROW][COL]){

    //文件输出准备部分
    string _PATH = filename.replace(filename.end()-4, filename.end(), ".res");
    bool suc;
    int *book = new int[FunNum];
    memset(book, 0, sizeof(int)*FunNum);
    int begin = 0, end = 0;

    //DPLL()核心处理部分
    begin = clock();
    bool isTrue;
    if(!isBetter) {isTrue = DPLL(L, book);}
    else {isTrue = NewDPLL(L, book);}
    if(isTrue) {suc = TRUE;}
    else {suc = FALSE;}
    if(cod == 1){
        if(isTrue) {cout << "为真" << endl;}
        else {cout << "为假" << endl;}
        end = clock();

        cout << "DPLL()部分运行的时间为" << end-begin << "ms" << endl;
    }
    else{
        end = clock();
        cout << "DPLL()部分运行的时间为" << end-begin << "ms" << endl;
        cout << "数独游戏开始，您可以随时输入0以终止游戏" << endl;
        while(zeroNum){//如果还有空元
            cout << "请输入您填入的下一个数字，111表示在第一行第一列填入数字1" << endl;
            int opeNum; cin >> opeNum;
            int x = opeNum/100 - 1; int y = (opeNum/10)%10 - 1;
            if(!opeNum){exit(0);}
            if(book[opeNum] > 0 && array[x][y] == 0){
                array[x][y] = (opeNum%100)%10;
                zeroNum--;
                print(array);
                cout << "填入成功，请填写下一个" << endl; 
            }
            else{
                cout << "输入的数字不正确！" << endl;
                continue;
            }
        }
        cout << "游戏结束，恭喜您成功过关！" << endl;
    }
    //输出.res文件
    OutFileFun1(_PATH, suc, book, end-begin, FunNum, cod);
}