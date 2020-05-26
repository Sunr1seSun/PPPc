#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Person{
    string name;
    Person(string _name):name(_name){
    }
    ~Person(){
        cout << "~Person " << name << endl;
    }
};

unique_ptr<Person> back(){
    return unique_ptr<Person>(new Person("uniquePtr3"));
}

int main()
{
    string* str(new string("hello world"));
    cout << *str << endl;;
    delete str;

    /*
        unique_ptr只能由一个对象拥有所有权。
    */
    //使用独有指针指向字符串
    unique_ptr<string> uniquePtr1(new string("I am unique_ptr!"));
    cout << *uniquePtr1 << endl;

    //使用独有指针指向一个对象，析构函数自动调用。
    unique_ptr<Person> uniquePtr2(new Person("uniquePtr2"));

    //不使用智能指针需要自己手动释放。
    Person* personPtr = new Person("personPtr");
    delete personPtr;

    //独有指针可以通过函数返回保持生命
    unique_ptr<Person> uniquePtr3 = back();

    //使用move转移后，原指针不再指向该对象。
    unique_ptr<Person> uniquePtr4 = move(uniquePtr2);
    cout << (!uniquePtr2) << endl;

    // p.reset()先释放p指向的对象，然后重置p的值。
    uniquePtr4.reset(new Person("reset uniquePtr4"));

    //使用make_unique创建独有指针。
    auto makePtr = make_unique<Person>("makePtr");
}