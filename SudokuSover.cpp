//SudokuSover.cpp
#include "Global.h"

#define CORRECT 0
#define WRONG -1
static int T = 0;

//根据holes来挖洞
//此函数输出数独初盘，同时返回解析后的.cnf文件
string createSudokuToFile(int holes, int array[ROW][COL]) {
    int sudoku[ROW][COL]={0};
    int starting_grid[ROW][COL]={0};
    createSudoku(sudoku);//生成数独终盘
    createStartinggrid(sudoku,starting_grid,holes);//生成初盘
    memcpy(array, starting_grid, ROW*COL*sizeof(int));
    cout << "初始化后数独初盘为：" << endl;
    print(starting_grid);//输出初盘
    //转化为cnf文件
    string filename = ToCnf(starting_grid,holes);
    return filename;
}

int Digit(int a[][COL], int i, int j) {//递归填充数独元素
    if (i < ROW && j < COL) {
        int x,y,k;
        int check[COL+1]={CORRECT};//用于排除已经使用过的的数字
        for(x = 0 ; x < i ; x++)
            check[a[x][j]] = WRONG;//列已使用的数字置为WRONG
        for(x = 0 ; x < j ; x++)
            check[a[i][x]] = WRONG;//行使用过的数字置为WRONG
        for(x = i/3*3 ; x <= i; x++) {
            if(x == i)
                for(y = j/3*3 ; y < j; y++)
                    check[a[x][y]] = WRONG;
            else
                for(y = j/3*3 ; y < j/3*3 + 3; y++)
                    check[a[x][y]] = WRONG;
        }

        int flag = 0;
        for(k = 1; k <= COL && flag == 0 ; k++){//从check数组中查找安全的数字
            if(check[k] == CORRECT){
                flag = 1;
                a[i][j] = k;
                if(j == COL-1 && i != ROW-1){
                    if(Digit(a,i+1,0) == CORRECT) return CORRECT;
                    else flag = 0;
                }
                else if(j != COL-1){
                    if(Digit(a,i,j+1) == CORRECT) return CORRECT;
                    else flag = 0;
                }
            }
        }
        if( flag == 0 ) {
            a[i][j] = 0;
            return WRONG;
        }
    }
    return CORRECT;
}

void randomFirstRow(int a0[], int n) {//随机生成第一行
    int i,j;
    srand((unsigned)time(nullptr));
    for( i = 0 ; i < n ; i++){
        a0[i] = rand()%9 + 1;
        j = 0 ;
        while(j < i){
            if(a0[i] == a0[j]){
                a0[i] = rand()%9 + 1;
                j = 0;
            }
            else j++;
        }
    }
}

void createSudoku(int a[][COL]){ //生成数独
    randomFirstRow(a[0],COL);//随机生成第一行
    Digit(a,1,0);//递归生成后i行
}

void createStartinggrid(const int a[][COL], int b[][COL], int numDigits) {//随机生成初盘
    int i,j,k;
    srand((unsigned)time(nullptr));
    for( i = 0; i < ROW ; i ++)
        for( j = 0; j < COL ; j++)
            b[i][j] = a[i][j];

    //int c[numDigits][2];//此处可以采用c++中的new动态为二维数组分配内存
    int** c = new int* [numDigits];
    for(int i = 0; i < numDigits; i++){
        c[i] = new int [2];
    }
    int m,flag = 0;

    for( i = 0; i < numDigits ; i++) {
        j = rand()%9;
        k = rand()%9;

        flag = 0;
        for(m = 0; m < i ; m++)
            if( j == c[m][0] && k == c[m][1])
                flag = 1;

        if(flag == 0){
            b[j][k] = 0;
            c[i][0] = j;
            c[i][1] = k;
        }
        else
            i--;
    }
}

void print(const int a[][COL]){//打印数独数组
    int i,j;
    for( i = 0 ; i < ROW ; i++){
        for( j = 0 ; j < COL ; j++)
            printf("%d ", a[i][j]);
        cout<<endl;
    }
}

string ToCnf(int a[][COL],int holes) {
    ofstream in (".\\sudoku.cnf");//定义输入文件
    if(!in.is_open())
        cout<<"can't open!\n";
    in<<"p"<<" "<<"cnf"<<" "<<729<<" "<<8829+81-holes<<" "<<endl;
    //single clause
    for (int x = 0; x < ROW; ++x) {
        for (int y = 0; y < COL; ++y)
            if(a[x][y] != 0)
                in<<(x+1)*100 + (y+1)*10 + a[x][y]<<" "<<0<<endl;
    }
    //entry
    for (int x = 1; x <= 9; ++x) {
        for (int y = 1; y <= 9; ++y) {
            for (int z = 1; z <= 9; ++z)
                in << x * 100 + y * 10 + z << " ";
            in<<0;
            in<<endl;
        }
    }
    //row
    for (int y = 1; y <= 9; ++y) {
        for (int z = 1; z <= 9; ++z)
            for (int x = 1; x <= 8; ++x)
                for (int i = x+1; i <= 9; ++i)
                    in<<0 - (x*100 + y*10 + z)<<" "
                      <<0 - (i*100 + y*10 + z)<<" "<<0<<endl;
    }
    //column
    for (int x = 1; x <= 9; ++x) {
        for (int z = 1; z <=9 ; ++z)
            for (int y = 1; y <= 8; ++y)
                for (int i = y+1; i <= 9; ++i)
                    in<<0-(x*100 + y*10 + z)<<" "
                      <<0-(x*100 + i*10 + z)<<" "<<0<<endl;
    }
    //3*3 sub-grids
    for (int z = 1; z <= 9 ; ++z) {
        for (int i = 0; i <=2 ; ++i)
            for (int j = 0; j <=2 ; ++j)
                for (int x = 1; x <= 3 ; ++x)
                    for (int y = 1; y <= 3; ++y)
                        for (int k = y+1; k <= 3; ++k)
                            in<<0 - ((3*i+x)*100 + (3*j+y)*10 + z)<<" "
                              <<0-((3*i+x)*100 + (3*j+k)*10 + z)<<" "<<0<<endl;
    }
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int x = 1; x <= 3; x++)
                    for (int y = 1; y <= 3; y++)
                        for (int k = x + 1; k <= 3; k++)
                            for (int l = 1; l <= 3; l++)
                                in << 0 - ((3*i+x)*100 + (3*j+y)*10 + z) << ' '
                                   << 0 - ((3*i+k)*100 + (3*j+l)*10 + z) << ' ' << 0 <<endl;
    }
    in.close();
    return ".\\sudoku.cnf";//返回一个string类型的对象
}