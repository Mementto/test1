/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:��ini�����ļ��и��ݽ�����ȡ��-ֵ��
			���磺[section]������
				  key=value������-ֵ��

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

	Description:���캯��

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	CParseIniFile();

	/**************************************************

	Function:~CParseIniFile

	Description:��������

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~CParseIniFile();

	/**************************************************

	Function:ReadConfig

	Description:��ini�ļ��е�ָ����-ֵ�������map��

	Calls:���࣬AnalyseLine(const string& line,
		  string& key, string& val)

	Input:fileName�������ļ����ļ���

		  content���洢��-ֵ�Ե�map

		  section�������ļ��Ľ�

	Output:����ֵ��trueΪ����ɹ���false��Ϊʧ��

	Others:null

	**************************************************/
	bool ReadConfig(const string& filename, map<string, string>& content, const string& section);

	/**************************************************

	Function:AnalyseLine

	Description:���д��������ļ��е����ݣ����
				�Ⱥ����ҵĽ���ֵ���ֱ��������
				�ַ���������

	Calls:���࣬Trim(string& str)

	Input:line��һ�е��������ݣ��ַ�����

		  key���洢���еĽ�

		  val���洢���е�ֵ

	Output:����ֵ��trueΪ�ɹ���falseΪʧ��

	Others:null

	**************************************************/
	bool AnalyseLine(const string& line, string& key, string& val);

	/**************************************************

	Function:Trim

	Description:ȥ���ַ����������˵Ŀո�

	Calls:���࣬IsSpace(char c)

	Input:str����Ҫȥ���ո���ַ���������ȥ����ɺ�
		  ���ַ�����ظò�����

	Output:null

	Others:null

	**************************************************/
	void Trim(string& str);

	/**************************************************

	Function:IsSpace

	Description:�ж�������ַ��Ƿ�Ϊ�ո�

	Calls:null

	Input:c��������ַ�

	Output:����ֵ���ǿո����true����֮false

	Others:null

	**************************************************/
	bool IsSpace(char c);

	/**************************************************

	���ܲ���
	����δ������

	**************************************************/
	bool IsCommentChar(char c);

	/**************************************************

	���ܲ���
	����δ������

	**************************************************/
	void PrintConfig(const map<string, string>& mContent);
private:
};

#endif // !__CPARSEINIFILE__