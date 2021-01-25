/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:主函数的源文件

**************************************************/

#include <QCoreApplication>
#include <GUIMain.h>

/* 照相机数量，也是生产者的线程数 */
const int CameraNum = 5;

/* 从1号临界区读取图片的线程数 */
const int WindowNum = 1;

/* 1号临界区缓冲区大小 */
const int bufferSize_1 = 150;

/* 2号临界区缓冲区大小 */
const int bufferSize_2 = 10;

/* 为了防止缓冲区和图片存储空间同时满而阻塞
（图片存储空间满后要进行循环删除图片），图片
存储空间要略小与可用缓冲区大小。LessNum为略
小于的量 */
const int LessNum = 5;

/* 配置文件的节 */
const string Section = "camera_wifi_path";

/* 配置文件的文件名 */
const string FileName = "config.ini";

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
    GUIMain* main = new GUIMain(FileName, Section, CameraNum, WindowNum, bufferSize_1, bufferSize_2, LessNum);
    main->create();
    main->start();
    return a.exec();
}
