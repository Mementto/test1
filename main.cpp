/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:主函数的源文件

**************************************************/
#include <QCoreApplication>
#include "Detect.h"

/**************************************************

Function:main

Description:主函数，入口函数

Calls:GUIMain类，GUIMain构造函数

Input:argc，argc

Output:a.exec()

Others:null

**************************************************/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Detect* detect = new Detect();
    return a.exec();
}
