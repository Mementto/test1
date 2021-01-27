/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:CParseIniFile的功能实现源文件

**************************************************/

#include "CParseIniFile.h"

CParseIniFile::CParseIniFile() {}

CParseIniFile::~CParseIniFile() {}

bool CParseIniFile::ReadConfig(const string& filename, map<string, string>& content, const string& section) {
	content.clear();
	ifstream infile(filename.c_str());
	if (!infile) {
		// LOG4CXX_ERROR(logger, "file open error!");
		return false;
	}
	string line, key, value;
	int pos = 0;
	string Tsection = string("[") + section + "]";
	bool flag = false;
	while (getline(infile, line)) {
		if (!flag) {
			pos = line.find(Tsection, 0);
			if (-1 == pos) {
				continue;
			} else {
				flag = true;
				getline(infile, line);
			}
		}
		if (0 < line.length() && '[' == line.at(0)) {
			break;
		}
		if (0 < line.length() && AnalyseLine(line, key, value)) {

			if (value.length() > 0) {
				if (value[value.size() - 1] == '\r') {
					value[value.size() - 1] = '\0';
				}
			}
			content[key] = value;
		}
	}
	infile.close();
	return true;
}

bool CParseIniFile::AnalyseLine(const string& line, string& key, string& val) {
	if (line.empty()) {
		return false;
	}
	int start_pos = 0, end_pos = line.size() - 1, pos = 0;
	if ((pos = line.find(COMMENT_CHAR)) != -1) {
		/* 行的第一个字符就是注释字符 */
		if (0 == pos) {
			return false;
		}
		end_pos = pos - 1;
	}

	/* 预处理，删除注释部分 */
	string new_line = line.substr(start_pos, start_pos + 1 - end_pos);

	/* 没有=号 */
	if ((pos = new_line.find('=')) == -1) {
		return false;
	}

	key = new_line.substr(0, pos);
	val = new_line.substr(pos + 1, end_pos + 1 - (pos + 1));

	Trim(key);
	if (key.empty()) {
		return false;
	}
	Trim(val);
	return true;
}

void CParseIniFile::Trim(string& str) {
	if (str.empty()) {
		return;
	}
	int i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	/* 全部是空白字符串 */
	if (i == str.size()) {
		str = "";
		return;
	}

	start_pos = i;

	for (i = str.size() - 1; i >= 0; --i) {
		if (!IsSpace(str[i])) {
			break;
		}
	}
	end_pos = i;

	str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool CParseIniFile::IsSpace(char c) {
	if (' ' == c || '\t' == c) {
		return true;
	}
	return false;
}

bool CParseIniFile::IsCommentChar(char c) {
	switch (c) {
	case COMMENT_CHAR:
		return true;
	default:
		return false;
	}
}

void CParseIniFile::PrintConfig(const map<string, string>& mContent) {
	map<string, string>::const_iterator mite = mContent.begin();
	for (; mite != mContent.end(); ++mite) {
		cout << mite->first << "=" << mite->second << endl;
	}
}