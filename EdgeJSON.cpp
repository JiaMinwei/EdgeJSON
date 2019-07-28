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
#include "EdgeJSON.h"

using namespace std;

Node::~Node()
{
	int count = this->children.size();
	for (size_t i = 0; i < count; i++) //遍历删除所有子节点
	{
		delete this->children[i];
	}
	this->children.clear();
}

Node &Node::operator[](const char *c)
{
	return GetNode(c);
}

Node &Node::operator[](int i)
{
	return GetNode(i);
}

EJ::EJ()
{
	this->root = nullptr; //初始化root指针
	this->index = 0;
}

Node &EJ::operator[](const char *c)
{
	return (*root)[c];
}

Node &EJ::operator[](int i)
{
	return (*root)[i];
}

Node &Node::AddKeyvalue(const char *c, int i)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_int;  //设置节点类型
	add_ptr->key = c;			  //设置健名称
	add_ptr->value.value_int = i; //设置值
	return *add_ptr;
}

Node &Node::AddKeyvalue(const char *c, double d)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_double;
	add_ptr->key = c;
	add_ptr->value.value_dou = d;
	return *add_ptr;
}

Node &Node::AddKeyvalue(const char *c, const char *cc)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_string;
	add_ptr->key = c;
	add_ptr->value_str = cc;
	return *add_ptr;
}

Node &Node::AddKeyvalue(const char *c, bool b)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_bool;
	add_ptr->key = c;
	add_ptr->value.value_boo = b;
	return *add_ptr;
}

Node &Node::AddKeyvalue(const char *c)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_null;
	add_ptr->key = c;
	add_ptr->value.value_int = 0;
	return *add_ptr;
}

Node &Node::AddArray(const char *c)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_array;
	add_ptr->key = c;
	return *add_ptr;
}

Node &Node::AddArray()
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_array;
	return *add_ptr;
}

Node &EJ::AddArray()
{
	Node *add_ptr = new Node;
	this->root = add_ptr;
	add_ptr->node_type = EJ_array;
	return *add_ptr;
}

Node &Node::AddObject(const char *c)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_object;
	add_ptr->key = c;
	return *add_ptr;
}

Node &Node::AddObject()
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_object;
	return *add_ptr;
}

Node &EJ::AddObject()
{
	Node *add_ptr = new Node;
	this->root = add_ptr;
	add_ptr->node_type = EJ_object;
	return *add_ptr;
}

Node &Node::AddValue(int i)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_int;
	add_ptr->value.value_int = i;
	return *add_ptr;
}

Node &Node::AddValue(double d)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_double;
	add_ptr->value.value_dou = d;
	return *add_ptr;
}

Node &Node::AddValue(const char *c)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_string;
	add_ptr->value_str = c;
	return *add_ptr;
}

Node &Node::AddValue(bool b)
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_bool;
	add_ptr->value.value_boo = b;
	return *add_ptr;
}

Node &Node::AddValue()
{
	Node *add_ptr = CreatNode();
	add_ptr->node_type = EJ_null;
	add_ptr->value.value_null = 0;
	return *add_ptr;
}

inline Node *Node::CreatNode()
{
	Node *new_ptr = new Node;
	this->children.push_back(new_ptr);
	return new_ptr;
}

string EJ::EJPrint()
{
	string print_str;			  //存储生成的json字符串
	Node *print_ptr = this->root; //取出json结构首节点开始处理
	if (print_ptr == nullptr)
	{
		return print_str;
	}
	if (print_ptr->node_type == EJ_object) //分列处理
	{
		print_str = print_str + PrintObject(print_ptr);
	}
	else
	{
		print_str = print_str + PrintArray(print_ptr);
	}

	return print_str; //返回字符串
}

void EJ::DeleteEJ() //删除所有节点
{
	if (this->root != nullptr)
	{
		delete this->root;
		this->root = nullptr;
	}
}

bool EJ::EJParse(string *parse_str)
{
	mode = STRMODE;
	inStr = parse_str;
	return parse();
}

bool EJ::EJParse(char *filePath)
{
	mode = FILEMODE;
	file = new ifstream(filePath);
	if (!*file)
	{
		return false;
	}
	return parse();
}

