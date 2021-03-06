[TOC]
> 作者: 苏丙榅
链接: https://subingwen.cn/qt/qt-json/#4-QJsonDocument
来源: 爱编程的大丙
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
### JSON
`JSON(JavaScrip Object Notation)` 是一种轻量级的数据交换格式。它基于 ECMAScript (欧洲计算机协会制定的 js 规范) 的一个子集，采用完全独立于编程语言的文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

关于上面的描述可以精简为一句话：<font color=blue>Json 是一种数据格式，和语言无关，在什么语言中都可以使用 Json。</font>基于这种通用的数据格式，一般处理两方面的任务：

* 组织数据（数据序列化），用于数据的网络传输
* 组织数据（数据序列化），写磁盘文件实现数据的持久化存储（一般以.json 作为文件后缀）

Json 中主要有两种数据格式：Json 数组和 Json 对象，并且这两种格式可以交叉嵌套使用，下面依次介绍下这两种数据格式：

### 1. Json 数组

Json 数组使用 [] 表示，[] 里边是元素，元素和元素之间使用逗号间隔，最后一个元素后边没有逗号，一个 Json 数组中支持同时存在多种不同类型的成员，包括：整形、 浮点、 字符串、 布尔类型、 json数组、 json对象、 空值-null。由此可见 Json 数组比起 C/C++ 数组要灵活很多。

#### 1.1 Json 数组中的元素数据类型一致
```json
// 整形
[1,2,3,4,5]
// 字符串
["luffy", "sanji", "zoro", "nami", "robin"]

```

#### 1.2 Json 数组中的元素数据类型不一致
```json
[12, 13.34, true, false, "hello,world", null]
```
#### 1.3 Json 数组中的数组嵌套使用
```json
[
    ["cat", "dog", "panda", "beer", "rabbit"],
    ["北京", "上海", "天津", "重庆"],
    ["luffy", "boy", 19]
]
```
#### 1.4 Json 数组和对象嵌套使用
```json
    [
        "luffy":{
        	"age":19,
        	"father":"Monkey·D·Dragon",
        	"grandpa":"Monkey D Garp",
        	"brother":"Portgas D Ace",
        	"brother":"Sabo"
        }
    ]
```
### 2. Json 对象

Json 对象使用 {} 来描述，每个 Json 对象中可以存储若干个元素，**每一个元素对应一个键值对（key：value 结构）**，元素和元素之间使用逗号间隔，最后一个元素后边没有逗号。对于每个元素中的键值对有以下细节需要注意：

    **键值（key）必须是字符串，位于同一层级的键值不要重复（因为是通过键值取出对应的 value 值）**
    value 值的类型是可选的，可根据实际需求指定，可用类型包括：`整形、 浮点、 字符串、 布尔类型、 json数组、 json对象、 空值-null`。

#### 2.1 使用 Json 对象描述一个人的信息:
```json
{
    "Name":"Ace",
    "Sex":"man",
    "Age":20,
    "Family":{
        "Father":"Gol·D·Roger",
        "Mother":"Portgas·D·Rouge",
        "Brother":["Sabo", "Monkey D. Luffy"]
    },
    "IsAlive":false,
    "Comment":"yyds"
}
```
### 3. 注意事项

通过上面的介绍可用看到，Json 的结构虽然简单，但是进行嵌套之后就可以描述很复杂的事情，在项目开发过程中往往需要我们根据实际需求自己定义 Json 格式用来存储项目数据。

另外，如果需要将 Json 数据持久化到磁盘文件中，需要注意一个问题：**在一个 Json 文件中只能有一个 Json 数组或者 Json 对象的根节点，不允许同时存储多个并列的根节点**。下面举例说明：

#### 3.1 错误的写法
```cpp
// test.json
{
    "name":"luffy",
    "age":19
}
{
    "user":"ace",
    "passwd":"123456"
}
```
错误原因：在一个 Json 文件中有**两个并列的 Json 根节点**（并列包含 Json 对象和 Json 对象、Json 对象和 Json 数组、Json 数组和 Json 数组,**都是不正确的**），**根节点只能有一个**。

