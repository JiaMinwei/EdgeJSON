/*
EdgeJSON-许可协议
Copyright (c) 2019 Jiaminwei

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
#include "EdgeJSON.h"

using namespace std;

Node::Node() //节点构造函数,通过节点成员的值是否为空判断是否被使用
{
	this->brother = nullptr; //初始化指针类型的成员为空指针
	this->son = nullptr;
	this->key = "";
	this->value_boo = NULL; //初始化数值类型的成员为NULL
	this->value_dou = NULL;
	this->value_int = NULL;
	this->value_null = NULL;
	this->value_str = "";
}

Node &Node::operator[](const char *c) //[]运算符重载,获取最近一层节点的键名称为c的节点
{
	Node *now_ptr = this->son; //将调用该函数的对象的子节点的指针取出
	return GetNode(now_ptr, c);
}

Node &Node::operator[](int i) //[]运算符重载,获取最近一层节点的第i个节点
{
	Node *now_ptr = this->son; //将调用该函数的对象的子节点的指针取出
	return GetNode(now_ptr, i);
}

token::token()
{
	this->token_type = EdgeJSON_void;
}

EdgeJSON::EdgeJSON()
{
	this->root = nullptr; //初始化root指针
}

Node &EdgeJSON::operator[](const char *c) //[]运算符重载,获取最近一层节点的键名称为c的节点
{
	Node *now_ptr = this->root; //取出EdgeJSON类指向的根节点指针
	return GetNode(now_ptr, c);
}

Node &EdgeJSON::operator[](int i) //[]运算符重载,获取最近一层节点的第i个节点
{
	Node *now_ptr = this->root; //取出EdgeJSON类指向的根节点指针
	return GetNode(now_ptr, i);
}

Node *EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, int i)
{
	Node *add_ptr = CreateNode(n, r); //创建节点完成挂载
	if (add_ptr == nullptr)			  //判断节点是否创建成功,失败则返回空指针
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_int; //设置节点类型
	add_ptr->key = c;				   //设置健名称
	add_ptr->value_int = i;			   //设置值
	return add_ptr;
}

Node *EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, double d)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_double;
	add_ptr->key = c;
	add_ptr->value_dou = d;
	return add_ptr;
}

Node *EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, const char *cc)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_string;
	add_ptr->key = c;
	add_ptr->value_str = cc;
	return add_ptr;
}

Node *EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, bool b)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_bool;
	add_ptr->key = c;
	add_ptr->value_boo = b;
	return add_ptr;
}

Node *EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_null;
	add_ptr->key = c;
	add_ptr->value_int = NULL;
	return add_ptr;
}

Node *EdgeJSON::AddArray(Node &n, Relations r, const char *c)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_array;
	add_ptr->key = c;
	return add_ptr;
}

Node *EdgeJSON::AddArray(Node &n, Relations r)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_array;
	return add_ptr;
}

Node *EdgeJSON::AddArray(EdgeJSON &n)
{
	Node *add_ptr = new Node;
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	n.root = add_ptr;
	add_ptr->node_type = EdgeJSON_array;
	return add_ptr;
}

Node *EdgeJSON::AddObject(Node &n, Relations r, const char *c)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_object;
	add_ptr->key = c;
	return add_ptr;
}

Node *EdgeJSON::AddObject(Node &n, Relations r)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_object;
	return add_ptr;
}

Node *EdgeJSON::AddObject(EdgeJSON &n)
{
	Node *add_ptr = new Node;
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	n.root = add_ptr;
	add_ptr->node_type = EdgeJSON_object;
	return add_ptr;
}

Node *EdgeJSON::AddValue(Node &n, Relations r, int i)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_int;
	add_ptr->value_int = i;
	return add_ptr;
}

Node *EdgeJSON::AddValue(Node &n, Relations r, double d)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_double;
	add_ptr->value_dou = d;
	return add_ptr;
}

Node *EdgeJSON::AddValue(Node &n, Relations r, const char *c)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_string;
	add_ptr->value_str = c;
	return add_ptr;
}

Node *EdgeJSON::AddValue(Node &n, Relations r, bool b)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_bool;
	add_ptr->value_boo = b;
	return add_ptr;
}

Node *EdgeJSON::AddValue(Node &n, Relations r)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_null;
	add_ptr->value_int = NULL;
	return add_ptr;
}

string EdgeJSON::EdgeJSONPrint()
{
	string print_str;			  //存储生成的json字符串
	Node *print_ptr = this->root; //取出json结构首节点开始处理
	if (print_ptr == nullptr)
	{
		return print_str;
	}
	print_str = print_str + TraversalPrint(print_ptr); //调用遍历结构的函数
	return print_str;								   //返回字符串
}

bool EdgeJSON::DeleteEdgeJSON() //删除所有节点
{
	if (TraversalDelete(this->root)) //传入首节点进行遍历删除
	{
		this->root = nullptr; //将EdgeJSON对象的root置空
		return true;
	}
	return false;
}

void EdgeJSON::EdgeJSONParse(string &parse_str)
{
	string words;
	int flag = 0;
	for (int i = 0; i < parse_str.size(); i++) //剔除空格、换行符、制表符
	{
		if ((parse_str[i] == '\"') && parse_str[i - 1] != '\\')
		{
			flag++;
		}
		if (((parse_str[i] != ' ') && (parse_str[i] != '\n') && (parse_str[i] != '\t')) ||
			flag % 2 != 0)
		{
			int j = 0;
			words += parse_str[i];
			j++;
		}
	}
	parse_str = words;
	this->root = LayerParse(words);
}

void EdgeJSON::isSucceed(string &pret,string &result)
{
	for (int i = 0; i < pret.size(); i++)
	{
		if (pret[i] == result[i])
		{
			cout << 'O' << flush;
		}
		else
		{
			cout << 'X' << flush;
			cout << "\n<<<出错位置>>>：" << i << endl;
			i -= 5;
			for (int j = 0; j < 10; j++)
			{
				cout << pret[i + j];
			}
			cout << endl;
			for (int j = 0; j < 10; j++)
			{
				cout << result[i + j];
			}
			break;
		}
		if (i == pret.size() - 1)
		{
			cout << "\n<<<解析无误>>>" << endl;
		}
	}
}

Node *EdgeJSON::CreateNode(Node &n, Relations r)
{
	Node *newnode_ptr = new Node; //动态开辟一个节点的内存空间
	if (newnode_ptr == nullptr)   //判断是否成功生成新节点
	{
		return nullptr;
	}
	if (r == son) //以子节点身份挂载
	{
		n.son = newnode_ptr;
	}
	else
	{
		n.brother = newnode_ptr; //以兄弟节点身份挂载
	}
	return newnode_ptr; //返回新建节点的指针
}

string EdgeJSON::TraversalPrint(Node *n) //对节点分类进行处理
{
	string temp;
	Node *now_ptr = n;
	while (1)
	{
		if (now_ptr->node_type == EdgeJSON_object) //打印对象并进字符串
		{
			temp += PrintObject(now_ptr);
		}
		if (now_ptr->node_type == EdgeJSON_array) //打印数组并进字符串
		{
			temp += PrintArray(now_ptr);
		}
		if ((now_ptr->node_type == EdgeJSON_int) || (now_ptr->node_type == EdgeJSON_double) ||
			(now_ptr->node_type == EdgeJSON_string) || (now_ptr->node_type == EdgeJSON_bool) ||
			now_ptr->node_type == EdgeJSON_null) //打印数值
		{
			temp += PrintKeyvalue(now_ptr);
		}
		if (now_ptr->brother != nullptr) //当前节点若有兄弟节点则将兄弟节点指针赋予当前节点
		{
			now_ptr = now_ptr->brother; //更新当前节点指向后,再次执行循环体
			temp += ",";				//加个逗号
		}
		else
		{
			break; //如果没有兄弟节点则退出循环
		}
	}
	return temp; //返回字符串
}

string EdgeJSON::PrintObject(Node *now_ptr)
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
	if (now_ptr->son != nullptr) //若当前节点有子节点,则进行递归调用
	{
		temp += TraversalPrint(now_ptr->son);
	}
	temp += "}"; //子节点处理完毕,加一个}闭合对象
	return temp; //返回处理完毕的字符串
}

string EdgeJSON::PrintArray(Node *now_ptr)
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
	if (now_ptr->son != nullptr)
	{
		temp += TraversalPrint(now_ptr->son);
	}
	temp += "]";
	return temp;
}

string EdgeJSON::PrintKeyvalue(Node *now_ptr)
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
	case EdgeJSON_int:
		temp += to_string(now_ptr->value_int); //to_string用于将其他数据类型转换成字符串
		break;
	case EdgeJSON_double:
		os << now_ptr->value_dou;
		temp += os.str();
		break;
	case EdgeJSON_string:
		temp += "\"";
		temp += now_ptr->value_str; //字符串值要加双引号
		temp += "\"";
		break;
	case EdgeJSON_bool:
		if (now_ptr->value_boo == true) //将布尔型转换成字符串
		{
			temp += "true";
		}
		else
		{
			temp += "false";
		}
		break;
	case EdgeJSON_null:
		temp += "null";
		break;
	default:
		break;
	}
	return temp; //返回字符串
}

bool EdgeJSON::TraversalDelete(Node *nownode_ptr)
{
	if (nownode_ptr->son != nullptr) //判断是否有子节点
	{
		if (TraversalDelete(nownode_ptr->son)) //删除子节点
		{
			nownode_ptr->son = nullptr; //将指向子节点的指针置空
		}
	}
	if (nownode_ptr->brother != nullptr) //判断是否有兄弟节点
	{
		if (TraversalDelete(nownode_ptr->brother)) //删除子节点
		{
			nownode_ptr->brother = nullptr; //将指向兄弟节点的指针置空
		}
	}
	if ((nownode_ptr->son == nullptr) && (nownode_ptr->brother == nullptr))
	{
		delete nownode_ptr; //若当前节点不再有子节点和兄弟节点,则删除当前节点
		return true;		//返回删除成功
	}
	return false; //否则返回删除失败
}

Node *EdgeJSON::LayerParse(string &words)
{
	vector<token *> tokenarray; //存储各个词素对象的指针
	Node *bynode_ptr = nullptr; //当前一层结构的挂载点,便于挂载到上一层
	Node *temp_ptr = nullptr;   //本层节点的临时挂载点,便于本层节点组成链表
	Lexing(tokenarray, words);  //调用词法分析器,生成词素
	for (int i = 0; i < tokenarray.size(); i++)
	{
		switch (tokenarray[i]->token_type) //针对各个词素类型调用相应方法创建节点
		{
		case EdgeJSON_object:
			if (i == 0) //如果是本层首节点,则将方法返回的节点指针挂载到bynode_ptr
			{
				bynode_ptr = ParseObject(tokenarray[0]->token_str); //传入词素内容
				temp_ptr = bynode_ptr;								//将方法返回的节点指针存入临时挂载点
			}
			else
			{
				temp_ptr->brother = ParseObject(tokenarray[i]->token_str); //非首节点则以兄弟节点身份挂载到临时挂载点
				temp_ptr = temp_ptr->brother;							   //将方法返回的节点指针存入临时挂载点
			}
			break;
		case EdgeJSON_array:
			if (i == 0)
			{
				bynode_ptr = ParseArray(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseArray(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_int:
			if (i == 0)
			{
				bynode_ptr = ParseInt(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseInt(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_double:
			if (i == 0)
			{
				bynode_ptr = ParseDouble(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseDouble(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_string:
			if (i == 0)
			{
				bynode_ptr = ParseString(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseString(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_bool:
			if (i == 0)
			{
				bynode_ptr = ParseBool(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseBool(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_null:
			if (i == 0)
			{
				bynode_ptr = ParseNull(tokenarray[0]->token_str);
				temp_ptr = bynode_ptr;
			}
			else
			{
				temp_ptr->brother = ParseNull(tokenarray[i]->token_str);
				temp_ptr = temp_ptr->brother;
			}
			break;
		case EdgeJSON_layer: //词素为layer类型则直接将方法返回的节点以子节点身份挂载到临时挂载点
			temp_ptr->son = LayerParse(tokenarray[i]->token_str);
			break;
		default:
			break;
		}
		delete tokenarray[i]; //每处理一个词素后释放词素所占内存
	}
	return bynode_ptr; //返回本层结构挂载点
}

void EdgeJSON::Lexing(vector<token *> &tokenarray, string &words)
{
	tokenarray.push_back(new token);										   //新建词素
	int flag = 0, flag_o = 0, flag_a = 0, flag_c = 0, flag_one = 0, count = 0; //声明标志变量与计数器变量
	for (int i = 0; i < words.size(); i++)
	{
		tokenarray[count]->token_str += words[i]; //将读取到的字符存入词素
		if (words[i] == '{' && flag_c % 2 == 0)
		{
			flag_o++;
			if (flag_o == 1 && flag_a == 0)
			{
				tokenarray[count]->token_type = EdgeJSON_object;
				tokenarray.push_back(new token);
				count++;
				tokenarray[count]->token_type = EdgeJSON_layer;
			}
		}
		if (words[i] == '}' && flag_c % 2 == 0)
		{
			flag_o--;
			if (flag_o == 0 && flag_a == 0)
			{
				tokenarray[count]->token_str.pop_back();
			}
		}
		if (words[i] == '[' && flag_c % 2 == 0)
		{
			flag_a++;
			if (flag_a == 1 && flag_o == 0)
			{
				tokenarray[count]->token_type = EdgeJSON_array;
				tokenarray.push_back(new token);
				count++;
				tokenarray[count]->token_type = EdgeJSON_layer;
			}
		}
		if (words[i] == ']' && flag_c % 2 == 0)
		{
			flag_a--;
			if (flag_a == 0 && flag_o == 0)
			{
				tokenarray[count]->token_str.pop_back();
			}
		}
		if (words[i] == ',' && flag_c % 2 == 0 && flag_o == 0 && flag_a == 0)
		{
			tokenarray[count]->token_str.pop_back();
			tokenarray.push_back(new token);
			count++;
		}
		if ((words[i] == '\"' && i == 0) || (words[i] == '\"' && i >= 1 && words[i - 1] != '\\')) //遇到引号,标志加1
		{
			flag_c++;
		}
	}

	for (int i = 0; i < tokenarray.size(); i++)
	{
		if (tokenarray[i]->token_type == EdgeJSON_void) //对未赋予类型的词素进行词素赋予
		{
			int j, k = 1; //循环变量
			for (j = 0; j < tokenarray[i]->token_str.size(); j++)
			{
				if (tokenarray[i]->token_str[j] == ':') //如果词素内容有冒号则将标志置1
				{
					flag = 1;
					break; //退出循环
				}
			}
			if (flag == 1) //有冒号是键值对数字,无则是数组元素数字
			{
				k = j + 2; //有冒号则给k赋值j+2
			}
			else
			{
				j = -1; //无冒号时给j赋值为-1
			}
			if (((tokenarray[i]->token_str[j + 1] >= '0') && (tokenarray[i]->token_str[j + 1] <= '9')) || (tokenarray[i]->token_str[j + 1] == '-')) //有冒号,j+1则是判断冒号后的字符
			{																																		//无冒号,j+1则是判断首字符
				for (; k < tokenarray[i]->token_str.size(); k++)																					//有冒号,k=j+2是从冒号后第二个字符开始检测
				{																																	//无冒号,k=1是从首字符的下一个字符开始检测
					if ((tokenarray[i]->token_str[k] == '.') || (tokenarray[i]->token_str[k] == 'e') || (tokenarray[i]->token_str[k] == 'E'))
					{
						tokenarray[i]->token_type = EdgeJSON_double; //有小数点或者指数符号的是double
					}
				}
				if (tokenarray[i]->token_type == EdgeJSON_void)
				{
					tokenarray[i]->token_type = EdgeJSON_int; //此代码块只处理数字,非double即int
				}
			}
			if (tokenarray[i]->token_str[j + 1] == '\"')
			{
				tokenarray[i]->token_type = EdgeJSON_string; //冒号后或词素首字符是引号则赋予词素string类型
			}
			if ((tokenarray[i]->token_str[j + 1] == 't') || (tokenarray[i]->token_str[j + 1] == 'f'))
			{
				tokenarray[i]->token_type = EdgeJSON_bool; //冒号后或词素首字符是t或f则赋予词素bool类型
			}
			if (tokenarray[i]->token_str[j + 1] == 'n')
			{
				tokenarray[i]->token_type = EdgeJSON_null; //冒号后或词素首字符是n则赋予词素null类型
			}
		}
	}
	#ifdef DEBUG
	for (int i = 0; i < tokenarray.size(); i++)		//打印分词结果，用以调试分词器
	{
		cout << tokenarray[i]->token_str << endl;
	}
	#endif
}

Node *EdgeJSON::ParseObject(string token_str)
{
	Node *return_ptr = new Node;			 //创建一个新节点
	return_ptr->node_type = EdgeJSON_object; //赋予节点类型
	if (token_str[0] == '\"')				 //词素首字符是引号则提取键名称
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++) //如果下一字符是引号则提取完毕
		{
			return_ptr->key += token_str[i];
		}
	}
	return return_ptr; //返回节点指针
}

Node *EdgeJSON::ParseArray(string token_str)
{
	Node *return_ptr = new Node;
	return_ptr->node_type = EdgeJSON_array;
	if (token_str[0] == '\"')
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	return return_ptr;
}

Node *EdgeJSON::ParseInt(string token_str)
{
	Node *return_ptr = new Node;
	string temp; //临时存放字符
	int e_flag = 0;
	return_ptr->node_type = EdgeJSON_int;
	if (token_str[0] == '\"') //词素首字符是引号则提取键名称
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	for (int i = 0; i < token_str.size(); i++) //循环提取有效字符
	{
		if (token_str[i] == ':') //词素内容如果有冒号则提取冒号后的数字字符
		{
			for (int j = i + 1; j < token_str.size(); j++)
			{
				temp += token_str[j]; //存入temp
			}
			break; //提取完毕则退出循环
		}
		if (((token_str[0] >= '0') && (token_str[0] <= '9')) || (token_str[0] == '-')) //词素首字符是数字则直接提取数字
		{
			for (int i = 0; i < token_str.size(); i++)
			{
				temp += token_str[i];
			}
			break; //提取完毕后退出循环
		}
	}
	stringstream ss(temp);
	ss >> return_ptr->value_int; //将temp内的数字字符转换为int
	return return_ptr;
}

Node *EdgeJSON::ParseDouble(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_double;
	if (token_str[0] == '\"')
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	for (int i = 0; i < token_str.size(); i++)
	{
		if (token_str[i] == ':')
		{
			for (int j = i + 1; j < token_str.size(); j++)
			{
				temp += token_str[j];
			}
			break;
		}
		if (((token_str[0] >= '0') && (token_str[0] <= '9')) || (token_str[0] == '-'))
		{
			for (int i = 0; i < token_str.size(); i++)
			{
				temp += token_str[i];
			}
			break;
		}
	}
	stringstream ss(temp);
	ss >> return_ptr->value_dou; //将temp内的数字字符转换为double
	return return_ptr;
}

Node *EdgeJSON::ParseString(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_string;
	if (token_str[0] == '\"') //提取键名称
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
			if (i + 2 == token_str.size()) //如果冒号是词素内容的末尾字符则将提取到的字符转存到节点value_str中
			{
				return_ptr->value_str = return_ptr->key;
				return_ptr->key = ""; //将键名称置空
			}
		}
	}
	for (int i = 0; i < token_str.size(); i++)
	{
		if (token_str[i] == ':') //如果遇到冒号则提取冒号后的字符串到value_str
		{
			for (int j = i + 1; j + 2 < token_str.size(); j++)
			{
				return_ptr->value_str += token_str[j + 1];
			}
			break;
		}
	}
	return return_ptr;
}

Node *EdgeJSON::ParseBool(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_bool;
	if (token_str[0] == '\"') //提取键名称
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	if ((token_str[0] == 't') || (token_str[0] == 'f'))
	{
		for (int i = 0; i < token_str.size(); i++)
		{
			temp += token_str[i]; //如果词素首字符是t或f则提取字符到temp
		}
	}
	for (int i = 0; i < token_str.size(); i++)
	{
		if (token_str[i] == ':')
		{
			for (int j = i + 1; j != token_str.size(); j++)
			{
				temp += token_str[j]; //如果词素内容有冒号则提取冒号后的字符到temp
			}
			break; //提取完毕退出循环
		}
	}
	if (temp == "true") //如果temp为true则给value_boo赋值为1(节点初始化时是0)
	{
		return_ptr->value_boo = 1;
	}
	return return_ptr;
}

Node *EdgeJSON::ParseNull(string token_str)
{
	Node *return_ptr = new Node;
	return_ptr->node_type = EdgeJSON_null;
	if (token_str[0] == '\"') //提取键名称
	{
		for (int i = 1; !(token_str[i] == '\"' && token_str[i - 1] != '\\'); i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	return_ptr->value_null = 0; //null类型直接置0即可,打印时会识别节点类型直接打印null
	return return_ptr;
}

Node &GetNode(Node *now_ptr, const char *c)
{
	if (now_ptr == nullptr) //判断当前节点是否存在
	{
		return *now_ptr; //若当前节点不存在,则退出函数
	}
	else
	{
		while (now_ptr->key == "") //逐层判断,直到找到一个键名称不为空的节点
		{
			now_ptr = now_ptr->son;
		}
		while (1)
		{
			if (now_ptr->key == c) //若键名称匹配,则返回当前节点
			{
				return *now_ptr;
			}
			if (now_ptr->brother == nullptr) //若当前节点不匹配且不再有兄弟节点,则退出函数
			{
				return *now_ptr;
			}
			else
			{
				now_ptr = now_ptr->brother; //若当前节点不匹配且有兄弟节点,则取兄弟节点为当前节点,继续匹配
			}
		}
	}
}

Node &GetNode(Node *now_ptr, int i)
{
	if (now_ptr == nullptr)
	{
		return *now_ptr;
	}
	else
	{
		while (now_ptr->key != "") //逐层判断,直到找到一个键名称为空的节点
		{
			now_ptr = now_ptr->son;
		}
		for (int counter = 1; counter < i; counter++) //在当前层找到第i个节点并返回
		{
			now_ptr = now_ptr->brother;
		}
		return *now_ptr;
	}
}