// C++ 面向对象 编程技术
/**
 * 内存分区模型     生命周期不同
    1. 代码区：CPU执行的机器指令，只读且共享，存放函数体的二进制代码，由操作系统进行管理的
    2. 全局区：存放全局变量和静态变量以及常量（常量区，const修饰的全局常量 和 字符串常量），在程序结束后由操作系统释放
    3. 栈区：由编译器自动分配释放, 存放函数的参数值,局部变量等
    4. 堆区：由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收
    程序运行前，分为全局区和代码区
    程序运行后，分为
        栈区：编译器自动分配释放，存放函数的参数值，局部变量
        堆区：由程序员分配释放（使用new分配, delete释放），
             若程序员不释放会在程序结束后由系统回收
*/
/* UNIX/LINUX 平台下三种主要的可执行文件格式：
1. a.out（assembler and link editor output 汇编器和链接编辑器的输出）
2. COFF（Common Object File Format 通用对象文件格式）
3. ELF（Executable and Linking Format 可执行和链接格式）

可执行文件的大小、运行速度、资源占用情况、可扩展性、可移植性等
         与文件格式的定义和文件加载过程紧密相关
代码和数据 -> 引用外部文件定义的符号（变量和函数）-> 重定位信息和符号信息 -> 辅助信息（调试信息、硬件信息）
按区间保存上述信息，称为段（Segment）或节（Section）
文件头部：描述本文件的总体结构
*/
// ？错误异常崩溃：zsh: segmentation fault  ./cpp_core_learn_terminal.out
/**
 * 改错“？”
 * 1. 构造函数的地方编译出错
 * 2. 空指针的函数调用要重新规范
*/

#include <iostream>
using namespace std;
const double PI = 3.14;

int *func()
{
    int a = 10;           //栈区局部变量
    int *b = new int(10); //new 初始值为10的数据，返回对应类型的指针
    cout << &a << endl;   //0x7ffeeb9b7a6c
    cout << &b << endl;   //0x7ffeeb9b7a60
    cout << *b << endl;
    // address of stack memory associated with local variable 'a' returned [-Wreturn-stack-address]
    // return &a; //不要返回局部变量的地址，可编译但存在警告
    return b;
}