#### 3.2 正确的写法
```cpp
// test.json
{
    "Name":"Ace",
    "Sex":"man",
    "Age":20,
    "Family":{
        "Father":"Gol·D·Roger",
        "Mother":"Portgas·D·Rouge",
        "Brother":["Sabo", "Monkey D. Luffy"]
    },
    "IsAlive":false,
    "Comment":"yyds"
}
```
在上面的例子中通过Json对象以及Json数组的嵌套描述了一个人的身份信息，并且根节点只有一个就是Json对象，如果还需要使用Json数组或者Json对象描述其他信息，需要将这些信息写入到其他文件中，不要和这个Json对象并列写入到同一个文件里边，切记！！！
###  4 Qt json 操作:
在 Json 的两种格式中介绍了 Json 的格式以及应用场景。由于这种数据格式与语言无关，下面介绍一下 Json 在 Qt 中的使用。

从 Qt 5.0 开始提供了对 Json 的支持，我们可以直接使用 Qt 提供的 Json 类进行数据的组织和解析。相关的类常用的主要有四个，具体如下：

|Json 类| 	介绍|
|-------|-------|
|QJsonDocument |	它封装了一个完整的 JSON 文档，并且可以从 UTF-8 编码的基于文本的表示以及 Qt 自己的二进制格式读取和写入该文档。|
|QJsonArray |	JSON 数组是一个值列表。可以通过从数组中插入和删除 QJsonValue 来操作该列表。|
|QJsonObject 	|JSON 对象是键值对的列表，其中键是唯一的字符串，值由 QJsonValue 表示。|
|QJsonValue 	|该类封装了 JSON 支持的数据类型。

#### 4.1. QJsonValue

在 Qt 中 QJsonValue 可以封装的基础数据类型有六种（和 Json 支持的类型一致），分别为：

* 布尔类型：`QJsonValue::Bool`
* 浮点类型（包括整形）： `QJsonValue::Double`
* 字符串类型： `QJsonValue::String`
* Json 数组类型：` QJsonValue::Array`
* Json 对象类型：`QJsonValue::Object`
* 空值类型： `QJsonValue::Null`

这个类型可以通过 QJsonValue 的构造函数被封装为一个类对象:
```cpp
// Json对象
QJsonValue(const QJsonObject &o);
// Json数组
QJsonValue(const QJsonArray &a);
// 字符串
QJsonValue(const char *s);
QJsonValue(QLatin1String s);
QJsonValue(const QString &s);
// 整形 and 浮点型
QJsonValue(qint64 v);
QJsonValue(int v);
QJsonValue(double v);
// 布尔类型
QJsonValue(bool b);
// 空值类型
QJsonValue(QJsonValue::Type type = Null);
```
如果我们得到一个 QJsonValue 对象，如何判断内部封装的到底是什么类型的数据呢？这时候就需要调用相关的判断函数了，具体如下：
```cpp
// 是否是Json数组
bool isArray() const;
// 是否是Json对象
bool isObject() const;
// 是否是布尔类型
bool isBool() const;
// 是否是浮点类型(整形也是通过该函数判断)
bool isDouble() const;
// 是否是空值类型
bool isNull() const;
// 是否是字符串类型
bool isString() const;
// 是否是未定义类型(无法识别的类型)
bool isUndefined() const;
```
通过判断函数得到对象内部数据的实际类型之后，如果有需求就可以再次将其转换为对应的基础数据类型，对应的 API 函数如下：
```cpp
// 转换为Json数组
QJsonArray toArray(const QJsonArray &defaultValue) const;
QJsonArray toArray() const;
// 转换为布尔类型
bool toBool(bool defaultValue = false) const;
// 转换为浮点类型
double toDouble(double defaultValue = 0) const;
// 转换为整形
int toInt(int defaultValue = 0) const;
// 转换为Json对象
QJsonObject toObject(const QJsonObject &defaultValue) const;
QJsonObject toObject() const;
// 转换为字符串类型
QString toString() const;
QString toString(const QString &defaultValue) const;
```
#### 4.2. QJsonObject

QJsonObject 封装了 Json 中的对象，在里边可以存储多个键值对，为了方便操作，键值为字符串类型，值为 QJsonValue 类型。关于这个类的使用类似于 C++ 中的 STL 类，仔细阅读 API 文档即可熟练上手使用，下面介绍一些常用 API 函数:

