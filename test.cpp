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
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	EJ newjson;
	clock_t start, ends;

	//构建测试
	Node &ob = newjson.AddObject();
	ob.AddKeyvalue("name", "金庸");
	ob.AddKeyvalue("foreign-language name", "Louis Cha");
	ob.AddKeyvalue("nationality", "中国");
	ob.AddKeyvalue("nation", "汉族");

	Node &ar0 = ob.AddArray("birthplace");
	ar0.AddObject().AddKeyvalue("province", "浙江");
	ar0.AddObject().AddKeyvalue("city", "嘉兴");

	Node &ar2 = ob.AddArray("profession");
	ar2.AddValue("作家");
	ar2.AddValue("政论家");
	ar2.AddValue("社会活动家");

	Node &ar3 = ob.AddArray("works");
	ar3.AddValue("射雕英雄传");
	ar3.AddValue("神雕侠侣");
	ar3.AddValue("倚天屠龙记");

	//数据接口测试
	ar0[1]["city"].value_str = "海宁";
	(ar3)[2].value_str = "天龙八部";

	//打印构建结构
	cout << "构建json>>>\n"
		 << newjson.EJPrint() << "\n\n";
	newjson.DeleteEJ(); //删除json结构

	// //解析sample.json测试
	fstream test;
	test.open("/Users/minweichia/EdgeJSON-2.0/sample.json", ios::in); //打开sample.json文件
	string s;
	while (!test.eof())
	{
		s += test.get(); //依次读入文件内容
	}
	s = s.substr(0, s.size() - 1); //去除字符串末尾的EOF
	test.close();

	//字符串解析
	start = clock();
	newjson.EJParse(&s);
	ends = clock();

	cout << "字符串解析json>>>\n"
		 << newjson.EJPrint() << endl;
	cout << "解析耗时: " << (double)(ends - start) / CLOCKS_PER_SEC << endl
		 << endl;
	newjson.DeleteEJ();

	//文件解析
	start = clock();
	newjson.EJParse("/Users/minweichia/EdgeJSON-2.0/sample.json"); //调用解析方法
	ends = clock();

	cout << "文件解析json>>>\n"
		 << newjson.EJPrint() << endl;
	cout << "解析耗时: " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	newjson.DeleteEJ();

	system("pause");
	char c;
	cin >> c;
	return 0;
}
