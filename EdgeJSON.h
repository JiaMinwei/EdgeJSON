/*
EdgeJSON-���Э��
Copyright (c) 2018 Jiaminwei

1.����:��Э�����ڹ�Ͻ�û�����ҵʵ�� (���¼�ƣ��������) �����ԭ���ߣ����¼�ƣ���ɷ���֮��
  �Ĺ�ϵ��ʹ�ñ�����������������ڸ��ơ����ء���װ�����б����������Ϊͬ�ⱾЭ�顣��Э��涨��
  ʹ����ɷ�������ӵ�е�EdgeJSON (���¼�Ʊ����) �����Ȩ�������ƺ�������������:
2.���֤����:��ɷ��ش����豻����˸��˸��ơ��ַ����޸��Լ�����ҵ��ʹ�ñ������Ȩ��(��ҵʹ����
  ��ϵ���ԭ����)��
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
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum Types			
{
	EdgeJSON_object,		//7�ֽڵ�����
	EdgeJSON_array,
	EdgeJSON_int,
	EdgeJSON_double,
	EdgeJSON_string,
	EdgeJSON_bool,
	EdgeJSON_null,

	EdgeJSON_layer,		//Ϊ�ʷ�������������չ2������
	EdgeJSON_void
};		

enum Relations		//�ڵ�֮��Ĺ�ϵ
{
	brother,		//�ֵܽڵ��ϵ
	son				//���ӽڵ��ϵ
};

class Node			//�ڵ���
{
  public:
	Node *brother;		//ָ���ֵܽڵ��ָ��
	Node *son;			//ָ���ӽڵ��ָ��

	Types node_type;	//�ڵ�����
	string key;			//�ڵ�ļ�����(�����)
	
	string value_str;	//�ڵ��ֵ����,��4��
	int value_int;
	int value_null;
	double value_dou;
	bool value_boo;

	Node();				//���캯��,��ʼ���ڵ�ĳ�Ա����

	Node &operator[](const char *);		//��ȡָ���ڵ������
	Node &operator[](int);
};

class token				//�ʷ����������صĴ洢
{
public:
	Types token_type;	//��������
	string token_str;	//��������

	token();			//��ʼ��������ĳ�Ա����
};

class EdgeJSON			//��Ҫ��,ʹ�ñ�������,�����Է�װ�ڴ�
{
  public:
	Node *root;			//ָ��json�ṹ�׽ڵ�
	
	EdgeJSON();			//���캯��,��ʼ��rootָ��

	Node &operator[](const char *);		//��ȡָ���ڵ������
	Node &operator[](int);

	/*����ڵ㺯��,ͨ�������б�Ĳ�ͬ���غ���.
	 *Node�Ǳ����صĽڵ�,Relations��������ʲô��ݹ���.
	 *��������Ӽ���Ľڵ��������.
	 */
	Node *AddKeyvalue(Node &, Relations, const char*, int);			//����ֵΪint�ͼ�ֵ��
	Node *AddKeyvalue(Node &, Relations, const char*, double);		//����ֵΪdouble�ͼ�ֵ��
	Node *AddKeyvalue(Node &, Relations, const char*, const char *);	//����ֵΪstring�ͼ�ֵ��
	Node *AddKeyvalue(Node &, Relations, const char*, bool);			//����ֵΪbool�ͼ�ֵ��
	Node *AddKeyvalue(Node &, Relations, const char *);		//����null����

	Node *AddArray(Node &, Relations, const char *);	//�������鵽����
	Node *AddArray(Node &, Relations);				//�������鵽����
	Node *AddArray(EdgeJSON &);			//�������鵽EdgeJSON

	Node *AddObject(Node &, Relations, const char *); //������󵽶���
	Node *AddObject(Node &, Relations);				 //�����������
	Node *AddObject(EdgeJSON &);			 //�������EdgeJSON

	Node *AddValue(Node &, Relations, int);			//����int������Ԫ��
	Node *AddValue(Node &, Relations, double);		//����double������Ԫ��
	Node *AddValue(Node &, Relations, const char *);	//����string������Ԫ��
	Node *AddValue(Node &, Relations, bool);			//����bool������Ԫ��
	Node *AddValue(Node &, Relations);					//����null����Ԫ��

	string EdgeJSONPrint();				//��ӡjson�ṹ,����ַ���
	bool DeleteEdgeJSON();		//ɾ�������ṹ
	void EdgeJSONParse(string);		//�����ַ���

private:
	Node * CreateNode(Node &, Relations);		//����һ���ڵ㣬�Ա���ֵ����ص����ṹ��

	string TraversalPrint(Node *);		//���������ṹ��ÿ���ڵ��Ա���������ַ���
	string PrintObject(Node *);			//��ӡ����
	string PrintArray(Node *);			//��ӡ����
	string PrintKeyvalue(Node *);		//��ӡ�м�ֵ

	bool TraversalDelete(Node *);		//����json�ṹ����ɾ��

	Node *LayerParse(string);			//�ֲ����
	void  Lexing(vector<token *>&, string &);	//�ʷ�������
	Node *ParseObject(string);			//��������
	Node *ParseArray(string);			//��������
	Node *ParseInt(string);				//����int
	Node *ParseDouble(string);			//����double
	Node *ParseString(string);			//����string
	Node *ParseBool(string);			//����bool
	Node *ParseNull(string);			//����null
};

Node &GetNode(Node *, const char *);		//Ϊoperator[]���ò���
Node &GetNode(Node *, int);