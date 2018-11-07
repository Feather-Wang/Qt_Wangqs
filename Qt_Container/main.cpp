#include <QApplication>
#include <QLinkedList>
#include <QTextEdit>

QString show;

/*
一、介绍
Qt中除了可以使用C++ STL标准库的容器外，本身还提供了多种容器。包括QList<T>、QVector<T>、QMap<K,T>等。

二、Qt的容器的优势
Qt容器的主要优点是它们在所有的平台上在运行时都表现的一致，并且它们都采用了隐含共享技术。
而且，Qt的容器的另一个主要特征是易于使用的迭代器类，这是从Java中得到的灵感，它们可以利用QDataStream变成数据流，而且它们通常可以使可执行文件中的代码量比相应的STL类要少。
最后，在Qt/Embedded Linux支持的一些硬件平台上，通常只能使用Qt的容器。


三、关于隐含共享
隐含共享（implicit sharing），或者称为“写时复制”，是一个能够把整个容器作为不需要太多运行成本的值来传递的最优化过程。
就是当发生写操作时，才会对数据进行复制，其核心是数据的引用计数的使用。
通过对引用的数据，添加引用计数，来判断是否进行复制。引用计数的取值，如下：
0：表示数据没有被任何对象引用，这部分数据所占的内存将会被释放。
1：表示数据只有被一个对象引用，当发生写操作时，不用进行复制，直接修改。
大于1：表示数据被多个对象引用，当其中一个对象产生些操作时，首先为该对象复制一份数据，让该对象引用新复制的数据，复制后的数据的引用计数记为1，原数据的引用计数减一，然后在进行数据的修改。

举例：
QSring str1 = “first”；
此时，“first”的引用计数是1。
QString str2 = str1;
因为将str1赋给str2，所以str2也指向了"first"，此时"first"的引用计数为2。
str2[0] = 'D';
此时，修改str2的第一个字符，发生了写操作，会先检查指向数据的引用计数是否为1，如果大于1，就先将数据做一次复制，然后让str2指向复制的数据，且数据的引用计数设置为1，然后再将写的数据修改到复制后的数据上。并且，将原数据"first"的引用计数也改为1（此时，只有str1引用了该数据）。
str2[1] = 'F';
第二次修改str2的数据时，因为这时候数据的引用计数为1，表示没有其它对象引用该数据，所以可以直接修改，而不会发送复制行为。
str1 = str2;
将str2复制给str1，也就是让str1指向str2指向的数据，此时，该数据的引用计数+1，也就是2，而str1原来指向的数据的引用计数变为0，表名没有被引用，这些数据就会从内存中释放。

一般情况下，引用计数会存在竞争的情况，所以数据共享在多线程中通常只是作为一个选项而没有给予关注。
使用Qt，这并不是一个问题，在内部，容器类使用汇编语言指令执行基本的引用计数，通过QSharedData和QSharedDataPointer类，Qt的用户也可以使用这项技术。

四、Qt的容器的分类
Qt提供的容器类分为两种：连续容器类、关联容器类。
连续容器类：类似于数组，元素是连续存放的。Qt提供的连续容器有：QVector<T>、QLinkedList<T>、QList<T>
关联容器类：关联容器存储的是键值对。Qt提供的关联容器有：QMap<K,T>、QHash<K,T>

五、关于容器的元素的类型
在所有的容器类中，元素类型都是T，类型T可以是一个基础类型、指针类型、具有默认构造函数的类（没有参数的构造函数）、复制构造函数或者赋值操作符的类。
例如：QByteArray、QDateTime、QRegExp、QString和QVariant。
派生自QObject的Qt类不具备资格，因为它们没有复制构造函数和赋值操作符，这在实际应用中并不是问题，因为我们可以简单的存储指向QObject类的指针而不是对象本身。
类型T也可以是一个容器，在这种情况下，必须记得用空格分开连续的尖括号，否则，编译器将会把连续的尖括号认作是>>操作符而停止工作。
例如：QList<QVector<double> >list;
在QMap<K,T>容器中，因为所有的键值对都是以升序排列的，所以类型K，还必须提供operator <()。

六、关于迭代器
对于每种容器类，都有两种Java风格的迭代器类型：只读迭代器、读-写迭代器。
只读迭代器有：QVectorIterator<T>、QLinkedListIterator<T>、QListIterator<T>
读-写迭代器，则是在其名字前都含有”Mutable“的字样：QMutableVectorIterator<T>、QMutableLinkedListIterator<T>、QMutableListIterator<T>

七、关于容器的通用算法
Qt还提供了在任意容器上执行相关操作的通用算法，这些算法与STL所提供的算法类似：
qSort()：对一个连续容器进行排序
qBinaryFind()：在经过排序的连续容器上执行一个二分搜索
*/


