/*
EdgeJSON-���Э��
Copyright (c) 2018 Jiaminwei

1.����:��Э�����ڹ�Ͻ�û�����ҵʵ�� (���¼�ƣ��������) �����ԭ���ߣ����¼�ƣ���ɷ���֮��
  �Ĺ�ϵ��ʹ�ñ�����������������ڸ��ơ����ء���װ�����б����������Ϊͬ�ⱾЭ�顣��Э��涨��
  ʹ����ɷ�������ӵ�е�EdgeJSON (���¼�Ʊ����) �����Ȩ�������ƺ�������������:
2.���֤����:��ɷ��ش����豻����˸��˸��ơ��ַ����޸��Լ�����ҵ��ʹ�ñ������Ȩ����
3.�����������
	3.1.������Ĵ����У��޸ĺ��ɱ������Դ���������Ĵ����У��������ԭ�����е�Э����������
	3.2.����������޸��˴��룬������ڱ��޸ĵ��ļ���������Ӧ˵����
4.����:��ֹ�����������ҵ��ӯ��ΪĿ��ʹ�ñ��������������Ʒ���������������޸ı�������Ա����Ϊ
  �������ж��ο��������ñ����������Ľӿڵȣ���
5.��ֹ:
	5.1.�����������Υ��Э����һ����Զ���ֹ��ɡ�
	5.2.��ɷ���Ȩ��ֹ��Э�鼰�Ա�����˵���ɡ�
6.��������:�ڷ�������ķ�Χ�ڣ�����Ǹ���ԭ���ṩ�ġ���ɷ���Ӧ��������Ĳ��������ϡ�bug����
  ���뱻��ɷ��������豸֮����κ��������������µ��κ��𺦡����á��κ���������е����Σ����⣬��
  �����������ʹ�ñ������Դ����ʱ�� ��ɷ���Ӧ�Ա���ɷ���д��Դ�����е��κ�ȱ�ݸ���
7.����Ȩ������ɷ���Ȩ�޸ı�Э�������������˲���ͬ�޸ĺ��Э�������ֹͣʹ�ñ����������ʹ
  �ü�����ͬ���޸ĺ��Э����������Ա�Э��δ�����˱�������Ȩ����
*/
#include "EdgeJSON.h"

using namespace std;

Node::Node()		//�ڵ㹹�캯��,ͨ���ڵ��Ա��ֵ�Ƿ�Ϊ���ж��Ƿ�ʹ��
{
	this->brother = nullptr;		//��ʼ��ָ�����͵ĳ�ԱΪ��ָ��
	this->son = nullptr;
	this->key = "";
	this->value_boo = NULL;			//��ʼ����ֵ���͵ĳ�ԱΪNULL
	this->value_dou = NULL;
	this->value_int = NULL;
	this->value_null = NULL;
	this->value_str = "";
}

Node & Node::operator[](const char *c)		//[]���������,��ȡ���һ��ڵ�ļ�����Ϊc�Ľڵ�
{
	Node *now_ptr = this->son;		//�����øú����Ķ�����ӽڵ��ָ��ȡ��
	return GetNode(now_ptr, c);
}

Node & Node::operator[](int i)			//[]���������,��ȡ���һ��ڵ�ĵ�i���ڵ�
{
	Node *now_ptr = this->son;		//�����øú����Ķ�����ӽڵ��ָ��ȡ��
	return GetNode(now_ptr, i);
}

token::token()
{
	this->token_type = EdgeJSON_void;
}

EdgeJSON::EdgeJSON()
{
	this->root = nullptr;			//��ʼ��rootָ��
}

Node & EdgeJSON::operator[](const char *c)		//[]���������,��ȡ���һ��ڵ�ļ�����Ϊc�Ľڵ�	
{
	Node *now_ptr = this->root;		//ȡ��EdgeJSON��ָ��ĸ��ڵ�ָ��
	return GetNode(now_ptr, c);
}

Node & EdgeJSON::operator[](int i)		//[]���������,��ȡ���һ��ڵ�ĵ�i���ڵ�
{
	Node *now_ptr = this->root;		//ȡ��EdgeJSON��ָ��ĸ��ڵ�ָ��
	return GetNode(now_ptr, i);
}

