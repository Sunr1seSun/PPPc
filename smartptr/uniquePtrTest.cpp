#include<iostream>
#include<string>
#include<memory>
using namespace std;

template<typename T>
struct Node{
    T data;
    unique_ptr<Node<T>> next;
    ~Node(){
        cout << "~Node " << data << endl;
    }
};

template<typename T>
class Link{
public:
    void front(const T& data){
        auto node = make_unique<Node<T>>();
        node->data = data;
        node->next = move(head_.next);
        head_.next = move(node);
    }
    
    void print(){
        Node<T> *p = head_.next.get();
        while(p){
            cout << p->data << ' ';
            p = p->next.get();
        }
    }

private:
    Node<T> head_;
};

int main()
{
    Link<int> l1;
    for(int val :{1,2,3,4,5}){
        l1.front(val);
    }

    l1.print();

}