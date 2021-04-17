/**
 * 范型编程、STL技术
 * 函数模版、类模版：   
 *      1. 提高复用性，将类型参数化
 *      2. 自动类型推导，不发生隐式类型转换，但显示指定类型时，可以发生隐式类型转换
 *      3. 必须一致的数据类型T才可以，且必须能确定的 T 数据类型
 * 普通函数：
 *      1. 自动类型转换
*/

#include <iostream>
using namespace std;

// typename 可以用 class 代替
template<typename T>    // 创建模版数据类型
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
template<class T>
void func() {}
template<typename T>
void printArray(T arr[], int len) {
    for (size_t i = 0; i < len; i++) {
        cout << arr[z] << " ";
    }
    cout << endl;
}

/**
 * 使用函数模版对不同数据类型进行 选择排序（排序算法）
 * 使用 char 数组和 int 数组测试
 */
template<class T>
// void mySort(T arr[], int len)   // 我实现的应该是冒泡排序
// {
//     for(int i = 0; i < len; i++ ){
//         for(int j = 0; j < len-i-1; j++){
//             if (arr[j] < arr[j+1]){
//                 mySwap(arr[j], arr[j+1]);
//             }
//         }
//         printArray(arr, len);
//     }
//     printArray(arr, len);
// }
void mySort(T arr[], int len)
{
	for (int i = 0; i < len; i++){
		int max = i; //最大数的下标
		for (int j = i + 1; j < len; j++){
			if (arr[max] < arr[j]){
				max = j;
			}
		}
		if (max != i){  //如果最大数的下标不是i，交换两者
			mySwap(arr[max], arr[i]);
		}
        printArray(arr, len);
	}
}

int main()
{
    int a = 10;
    int b = 20;
    char c = 'c';
    mySwap(a, b);   //自动类型推导
    mySwap<int>(a, b);  //显式指定类型
    // mySwap(a, c);    //错误
    // func();     //错误
    func<int>();    // T 必须为可确定类型
    int arr[] = {9, 3, 7, 4, 6, 5, 0, 8, 2, 1};
    // char arr_c[10] = {'g', 'a', 'd', 'i', 'e', 'b', 'j', 'c', 'h', 'f'};
    mySort(arr, sizeof(arr) / sizeof(int));
    char charArr[] = "bdcjfeaghi";
	int num = sizeof(charArr) / sizeof(char);
}