Node * EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, int i)
{
	Node *add_ptr = CreateNode(n,r);		//�����ڵ���ɹ���
	if (add_ptr == nullptr)					//�жϽڵ��Ƿ񴴽��ɹ�,ʧ���򷵻ؿ�ָ��
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_int;		//���ýڵ�����
	add_ptr->key = c;						//���ý�����
	add_ptr->value_int = i;					//����ֵ
	return add_ptr;							
}

Node * EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, double d)
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

Node * EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, const char *cc)
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

Node * EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c, bool b)
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

Node * EdgeJSON::AddKeyvalue(Node &n, Relations r, const char *c)
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

Node * EdgeJSON::AddArray(Node &n, Relations r, const char *c)
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

Node * EdgeJSON::AddArray(Node &n, Relations r)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_array;
	return add_ptr;
}

Node * EdgeJSON::AddArray(EdgeJSON &n)
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

Node * EdgeJSON::AddObject(Node &n, Relations r, const char *c)
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

Node * EdgeJSON::AddObject(Node &n, Relations r)
{
	Node *add_ptr = CreateNode(n, r);
	if (add_ptr == nullptr)
	{
		return nullptr;
	}
	add_ptr->node_type = EdgeJSON_object;
	return add_ptr;
}

Node * EdgeJSON::AddObject(EdgeJSON &n)
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

Node * EdgeJSON::AddValue(Node &n, Relations r, int i)
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

Node * EdgeJSON::AddValue(Node &n, Relations r, double d)
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

Node * EdgeJSON::AddValue(Node &n, Relations r, const char *c)
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

Node * EdgeJSON::AddValue(Node &n, Relations r, bool b)
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

Node * EdgeJSON::AddValue(Node &n, Relations r)
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
	string print_str;					//�洢���ɵ�json�ַ���
	Node *print_ptr = this->root;		//ȡ��json�ṹ�׽ڵ㿪ʼ����
	if (print_ptr == nullptr)
	{
		return print_str;
	}
	print_str = print_str + TraversalPrint(print_ptr);		//���ñ����ṹ�ĺ���
	return print_str;					//�����ַ���
}

bool EdgeJSON::DeleteEdgeJSON()		//ɾ�����нڵ�
{
	if (TraversalDelete(this->root))			//�����׽ڵ���б���ɾ��
	{
		this->root = nullptr;					//��EdgeJSON�����root�ÿ�
		return true;						
	}
	return false;
}

void EdgeJSON::EdgeJSONParse(string parse_str)
{
	string words;
	int flag = 0;
	for (int i = 0; i < parse_str.size(); i++)		//�޳��ո񡢻��з����Ʊ��
	{
		if (parse_str[i] == '\"')
		{
			flag++;
		}
		if (((parse_str[i] != ' ') && (parse_str[i] != '\n') && (parse_str[i] != '\t'))||
			flag%2!=0)
		{
			int j = 0;
			words += parse_str[i];
			j++;
		}
	}
	cout << words << endl;
	this->root = LayerParse(words);
}

Node *EdgeJSON::CreateNode(Node &n, Relations r)
{
	Node *newnode_ptr = new Node;		//��̬����һ���ڵ���ڴ�ռ�
	if (newnode_ptr == nullptr)			//�ж��Ƿ�ɹ������½ڵ�
	{
		return nullptr;
	}
	if (r == son)						//���ӽڵ���ݹ���
	{
		n.son = newnode_ptr;
	}
	else
	{
		n.brother = newnode_ptr;		//���ֵܽڵ���ݹ���
	}
	return newnode_ptr;					//�����½��ڵ��ָ��
}

string EdgeJSON::TraversalPrint(Node *n)		//�Խڵ������д���
{
	string temp;
	Node *now_ptr = n;
	while (1)
	{
		if (now_ptr->node_type == EdgeJSON_object)		//��ӡ���󲢽��ַ���
		{
			temp += PrintObject(now_ptr);
		}
		if (now_ptr->node_type == EdgeJSON_array)		//��ӡ���鲢���ַ���
		{
			temp += PrintArray(now_ptr);
		}
		if ((now_ptr->node_type == EdgeJSON_int) || (now_ptr->node_type == EdgeJSON_double) ||
			(now_ptr->node_type == EdgeJSON_string) || (now_ptr->node_type == EdgeJSON_bool) ||
			now_ptr->node_type == EdgeJSON_null)		//��ӡ��ֵ
		{
			if (now_ptr->key != "")		//��ӡ�м����Ƶ���ֵ�����ַ���
			{
				temp += PrintKeyvalue(now_ptr);
			}
			else
			{									//��ӡ�޼����Ƶ���ֵ�����ַ���
				temp += PrintValue(now_ptr);
			}
		}
		if (now_ptr->brother != nullptr)		//��ǰ�ڵ������ֵܽڵ����ֵܽڵ�ָ�븳�赱ǰ�ڵ�
		{
			now_ptr = now_ptr->brother;			//���µ�ǰ�ڵ�ָ���,�ٴ�ִ��ѭ����
			temp += ",";						//�Ӹ�����
		}
		else
		{
			break;								//���û���ֵܽڵ����˳�ѭ��
		}
	}
	return temp;			//�����ַ���
}

