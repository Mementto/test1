/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:��������Դ�ļ�

**************************************************/
#include <QCoreApplication>
#include "Detect.h"

/**************************************************

Function:main

Description:����������ں���

Calls:GUIMain�࣬GUIMain���캯��

Input:argc��argc

Output:a.exec()

Others:null

**************************************************/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Detect* detect = new Detect();
    return a.exec();
}