/*
QVector<T>：
缺点：当容器内的元素过多时，在容器的开头或者中间插入项，或者在这些位置删除项，都是非常耗时的
*/
void QVector_Test()
{
    /*创建一个含有3个元素的QVector容器*/
    /*元素将会调用默认构造函数进行初始化。基本类型和指针类型都会被初始化为0*/
    QVector<double> vect1(3);
    /*直接为这三个元素赋值*/
    vect1[0] = 1.0;
    vect1[1] = 1.1;
    vect1[2] = 1.2;

    /*创建一个空的QVector容器*/
    QVector<double> vect2;
    /*通过append()向QVector的末端添加新的元素*/
    vect2.append(1.0);
    vect2.append(1.1);
    vect2.append(1.2);
    /*也可以使用"<<"代替append()*/
    vect2 << 1.5 << 1.4 << 1.3;

    /*从序号为2的元素开始，移除3个元素，也可以不写第二个参数，默认为1*/
    vect2.remove(2, 3);

    /*遍历QVector容器的方法一*/
    for( int i = 0; i < vect2.count(); ++i)
    {
        double element = vect2[i];

        show.append(QString("element = %1\n").arg(element));
    }
    /*遍历QVector容器的方法二：迭代器*/

}

/*
QLinkedList<T>
内部采用的是链表结构，链表不支持快速的随机访问，但提供了“常量时间”的插入和删除
*/
void QLinkedList_test()
{
    QLinkedList<QString> list;
    list.append("1.0");
    list.append("1.5");
    list.append("1.2");

    QLinkedListIterator<QString> i(list);
    while( i.hasNext() )
    {
        QString element = i.next();
        show.append(element + "\n");
    }
}

/*
QList<T>连续容器是一个“数组列表”，结合了单一类中QVector<T>和QLinkedList<T>的最重要的优点。
它支持随机访问，而且它的界面与QVector的一样是基于索引的。
在QList<T>的任意一端插入或移除项都是非常快速的，并且对含1000项以上的列表来说，在中间插入项也是很快的，除非我们想在一个极大的列表中执行插入或者要求列表中的元素都必须占据连续的内存地址，否则QList<T>通常是最适合采用的多用途容器类。
*/
void QList_test()
{
    /*QList容器，不能像QVector容器一样，直接设置容器的元素个数，只能通过append()或者<<操作符添加新元素*/
    QList<double> list;
    /*为容器预留100个元素的内存空间*/
    list.reserve(100);

    list.append(1.0);
    list.append(1.1);
    /*可以添加相同的值的元素*/
    list.append(1.2);
    list.append(1.2);

    list << 1.3 << 1.4 << 1.5;

    /*在容器的最前面，添加元素2*/
    list.prepend(2);
    /*在序号为2的位置，插入元素10.5，序号为2以后的元素（包括2）顺序后移*/
    list.insert(2, 10.5);
    /*修改序号为1的元素的值为200.5*/
    list.replace(1, 200.5);
    /*移除所有值为10.5的元素*/
    list.removeAll(10.5);
    /*获取值为1.2的元素的个数*/
    int count = list.count(1.2);
    list.isEmpty();

    /*遍历QList容器的方法*/
    /*方法一：使用序号*/
    for( int i = 0; i < list.count(); ++i)
    {
        double element = list[i];
        element = list.at(i);
        element = list.value(i);
        element = list.value(i, 100);
    }
    /*方法二：使用迭代器，可以是只读迭代器，也可以是读写迭代器*/
    QListIterator<double> i1(list);
    /*从开始向后遍历*/
    /*回到迭代器的最前面，初始化迭代器后默认是在最前面*/
    i1.toFront();
    while( i1.hasNext() )
    {
        double element = i1.next();
        show.append(QString("FrontToLast : element = %1\n").arg(element));
    }
    /*从结尾向前遍历*/
    i1.toBack();
    while( i1.hasPrevious() )
    {
        double element = i1.previous();
        show.append(QString("LastToFront : element = %1\n").arg(element));
    }

    /*读写迭代器*/
    QMutableListIterator<double> i2(list);

    while( i2.hasNext() )
    {
        /*
         * remove()总是对最后被跳过的项做操作，不管是向前跳或者向后跳
         * setValue()总是对最后被跳过的项做操作，不管是向前跳或者向后跳
         * next()则返回当前指针后面的项，并且跳过这个项
         */
        if( i2.next() < 1.3 )
            i2.remove();
        //if( i2.value() < 1.3 )
            //i2.setValue( -i2.value() );
    }

    /*STL风格的迭代器*/
    for(QList<double>::iterator i = list.begin(); i != list.end(); ++i)
    {
        double element = *i;
        *i = element;
        show.append(QString("changed : element = %1\n").arg(element));
    }
}