string EdgeJSON::PrintObject(Node *now_ptr)
{
	string temp;
	if (now_ptr->key != "")		//����ڵ�����޼���������
	{
		temp += "\"";
		temp += now_ptr->key;			//�м����ƵĴ���
		temp += "\"";
		temp += ":{";
	}
	else
	{
		temp += "{";					//�޼����ƵĴ���
	}
	if (now_ptr->son != nullptr)		//����ǰ�ڵ����ӽڵ�,����еݹ����
	{
		temp += TraversalPrint(now_ptr->son);						
	}
	temp += "}";						//�ӽڵ㴦�����,��һ��}�պ϶���
	return temp;						//���ش�����ϵ��ַ���
}

string EdgeJSON::PrintArray(Node *now_ptr)
{
	string temp;				//�㷨���ӡ��������
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
	string temp;			//�������Ʋ����ַ���
	temp += "\"";
	temp += now_ptr->key;
	temp += "\"";
	temp += ":";
	ostringstream os;
	switch (now_ptr->node_type)		//���ݽڵ��ֵ����ȡ����Ӧֵ�����ַ���
	{
	case EdgeJSON_int:
		temp += to_string(now_ptr->value_int);		//to_string���ڽ�������������ת�����ַ���
		break;
	case EdgeJSON_double:
		os << now_ptr->value_dou;
		temp += os.str();
		break;
	case EdgeJSON_string:
		temp += "\"";
		temp += now_ptr->value_str;		//�ַ���ֵҪ��˫����
		temp += "\"";
		break;
	case EdgeJSON_bool:
		if (now_ptr->value_boo == true)		//��������ת�����ַ���
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
	}
	return temp;			//�����ַ���
}

string EdgeJSON::PrintValue(Node *now_ptr)
{
	string temp;			//�㷨�봦���м����Ƶ�ֵ���㷨����
	ostringstream os;
	switch (now_ptr->node_type)
	{
	case EdgeJSON_int:
		temp += to_string(now_ptr->value_int);
		break;
	case EdgeJSON_double:
		os << now_ptr->value_dou;
		temp += os.str();
		break;
	case EdgeJSON_string:
		temp += "\"";
		temp += now_ptr->value_str;
		temp += "\"";
		break;
	case EdgeJSON_bool:
		if (now_ptr->value_boo == true)
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
	}
	return temp;
}

bool EdgeJSON::TraversalDelete(Node *nownode_ptr)
{
	if (nownode_ptr->son != nullptr)				//�ж��Ƿ����ӽڵ�
	{
		if (TraversalDelete(nownode_ptr->son))		//ɾ���ӽڵ�
		{
			nownode_ptr->son = nullptr;				//��ָ���ӽڵ��ָ���ÿ�
		}
	}
	if (nownode_ptr->brother != nullptr)			//�ж��Ƿ����ֵܽڵ�
	{
		if (TraversalDelete(nownode_ptr->brother))	//ɾ���ӽڵ�
		{
			nownode_ptr->brother = nullptr;			//��ָ���ֵܽڵ��ָ���ÿ�
		}
	}
	if ((nownode_ptr->son == nullptr) && (nownode_ptr->brother == nullptr))
	{
		delete nownode_ptr;			//����ǰ�ڵ㲻�����ӽڵ���ֵܽڵ�,��ɾ����ǰ�ڵ�
		return true;				//����ɾ���ɹ�
	}
	return false;					//���򷵻�ɾ��ʧ��
}