// 引用，1. 值传递，实参不变
void mySwap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
//2. 地址传递，实参改变
void mySwap02(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
//3. 引用传递，实参也改变
void mySwap03(int &a, int &b)
{                 //a和b是引用，转换为 int* const a
    int temp = a; //a和b是引用，自动转换为*a和*b
    a = b;
    b = temp;
}
//返回局部变量引用，局部变量离开方法内存空间被释放，地址指向的内存随时被使用
int &test01()
{
    int a = 10; //局部变量
    return a;   //警告，【-Wreturn-stack-address】
}
//返回静态变量引用
int &test02()
{
    static int a = 20;
    return a;
}
//引用使用的场景，通常用来修饰形参
void showValue(const int &v)
{ //引用规定初始化后不可更改，则引用指针不可修改
    // v += 10;      //const 修饰了引用则变为 const的第三种情况
    cout << v << endl;
}

//1. 如果某个位置参数有默认值，那么从这个位置往后，从左向右，必须都要有默认值
//2. 如果函数声明有默认值，函数实现的时候就不能有默认参数
int func2(int a, int, int b = 10, int c = 10); //占位参数，和默认值
int func2(int a, int, int b, int c)
{
    return a + b + c;
}
//1、引用作为重载条件
void func(int &a)
{
    cout << "func (int &a) 调用 " << endl;
}
void func(const int &a)
{
    cout << "func (const int &a) 调用 " << endl;
}
//2、函数重载碰到函数默认参数
void func1(int a, int b = 10)
{
    cout << "func1(int a, int b = 10) 调用" << endl;
}
void func1(int a)
{
    cout << "func1(int a) 调用" << endl;
}

// 类和对象
class Virtual_Class // 抽象类，存在（纯虚函数/纯析构函数）的类，无法实例化，因为调用构造函数生成对象会出错
{
public:
    virtual void base(){    //虚函数，方便继承重写，多态，也可以不重写
        cout << "base" << endl;
    };
    virtual void func() = 0;    //纯虚函数, 必须重写
    Virtual_Class();
    // virtual ~Virtual_Class(){   //虚析构函数
    //     cout << "虚析构" << endl;
    // };   
    virtual ~Virtual_Class() = 0;   //纯虚析构函数
};
Virtual_Class::Virtual_Class(){}
Virtual_Class::~Virtual_Class() {
    cout << "析构" << endl;
}

class Inherite_Virtual: public Virtual_Class {
public: 
    string *name;   //子类带有堆区变量，父类必须实现虚析构/纯虚析构
    Inherite_Virtual(string name);
    ~Inherite_Virtual();
    virtual void func(){
        cout << "纯虚函数必须重写" << endl;
    }
};
Inherite_Virtual::Inherite_Virtual(string name){
    this->name = new string(name);
}
Inherite_Virtual::~Inherite_Virtual(){  //按正常方式释放堆区变量
    if (this->name != NULL) {
        delete this->name;
        this->name = NULL;
    }
}


class Operation
{
private:    //私有成员也被继承，但由编译器隐藏后无法访问
    int private_id;
    static int sta_pri_id;
protected:
    int protect_val;
    static int sta_pro_val;
public:
    static int sta_pub_val;
    int pub_val;
    int *heap_val;
    Operation();
    Operation(int val);
    ~Operation();
    Operation& operator=(Operation &op) {   //&&若返回的不是&引用，那么会导致指针重复释放
        if (heap_val != NULL) {     //如果不为空指针，那就是按规定指向堆区的变量
            delete heap_val;    //清除heap_val的堆区内存
            heap_val = NULL;    //把heap_val设置为空指针
        }
        // heap_val = dot.heap_val;     //编译器提供的代码是浅拷贝
        heap_val = new int(*op.heap_val);  //按照dot对象指针的heap_val值拷贝一份新的堆内存
        return *this;
    }
    bool operator==(Operation &op) {
        if (this->heap_val == op.heap_val) {
            return true;
        }else {
            return false;
        }
    }
    bool operator!=(Operation &op) {
        if (this->heap_val == op.heap_val) {
            return false;
        }else {
            return true;
        }
    }
    void operator()(string text) {      //仿函数
        cout << text << endl;
    }
    int operator()(int v1, int v2) {
        return v1 + v2;
    }
};
Operation::Operation(){}
Operation::Operation(int val)
{
    heap_val = new int(val);  //通过构造函数把变量控制在堆区
}

Operation::~Operation()     //添加了堆区变量，所以析构函数要清除堆区变量heap_val
{
    if (heap_val != NULL) {     //如果不为空指针，那就是按规定指向堆区的变量
        delete heap_val;    //清除heap_val的堆区内存
        heap_val = NULL;    //把heap_val设置为空指针
    }
}
// 表现     个性          共性       
//      子类/派生类        父类/基类
//继承Operation, 必须添加public，否则属性无法访问，继承过来也是私有
//继承方式有三种：公共继承 public、保护继承 protected、私有继承（默认）private
class Inherit_Class: private Operation  
// class Inherit_Class: protected Operation  
// class Inherit_Class: public Operation  
{
private:
    int i_id;
public:
    Inherit_Class();
    ~Inherit_Class();
    void newOperate(){
        cout << "newOperate特有的" << endl;
        //public 继承 和 protected 继承 和 private 继承，不可访问私有、其他都可以访问
        // cout << "private_id:" << private_id << endl;    
        cout << "protect_val:" << protect_val << endl;
        cout << "heap_val:" << heap_val << endl;
        // 除了私有静态变量，其他都可以访问
        // cout << "sta_pri_id:" << sta_pri_id << endl;
        cout << "sta_pro_val:" << sta_pro_val << endl;
        cout << "sta_pub_val:" << sta_pub_val << endl;
    }
};
Inherit_Class::Inherit_Class(){}
Inherit_Class::~Inherit_Class(){}

class Private_Public_Class:public Inherit_Class 
{   //当Inherit_Class为private继承时
public:
    Private_Public_Class();
    ~Private_Public_Class();
    void readPrivateClass() {
        //全部继承的成员变量都不无法访问，包括静态变量
        // cout << private_id << endl;
        // cout << protect_val << endl;
        // cout << heap_val << endl;
        // cout << "sta_pri_id:" << sta_pri_id << endl;
        // cout << "sta_pro_val:" << sta_pro_val << endl;
        // cout << "sta_pub_val:" << sta_pub_val << endl;
        // cout << "sta_pro_val:" << Inherit_Class::sta_pro_val << endl;
        // cout << "sta_pub_val:" << Inherit_Class::sta_pub_val << endl;
    }
};
Private_Public_Class::Private_Public_Class(){}
Private_Public_Class::~Private_Public_Class(){}

class Circle;   //因为Circle声明在下面
class Dot
{   // 类成员默认私有
    friend void getPrivateValue(Dot dot);   //使全局函数 getPrivateValue 作为 Dot 的友元，可以访问 Dot 的私有内容
    // 使用友元，让自定义左移运算符重载新的数据类型
    friend ostream& operator<<(ostream& out, Dot& dot); 
private:
    Circle *dot_cir;    //Dot 类作为 Circle 的友元
    int id;  //非静态成员变量占对象空间
    //属于静态变量，实质在类外初始化，在编译阶段分配内存
    //数据唯一，所有对象都共享同一份数据
    //有访问权限
    static int m_a;     //静态成员变量不占对象空间
    static void func1()     //静态成员函数不占对象空间
    {
        cout << "静态成员函数也有访问权限" << endl;
    }
    
public:
    int* heap_val;   //堆区变量
    int p_b;    //常量对象不可修改
    mutable int p_c;    //有mutable常量对象可以修改
    static int m_b;
    float locate[2];     //坐标点x,y，不使用指针，可以控制为二元数组，使用指针要考虑拷贝构造函数深拷贝
    //使用引用或指针，都可以修改实参，C++推荐使用引用
    Dot();
    Dot(float loc[]);      //传入坐标数组名直接退化为指针，与指针形参无异
    // Dot(float* loc);    //数组无法使用引用，值传递和指针传递效果一致，导致redeclare
    ~Dot();
    //定义一个返回的结果为引用，实质生成的对象为构造函数开辟的新对象
    Dot& changeDot(Dot dot) //值传递方式，形参以隐式转换方式调用Dot构造函数，但生成的dot无任何意义
    {   
        // 'this' pointer cannot be null in C++ code;comparision may be assumed to always evaluate to false [-Wtautological-undefined-compare]
        // if (this == NULL) return *this;
        this->locate[0] = dot.locate[0];
        this->locate[1] = dot.locate[1];
        return *this;
    }
    void func2()    //函数也不占对象空间，所有对象共享一个函数实例
    {       //非静态函数只生成一个函数实例
        cout << m_b << endl;    //虽然可写私有变量m_a，但m_a是私有变，编译出错
    }
    //静态成员函数，程序共享一个函数，静态成员函数只能访问静态成员变量
    static void func()
    {   //只能访问静态成员变量
        m_a = 20;
        m_b = 30;
        // locate[0];
    }
    //this指针的本质是一个指针常量，指针的指向不可修改
	void ShowDot() const {  //常函数    指针指向的值也不可以修改
		//const Type* const pointer;    //const双修
		//this = NULL;      //不能修改指针的指向 Dot* const this;
		// this->p_b = 100;      //只可修改 静态 和 mutable数据
		//const修饰成员函数，表示指针指向的内存空间的数据不能修改，除了mutable修饰的变量
		this->m_b = 100;
        this->p_c = 101;
    }
    void visitCir();   //友元类的调用cir私有属性的函数声明接口
    void methodVisitCir();  //友元函数声明接口
    // 运算符重载，可发生函数重载   同函数重载，可因形参不同
    // 或写成全局 operator+
    Dot operator+(const Dot& dot) {     //const 修饰不可修改的引用，即不可修改值（引用本质：常量指针）
        this->locate[0] += dot.locate[0];
        this->locate[1] += dot.locate[1];
        return *this;
    }       //除非函数定义新开辟一个Dot对象，否则使用本身。
            //？此处修改的写法有问题，应该有新内存空间开辟，如果需要，通过值传递方式隐式调用构造函数
    Dot operator+(float add_val) {     //const 修饰不可修改的引用，即不可修改值（引用本质：常量指针）
        this->locate[0] += add_val;
        this->locate[1] += add_val;
        return *this;
    }
    // Dot operator<<(Dot& dot){    //成员左移重载
    //     cout << "operator << " << endl;
    //     return *this;
    // }
    Dot& operator++() { //前置++     //案例为整型类，作为类应该可以实现
        p_b++;  //先++
        return *this;
    }
    Dot operator++(int) {   //后置++
        Dot temp = *this;
        p_b++;
        return temp;    //返回的是自增前的值
    }
};
//全局函数实现左移重载
ostream& operator<<(ostream& out, Dot& dot) {   //ostream对象只能有一个
	out << "x:" << dot.locate[0] << " y:" << dot.locate[1];     //自定义输出
	return out;     //可以自定义类型，配合友元操作私有函数和变量
}
Dot::Dot(float loc[])
{
    locate[0] = loc[0];
    locate[1] = loc[1];
    // memcpy(locate, loc, sizeof(loc));    //可能loc大小和locate大小没有限制对应匹配导致有警告
}
Dot::~Dot(){}
int Dot::m_b = 10;      //m_b为静态变量

void getPrivateValue(Dot dot)
{
    dot.id = 1;     //被声明为Dot的友元，可访问修改私有变量
    // dot.m_a = 2;    //访问修改私有静态变量编译出错
    // cout << Dot::m_a << endl;    //左右友元无法访问私有静态变量
    dot.func1();                //被声明为Dot的友元，可访问私有成员函数

}

class Circle
{
private:    //类成员默认私有
    int a;
    // Dot dot;    //对象成员
    friend class Dot;     //类做友元，让 Dot 对象可访问 成员circle对象的私有变量和函数
    friend void Dot::methodVisitCir();    //让 Dot 的成员函数作为友元
public:
    Circle();           //无参构造函数，默认
    Circle(int m_r);    //有参构造函数
    Circle(int o_id, int c_r);
    Circle(const Circle& c);     //拷贝构造函数
    //初始化列表方式初始化, 必须放在类里
	Circle(int c_r, int o_id, int c) :m_r(c_r), c_id(new int(o_id)), a(c) {}
    // 当有对象成员 Dot 时, 在初始化列表中指定 对象成员所调用的构造函数
	// Circle(int c_r, int o_id, int c, Dot o_dot) :dot(o_dot), m_r(c_r), c_id(new int(o_id)), a(c) {}

    ~Circle();              //析构函数
    int m_r;
    // 程序员可操作内存为堆区，一旦使用指针，则必须有构造函数和考虑深拷贝，即开辟new内存空间
    int* c_id;      //指针，要注意对象需要在构造函数开辟指针变量独有的内存空间，避免重复释放问题
    double calculateZC()
    {
        return 2 * PI * m_r;
    }
};
/* 构造函数     无须手动调用，且只会调用一次
    参数：有参构造和无参构造
    类型：普通构造和拷贝构造
    调用方式：括号法、显示法、隐式转换法
*/
Circle::Circle(int m_r) //有参构造，普通构造 //没有返回值也不写void
{
    //可以有参数，因此可以发生重载
    this->m_r = m_r;    //使用this区别同名的形参和成员变量
}
Circle::Circle(int o_id, const int c_r) //使用const避免起义，优先调用无const构造函数
{
    m_r = c_r;
    c_id = new int(o_id);   //由于c_id是指针 
    /*** 此处可能 new 默认返回的是值为o_id的新的&地址值 ***************************************/
}
Circle::Circle(){}  //无参构造，普通构造
Circle::Circle(const Circle& c)     //拷贝构造
{
    m_r = c.m_r;
    c_id = new int(*c.c_id);
}
//析构函数      无须手动调用, 且只会调用一次
Circle::~Circle() //没有返回值也不写void
{
    //不可以有参数，因此不可以发生重载
}

//非类的成员函数，一般全局函数
Circle newACircle(Circle cir) //值传递方式调用拷贝构造，相当于隐式转换 Circle cir = cir1
{
    Circle cir0(20);
    //适用对象来初始化，则调用拷贝构造函数
    Circle i_cir(cir0);
    Circle i_cir1 = i_cir;  //隐式转换法
    //返回局部变量
    return Circle(20);  //返回局部匿名对象
}
// 如果在 Dot 实现文件中，需要导入Circle的头文件，在同一个文件下，需要放在Circle的声明下面。
Dot::Dot(){
    dot_cir = new Circle();
}
void Dot::visitCir()    //实现接口
{
    dot_cir->a = 0;
}
void Dot::methodVisitCir()
{
    cout << dot_cir->a << endl;
}

int main()
{
    int *p = func();
    cout << *p << endl;         //返回a时10
    cout << *p << endl;         //返回a时32767
    cout << sizeof(*p) << endl; //堆区的整型10占4个字节
    cout << sizeof(p) << endl;  //指针占8个字节
                                //返回b时   利用delete释放堆区数据
    delete p;
    //cout << *p << endl; //报错，释放的空间不可访问

    //堆区开辟数组
    int *arr = new int[10];
    for (size_t i = 0; i < 10; i++)
    {
        arr[i] = i + 100;
        cout << arr[i] << endl;
    }
    delete[] arr; //释放数组

    /**
     * 引用，给变量起别名   本质：指针常量
     *      1. 必须初始化
     *      2. 初始化后不可改变
     *      C++推荐用引用技术，语法方便，所有指针操作由编译器来做
     * 引用做函数参数
     *      1. 通过引用让形参修饰实参
     *      2. 简化指针修改实参
     *      引用的本质：在c++内部实现了一个指针常量，不可改变变量但可改变值
     * 引用做函数返回值
     *      不要返回局部变量的引用
     * 常量引用
     *      const 修饰形参防止误操作实参
    */
    int a = 11;
    int c = 20;
    int &b = a; //自动转换为 int* const b = &a;指针常量的指向不可修改但变量的值可以修改
    b = 100;    //自动转换为*b = 100
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    b = c; //赋值，不是引用
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    //使用引用做参数
    c = 50;         //a=20
    mySwap01(a, c); //实参不变
    cout << "a:" << a << " c:" << c << endl;
    mySwap02(&a, &c); //实参互换
    cout << "a:" << a << " c:" << c << endl;
    mySwap03(a, c); //实参互换
    cout << "a:" << a << " c:" << c << endl;

    //引用做返回值
    int &ref2 = test02();
    cout << "ref2 = " << ref2 << endl;
    cout << "ref2 = " << ref2 << endl;
    test02() = 1000; //如果函数做左值，那么必须返回引用
    cout << "ref2 = " << ref2 << endl;
    cout << "ref2 = " << ref2 << endl;

    //int& ref = 10;  引用本身需要一个合法的内存空间，只能指向变量
    //加入const就可以了，编译器优化代码，int temp = 10; const int& ref = temp;
    const int &ref = 10; //常量引用
    showValue(a);

    /**
     * 函数默认参数
     * 函数重载     函数名相同提高复用性
     *      条件：   1.同一个作用域    2.函数名相同    3.参数类型/个数/顺序不同
     *      函数的返回值不可以作为函数重载的条件
     *      注意事项：  1. 引用作为重载条件，默认有限调用无const
     *                2. 函数重载碰到函数默认参数，产生警告歧义
    */
    cout << "ret = " << func2(100, 2) << endl; //占位参必须填补

    func(a);  //调用无const
    func(10); //调用有const
              // func1(10); //碰到默认参数产生歧义，需要避免

    /**
     * 类和对象
     *  三大特性：1. 封装   
     *              a.设计类时，属性和行为作为一个整体加以权限控制
     *              b.访问权限：    类内皆可访问
     *                  public 公共权限         类外可访问
     *                  protected 保护权限      类外不可访问
     *                  private 私有权限        类外不可访问  
     *              struct 和 class 的区别：默认的访问权限不同，不添加 public等设定时
     *                  struct 默认权限：公共
     *                  class 默认权限：私有       
     *          2. 继承
     *          3. 多态
     *  
     * 对象的初始化和清理
     *    1. 构造函数（对象初始化）：创建时编译器自动给成员属性赋值
     *    2. 析构函数（对象清理）：对象销毁前系统自动调用
     *       若两个函数无实现，编译器自动提供空实现
     *    拷贝构造函数调用时机：
     *         1. 使用一个已经创建完毕的对象来初始化一个新对象
     *         2. 值传递的方式给函数参数传值
     *         3. 以值方式返回局部对象
     *    默认情况下，c++编译器至少给一个类添加3个函数
     *         1．默认构造函数(无参，函数体为空)
     *         2．默认析构函数(无参，函数体为空)
     *         3．默认拷贝构造函数，对属性进行值拷贝 
     *    构造函数调用规则：若有拷贝构造函数，C++什么也不提供，
     *                   若有有参构造函数，C++只提供拷贝构造函数
     *    深拷贝：在堆区重新申请空间，进行拷贝操作
     *    浅拷贝：简单的赋值拷贝操作
     *    如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题
     *    
     *    “初始化列表”方式初始化，C++提供
     *    对象成员：   1. 先调用对象成员的构造，再调用本类构造
     *               2. 析构顺序与构造相反
     *    静态成员：   成员变量和成员函数前有 static 关键字
     *         静态成员变量：1. 所有对象共享同一份数据
     *                     2. 在编译阶段分配内存
     *                     3. 类内声明，类外初始化     
     *         静态成员函数：1. 所有对象共享同一个函数
     *                     2. 静态成员函数只能访问静态成员变量
     * 
     * C++对象模型和this指针
     * C++中，类内的成员变量和成员函数分开存储，只有非静态成员变量才属于类的对象上
     * this指针：   非静态的函数实例只有一个，使用this区别调用单一实例的的对象
     *             隐含每一个非静态成员函数内的一种指针
     *      用途：  1. 当形参与成员变量同名，使用this区别
     *             2. 在类的非静态成员函数中返回对象本身，使用return *this;
     *      空指针：可以访问成员函数，但函数内使用this阵阵需要加以判断保证代码健壮性
     * 
     *      常函数：const修饰，不可修改成员属性，除非属性声明带mutable关键字
     *      常对象：const修饰，只能调用常函数
     * 
     * 友元：   关键字 friend，    让一个函数或者类访问另一个类中的私有成员
     *      1. 全局函数
     *      2. 类
     *      3. 成员函数
     * 
     * 运算符重载   对已有的运算符重新定义，适应不同数据类型，赋予另一种功能
     *      加号运算符重载
     *          1. 对于内置的数据类型的表达式的运算符是不可能改变的
     *          2. 不要滥用运算符重载
     *      左移运算符重载      输出自定义数据类型
     *          1. 重载左移运算符配合友元可以实现输出自定义数据类型
     *      递增运算符重载      实现自定义整型数据
     *          1. 前置递增返回引用，后置递增返回值
     *      赋值运算符重载      
     *          C++默认给类添加的4个函数：
     *              1. 默认构造函数(无参，函数体为空)
     *              2. 默认析构函数(无参，函数体为空)
     *              3. 默认拷贝构造函数，对属性进行值拷贝
     *              4. 赋值运算符 operator=, 对属性进行值拷贝
     *          如果属性有指向堆区，赋值操作时会出现深浅拷贝问题
     *      关系运算符重载      两个自定义类型对象进行对比操作
     * 
     *      函数调用运算符重载    
     *             1. 函数调用运算符()也可以重载
     *             2. 仿函数，重载后使用方法一致
     *             3. 仿函数写法灵活
     * 
     * 继承：（公共、保护、私有）继承
     *          1. 子类的创建、先调用父类构造函数，再调用子类构造函数
     *          2. 析构顺序与构造相反
     *          3. 子类同名成员：直接访问即可；父类同名成员(被子类隐藏)：需要加作用域   
     *             访问父类：     obj.Base::m_A;      obj.Base::func();
     *          4. 子类同名静态成员：直接访问即可；父类同名静态成员：需要加作用域
     *             访问父类：
     *                  对象访问：obj.Base::m_A  obj.Base::func();
     *                  类名访问：Son::Base::m_A     Son::Base::func();
     *      多继承   同继承，使用（，）逗号分开
     *          可能引发父同名成员，同理添加作用域区分
     *          C++不建议多继承
     *      菱形继承/钻石继承    基类 -继承后-> 派生类1、派生类2 -同时继承后-> 类
     *          //继承前加virtual关键字后，变为虚继承
     *          //此时公共的父类Animal称为虚基类（保证SheepTuo只有一份Animal继承数据）
     *              class Sheep : virtual public Animal {};
     *              class Tuo   : virtual public Animal {};
     *              class SheepTuo : public Sheep, public Tuo {};
     * 
     * 多态：   父类指针或引用指向子类对象
     *      C++提倡多态设计程序架构
     *      条件： 1、有继承关系    2、子类重写父类中的虚函数, 函数名完全一致，非函数重载
     *      1. 静态多态: 
     *              a. 函数重载 和 运算符重载 属于静态多态，复用函数名
     *              b. 函数地址早绑定 - 编译阶段确定函数地址(静态联编)
     *      2. 动态多态: 
     *              a. 派生类 和 虚函数/纯虚函数(virtual关键字) 实现运行时多态
     *              b. 函数地址晚绑定 - 运行阶段确定函数地址(动态联编)
     *      优点:   1. 代码组织结构清晰
     *             2. 可读性强
     *             3.利于前期和后期的扩展以及维护
     *      纯虚函数：  多态中父类的虚函数（纯虚函数）（本质无意义，如果一个空实现的声明），主要提供给子类重写
     *      抽象类：1. 无法实例化对象   2. 所有纯虚函数必须重写，否则子类也是抽象类
     *      虚析构和纯虚析构：  解决父类无法调用 有开辟堆区变量的子类的析构函数 的问题
     *          父类的析构函数改为 虚析构 或者 纯虚析构（抽象类的虚析构函数）
     *      
    */
    Circle cir;   //调用无参构造，注意1：如果加了括号编译器认为这是一个函数声明
    Circle cir1(10);     //括号法，常用
    //显示法
    Circle cir2 = Circle(20);
    // Circle cir3 = Circle(cir1);      //？错误崩溃，应该是拷贝构造函数出错
    // Circle(20);     //匿名对象   当前行结束之后，马上析构
    //隐式转换法
    Circle cir4 = 90;
    // Circle cir5 = cir3;     //隐式转换调用拷贝构造函数  ？错误崩溃，拷贝构造函数
    //注意2：不能利用 拷贝构造函数 初始化匿名对象 编译器认为是对象声明
	//Circle cir6(cir4);  
    float loc[2] = {1.0, 2.0};
    Dot dot(loc);

    //通过对象访问静态成员变量
    cout << dot.m_b << endl;
    cout << Dot::m_b << endl;   
    // cout << dot.m_a (Inaccessible) << endl;  //私有变量的访问受权限限制出警告
    dot.func2();    
    // dot.func1();   //私有变量的访问受权限限制出警告
    // dot.func();       //公开的静态函数，由于只读静态变量，因此编译出错
    
    //通过类名访问静态成员变量
    cout << Dot::m_b << endl; 
    // cout << Dot::m_a (Inaccessible) << endl; //私有变量的访问受权限限制出警告
    // Dot::func2();    //非静态函数只能通过对象访问
    // Dot::func1 (Inaccessible)();    //私有变量的访问受权限限制出警告
    // Dot::func();    //公开的静态函数，由于只读静态变量，因此编译出错
    
    // Dot dot1 = NULL;    //空指针可以访问成员函数    //？错误崩溃
    // dot1.changeDot(dot);    //但函数内使用this阵阵需要加以判断保证代码健壮性

    const Dot c_dot(loc);   //常量对象
    // 与常量函数一样，不能修改变量值，可以修改 静态 和 mutable数据
    // c_dot.locate[0] = 100;
    // c_dot.p_b = 15;
    c_dot.m_b = 55;
    c_dot.p_c = 66;
    c_dot.ShowDot();

    //加号运算符重载
    // dot = dot + 10.0;   //调用+的是dot，等效于 dot.operator+(10.0);
    // dot = dot + c_dot;  //等效于 dot.operator+(c_dot);
    //由于重写了赋值运算符，所以上述两个“=”运算已经不等效
    dot + 10.0;   //调用+的是dot，等效于 dot.operator+(10.0);
    dot + c_dot;
    //左移运算符重载
    cout << dot << endl;    //输出为自定义结构
    //递增运算符重载
    cout << "<< " << dot.p_b << endl;
    cout << "<< " << (dot++).p_b << endl;
    cout << "<< " << ++dot << endl;
    cout << "<< " << dot.p_b << endl;
    //赋值运算符重载
    Operation op_equal(9);   //调取有参为整型的重载的构造函数，此函数开辟了heap_val堆区变量
    Operation op_equal1(20);
    Operation op_equal2(30);
    cout << &op_equal << endl;
    cout << &op_equal1 << endl;
    cout << &op_equal2 << endl;
    op_equal2 = op_equal1 = op_equal;   //赋值操作
    // op_equal2 = op_equal1;    //赋值操作
    // op_equal1 = op_equal;
    cout << *op_equal.heap_val << endl;
    cout << *op_equal1.heap_val << endl;
    cout << *op_equal2.heap_val << endl;
    //关系运算符
    cout << (op_equal1 == op_equal2) << endl;
    cout << (op_equal1 != op_equal2) << endl;
    // 函数调用运算符重载
    op_equal("函数调用");
    int ret = op_equal(1, 2);
    cout << Operation()(3, 4) << endl;  //匿名对象调用，必须实现无参构造函数

    Inherit_Class cl;
    // public 继承的对象只能访问public变量, 包括静态变量
    // protected 继承 和 private 继承的对象都不可访问所有变量，包括静态变量
    // cout << cl.heap_val << endl;
    // cout << cl.protect_val << endl;
    // cout << cl.private_id << endl;
    // cout << "sta_pro_val:" << cl.sta_pro_val << endl;
    // cout << "sta_pub_val:" << cl.sta_pub_val << endl;
    // cout << "sta_pro_val:" << Inherit_Class::sta_pro_val << endl;
    // cout << "sta_pub_val:" << Inherit_Class::sta_pub_val << endl;

    Virtual_Class *inher = new Inherite_Virtual("继承");    //不用new会出现强制转换类型错误
    inher->func();
    //通过父类指针去释放，会导致子类对象可能清理不干净，造成内存泄漏
    delete inher;   //虚析构 或者 纯虚析构, 保证不对称指针的堆区释放问题

    return 0;
}
