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
#include "EdgeJSON.h"
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	EdgeJSON newjson;

	//��������
	newjson.AddObject(newjson);
	newjson.AddKeyvalue(newjson[1], son, "name", "��ӹ");
	newjson.AddKeyvalue(newjson["name"], brother, "foreign-language name", "Louis Cha");
	newjson.AddKeyvalue(newjson["foreign-language name"], brother, "nationality", "�й�");
	newjson.AddKeyvalue(newjson["nationality"], brother, "nation", "����");
	newjson.AddArray(newjson["nation"], brother, "birthplace");
	newjson.AddObject(newjson["birthplace"], son);
	newjson.AddObject(newjson["birthplace"][1], brother);
	newjson.AddKeyvalue(newjson["birthplace"][1], son, "province", "�㽭");
	newjson.AddKeyvalue(newjson["birthplace"][2], son, "city", "����");
	newjson.AddArray(newjson["birthplace"], brother, "profession");
	newjson.AddValue(newjson["profession"], son, "����");
	newjson.AddValue(newjson["profession"][1], brother, "���ۼ�");
	newjson.AddValue(newjson["profession"][2], brother, "�����");
	newjson.AddArray(newjson["profession"], brother, "works");
	newjson.AddValue(newjson["works"], son, "���Ӣ�۴�");
	newjson.AddValue(newjson["works"][1], brother, "�������");
	newjson.AddValue(newjson["works"][2], brother, "����������");

	//���ݽӿڲ���
	newjson["birthplace"][2]["city"].value_str = "����";
	newjson["works"][2].value_str = "�����˲�";

	//��ӡ�����ṹ
	cout << newjson.EdgeJSONPrint() << "\n\n";
	newjson.DeleteEdgeJSON();		//ɾ��json�ṹ
	
	//����sample.json����
	fstream test;
	test.open("sample.json", ios::in);		//��sample.json�ļ�
	string s;
	while (!test.eof())
	{
		s += test.get();				//���ζ����ļ�����
	}
	s = s.substr(0, s.size() - 1);		//ȥ���ַ���ĩβ��EOF
	cout << s << "\n\n";					//��ӡ����ǰ���ַ���
	newjson.EdgeJSONParse(s);			//���ý�������
	cout << newjson.EdgeJSONPrint() << "\n\n";		//��ӡ�������ɵ�json�ṹ
	system("pause");
	return 0;
}