* 如何创建空的 Json 对象
```cpp
QJsonObject::QJsonObject();	// 构造空对象
```
* 将键值对添加到空对象中
```cpp
iterator QJsonObject::insert(const QString &key, const QJsonValue &value);
```
* 获取对象中键值对个数
```cpp
int QJsonObject::count() const;
int QJsonObject::size() const;
int QJsonObject::length() const;
```
* 通过 key 得到 value
```cpp
QJsonValue QJsonObject::value(const QString &key) const;    // utf8
QJsonValue QJsonObject::value(QLatin1String key) const;	    // 字符串不支持中文
QJsonValue QJsonObject::operator[](const QString &key) const;
QJsonValue QJsonObject::operator[](QLatin1String key) const;
```
* 删除键值对
```cpp
void QJsonObject::remove(const QString &key);
QJsonValue QJsonObject::take(const QString &key);	// 返回key对应的value值
```
* 通过 key 进行查找
```cpp
iterator QJsonObject::find(const QString &key);
bool QJsonObject::contains(const QString &key) const;
```
遍历，方式有三种：

    1. 使用相关的迭代器函数

    2. 使用 [] 的方式遍历，类似于遍历数组，[] 中是键值

    3. 先得到对象中所有的键值，在遍历键值列表，通过 key 得到 value 值
   
```cpp
    QStringList QJsonObject::keys() const;
```
### 4.3. QJsonArray

QJsonArray 封装了 Json 中的数组，在里边可以存储多个元素，为了方便操作，所有的元素类统一为 QJsonValue 类型。关于这个类的使用类似于 C++ 中的 STL 类，仔细阅读 API 文档即可熟练上手使用，下面介绍一些常用 API 函数:

* 创建空的 Json 数组
```cpp
QJsonArray::QJsonArray();
```
* 添加数据
```cpp
void QJsonArray::append(const QJsonValue &value);	// 在尾部追加
void QJsonArray::insert(int i, const QJsonValue &value); // 插入到 i 的位置之前
iterator QJsonArray::insert(iterator before, const QJsonValue &value);
void QJsonArray::prepend(const QJsonValue &value); // 添加到数组头部
void QJsonArray::push_back(const QJsonValue &value); // 添加到尾部
void QJsonArray::push_front(const QJsonValue &value); // 添加到头部
```
* 计算数组元素的个数
```cpp
int QJsonArray::count() const;
int QJsonArray::size() const;
```
* 从数组中取出某一个元素的值
```cpp
QJsonValue QJsonArray::at(int i) const;
QJsonValue QJsonArray::first() const; // 头部元素
QJsonValue QJsonArray::last() const; // 尾部元素
QJsonValueRef QJsonArray::operator[](int i);
```
* 删除数组中的某一个元素
```cpp
    iterator QJsonArray::erase(iterator it);    // 基于迭代器删除
    void QJsonArray::pop_back();           // 删除尾部
    void QJsonArray::pop_front();          // 删除头部
    void QJsonArray::removeAt(int i);      // 删除i位置的元素
    void QJsonArray::removeFirst();        // 删除头部
    void QJsonArray::removeLast();         // 删除尾部
    QJsonValue QJsonArray::takeAt(int i);  // 删除i位置的原始, 并返回删除的元素的值
```
Josn 数组的遍历，常用的方式有两种：
    1. 可以使用迭代器进行遍历（和使用迭代器遍历 STL 容器一样）
    2. 可以使用数组的方式遍历

### 4.4. QJsonDocument

它封装了一个完整的 JSON 文档，并且可以从 UTF-8 编码的基于文本的表示以及 Qt 自己的二进制格式读取和写入该文档。QJsonObject 和 QJsonArray 这两个对象中的数据是不能直接转换为字符串类型的，如果要进行数据传输或者数据的持久化，操作的都是字符串类型而不是 QJsonObject 或者 QJsonArray 类型，我们需要通过一个 Json 文档类进行二者之间的转换。

下面依次介绍一下这两个转换流程应该如何操作:

    QJsonObject 或者 QJsonArray ===> 字符串

* 创建 QJsonDocument 对象
```cpp
QJsonDocument::QJsonDocument(const QJsonObject &object);
QJsonDocument::QJsonDocument(const QJsonArray &array);
```

可以看出，通过构造函数就可以将实例化之后的 **QJsonObject 或者 QJsonArray** 转换为 QJsonDocument 对象了。

将文件对象中的数据进行序列化
```cpp
    // 二进制格式的json字符串
    QByteArray QJsonDocument::toBinaryData() const;	 
    // 文本格式
    QByteArray QJsonDocument::toJson(JsonFormat format = Indented) const;	
```
通过调用 toxxx() 方法就可以得到文本格式或者二进制格式的 Json 字符串了。

* 使用得到的字符串进行数据传输，或者磁盘文件持久化

`字符串 ===> QJsonObject 或者 QJsonArray`

