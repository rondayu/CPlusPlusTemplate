#include <iostream>
using namespace std;

class Operation
{
private:
    int id;
public:
    int *heap_val;
    Operation(int val);
    ~Operation();
    Operation& operator=(Operation &op) {
        cout << heap_val << endl;
        cout << *heap_val << endl;
        cout << &heap_val << endl;
        if (heap_val != NULL) {     //如果不为空指针，那就是按规定指向堆区的变量
            delete heap_val;    //清除heap_val的堆区内存
            heap_val = NULL;    //把heap_val设置为空指针
        }
        // heap_val = dot.heap_val;     //编译器提供的代码是浅拷贝
        heap_val = new int(*op.heap_val);  //按照dot对象指针的heap_val值拷贝一份新的堆内存
        return *this;
    }
};

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

int main(){

    Operation op_equal(9);   //调取有参为整型的重载的构造函数，此函数开辟了heap_val堆区变量
    Operation op_equal1(20);
    Operation op_equal2(30);
    cout << &op_equal << endl;
    cout << &op_equal1 << endl;
    cout << &op_equal2 << endl;
    op_equal2 = op_equal1 = op_equal;
    // op_equal2 = op_equal1;    //赋值操作
    // op_equal1 = op_equal;
    cout << *op_equal.heap_val << endl;
    cout << *op_equal1.heap_val << endl;
    cout << *op_equal2.heap_val << endl;
    
    return 0;
}