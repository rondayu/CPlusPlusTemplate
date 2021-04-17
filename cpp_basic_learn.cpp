// C++ 入门
// https://github.com/AnkerLeng/Cpp-0-1-Resource/blob/master

#include <iostream> //输入输出，含有std类，需要预处理
#include <cstring>
// 或使用iosstream.h，但这个不含有std类，含有cin和cout，不需要使用命名空间
using namespace std;
//std类预处理，否则要在接口前添加std::调用命名空间std内定义的所有标识符
/* 
std::basic_string 和 std::__1::basic_string
是两种数据结构  data structure
对于链接器 linker 而言，分别对应: gcc's libstdc++ 和 libc++
 https://stackoverflow.com/questions/8454329/why-cant-clang-with-libc-in-c0x-mode-link-this-boostprogram-options-examp
 libc++ is not binary compatible with gcc's libstdc++ (except for some low level stuff such as operator new). 
 For example the std::string in gcc's libstdc++ is refcounted, whereas in libc++ it uses the "short string optimization". 
 If you were to accidentally mix these two strings in the same program (and mistake them for the same data structure), you would inevitably get a run time crash.

 In order to turn this run time crash into a link time error, 
 libc++ uses a C++11 language feature called inline namespace to change the ABI of std::string without impacting the API of std::string. 
 That is, to you std::string looks the same. But to the linker, std::string is being mangled as if it is in namespace std::__1. 
 Thus the linker knows that std::basic_string and std::__1::basic_string are two different data structures (the former coming from gcc's libstdc++ and the latter coming from libc++).
*/

//宏常量
#define day 7

/*
    结构体：自定义数据类型      
    3种创建方式
        1. 定义时关键字 struct 不可省略
        2. 创建时，关键字 struct 可省略
        3. 结构体变量利用操作符“.”访问成员变量 
*/
struct student //关键字struct不可省略
{
    //成员变量
    string name;
    int age;
    int score;
} stu3; //stu3 为创建方式3

/**
 * 结构体嵌套结构体
 */
struct teacher
{
    int id;
    string name;
    int age;
    struct student stu;
};

/**
 * 结构体做函数参数
 * 1. 值传递   为形参， 不影响实参
 * 2. 地址传递
*/
// 值传递
void printStu(student stu)
{
    stu.age = 1;
    //链式编程
    cout << "子函数中 姓名：" << stu.name << " 年龄： " << stu.age << " 分数：" << stu.score << endl;
}
// 地址传递
void printPointStu(student *stu)
{
    stu->age = 2;
    cout << "子函数中 姓名：" << stu->name << " 年龄： " << stu->age << " 分数：" << stu->score << endl;
}

/**
 * 结构体中 const 使用场景
 * 若改为指针常量，则不可修改变量，可以修改变量值，这跟不添加const一样
 * 使用常量指针，则可修改变量不可修改变量的值，但修改为局部变量无意义
*/
void printStuConst(const student *stu)  //常量指针 加const防止函数体中的误操作
{
    //stu->age = 100; //操作失败，因为加了const修饰
	cout << "姓名：" << stu->name << " 年龄：" << stu->age << " 分数：" << stu->score << endl;
}