一般情况下，通过网络通信或者读磁盘文件就会得到一个 Json 格式的字符串，如果想要得到相关的原始数据就需要对字符串中的数据进行解析，具体解析流程如下：

将得到的 Json 格式字符串通过 QJsonDocument 类的静态函数转换为 QJsonDocument 类对象
```cpp
[static] QJsonDocument QJsonDocument::fromBinaryData(const QByteArray &data, DataValidation validation = Validate);
// 参数文件格式的json字符串
[static] QJsonDocument QJsonDocument::fromJson(const QByteArray &json, QJsonParseError *error = Q_NULLPTR);
```
* 将文档对象转换为 json 数组 / 对象
```cpp
    // 判断文档对象中存储的数据是不是数组
    bool QJsonDocument::isArray() const;
    // 判断文档对象中存储的数据是不是json对象
    bool QJsonDocument::isObject() const
        
    // 文档对象中的数据转换为json对象
    QJsonObject QJsonDocument::object() const;
    // 文档对象中的数据转换为json数组
    QJsonArray QJsonDocument::array() const;
```
 通过调用 QJsonArray , QJsonObject 类提供的 API 读出存储在对象中的数据。

关于 Qt 中 Json 数据对象以及字符串之间的转换的操作流程是固定的，我们在编码过程中只需要按照上述模板处理即可，相关的操作是没有太多的技术含量可言的。

```cpp
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
void Widget::writeJson()
{
    QJsonObject obj;
    obj.insert("Name","zhansan");
    obj.insert("Sex","man");
    obj.insert("age",25);

    QJsonObject subJsonObj;
    subJsonObj.insert("hobic","play games");
    subJsonObj.insert("test",1);
    subJsonObj.insert("bool",true);

    QJsonArray jsonArray;
    jsonArray.append("test1");
    jsonArray.append(true);
    jsonArray.append(100);

    subJsonObj.insert("subArray",jsonArray);
    obj.insert("test2",100.5);
    obj.insert("test3","this is a string");
    obj.insert("test4",subJsonObj);

    QJsonDocument doc(obj);
    QByteArray json= doc.toJson();
    QFile file("test.json");
    file.open(QFile::OpenModeFlag::WriteOnly);
    file.write(json);
    file.close();
}

void Widget::readJson()
{
    QFile file("/home/mrzhao/Documents/Qt/Test/build-JsonTest-Desktop_Qt_5_14_2_GCC_64bit-Debug/test.json");
    file.open(QFile::OpenModeFlag::ReadOnly);
    QByteArray json=file.readAll();
    file.close();

    QJsonDocument doc=QJsonDocument::fromJson(json);
    if(doc.isObject())
    {
        QJsonObject obj=doc.object();
        QStringList keys= obj.keys();

        for(int i=0;i<keys.size();i++)
        {
            QString key=keys.at(i);
            QJsonValue value=obj.value(key);

            if(value.isBool())
            {
                qDebug()<<key<<":"<<value.toBool()<<endl;
            }
            if(value.isString())
            {
                qDebug()<<key<<":"<<value.toString()<<endl;
            }
            if(value.isDouble())
            {
                qDebug() << key << ":" << value.toDouble();
            }

            if(value.isObject())
            {
                qDebug()<< key << ":";
                QJsonObject subObj=value.toObject();
                QStringList subKeys=subObj.keys();
                for(int j=0;j<subKeys.size();j++)
                {
                    QJsonValue subValue=subObj.value(subKeys.at(j));//此处未再声明key;
                    if(subValue.isString())
                    {
                        qDebug()<<subKeys.at(j)<<":"<<subValue.toString()<<endl;
                    }
                    if(subValue.isBool())
                    {
                        qDebug()<<subKeys.at(j)<<":"<<subValue.toBool()<<endl;
                    }
                    if(subValue.isArray())
                    {
                        QJsonArray subArray=subValue.toArray();
                        qDebug() << "   " << subKeys.at(j) << ":";
                        for(int k=0;k<subArray.size();k++)
                        {
                            if(subArray.at(k).isString())
                            {
                                qDebug()<<subArray.at(k)<<":"<<subArray.at(k).toString()<<endl;
                            }
                            if(subArray.at(k).isBool())
                            {
                                qDebug()<<subArray.at(k)<<":"<<subArray.at(k).toBool()<<endl;
                            }
                            if(subArray.at(k).isDouble())
                            {
                                qDebug()<<" "<<subArray[k].toDouble()<<endl;
                            }
                        }
                    }
                }
            }

        }
    }
}


```