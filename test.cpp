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
#include "EdgeJSON.h"
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	EdgeJSON newjson;

	//构建测试
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

	//数据接口测试
	newjson["birthplace"][2]["city"].value_str = "海宁";
	newjson["works"][2].value_str = "天龙八部";

	//打印构建结构
	cout << newjson.EdgeJSONPrint() << "\n\n";
	newjson.DeleteEdgeJSON();		//删除json结构
	
	//解析sample.json测试
	fstream test;
	test.open("sample.json", ios::in);		//打开sample.json文件
	string s;
	while (!test.eof())
	{
		s += test.get();				//依次读入文件内容
	}
	s = s.substr(0, s.size() - 1);		//去除字符串末尾的EOF
	cout << s << "\n\n";					//打印解析前的字符串
	newjson.EdgeJSONParse(s);			//调用解析方法
	cout << newjson.EdgeJSONPrint() << "\n\n";		//打印解析生成的json结构
	system("pause");
	return 0;
}