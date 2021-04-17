/**
 * g++ 源文件 -o 输出文件.out
 * ./输出文件.out
 */


#include <iostream>
#include <cstring>
using namespace std;

/*
Implement an algorithm to determine if a string has all unique characters. 
What if you can not use additional data structures?
*/
bool isUnique1(string s)
{
    bool a[256];
    memset(a, 0, sizeof(a));    //清空并配置256字节为0
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        int v = (int)s[i];
        if (a[v])
            return false;
        a[v] = true;    //使用一个字节来表示1
    }
    return true;
}

bool isUnique2(string s)
{
    int a[8];
    memset(a, 0, sizeof(a));
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        int v = (int)s[i];
        int idx = v / 32, shift = v % 32;
        if (a[idx] & (1 << shift))
            return false;
        a[idx] |= (1 << shift);
    }
    return true;
}
bool isUnique3(string s)
{
    int check = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        int v = (int)(s[i] - 'a');
        if (check & (1 << v))
            return false;
        check |= (1 << v);
    }
    return true;
}
/*
Write code to reverse a C-Style String. 
(C-String means that “abcd” is represented as five characters, 
including the null character.)
*/
void swap(char &a, char &b){
    a = a^b;
    b = a^b;
    a = a^b;
}

void reverse1(char *s){
    if(!s) return;
    char *p = s, *q = s;
    while(*q) ++q;
    --q;
    while(p < q) {
        // cout << "p:" << p << " q:" << q << endl;
        // cout << "*p:" << *p << " *q:" << *q << endl;
        swap(*p++, *q--);
        // cout << "p:" << p << " q:" << q << endl;
        // cout << "*p:" << *p << " *q:" << *q << endl;
    }
}
void reverse2(char *s)
{
    int n = strlen(s);
    for(int i=0; i < n/2; ++i)
        swap(s[i], s[n-i-1]);
}

/*
Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. 
NOTE: One or two additional variables are fine. An extra copy of the array is not.
*/
void remove_extra(char *s)
{
    int index = 0;
    bool exist = false;
    //2oo12jjkalllskknndggg
    for (int i = 1; i < strlen(s); i++)
    {
        for (int j = 0; j <= index; j++){
            if (s[j] == s[i]) {
                exist = true;
                cout << "exist" << endl;
                break;
            }else cout << s[j] << "!=" << s[i] << endl;
            if (j == index) exist = false;
        }
        if (!exist) {
            index++;
            if (index != i) {
                cout << "should swap " << index << "and " << i << endl;
                swap(s[index], s[i]);
            }
        }
        exist = false;
    }
    cout << "index: " << index << endl;
    s[index+1] = '\0';
    cout << s << endl;
}

int main()
{
    string s1 = "i am hawstein.";
    string s2 = "abcdefghijklmnopqrstuvwxyzABCD1234567890";
    cout << isUnique1(s1) << " " << isUnique1(s2) << endl;
    cout << isUnique2(s1) << " " << isUnique2(s2) << endl;

    char str[50];
    strcpy(str, "This is string.h library function");
    puts(str);  //c语言的输出
    memset(str, '$', 7);
    puts(str);

    // char *ch = new char("c"); 
    char c_str[] = "abcd";
    reverse1(c_str);
    cout << "&c_str:" << &c_str << " c_str:" << c_str << endl;
    reverse2(c_str);
    cout << "&c_str:" << &c_str << " c_str:" << c_str << endl;

    char uni_str[] = "2oo12jjkalllskknndggg";
    remove_extra(uni_str);
    cout << uni_str << endl;

    return 0;
}