Node * EdgeJSON::LayerParse(string words)
{
	vector<token *>tokenarray;		//�洢�������ض����ָ��
	Node *bynode_ptr = nullptr;		//��ǰһ��ṹ�Ĺ��ص�,���ڹ��ص���һ��
	Node *temp_ptr = nullptr;		//����ڵ����ʱ���ص�,���ڱ���ڵ��������
	Lexing(tokenarray, words);		//���ôʷ�������,���ɴ���
	for (int i = 0; i < tokenarray.size(); i++)		
	{
		switch (tokenarray[i]->token_type)		//��Ը����������͵�����Ӧ���������ڵ�
		{
		case EdgeJSON_object:
			if (i == 0)			//����Ǳ����׽ڵ�,�򽫷������صĽڵ�ָ����ص�bynode_ptr
			{
				bynode_ptr = ParseObject(tokenarray[0]->token_str);		//�����������
				temp_ptr = bynode_ptr;			//���������صĽڵ�ָ�������ʱ���ص�
			}
			else
			{
				temp_ptr->brother = ParseObject(tokenarray[i]->token_str);		//���׽ڵ������ֵܽڵ���ݹ��ص���ʱ���ص�
				temp_ptr = temp_ptr->brother;	//���������صĽڵ�ָ�������ʱ���ص�
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
		case EdgeJSON_layer:			//����Ϊlayer������ֱ�ӽ��������صĽڵ����ӽڵ���ݹ��ص���ʱ���ص�
			temp_ptr->son = LayerParse(tokenarray[i]->token_str);	
			break;
		}
		delete tokenarray[i];		//ÿ����һ�����غ��ͷŴ�����ռ�ڴ�
	}
	return bynode_ptr;		//���ر���ṹ���ص�
}

void EdgeJSON::Lexing(vector<token*>&tokenarray, string &words)
{
	tokenarray.push_back(new token);		//�½�����
	int flag = 0, flag_one = 0, count = 0;	//������־���������������
	for (int i = 0; i < words.size(); i++)	
	{
		tokenarray[count]->token_str += words[i];	//����ȡ�����ַ��������
		if ((words[0] != '{') && (words[0] != '['))		//�����ַ������ַ�����{��[ʱִ�����ųɶ�ʶ��
		{
			if (words[i] == '\"')		//��������,��־��1
			{
				flag_one++;
			}
			if (words[i + 1] == ',')	//�����һ���ַ��Ƕ���
			{
				if ((flag == 0) && (flag_one % 2 == 0))		//flag=0˵�����Ų��ڵ�ǰ������ȡ�Ĵ�����
				{											//flag_oneΪż˵�����Ų��ڵ�ǰ������ȡ�Ĵ����е����Ŷ�֮��
					tokenarray.push_back(new token);		//��������ʱ������һ���ص���ȡ
					count++;
					i++;			//��������
				}
			}
		}
		if ((words[i] == '{') || (words[i] == '['))
		{
			if (flag == 0)		//flag=0˵��{��[���ڵ�ǰ������ȡ�Ĵ�����
			{
				if (words[i] == '{')	//��ȡһ���������
				{
					tokenarray[count]->token_type = EdgeJSON_object;
				}
				if (words[i] == '[')	//��ȡһ���������
				{
					tokenarray[count]->token_type = EdgeJSON_array;
				}
				tokenarray.push_back(new token);	//flag=0ʱ������һ���ص���ȡ
				count++;
			}
			flag++;			//����{��[,��־��1
		}
		if ((words[i + 1] == '}') || (words[i + 1] == ']'))
		{
			flag--;			//����}��],��־��1
			if (flag == 0)		//flag=0˵��������ȡ�Ĵ��ص���ȡ�����ѽ���
			{
				tokenarray[count]->token_type = EdgeJSON_layer;		//�����������
				if (words.size() - 1 != i + 1)		
				{
					tokenarray.push_back(new token);	//����ַ���û�ж�ȡ���,�����������ش洢�ռ�
					count++;
				}
				if (words[i + 2] == ',')	//����һ���ַ��Ƕ���,������һ���ַ�
				{
					i++;
				}
				i++;			//����}��]
			}
		}
	}
	for (int i = 0; i < tokenarray.size(); i++)
	{
		if (tokenarray[i]->token_type == EdgeJSON_void)		//��δ�������͵Ĵ��ؽ��д��ظ���
		{
			int j, k = 1;		//ѭ������
			for (j = 0; j < tokenarray[i]->token_str.size(); j++)
			{
				if (tokenarray[i]->token_str[j] == ':')		//�������������ð���򽫱�־��1
				{
					flag = 1;
					break;		//�˳�ѭ��
				}
			}
			if (flag == 1)		//��ð���Ǽ�ֵ������,����������Ԫ������
			{
				k = j + 2;		//��ð�����k��ֵj+2
			}
			else
			{
				j = -1;			//��ð��ʱ��j��ֵΪ-1
			}
			if (((tokenarray[i]->token_str[j + 1] >= '0') && (tokenarray[i]->token_str[j + 1] <= '9'))
				|| (tokenarray[i]->token_str[j + 1] == '-'))	//��ð��,j+1�����ж�ð�ź���ַ�
			{													//��ð��,j+1�����ж����ַ�
				for (k; k < tokenarray[i]->token_str.size(); k++)	//��ð��,k=j+2�Ǵ�ð�ź�ڶ����ַ���ʼ���
				{													//��ð��,k=1�Ǵ����ַ�����һ���ַ���ʼ���
					if (tokenarray[i]->token_str[k] == '.')		
					{
						tokenarray[i]->token_type = EdgeJSON_double;		//��С������double
					}
				}
				if (tokenarray[i]->token_type == EdgeJSON_void)
				{
					tokenarray[i]->token_type = EdgeJSON_int;	//�˴����ֻ��������,��double��int
				}
			}
			if (tokenarray[i]->token_str[j + 1] == '\"')
			{
				tokenarray[i]->token_type = EdgeJSON_string;		//ð�ź��������ַ��������������string����
			}
			if ((tokenarray[i]->token_str[j + 1] == 't') || (tokenarray[i]->token_str[j + 1] == 'f'))
			{
				tokenarray[i]->token_type = EdgeJSON_bool;	//ð�ź��������ַ���t��f�������bool����	
			}
			if (tokenarray[i]->token_str[j + 1] == 'n')
			{
				tokenarray[i]->token_type = EdgeJSON_null;	//ð�ź��������ַ���n�������null����
			}
		}
	}
}

Node * EdgeJSON::ParseObject(string token_str)
{
	Node *return_ptr = new Node;	//����һ���½ڵ�
	return_ptr->node_type = EdgeJSON_object;		//����ڵ�����
	if (token_str[0] == '\"')		//�������ַ�����������ȡ������
	{
		for (int i = 1; token_str[i] != '\"'; i++)		//�����һ�ַ�����������ȡ���
		{
			return_ptr->key += token_str[i];
		}
	}
	return return_ptr;		//���ؽڵ�ָ��
}

Node * EdgeJSON::ParseArray(string token_str)
{
	Node *return_ptr = new Node;
	return_ptr->node_type = EdgeJSON_array;
	if (token_str[0] == '\"')
	{
		for (int i = 1; token_str[i] != '\"'; i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	return return_ptr;
}

Node * EdgeJSON::ParseInt(string token_str)
{
	Node *return_ptr = new Node;
	string temp;		//��ʱ����ַ�
	return_ptr->node_type = EdgeJSON_int;
	if (token_str[0] == '\"')		//�������ַ�����������ȡ������
	{
		for (int i = 1; token_str[i] != '\"'; i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	for (int i = 0; i < token_str.size(); i++)		//ѭ����ȡ��Ч�ַ�
	{
		if (token_str[i] == ':')	//�������������ð������ȡð�ź�������ַ�
		{
			for (int j = i + 1; j < token_str.size(); j++)
			{
				temp += token_str[j];		//����temp
			}
			break;			//��ȡ������˳�ѭ��
		}
		if (((token_str[0] >= '0') && (token_str[0] <= '9'))
			|| (token_str[0] == '-'))		//�������ַ���������ֱ����ȡ����
		{
			for (int i = 0; i < token_str.size(); i++)
			{
				temp += token_str[i];
			}
			break;			//��ȡ��Ϻ��˳�ѭ��
		}
	}
	stringstream ss(temp);
	ss >> return_ptr->value_int;		//��temp�ڵ������ַ�ת��Ϊint
	return return_ptr;
}

Node * EdgeJSON::ParseDouble(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_double;
	if (token_str[0] == '\"')
	{
		for (int i = 1; token_str[i] != '\"'; i++)
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
		if (((token_str[0] >= '0') && (token_str[0] <= '9'))
			|| (token_str[0] == '-'))
		{
			for (int i = 0; i < token_str.size(); i++)
			{
				temp += token_str[i];
			}
			break;
		}
	}
	stringstream ss(temp);
	ss >> return_ptr->value_dou;	//��temp�ڵ������ַ�ת��Ϊdouble
	return return_ptr;
}

Node * EdgeJSON::ParseString(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_string;
	if (token_str[0] == '\"')		//��ȡ������
	{
		for (int i = 1; token_str[i] != '\"'; i++)
		{
			return_ptr->key += token_str[i];
			if (i + 2 == token_str.size())		//���ð���Ǵ������ݵ�ĩβ�ַ�����ȡ�����ַ�ת�浽�ڵ�value_str��
			{
				return_ptr->value_str = return_ptr->key;
				return_ptr->key = "";			//���������ÿ�
			}
		}
	}
	for (int i = 0;i<token_str.size(); i++)
	{
		if (token_str[i] == ':')		//�������ð������ȡð�ź���ַ�����value_str
		{
			for (int j = i+1; token_str[j+1] != '\"'; j++)
			{
				return_ptr->value_str += token_str[j+1];
			}
			break;
		}
	}
	return return_ptr;
}

Node * EdgeJSON::ParseBool(string token_str)
{
	Node *return_ptr = new Node;
	string temp;
	return_ptr->node_type = EdgeJSON_bool;
	if (token_str[0] == '\"')		//��ȡ������
	{
		for (int i = 1; token_str[i] != '\"'; i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	if ((token_str[0] == 't') || (token_str[0] == 'f'))
	{
		for (int i = 0; i < token_str.size(); i++)
		{
			temp += token_str[i];		//����������ַ���t��f����ȡ�ַ���temp
		}
	}
	for (int i = 0; i<token_str.size(); i++)
	{
		if (token_str[i] == ':')
		{
			for (int j = i + 1; j != token_str.size(); j++)
			{
				temp += token_str[j];	//�������������ð������ȡð�ź���ַ���temp
			}
			break;		//��ȡ����˳�ѭ��
		}
	}
	if (temp == "true")		//���tempΪtrue���value_boo��ֵΪ1(�ڵ��ʼ��ʱ��0)
	{
		return_ptr->value_boo = 1;
	}
	return return_ptr;
}

Node * EdgeJSON::ParseNull(string token_str)
{
	Node *return_ptr = new Node;
	return_ptr->node_type = EdgeJSON_null;
	if (token_str[0] == '\"')		//��ȡ������
	{
		for (int i = 1; token_str[i] != '\"'; i++)
		{
			return_ptr->key += token_str[i];
		}
	}
	return_ptr->value_null = 0;		//null����ֱ����0����,��ӡʱ��ʶ��ڵ�����ֱ�Ӵ�ӡnull
	return return_ptr;
}

Node & GetNode(Node *now_ptr, const char *c)
{
	if (now_ptr == nullptr)			//�жϵ�ǰ�ڵ��Ƿ����
	{
		return *now_ptr;			//����ǰ�ڵ㲻����,���˳�����
	}
	else
	{
		while (now_ptr->key == "")		//����ж�,ֱ���ҵ�һ�������Ʋ�Ϊ�յĽڵ�
		{
			now_ptr = now_ptr->son;
		}
		while (1)
		{
			if (now_ptr->key == c)			//��������ƥ��,�򷵻ص�ǰ�ڵ�
			{
				return *now_ptr;
			}
			if (now_ptr->brother == nullptr)	//����ǰ�ڵ㲻ƥ���Ҳ������ֵܽڵ�,���˳�����
			{
				return *now_ptr;
			}
			else
			{
				now_ptr = now_ptr->brother;		//����ǰ�ڵ㲻ƥ�������ֵܽڵ�,��ȡ�ֵܽڵ�Ϊ��ǰ�ڵ�,����ƥ��
			}
		}
	}
}

Node & GetNode(Node *now_ptr, int i)
{
	if (now_ptr == nullptr)
	{
		return *now_ptr;
	}
	else
	{
		while (now_ptr->key != "")		//����ж�,ֱ���ҵ�һ��������Ϊ�յĽڵ�
		{
			now_ptr = now_ptr->son;
		}
		for (int counter = 1; counter < i; counter++)		//�ڵ�ǰ���ҵ���i���ڵ㲢����
		{
			now_ptr = now_ptr->brother;
		}
		return *now_ptr;
	}
}