/*
QStringList类是被广泛用于Qt应用编程接口的QList<QString>的子类。
除了从它的基类继承的函数外，QStringList还提供了一些特别的函数，以使得这种类对字符串的处理方式更通用。
*/
void QStringList_test()
{}

/*
QStack<T>：栈容器类
*/
void QStacl_test()
{}

/*
QQueue<T>：队列容器类
*/
void QQueue_test()
{}


/*以下是关联容器*/

/*
QMap<K,T>：是一个以升序键顺序存储键值对的数据结构，这种排列使它可以提供良好的查找和插入性能以及键序的迭代。
在内部，QMap<K,T>是作为一个跳跃表（Skip-List）来实现执行的。
*/
void QMap_test()
{
    /*创建一个空的QMap容器*/
    QMap<QString, int> map;
    /*添加新的键值对，方法一*/
    map.insert("first", 1);
    map.insert("second", 2);
    map.insert("eight", 8);
    /*添加新的键值对，方法二，使用[]操作符，既可以用于插入也可以用于检索。如果在非常量映射中使用[]为一个不存在的键检索值，则会用给定的键和空值创建一个新的键值对，所以，为了避免意外的创建空值，可以使用value(0函数替代[]操作符来获得项*/
    map["five"] = 5;
    map["nine"] = 9;

    int val = map.value("first");
    /*如果键值对不存在，也可以设置一个返回的默认值，同时不会创建新的项*/
    val = map.value("first", 100);

    /*通过keys()函数，可以获得键的QList，通过values()函数，可以获得值的QList*/
    QList<QString> keys = map.keys();
    QList<int> vals = map.values();

    /*修改key值*/
    map["five"] = 15;
    QMap<QString, int>::iterator iter = map.find("first");
    map.erase(iter);

    /*遍历容器，使用Java风格的迭代器*/
    /*因为QMap容器存在键和值两个值，所以它返回的信息，也是一个数据结构，如果只是获取单个的信息，比如只获取key，或者只获取value，可以通过i.next().key()或者i.next().value()来获取，如果需要同时获取，就不能这样做了，下面给出了两种方式去同时获取key和value*/
    QMutableMapIterator<QString, int> i(map);
    while( i.hasNext() )
    {
        /*通过迭代器的key()和value()获取，因为这两个函数返回的是最后一个被跳过的项的数据，所以还要先调用next()*/
        i.next();
        /*当迭代器是读-写迭代器时，可以通过setValue()修改key-value对的value值，与key()和value()一样，setValue()也是针对的最后一个被跳过的项*/
        i.setValue(1);

        QString key = i.key();
        int val = i.value();

        show.append(QString("element = %1:%2\n").arg(key).arg(val));
    }
}

/*QMultiMap<K,T>：该容器是QMap<K,T>的一个子类，可以支持一个键对应多个值，QMap只支持一个键对应一个值*/
void QMultiMap_test()
{
    QMultiMap<int,QString> multiMap;
    multiMap.insert(1, "one_one");
    multiMap.insert(1, "one_two");
    multiMap.insert(1, "one_three");

    QList<QString> vals = multiMap.values(1);
}

/*
QHash<K,T>：是一个在哈希表上存储键值对的容器，它提供了比QMap更快的查找功能，存储的键值对是无序的。
它的接口几乎与QMap<K,T>相同，但是与QMap相比，它对K的模板类型有不同的要求，需要提供一个operator ==()，并且需要一个能够为键返回哈希值的全局qHash()函数的支持，Qt已经为qHash()函数提供了整型、指针型、QChar、QString以及QByteArray。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    show.append("QVector_test()...\n\n");
    QVector_Test();

    show.append("\n\nQLinkedList_test()...\n\n");
    QLinkedList_test();

    show.append("\n\nQList_test()...\n\n");
    QList_test();

    show.append("\n\nQMap_test()...\n\n");
    QMap_test();

    QTextEdit text;
    text.setText(show);
    text.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    text.show();

    return a.exec();
}