/*
    冒泡排序
    1. 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
    2. 对每一对相邻元素做同样的工作，执行完毕后，找到第一个最大值。
    3. 重复以上的步骤，每次比较次数-1，直到不需要比较
*/
void bubbleSort(int *arr, int len)
{
    for (size_t i = 0; i < len - 1; i++)
    {
        for (size_t j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 数组名传入退化为指针，可以修改实参
void printArray(int arr[], int len)
{
    for (int i = 0; i < 9; i++)
    {
        cout << endl;
        if (i == 8)
        {
            arr[i] = 101;
        }
        cout << arr[i] << " ";
    }
}


int main()
{ //定义输出int main的输出要求为int
    /*
    /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1 
    c++/v1/iostream/std
    */
    //std::__1::ostream::std::__1::cout     __1表v1版本
    //std输入输出标准类，包括cin和cout
    cout << "Hello world" << endl; //cout 输出，<< 为输出运算符，
    //endl表结束此行，换行且同时对缓冲流进行冲刷，使得流中所有剩余字符被写入输出序列

    // C++  强类型，必须声明数据类型，才能分配内存
    //变量, 可修改，必须有初始值
    int a = 10;

    //常量，不可更改
    // #define 宏常量，位于文件上方定义
    // const 加在变量定义之前，指该变量不可修改
    const int month = 12;

    //关键字    C++ 预留单词（标识符）  关键字表
    /* 标识符（变量常量）命名规则：
        1. 不可使用关键字
        2. 只能用字母、数字、下划线组成
        3. 第一个字符为字母或下划线
        4. 区分大小写
        建议起到 见名知意 效果的命名
    */

    //数据类型
    /*            短整型   整型    长整型   长长整型
        整型：整数，short < int <= long <= long long
                    2      4      4/8         8
    */
    //sizeof 统计 内存大小
    cout << sizeof(int) << endl;

    /*
        浮点型：单精度 float        双精度 double
                    4                 8
                7位有效数字        15-16位有效数字
    */
    float f1 = 3.14f;
    double d1 = 3.14;

    cout << f1 << endl;
    cout << d1 << endl;
    cout << "float  sizeof = " << sizeof(f1) << endl;
    cout << "double sizeof = " << sizeof(d1) << endl;
    // 科学记数法
    float f2 = 3e2; // 3 * 10 ^ 2
    cout << "f2 = " << f2 << endl;

    float f3 = 3e-2; // 3 * 0.1 ^ 2
    cout << "f3 = " << f3 << endl;

    // 字符型：显示单个字符
    /*
        1. 单引号
        2. 只能一个字符，不能是字符串
        3. 1个字节
        4. 字符变量的存储内容在字符对应的ASCII码
    
    ASCII表
    ASCII码：	0-255表示256个字符
        前128：常见字符 非打印控制字符0-31  和  打印字符 32-126
        后128：特殊字符
    转义字符：\a警报（007）、\b退格(008)、\f换页（012）、\n换行（010）、
            \r回车（013）、\t水平制表（009）、\v垂直制表（011）、\\反斜线（092）、
            '单引号字符（039）、''双引号字符（034）、?问号（063）、\0数字0（000）、
            \ddd（3位8进制，8位转义字符，d范围0～7）、
            \xhh（3位16进制，16进制转义字符，h范围A-F）
    */
    char ch = 'a';
    cout << ch << endl;
    cout << (int)ch << endl; // 查看ASCII码

    // 字符串型
    //1. C风格字符串  使用双引号
    char str1[] = "hello world";
    //2. C++风格字符串  导入头文件 #include<string>
    string str = "hello world";

    /* 
    布尔类型 bool    真 true 1，假 false 0
        1个字节
    */
    bool flag = true;
    cout << flag << endl; //1

    /*
    数据的输入    从键盘获取数据
    关键字 cin
    */
    cout << "请输入整型变量：" << endl;
    cin >> a;
    cout << a << endl;

    /*
        运算符
        算术运算符：+正、-负、+、-、*、/、%（取模/取余）、++（前置或后置）、--（前置或后置）
                1. 除数不可为0
                2. 只有整型变量可以进行取模运算
                3. java中取模mod（商取小原则）、取余rem（商靠0原则）
        赋值运算符： =、+=、-+、*=、/=、%=
        比较运算符：==、!=、<、>、<=、>=
        逻辑运算符：!、&&、||
    */

    /*
    程序流程结构
    顺序结构：按顺序不跳转
    选择结构    
        if（单行格式 if{}，多行格式 if{}else{}，多条件 if{}elif{}else{}）
        三目运算符：a>b?a:b;
        switch 语句：结构清晰，执行效率高，缺点：不可以判断区间
    循环结构：
        while循环语句： while(){}, 必须提供跳出循环的出口，否则死循环
        do...while循环语句： do{}while(); 先做一遍再判断
        for循环语句： for(; ;){}
        嵌套循环
    
    跳转语句：
        break 语句： switch中，循环语句中，嵌套循环中跳出一层
        continue语句：跳过剩余未执行的语句，没有终止循环，break才终止
        goto语句：无条件跳转，不建议使用，流程易混乱
    */

    //三目运算，C++中三目运算符返回的是变量,可以继续赋值
    int b = 0;
    (a > b ? a : b) = 100;

    // switch 语句
    switch (a)
    { // (表达式) 只能是整型或者字符型
    case 10:
        cout << "经典" << endl;
        break; // 没有break则执行下去
    case 5:
        cout << "一般" << endl;
        break;
    default:
        cout << "烂" << endl;
        break;
    }

    //goto
    cout << "1" << endl;
    goto FLAG;
    cout << "2" << endl;
    cout << "3" << endl;
    cout << "4" << endl;
FLAG:
    cout << "5" << endl;

    /*
    数组，集合
        1. 相同类型的数据元素
        2. 连续的内存
        3. 从0开始索引
    一维数组， 一维数组名：1. 整个数组的内存中的长度，2. 数组在内存中的首地址
    二维数组， 二维数组名：1. 二维数组内存空间大小  2. 首地址
    */
    //一维数组      3种定义方式
    int score[10];
    int score1[10] = {1, 2};
    int score2[] = {1, 2};

    //数组名用途
    //1、可以获取整个数组占用内存空间大小
    cout << "整个数组所占内存空间为： " << sizeof(score1) << endl;
    cout << "每个元素所占内存空间为： " << sizeof(score1[0]) << endl;
    cout << "数组的元素个数为： " << sizeof(score1) / sizeof(score1[0]) << endl;

    //2、可以通过数组名获取到数组首地址
    // int p = (int)score1;
    cout << "数组首地址为： " << &score1 << endl;
    cout << "数组中第一个元素地址为： " << &score1[0] << endl;
    cout << "数组中第二个元素地址为： " << &score1[1] << endl;

    int arr[] = {4, 2, 8, 0, 5, 7, 1, 3, 9};
    int len = sizeof(arr) / sizeof(arr[0]);
    //当数组名传入到函数作为参数时，被退化为指向首元素的指针
    bubbleSort(arr, len);
    printArray(arr, len);

    // 二维数组     4种定义方式
    int arr1[2][3];
    arr1[0][0] = 1;
    int arr2[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};
    int arr3[2][3] = {1, 2, 3, 4, 5, 6};
    int arr4[][3] = {1, 2, 3, 4, 5, 6};

    cout << "二维数组大小： " << sizeof(arr2) << endl;
    cout << "二维数组一行大小： " << sizeof(arr2[0]) << endl;
    cout << "二维数组元素大小： " << sizeof(arr2[0][0]) << endl;

    cout << "二维数组行数： " << sizeof(arr2) / sizeof(arr2[0]) << endl;
    cout << "二维数组列数： " << sizeof(arr2[0]) / sizeof(arr2[0][0]) << endl;

    //地址
    cout << "二维数组首地址：" << arr2 << endl;
    cout << "二维数组第一行地址：" << arr2[0] << endl;
    cout << "二维数组第二行地址：" << arr2[1] << endl;

    cout << "二维数组第一个元素地址：" << &arr2[0][0] << endl;
    cout << "二维数组第二个元素地址：" << &arr2[0][1] << endl;

    /*
        指针，间接访问内存，指定数据类型
        1. 内存编号是从0开始记录的，一般用十六进制数字表示
        2. 可以利用指针变量保存地址
        普通变量：存数据，通过&获取变量地址
        指针变量：存地址，解引用：通过*操作符操作指针指向内存空间
        所有指针类型在32位操作系统下是4个字节

        空指针： 1. 指向编号为0的空间。
                2. 初始化指针变量，
                3. 空指针指向的内存不可访问
        野指针：指针变量指向非法的内存空间
        
        空指针和野指针都不是我们申请的空间，因此不要访问

        const 修饰指针： 
                1. const修饰指针----常量指针    可改变为不同变量的地址，但不允许通过*操作符修改变量的值
                2. const修饰常量----指针常量    永远指向初始化定值后的变量的地址，但可以通过*操作符修改变量的值
                3. const即修饰指针，又修饰常量   既不可以修改指向变量，也不可通过指针*操作符操作修改变量的值

        指针和数组：数组名==指针
        指针和函数：  1. 利用指针作函数参数，可以修改实参的值，
                    2. 如果不想修改实参，就用值传递，如果想修改实参，就用地址传递

        当数组名传入到函数作为参数时，被退化为指向首元素的指针

    */
    int *pointer_int = &b;
    cout << pointer_int << endl;
    pointer_int = &a;
    cout << "a:" << a << endl;
    cout << "&a:" << &a << endl;
    cout << "pointer_int:" << pointer_int << endl;
    cout << "*pointer_int:" << *pointer_int << endl;
    *pointer_int = 0;
    cout << "*pointer_int:" << *pointer_int << endl;
    cout << "a:" << a << endl;

    //空指针
    //内存编号0 ~255为系统占用内存，不允许用户访问
    int *pointer_NULL = NULL;
    //cout << *pointer_NULL << endl; //访问会报错

    //野指针
    //指针变量p指向内存地址编号为0x1100的空间
    int *pointer_dangling = (int *)0x1100;
    // cout << *pointer_dangling << endl;   //访问野指针报错

    a = 100;
    b = 99;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    cout << "&a:" << &a << endl;
    cout << "&b:" << &b << endl;
    // const修饰指针---常量指针
    const int *p1 = &a;
    cout << "p1:" << p1 << endl;
    cout << "*p1:" << *p1 << endl;
    p1 = &b; //可以修改指针指向，
    // *p1 = 101;    //但不可以修改存储值
    // a = 101;
    cout << "p1:" << p1 << endl;
    cout << "*p1:" << *p1 << endl;

    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    cout << "&a:" << &a << endl;
    cout << "&b:" << &b << endl;
    // const修饰常量---指针常量
    int *const p2 = &a;
    cout << "p2:" << p2 << endl;
    cout << "*p2:" << *p2 << endl;
    //p2 = &b;    //不可以修改指针指向
    *p2 = 101; //可以修改存储值;
    cout << "p2:" << p2 << endl;
    cout << "*p2:" << *p2 << endl;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    cout << "&a:" << &a << endl;
    cout << "&b:" << &b << endl;
    // const修饰指针和常量
    const int *const p3 = &a; // 指针指向和存储值都不可以修改

    // 指针和数组
    int *pointer_arr = arr;
    cout << "第一个元素" << arr[0] << endl;
    cout << "指针访问第一个元素：" << *pointer_arr << endl;

    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0] - 1); i++)
    {
        cout << "第" << i << "个元素：" << *pointer_arr << endl;
        pointer_arr++; // 指针等效数组，每++移动一个元素的位置，指向下一个元素的首地址
    }

    // 结构体
    // 创建方式1
    struct student stu1;
    student stu4; //struct可省略
    stu1.name = "zhangsan";
    stu1.age = 18;
    stu1.score = 100;
    // 创建方式2
    struct student stu2 = {"lisi", 20, 90};
    //创建方式3
    stu3.name = "wangwu";
    stu3.age = 18;
    stu3.score = 70;

    /**
     * 结构体数组   将自定义的结构体放入数组中方便维护
    */
    struct student stu_arr[3] =
        {
            {"zhangsan", 18, 80},
            {"lisi", 19, 60},
            {"wangwu", 20, 90}};

    for (size_t i = 0; i < 3; i++)
    {
        cout << "name:" << stu_arr[i].name << " age:" << stu_arr[i].age << " score:" << stu_arr[i].score << endl;
    }

    /**
     * 结构体指针：访问结构体成员
     * 操作符：->
    */
    struct student *pointer_stu = &stu1;
    pointer_stu->score = 96;
    cout << "pointer get value---name:" << pointer_stu->name << " age:" << pointer_stu->age << " score:" << pointer_stu->score << endl;

    teacher t1 = {1, "laowang", 40, stu1};
    cout << "嵌套的结构体  name:" << t1.stu.name << " age:" << t1.stu.age << " score:" << t1.stu.score << endl;

    cout << "值传递前 name:" << stu1.name << " age:" << stu1.age << " score:" << stu1.score << endl;
    printStu(stu1);
    cout << "值传递后&地址传递前 name:" << stu1.name << " age:" << stu1.age << " score:" << stu1.score << endl;
    printPointStu(&stu1);
    cout << "地址传递后 name:" << stu1.name << " age:" << stu1.age << " score:" << stu1.score << endl;

    system("pause"); //从程序调用pause命令，stdlib.h" 或 “cstdlib"头文件，但只适合DOS或Windows，不合适合Linux
    //在Linux可直接调用pause()。调用系统命令system()去实现暂停程序，耗费系统资源

    return 0;
}

/*
    函数：封装代码，减少重复
    较大的程序，分若干程序块，每个模块实现特定功能。

    返回值类型 函数名 （参数列表）  //形参
    {
        函数体语句
        return表达式
    }

    函数调用： 函数名（参数），实参
    值传递，形参改变不影响实参

    函数常见样式：1. 无参无返   2. 有参无返   3. 无参有返   4.有参有返

    函数的声明： 可以多次，但定义只能一次

    函数的分文件编写： 1. 在.h的头文件写声明    2. 在.cpp的源文件写定义
*/
//声明
int max(int a, int b);
int max(int a, int b);
//定义
int max(int a, int b)
{
    return a > b ? a : b;
}

// 指针和函数
//值传递    实参不变化
void swap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
//地址传递  实参有变化
void swap2(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