bool EJ::parse()
{
	stack<Node *> objArr;		   //存储左对象和左数组token
	Node *nowNode = root;		   //当前的挂载点
	Node *newNode = nullptr;	   //新节点
	string temp;				   //临时字符串
	Token *nowToken = nextToken(); //当前正在解析的token

	stringstream ss;			//字符串转数字
	while (nowToken != nullptr) //循环解析，直至没有下一个token
	{
		if (newNode == nullptr) //没有新节点要先生成
		{
			newNode = new Node;
		}
		switch (nowToken->token_type) //分别解析
		{
		case EJToken_leftObj:
			newNode->node_type = EJ_object;
			if (root == nullptr) //如果root还没有节点就先挂载在root
			{
				root = newNode;
			}
			else //否则挂载在当前挂载点
			{
				nowNode->children.push_back(newNode);
			}
			objArr.push(newNode);   //左对象token压栈
			nowNode = newNode;		//更新挂载点
			newNode = nullptr;		//置空新节点指针，代表新节点已经挂载了
			nowToken = nextToken(); //开始处理下一个token

			break;
		case EJToken_rightObj:
			if (nowNode->node_type != EJ_object)
				return false;
			objArr.pop();		 //弹出一个左对象token
			if (!objArr.empty()) //更新挂载点
				nowNode = objArr.top();
			nowToken = nextToken();
			break;
		case EJToken_leftArr:
			newNode->node_type = EJ_array;
			if (root == nullptr)
			{
				root = newNode;
			}
			else
			{
				nowNode->children.push_back(newNode);
			}
			objArr.push(newNode);
			nowNode = newNode;
			newNode = nullptr;
			nowToken = nextToken();

			break;
		case EJToken_rightArr:
			if (nowNode->node_type != EJ_array)
				return false;
			objArr.pop();
			if (!objArr.empty())
				nowNode = objArr.top();
			nowToken = nextToken();
			break;
		case EJToken_colon:
			nowToken = nextToken();
			break;
		case EJToken_comma:
			nowToken = nextToken();
			break;
		case EJToken_string:
			temp = nowToken->token_str;
			nowToken = nextToken();					   //预读下一个token，分辨出当前字符串token是不是键名称
			if (nowToken->token_type == EJToken_colon) //下一个token是冒号，说明是键名称
			{
				newNode->key = temp;
			}
			else //否则当作字符串值处理
			{
				newNode->value_str = temp; //挂载节点
				newNode->node_type = EJ_string;
				nowNode->children.push_back(newNode);
				newNode = nullptr;
			}
			break;
		case EJToken_double:
			newNode->node_type = EJ_double;
			ss.clear();
			ss << nowToken->token_str; //转换字符串成数字，然后挂载节点
			ss >> newNode->value.value_dou;
			nowNode->children.push_back(newNode);
			newNode = nullptr;
			nowToken = nextToken();
			break;
		case EJToken_int:
			newNode->node_type = EJ_int;
			ss.clear();
			ss << nowToken->token_str;
			ss >> newNode->value.value_int;
			nowNode->children.push_back(newNode);
			newNode = nullptr;
			nowToken = nextToken();
			break;
		case EJToken_bool:
			newNode->node_type = EJ_bool;
			if (nowToken->token_str == "true")
			{
				newNode->value.value_boo = true;
			}
			else
			{
				newNode->value.value_boo = false;
			}
			nowNode->children.push_back(newNode);
			newNode = nullptr;
			nowToken = nextToken();
			break;
		case EJToken_null:
			newNode->node_type = EJ_null;
			nowNode->children.push_back(newNode);
			newNode = nullptr;
			nowToken = nextToken();
			break;
		default:
			break;
		}
	}
}

inline char EJ::nextChar()
{
	char ch;
	//static int index = 0; //读取字符串下一个字符时用的下标
	switch (mode) //分模式处理
	{
	case STRMODE:
		if (index > inStr->size()) //边界检查
		{
			ch = -1;
		}
		else
		{
			ch = (*inStr)[index]; //读取
		}
		index++;
		break;
	case FILEMODE:
		(*file).read(&ch, 1); //从文件读一个字符
		if (ch == 0)
		{
			return -1;
		}
		break;
	}
	return ch;
}

inline Token *EJ::nextToken()
{
	char ch = nextChar(); //存储当前考察的字符
	static Token token;   //存储分析得到的token
	int count;			  //计数器

	while (1)
	{
		switch (ch) //有限状态机
		{
		case '{':
			token.token_type = EJToken_leftObj;
			return &token;
			break;
		case '}':
			token.token_type = EJToken_rightObj;
			return &token;
			break;
		case '[':
			token.token_type = EJToken_leftArr;
			return &token;
			break;
		case ']':
			token.token_type = EJToken_rightArr;
			return &token;
			break;
		case ':':
			token.token_type = EJToken_colon;
			return &token;
			break;
		case ',':
			token.token_type = EJToken_comma;
			return &token;
			break;
		case '\"':
			ch = nextChar();
			token.token_str.clear();
			while (ch != '\"')
			{
				token.token_str += ch;
				if (ch == '\\') //识别转义字符"
				{
					ch = nextChar();
					token.token_str += ch;
				}
				ch = nextChar();
			}
			token.token_type = EJToken_string;
			return &token;
			break;
		case '+':
		case '-':
		case '0' ... '9':
			token.token_str.clear();
			token.token_type = EJToken_int;
			while (ch == '-' || ch == '+' || ch == '.' || ch == 'e' || ch == 'E' || (ch >= '0' && ch <= '9'))
			{
				token.token_str += ch;
				if (ch == '.' || ch == 'e' || ch == 'E') //识别小数
				{
					token.token_type = EJToken_double;
				}
				ch = nextChar();
			}
			if (mode == FILEMODE) //因为预读一个字符，所以回退一个字符
				(*file).seekg(-1, ios::cur);
			else
				index--;

			return &token;
			break;
		case 't':
		case 'f':
			token.token_type = EJToken_bool;
			token.token_str.clear();
			token.token_str += ch;
			if (ch == 't')
			{
				count = 3;
			}
			else
			{
				count = 4;
			}
			for (int i = 0; i < count; i++) //读取bool字符串
			{
				ch = nextChar();
				token.token_str += ch;
			}
			return &token;
			break;
		case 'n':
			token.token_type = EJToken_null;
			token.token_str.clear();
			token.token_str += ch;
			for (int i = 0; i < 3; i++)
			{
				ch = nextChar();
				token.token_str += ch;
			}
			return &token;
			break;
		default:
			ch = nextChar(); //忽略其他字符
			if (ch == -1)
			{
				return nullptr;
			}
			break;
		}
	}
}

