//OutFile.cpp
#include"Global.h"

void OutFileFun1(string _PATH, bool suc, int* book, int _Ctime, int FunNum, int cod){
    ofstream op(_PATH);
    if(!op){
        cout << "OutFile can not open!" << endl;
        exit(0);
    }
    op << "s " << suc << endl;//结果
    if(suc){
        op << "v";
        for(int i = 1, k = 1; i <= FunNum; i++){
            op << " " << book[i]*i;
            k++;
            if(k == 10) {op << endl; k = 1;}
        }
        op << endl;
    }
    if(cod == 1) op << "t " << _Ctime << "ms";
    op.close();

    //c语言版本的文件输出
    // char *_path = new char[_PATH.length()+1];
    // strcpy(_path, _PATH.c_str());
    // FILE *op = fopen(_path, "w");
    // if(!op){
    //     printf("OutFile can not open!\n");
    //     exit(0);
    // }
    // fputc('c', op);
    // fprintf(op, " %d\n", suc);
    // if(suc){
    //     fputc('v', op);
    //     for(int i = 1, k = 1; i <= FunNum; i++){
    //         fprintf(op, " %d\n", book[i]*i);
    //         k++;
    //         if(k == 10){ fprintf(op, "\n"); k =1;}
    //     }
    //     fprintf(op, "\n");
    // }
    // fprintf(op, "t %d\nms", _Ctime);
}