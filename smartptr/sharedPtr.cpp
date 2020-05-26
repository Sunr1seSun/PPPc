#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Person
    : enable_shared_from_this<Person>{
    Person(string _str):str(_str){

    }
    ~Person(){
        cout << "~Person " << str << endl;
    }
    void show(){
        cout << str << endl;
    }

    shared_ptr<Person> getShared(){
        return shared_from_this();
    }

    string str;
};

int main()
{
    //引用计数
    shared_ptr<string> ptr1(new string("hello world"));
    cout << ptr1.use_count() << endl;
    auto ptr2 = ptr1;
    cout << ptr1.use_count() << endl;

    //从类返回的this共享指针
    shared_ptr<Person> objPtr(new Person("objPtr1"));
    shared_ptr<Person> objPtr2 = objPtr->getShared();
    cout << objPtr.use_count() << endl;

}