string EJ::TraversalPrint(Node *n) //对节点分类进行处理
{
	string temp;
	Node *now_ptr = n;

	if (now_ptr->node_type == EJ_object) //打印对象并进字符串
	{
		temp += PrintObject(now_ptr);
	}
	if (now_ptr->node_type == EJ_array) //打印数组并进字符串
	{
		temp += PrintArray(now_ptr);
	}
	if ((now_ptr->node_type == EJ_int) || (now_ptr->node_type == EJ_double) ||
		(now_ptr->node_type == EJ_string) || (now_ptr->node_type == EJ_bool) ||
		now_ptr->node_type == EJ_null) //打印数值
	{
		temp += PrintKeyvalue(now_ptr);
	}

	return temp; //返回字符串
}

string EJ::PrintObject(Node *now_ptr)
{
	string temp;
	if (now_ptr->key != "") //对象节点分有无键名称两种
	{
		temp += "\"";
		temp += now_ptr->key; //有键名称的处理
		temp += "\"";
		temp += ":{";
	}
	else
	{
		temp += "{"; //无键名称的处理
	}

	for (int i = 0; i < now_ptr->children.size(); i++)
	{
		temp += TraversalPrint(now_ptr->children[i]);
		temp += ',';
	}
	if (temp[temp.size() - 1] == ',')
		temp.erase(temp.size() - 1);
	temp += "}"; //子节点处理完毕,加一个}闭合对象
	return temp; //返回处理完毕的字符串
}

string EJ::PrintArray(Node *now_ptr)
{
	string temp; //算法与打印对象类似
	if (now_ptr->key != "")
	{
		temp += "\"";
		temp += now_ptr->key;
		temp += "\"";
		temp += ":[";
	}
	else
	{
		temp += "[";
	}
	for (int i = 0; i < now_ptr->children.size(); i++)
	{
		temp += TraversalPrint(now_ptr->children[i]);
		temp += ',';
	}
	if (temp[temp.size() - 1] == ',')
		temp.erase(temp.size() - 1);

	temp += "]";
	return temp;
}

string EJ::PrintKeyvalue(Node *now_ptr)
{
	string temp; //将键名称并进字符串
	if (now_ptr->key != "")
	{
		temp += "\"";
		temp += now_ptr->key;
		temp += "\"";
		temp += ":";
	}
	ostringstream os;
	switch (now_ptr->node_type) //根据节点的值类型取出相应值并进字符串
	{
	case EJ_int:
		temp += to_string(now_ptr->value.value_int); //to_string用于将其他数据类型转换成字符串
		break;
	case EJ_double:
		os << now_ptr->value.value_dou;
		temp += os.str();
		break;
	case EJ_string:
		temp += "\"";
		temp += now_ptr->value_str; //字符串值要加双引号
		temp += "\"";
		break;
	case EJ_bool:
		if (now_ptr->value.value_boo == true) //将布尔型转换成字符串
		{
			temp += "true";
		}
		else
		{
			temp += "false";
		}
		break;
	case EJ_null:
		temp += "null";
		break;
	default:
		break;
	}
	return temp; //返回字符串
}

Node &Node::GetNode(const char *c)
{
	if (!this->key.empty())
	{
		int count = this->children.size();
		for (size_t i = 0; i < count; i++)
		{
			if (strcmp(c, this->children[i]->key.c_str()))
			{
				return *(this->children[i]);
			}
		}
	}
	return *this;
}

Node &Node::GetNode(int i)
{
	if (this->key.empty())
	{
		if (i > this->children.size())
		{
			return *(this->children[i]);
		}
	}
	return *this;
}