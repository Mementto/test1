/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:��������Դ�ļ�

**************************************************/

#include <QCoreApplication>
#include <GUIMain.h>

/* �����������Ҳ�������ߵ��߳��� */
const int CameraNum = 5;

/* ��1���ٽ�����ȡͼƬ���߳��� */
const int WindowNum = 1;

/* 1���ٽ�����������С */
const int bufferSize_1 = 150;

/* 2���ٽ�����������С */
const int bufferSize_2 = 10;

/* Ϊ�˷�ֹ��������ͼƬ�洢�ռ�ͬʱ��������
��ͼƬ�洢�ռ�����Ҫ����ѭ��ɾ��ͼƬ����ͼƬ
�洢�ռ�Ҫ��С����û�������С��LessNumΪ��
С�ڵ��� */
const int LessNum = 5;

/* �����ļ��Ľ� */
const string Section = "camera_wifi_path";

/* �����ļ����ļ��� */
const string FileName = "config.ini";

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
    GUIMain* main = new GUIMain(FileName, Section, CameraNum, WindowNum, bufferSize_1, bufferSize_2, LessNum);
    main->create();
    main->start();
    return a.exec();
}
