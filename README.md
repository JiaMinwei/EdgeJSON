#  EdgeJSON

这是一个用C++编写的json类库,用于构建以及解析json文件,并提供简洁的API用来访问数据.

## 文档目录

* [许可证](#许可证)
* [使用](#使用)
  * [EdgeJSON介绍](#EdgeJSON介绍)
  * [数据结构](#数据结构)
  * [接口类](#接口类)
  * [举例](#举例)
    * [构建](#构建)
    * [解析](#解析)
    * [打印](#打印)
    * [删除](#删除)
    * [访问数据](#访问数据)
  * [注意事项](#注意事项)

## 许可证
>EdgeJSON-许可协议
>
>Copyright (c) 2018 Jiaminwei
>
>1.序言:本协议用于管辖用户及商业实体 (以下简称：被许可人) 和软件原作者（以下简称：许可方）之间
  的关系。使用本软件（包括但不限于复制、下载、安装、运行本软件）即视为同意本协议。本协议规定了
  使用许可方创建和拥有的EdgeJSON (以下简称本软件) 的条款、权利、限制和义务，详情如下:
>
>2.许可证授予:许可方特此授予被许可人个人复制、分发、修改以及非商业性使用本软件的权利(商业使用请
  联系软件原作者)。
>
>3.被许可人义务:  
  3.1在延伸的代码中（修改和由本软件的源代码衍生的代码中）必须包含原代码中的协议与声明。  
	3.2.若被许可人修改了代码，则必须在被修改的文件中作出相应说明。
>
>4.受限:禁止被许可人以商业或盈利为目的使用本软件或其衍生作品（包括但不限于修改本软件、以本软件为
  基础进行二次开发、调用本软件所定义的接口等）。
>
>5.终止:  
  5.1若被许可人有违本协议任一条款即自动终止许可。  
	5.2.许可方有权终止本协议及对被许可人的许可。
>
>6.免责条款:在法律允许的范围内，软件是根据原样提供的。许可方不应对因本软件的操作、故障、bug或本软
  件与被许可方的最终设备之间的任何其他交互而招致的任何损害、费用、任何其他付款承担责任，此外，在
  依赖本软件或使用本软件的源代码时， 许可方不应对被许可方编写的源代码中的任何缺陷负责。
>
>7.保留权利：许可方有权修改本协议条款（若被许可人不认同修改后的协议条款，可停止使用本软件，继续使
  用即代表同意修改后的协议条款），并对本协议未尽事宜保留所有权利。
## 使用

### EdgeJSON介绍

EdgeJSON是一个轻量级的json类库(一个头文件和一个源码文件,编译后即可使用),有助于程序员快速构建或解析json文件.EdgeJSON没有花里胡哨的功能,仅提供构建和解析以及访问和打印等核心功能,依据二八原则,这些代码足以应对80%的使用场景,后续将视情况酌情添加新的功能.作者会持续提供代码的优化与维护.



### 数据结构

```
enum Types			
{
	EdgeJSON_object,		//7种节点类型
	EdgeJSON_array,
	EdgeJSON_int,
	EdgeJSON_double,
	EdgeJSON_string,
	EdgeJSON_bool,
	EdgeJSON_null,

	EdgeJSON_layer,		//为词法分析器另外扩展2种类型
	EdgeJSON_void
};		

enum Relations		//节点之间的关系
{
	brother,		//兄弟节点关系
	son				//父子节点关系
};

class Node			//节点类
{
  public:
	Node *brother;		//指向兄弟节点的指针
	Node *son;			//指向子节点的指针

	Types node_type;	//节点类型
	string key;			//节点的键名称(如果有)
	
	string value_str;	//节点的值类型,共5种
	int value_int;
	int value_null;
	double value_dou;
	bool value_boo;

	Node();				//构造函数,初始化节点的成员变量

	Node &operator[](const char *);		//获取指定节点的引用
	Node &operator[](int);
};
```

此库的数据结构是类似于链表和树的混合体,具体情况已在代码中注释.



### 接口类

```
class EdgeJSON			//主要类,使用本库的起点,方法皆封装于此
{
  public:
	Node *root;			//指向json结构首节点
	
	EdgeJSON();			//构造函数,初始化root指针

	Node &operator[](const char *);		//获取指定节点的引用
	Node &operator[](int);

	/*加入节点函数,通过参数列表的不同重载函数.
	 *Node是被挂载的节点,Relations表明是以什么身份挂载.
	 *其余参数视加入的节点情况而定.
	 */
	Node *AddKeyvalue(Node &, Relations, const char*, int);			//加入值为int型键值对
	Node *AddKeyvalue(Node &, Relations, const char*, double);		//加入值为double型键值对
	Node *AddKeyvalue(Node &, Relations, const char*, const char *);	//加入值为string型键值对
	Node *AddKeyvalue(Node &, Relations, const char*, bool);			//加入值为bool型键值对
	Node *AddKeyvalue(Node &, Relations, const char *);		//加入null类型

	Node *AddArray(Node &, Relations, const char *);	//加入数组到对象
	Node *AddArray(Node &, Relations);				//加入数组到数组
	Node *AddArray(EdgeJSON &);			//加入数组到EdgeJSON

	Node *AddObject(Node &, Relations, const char *); //加入对象到对象
	Node *AddObject(Node &, Relations);				 //加入对象到数组
	Node *AddObject(EdgeJSON &);			 //加入对象到EdgeJSON

	Node *AddValue(Node &, Relations, int);			//加入int型数组元素
	Node *AddValue(Node &, Relations, double);		//加入double型数组元素
	Node *AddValue(Node &, Relations, const char *);	//加入string型数组元素
	Node *AddValue(Node &, Relations, bool);			//加入bool型数组元素
	Node *AddValue(Node &, Relations);					//加入null数组元素

	string EdgeJSONPrint();				//打印json结构,输出字符串
	bool DeleteEdgeJSON();		//删除整个结构
	void EdgeJSONParse(string);		//解析字符串
};
```

所有的方法都封装于此,所有的操作都要从实例化一个EdgeJSON对象开始.



### 举例

```
{
  "name": "金庸",
  "foreign-language name": "Louis Cha",
  "nationality": "中国",
  "nation": "汉族",
  "birthplace": [
    { "province": "浙江" },
    { "city": "海宁" }
  ],
  "profession": [ "作家", "政论家", "社会活动家" ],
  "works": [ "射雕英雄传", "天龙八部", "倚天屠龙记" ]
}
```

假设要处理的json文件如上所示.



#### 构建

```
EdgeJSON newjson;
newjson.AddObject(newjson);
newjson.AddKeyvalue(newjson[1], son, "name", "金庸");
newjson.AddKeyvalue(newjson["name"], brother, "foreign-language name", "Louis Cha");
newjson.AddKeyvalue(newjson["foreign-language name"], brother, "nationality", "中国");
newjson.AddKeyvalue(newjson["nationality"], brother, "nation", "汉族");
newjson.AddArray(newjson["nation"], brother, "birthplace");
newjson.AddObject(newjson["birthplace"], son);
newjson.AddObject(newjson["birthplace"][1], brother);
newjson.AddKeyvalue(newjson["birthplace"][1], son, "province", "浙江");
newjson.AddKeyvalue(newjson["birthplace"][2], son, "city", "嘉兴");
newjson.AddArray(newjson["birthplace"], brother, "profession");
newjson.AddValue(newjson["profession"], son, "作家");
newjson.AddValue(newjson["profession"][1], brother, "政论家");
newjson.AddValue(newjson["profession"][2], brother, "社会活动家");
newjson.AddArray(newjson["profession"], brother, "works");
newjson.AddValue(newjson["works"], son, "射雕英雄传");
newjson.AddValue(newjson["works"][1], brother, "神雕侠侣");
newjson.AddValue(newjson["works"][2], brother, "倚天屠龙记");
```

EdgeJSON对象加[]用来返回json结构首节点的子节点的引用.

Node对象加[]用来返回当前节点子节点的引用(子节点的兄弟节点也是当前节点的子节点).

[]中的字符串用于访问带键名称的子节点,数字用于访问无键名称的子节点(从1开始).



#### 解析

```
newjson.EdgeJSONParse(s);			//调用解析方法
```

直接用EdgeJSON对象调用EdgeJSONParse方法,传入要解析的字符串,解析后的json结构挂载在EdgeJSON对象的root成员变量上,可通过EdgeJSON对象访问整个json结构.



#### 打印

```
string EdgeJSONPrint();				//打印json结构,输出字符串
```

用EdgeJSON对象调用EdgeJSONPrint方法,将打印对象下所挂载的json结构,返回字符串.



#### 删除

```
bool DeleteEdgeJSON();		//删除整个结构
```

用EdgeJSON对象调用DeleteEdgeJSON方法,将删除对象下所挂载的json结构,返回bool值,标示成功或失败.



#### 访问数据

```
newjson["birthplace"][2]["city"].value_str = "海宁";
newjson["works"][2].value_str = "天龙八部";
```

获得需要操作的节点的引用后,访问成员变量,可进行读取或赋值操作.



### 注意事项

* 打印方法返回的是未经格式化的字符串.
* 暂未对json结构嵌套深度做限制,使用时请注意堆区和栈区溢出问题.