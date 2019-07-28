/*
EJ-许可协议
Copyright (c) 2019 Jiaminwei

1.序言:本协议用于管辖用户及商业实体 (以下简称：被许可人) 和软件原作者（以下简称：许可方）之间
  的关系。使用本软件（包括但不限于复制、下载、安装、运行本软件）即视为同意本协议。本协议规定了
  使用许可方创建和拥有的EJ (以下简称本软件) 的条款、权利、限制和义务，详情如下:
2.许可证授予:许可方特此授予被许可人个人复制、分发、修改以及非商业性使用本软件的权利(商业使用请
  联系软件原作者)。
3.被许可人义务：
	3.1.在延伸的代码中（修改和由本软件的源代码衍生的代码中）必须包含原代码中的协议与声明。
	3.2.若被许可人修改了代码，则必须在被修改的文件中作出相应说明。
4.受限:禁止被许可人以商业或盈利为目的使用本软件或其衍生作品（包括但不限于修改本软件、以本软件为
  基础进行二次开发、调用本软件所定义的接口等）。
5.终止:
	5.1.若被许可人有违本协议任一条款即自动终止许可。
	5.2.许可方有权终止本协议及对被许可人的许可。
6.免责条款:在法律允许的范围内，软件是根据原样提供的。许可方不应对因本软件的操作、故障、bug或本软
  件与被许可方的最终设备之间的任何其他交互而招致的任何损害、费用、任何其他付款承担责任，此外，在
  依赖本软件或使用本软件的源代码时， 许可方不应对被许可方编写的源代码中的任何缺陷负责。
7.保留权利：许可方有权修改本协议条款（若被许可人不认同修改后的协议条款，可停止使用本软件，继续使
  用即代表同意修改后的协议条款），并对本协议未尽事宜保留所有权利。
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>

#define STRMODE 'S'
#define FILEMODE 'F'

//#define DEBUG

using namespace std;

enum NodeTypes
{
	EJ_object, //7种节点类型
	EJ_array,
	EJ_int,
	EJ_double,
	EJ_string,
	EJ_bool,
	EJ_null
};

enum TokenTypes //token类型
{
	EJToken_leftObj,
	EJToken_rightObj,
	EJToken_leftArr,
	EJToken_rightArr,
	EJToken_colon,
	EJToken_comma,
	EJToken_string,
	EJToken_double,
	EJToken_int,
	EJToken_bool,
	EJToken_null
};

struct Node //节点类
{
	friend class EJ;

private:
	vector<Node *> children; //指向子节点的指针

	NodeTypes node_type; //节点类型
public:
	string key;		  //节点的键名称(如果有)
	string value_str; //节点的值类型,共5种

	union {
		long long value_int;
		int value_null;
		double value_dou;
		bool value_boo;
	} value;

public:
	~Node();
	Node &operator[](const char *); //获取指定节点的引用
	Node &operator[](int);

	/*加入节点函数,通过参数列表的不同重载函数.
	 *当前节点是被挂载的节点,
	 *其余参数视加入的节点情况而定.
	 */
	Node &AddKeyvalue(const char *, int);		   //加入值为int型键值对
	Node &AddKeyvalue(const char *, double);	   //加入值为double型键值对
	Node &AddKeyvalue(const char *, const char *); //加入值为string型键值对
	Node &AddKeyvalue(const char *, bool);		   //加入值为bool型键值对
	Node &AddKeyvalue(const char *);			   //加入null类型

	Node &AddArray(const char *); //加入数组到对象
	Node &AddArray();			  //加入数组到数组

	Node &AddObject(const char *); //加入对象到对象
	Node &AddObject();			   //加入对象到数组

	Node &AddValue(int);		  //加入int型数组元素
	Node &AddValue(double);		  //加入double型数组元素
	Node &AddValue(const char *); //加入string型数组元素
	Node &AddValue(bool);		  //加入bool型数组元素
	Node &AddValue();			  //加入null数组元素

private:
	Node &GetNode(const char *c);	//获得当前节点的子节点中键为c的节点引用
	Node &GetNode(int i);	//获得当前节点的子节点中第i个子节点的引用
	inline Node *CreatNode();	//创建新节点并挂载到当前节点
};

struct Token //词法分析器词素的存储
{
public:
	TokenTypes token_type; //词素类型
	string token_str;	  //词素内容
};

class EJ //主要类,使用本库的起点,方法皆封装于此
{
private:
	Node *root; //指向json结构首节点
	char mode;	//解析模式，有字符串和文件解析两种
	string *inStr;	//字符串解析模式存储字符串指针
	ifstream *file;	//文件解析模式保存文件指针
	int index;
public:
	EJ(); //构造函数,初始化root指针

	Node &operator[](const char *); //获取指定节点的引用
	Node &operator[](int);

	Node &AddArray();  //加入数组到EJ
	Node &AddObject(); //加入对象到EJ

	string EJPrint();			  //打印json结构,输出字符串
	void DeleteEJ();			  //删除整个结构
	bool EJParse(string *str);	//解析json字符串
	bool EJParse(char *filePath); //解析json文件

private:
	string TraversalPrint(Node *); //遍历类树结构的每个节点以便生成输出字符串
	string PrintObject(Node *);	//打印对象
	string PrintArray(Node *);	 //打印数组
	string PrintKeyvalue(Node *);  //打印键值

	bool parse();	//解析json
	inline char nextChar();	//获得下一个字符
	inline Token *nextToken();	//获得下一个token

	// Node *ParseObject(string); //解析对象
	// Node *ParseArray(string);  //解析数组
	// Node *ParseInt(string);	//解析int
	// Node *ParseDouble(string); //解析double
	// Node *ParseString(string); //解析string
	// Node *ParseBool(string);   //解析bool
	// Node *ParseNull(string);   //解析null
};
