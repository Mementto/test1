/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:从ini配置文件中根据节来读取键-值对
			例如：[section]叫做节
				  key=value叫做键-值对

**************************************************/

#ifndef __CPARSEINIFILE__
#define __CPARSEINIFILE__

#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#define COMMENT_CHAR '#'

class CParseIniFile {
public:

	/**************************************************

	Function:CParseIniFile

	Description:构造函数

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	CParseIniFile();

	/**************************************************

	Function:~CParseIniFile

	Description:析构函数

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~CParseIniFile();

	/**************************************************

	Function:ReadConfig

	Description:将ini文件中的指定键-值对输出到map中

	Calls:本类，AnalyseLine(const string& line,
		  string& key, string& val)

	Input:fileName，配置文件的文件名

		  content，存储键-值对的map

		  section，配置文件的节

	Output:布尔值，true为输出成功，false则为失败

	Others:null

	**************************************************/
	bool ReadConfig(const string& filename, map<string, string>& content, const string& section);

	/**************************************************

	Function:AnalyseLine

	Description:逐行处理配置文件中的数据，拆分
				等号左右的建和值，分别存入两个
				字符串变量中

	Calls:本类，Trim(string& str)

	Input:line，一行的所有数据（字符串）

		  key，存储行中的建

		  val，存储行中的值

	Output:布尔值，true为成功，false为失败

	Others:null

	**************************************************/
	bool AnalyseLine(const string& line, string& key, string& val);

	/**************************************************

	Function:Trim

	Description:去除字符串左右两端的空格

	Calls:本类，IsSpace(char c)

	Input:str，需要去除空格的字符串，并将去除完成后
		  的字符串存回该参数中

	Output:null

	Others:null

	**************************************************/
	void Trim(string& str);

	/**************************************************

	Function:IsSpace

	Description:判断输入的字符是否为空格

	Calls:null

	Input:c，输入的字符

	Output:布尔值，是空格输出true，反之false

	Others:null

	**************************************************/
	bool IsSpace(char c);

	/**************************************************

	功能不明
	至今未被调用

	**************************************************/
	bool IsCommentChar(char c);

	/**************************************************

	功能不明
	至今未被调用

	**************************************************/
	void PrintConfig(const map<string, string>& mContent);
private:
};

#endif // !__CPARSEINIFILE__