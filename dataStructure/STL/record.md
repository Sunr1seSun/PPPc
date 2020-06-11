## 字符串归纳

### 一、string

#### 1、初始化方法

- `string s1();`
- `string s2("Hello");`
- `string s3(4, 'K');`：s3 = "KKKK"
- `string s4("12345", 1, 3);`：s4 = "234"

#### 2、赋值

- =赋值

- assign赋值
  - `s1.assign(s2);`
  - `s1.assign(s2, index, n);` 
  - `s1.assign(4, 'K');`

#### 3、连接

- +=
- append

#### 4、子串

`substr(index, n);`

#### 5、转换

- string数字转换
  - `stoi()`
  - `to_string()`
-  string char转换
  - `str.c_str()`转为char*
  - `string s = char*`直接赋值

### 二、set

#### 1、初始化方法

- `set<T> s;`
- `set<T> s(s1);`
- `set<T> s(b, e);`

#### 2、数据插入

- insert()

#### 3、查找和读取

- count()：返回查找元素出现的次数。
- find()：返回查找元素的迭代器，找不到返回`s.end()`。

#### 4、删除

- erase(k)：删除某个元素
- erase(p)：删除迭代器p指向的元素
- erase(b,e)：删除迭代器b,e之间的元素。

### 三、map

#### 1、pair类型

初始化：

- `pair<T1, T2> p;`
- `pair<T1, T2> p(v1, v2);`
- `make_pair(v1, v2);`

操作：

- `p.first`
- `p.second`

#### 2、初始化方法

- `map<k, v> m;`
- `map<k, v> m(m2);`
- `map<k, v> m(b, e);`

#### 3、插入

两种方法：

- 使用下标
  - 在map中使用下标访问不存在的元素将导致在map容器中添加一个新的元素。
- 使用insert函数
  - `m.insert(e)`
  - `m.insert(beg, end)`
  - `m.insert(iter, e)`

#### 4、查找和读取

- count()：返回查找元素出现的次数。
- find()：返回查找元素的迭代器，找不到返回`m.end()`。

#### 5、删除

- `m.erase(k)`
- `m.erase(p)`
- `m.erase(b, e)`