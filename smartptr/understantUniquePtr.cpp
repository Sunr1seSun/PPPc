#include <iostream>
#include <string>
using namespace std;

// RAII：需要申请和释放的资源与一个对象的生命周期绑定

template<typename T>
class UniquePointer{
public:
    using Pointer = T*;
    using Reference = T&;
    
    // 初始化函数
    UniquePointer():ptr_(nullptr){}
    UniquePointer(Pointer ptr):ptr_(ptr){}
    
    // 移动语义
    UniquePointer(UniquePointer&& other)
        :ptr_(other.ptr_){
            other.ptr_ = nullptr;
        }
    UniquePointer& operator=(UniquePointer&& other){
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    // 删除拷贝赋值函数 和 =赋值函数
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    ~UniquePointer(){
        if(ptr_ != nullptr){
            delete ptr_;
        }
    }
    Pointer get(){
        return ptr_;
    }
    Reference operator *(){
        return *ptr_;
    }
    Pointer operator ->(){
        return ptr_;
    }

    operator bool(){
        return ptr_ != nullptr;
    }

    void reset(Pointer ptr = nullptr){
        if(ptr_ != nullptr){
            delete ptr_;
        }
        ptr_ = ptr;
    }
private:
    Pointer ptr_;
};

struct Person{
    ~Person(){
        cout << "~Demo" << endl;
    }
};

int main()
{
    
    UniquePointer<string> ptr(new string("hello"));

    ptr.reset(new string("small"));

    auto ptr1(move(ptr));

    cout << ptr1->c_str() << endl;

    if(!ptr){
        cout << "ptr为空" << endl;
    }
}
