#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class myString{
public:
    myString(const char* str = nullptr);
    ~myString();

    myString& operator=(const myString &str);
    myString operator+(const myString &str) const;
    

    int size() const;
    const char *c_str() const;
public:
    char *data;
    int length;
};

myString myString::operator+(const myString &str) const
{
    myString newString;
    newString.length = length + str.size();
    newString.data = new char[newString.length + 1];
    strcpy(newString.data, data);
    strcat(newString.data, str.data);
    return newString;
}

const char *myString::c_str() const
{
    return data;
}

myString& myString::operator=(const myString &str)
{
    if(this == &str) return *this;
    delete[] data;
    length = str.size();
    data = new char[length+1];
    strcpy(data, str.c_str());
    return *this;
}

myString::~myString()
{
    cout << "~myString" << endl;
}

int myString::size() const
{
    return length;
}

myString::myString(const char* str)
{
    if(!str){
        length = 0;
        data = new char[1];
        *data = '\0';
    }else{
        length = strlen(str);
        data = new char[length+1];
        strcpy(data, str);
    }
}

int main()
{
    
    myString x("sdf");
    myString y;
    cout << "already" << endl;
    y = "fffff";
    
    myString z = x + y;
    
    cout << y.data << " " << y.size() << endl;
    cout << x.data << " " << x.size() << endl;
    cout << z.data << " " << z.size() << endl;
    int a = 'a' + 1;
    cout << typeid(a).name() << " " << a << endl;
}
