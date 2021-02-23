/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:�����������̺߳��������̣߳�
			����������2���ٽ��������е�ͼƬ֡��

**************************************************/

#ifndef __GUIMAIN__
#define __GUIMAIN__
#include "Supplier.h"
#include "Producer.h"
#include "CParseIniFile.h"
#include "CriticalArea.h"
#include <time.h>

class VideoLoader {
public:

	/**************************************************

	Function:GUIMain

	Description:���캯������ʼ����Ա����

	Calls:null

	Input:fileName�������ļ����ļ���

		  section�������ļ��Ľ���

		  cameraNum��������������ޣ���ʼ��������
		  ָ������Ĵ�С���������̵߳������Լ����
		  �����������ļ��еļ�-ֵ������ȷ����

		  windowNum����ʼ��������ָ������Ĵ�С��
		  ȷ���������߳�����

		  bufferSize_1��1���ٽ�����������С

		  bufferSize_2��2���ٽ�����������С

		  lessNum��Ϊ�˷�ֹ��������ͼƬ�洢�ռ�ͬ
		  ʱ����������ͼƬ�洢�ռ�����Ҫ����ѭ��
		  ɾ��ͼƬ����ͼƬ�洢�ռ�Ҫ��С����û�
		  ������С��LessNumΪ��С�ڵ���

	Output:null

	Others:����ͨ��Ա������ʼ������ָ���Ա������
	�ٶѿռ�

	**************************************************/
	VideoLoader(
		const int& bufferSize_1,
		const int& lessNum,
		const int& videoCaptureReadTime,
		map<string, string> path);

	/**************************************************

	Function:~GUIMain()

	Description:����������delete����ָ��ѵ�ָ��

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~VideoLoader();

	/**************************************************

	Function:create

	Description:�����������̺߳��������߳�

	Calls:Producer�࣬setData(CriticalArea* data)��
		  setPath(string path)��setId(int id)��
		  run()

		  Consumer�࣬setData(CriticalArea* data)��
		  run()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void create();

	/**************************************************

	Function:stopAll

	Description:��ֹ�����߳�

	Calls:CriticalArea�࣬getStopReturnSignal()��
		  setRunSignal(const int& runSignal)

	Input:null

	Output:null

	Others:null

	**************************************************/
	void stopAll();

	void receiveImage();

private:

	Supplier* mSupplier;

	/* �����ߣ�������ж�ȡ�������ٽ���ջͼƬ���߳�ָ�� */
	Producer* mProducer;

	/* ָ���ٽ��������б�����ָ�� */
	CriticalArea* mCriticalArea;

	/* ��ȡini�����ļ���Ϣ���ָ�� */
	CParseIniFile* mCParseIniFile;

	const int mVideoCaptureReadTime;

	map<string, string> mPath;

	int mThreadNum;
};

#endif // !__GUIMAIN__
