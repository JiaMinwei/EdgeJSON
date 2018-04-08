/*
EdgeJSON-许可协议
Copyright (c) 2018 Jiaminwei

1.序言:本协议用于管辖用户及商业实体 (以下简称：被许可人) 和软件原作者（以下简称：许可方）之间
  的关系。使用本软件（包括但不限于复制、下载、安装、运行本软件）即视为同意本协议。本协议规定了
  使用许可方创建和拥有的EdgeJSON (以下简称本软件) 的条款、权利、限制和义务，详情如下:
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

using namespace std;

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
	
	string value_str;	//节点的值类型,共4种
	int value_int;
	int value_null;
	double value_dou;
	bool value_boo;

	Node();				//构造函数,初始化节点的成员变量

	Node &operator[](const char *);		//获取指定节点的引用
	Node &operator[](int);
};

class token				//词法分析器词素的存储
{
public:
	Types token_type;	//词素类型
	string token_str;	//词素内容

	token();			//初始化词素类的成员变量
};

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

private:
	Node * CreateNode(Node &, Relations);		//生成一个节点，以备赋值与挂载到树结构上

	string TraversalPrint(Node *);		//遍历类树结构的每个节点以便生成输出字符串
	string PrintObject(Node *);			//打印对象
	string PrintArray(Node *);			//打印数组
	string PrintKeyvalue(Node *);		//打印有键值

	bool TraversalDelete(Node *);		//遍历json结构进行删除

	Node *LayerParse(string);			//分层解析
	void  Lexing(vector<token *>&, string &);	//词法分析器
	Node *ParseObject(string);			//解析对象
	Node *ParseArray(string);			//解析数组
	Node *ParseInt(string);				//解析int
	Node *ParseDouble(string);			//解析double
	Node *ParseString(string);			//解析string
	Node *ParseBool(string);			//解析bool
	Node *ParseNull(string);			//解析null
};

Node &GetNode(Node *, const char *);		//为operator[]共用部分
Node &GetNode(Node *, int);