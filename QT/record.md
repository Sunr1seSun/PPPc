### 信号槽

```c++
QObject::connect(sender, signal, receiver, slot);
```

- sender：发出信号的对象
- signal：发送对象发出的信号 
- receiver：接收信号的对象
- slot：接收对象在接收到信号之后所需要调用的函数

#### 例子

```c++
#include <QObject>
////////// newspaper.h //////////
class Newspaper : public QObject
{
    Q_OBJECT
public:
    Newspaper(const QString & name) :
        m_name(name)
    {
    }
 
    void send()
    {
        emit newPaper(m_name);
    }
 
signals:
    void newPaper(const QString &name);
 
private:
    QString m_name;
};
 
////////// reader.h //////////
#include <QObject>
#include <QDebug>
 
class Reader : public QObject
{
    Q_OBJECT
public:
    Reader() {}
 
    void receiveNewspaper(const QString & name)
    {
        qDebug() << "Receives Newspaper: " << name;
    }
};
 
////////// main.cpp //////////
#include <QCoreApplication>
 
#include "newspaper.h"
#include "reader.h"
 
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
 
    Newspaper newspaper("Newspaper A");
    Reader reader;
    QObject::connect(&newspaper, &Newspaper::newPaper,
                     &reader,    &Reader::receiveNewspaper);
    newspaper.send();
 
    return app.exec();
}
```

newspaper对象发出一个信号，reader接收信号并处理。

- 只有集成`QObject`类，才有信号槽的能力，QObject类第一行都应写`Q_OBJECT`。
- `signals:`后列出的是该类的信号，信号是一个个函数。该函数返回值是void，参数是要传递的数据。信号由`emit`关键字发出。

- 成员函数，static函数，全局函数和lambda函数都可以作为槽函数。

注意：

- signals是函数声明，不需要实现函数代码。
- 槽函数是普通成员函数，受到public，private，protected影响。

更多用法：

- 一个信号可以和多个槽相连

- 多个信号可以连接到一个槽

- 信号可以连接到信号（？）

- Lambda表达式

  - ```c++
    /*函数原型（重载）
    QMetaObject::Connection QObject::connect(const QObject *sender,PointerToMemberFunction signal, Functor functor)
    */
    QObject::connect(&newspaper, static_cast
                     <void (Newspaper:: *)(const QString &)>
                     (&Newspaper::newPaper),
                     [=](const QString &name) 
                     { /* Your code here. */ }
    );
    ```

  - ```c++
    [函数对象参数](操作符重载函数参数)mutable或exception -> 返回值
    {函数体}
    ```

    - []，标识一个Lambda的开始，函数对象参数只能使用lambda所在范围的可见局部变量，有以下形式：
      - 空。没有函数对象参数。
      - =。所有可见局部变量，值传递。
      - &。所有可见局部变量，引用传递。
      - this。所在类中的成员变量。
      - a。将a值传递。
      - &a。将a引用传递
      - a，&b。将a值传递，b引用传递。
    - 操作符重载函数参数
      - 没有参数时，可以省略
    - 可修改标识符
      - mutable，值传递参数时，加上mutable可以修改传递进来的拷贝。

---

### 对象模型

QT引入对象树的概念，一定程度上解决了内存问题。

- 当一个QObject对象在堆上创建的时候，Qt会同时为其创建一个对象树。
- 对象树中的QObject对象delete的时候，如果这个对象有parent，则自动将其从parent的children()列表中删除；如果有孩子，自动delete每一个孩子。

习惯：尽量在构造的时候就指定parent对象，并且大胆在堆上创建。

---

### QMainWindow

为用户提供主窗口程序的类，包含一个菜单栏(menu bar)、多个工具栏(tool bars)、多个锚接部件(dock widgets)、一个状态栏(status bar)及一个中心部件(central widget)，是许多应用程序的基础，如文本编辑器，图片编辑器等。

#### 1 菜单栏

- 创建菜单栏

```c++
QMenuBar *	menuBar() const
```

- 创建菜单

```c++
QAction* addMenu(QMenu * menu)
QMenu* addMenu(const QString & title)
QMenu* addMenu(const QIcon & icon, const QString & title)
```

- 创建菜单项

```c++
QAction* activeAction() const
QAction* addAction(const QString & text)
QAction* addAction(const QIcon & icon, const QString & text)
QAction* addAction(const QString & text, const QObject * receiver,
 const char * member, const QKeySequence & shortcut = 0)
QAction* addAction(const QIcon & icon, const QString & text, 
const QObject * receiver, const char * member, 
const QKeySequence & shortcut = 0)
```

QMenuBar > QMenu > QAction

QAction添加到菜单，就显示成一个菜单项，添加到工具栏就显示成一个工具按钮。

#### 2 工具栏

`addToolBar（）`

---

### 对话框QDialog

#### 1 标准对话框

- QColorDialog：       选择颜色；
- QFileDialog：        选择文件或者目录；
- QFontDialog：        选择字体；
- QInputDialog：       允许用户输入一个值，并将其值返回；
- QMessageBox：        模态对话框，用于显示信息、询问问题等；
- QPageSetupDialog：   为打印机提供纸张相关的选项；
- QPrintDialog：       打印机配置；
- QPrintPreviewDialog：打印预览；
- QProgressDialog：    显示操作过程。

#### 2 自定义消息框

Qt 支持模态对话框和非模态对话框。

模态与非模态的实现：

- 使用QDialog::exec()实现应用程序级别的模态对话框
  - 用户必须首先对对话框进行交互。

- 使用QDialog::open()实现窗口级别的模态对话框
  - 仅仅阻塞与对话框关联的窗口，依然允许与其他窗口交互。

- 使用QDialog::show()实现非模态对话框。

#### 3 消息对话框

`QMessageBox`