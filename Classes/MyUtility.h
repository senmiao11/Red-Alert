//解决Windows平台GBK格式下中文乱码问题 调用方式 MyUtility::gbk_2_utf8() 注意包含头文件

#ifndef __MyUtility_H__
#define __MyUtility_H__
#include<string>
#include<Windows.h>
using namespace std;
class MyUtility
{
public:
	static string gbk_2_utf8(const string text);
};


#endif // !__MyUtility_H__



