/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:�����������̺߳��������̣߳�
			����������2���ٽ��������е�ͼƬ֡��

**************************************************/

#ifndef __GUIMAIN__
#define __GUIMAIN__
#include "Producer.h"
#include "Consumer.h"
#include "CParseIniFile.h"
#include "CriticalArea.h"

class GUIMain : public QThread {
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
	GUIMain(
		const string& fileName,
		const string& section,
		const int& cameraNum,
		const int& windowNum,
		const int& bufferSize_1,
		const int& bufferSize_2,
		const int& lessNum);

	/**************************************************

	Function:~GUIMain()

	Description:����������delete����ָ��ѵ�ָ��

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~GUIMain();

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

	Function:run

	Description:��������2���ٽ��������е�ͼƬ֡

	Calls:CriticalArea�࣬getQMutex_2()��
		  getNumUsedBytes_2()��getFull_2()��
		  getTestStream()��getNumUsedBytes_1()��
		  getEmpty_2()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();

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

private:

	/* �����ߣ�������ж�ȡ�������ٽ���ջͼƬ���߳�ָ�� */
	Producer* mProducer;

	/* �����ߣ����ٽ���ջ�ж�ȡ��������Զ��е��߳�ָ�� */
	Consumer* mConsumer;

	/* ָ���ٽ��������б�����ָ�� */
	CriticalArea* mCriticalArea;

	/* ��ȡini�����ļ���Ϣ���ָ�� */
	CParseIniFile* mCParseIniFile;

	/* ��ʼ��������ָ������Ĵ�С��ȷ���������߳����� */
	const int mWindowNum;

	/* ������������ޣ���ʼ��������ָ��
	����Ĵ�С���������̵߳������Լ����
	�����������ļ��еļ�-ֵ������ȷ���� */
	const int mCameraNum;

	/* �����ļ����ļ��� */
	const string mFileName;

	/* �����ļ��Ľ��� */
	const string mSection;

	/* �������ļ��ļ�-ֵ�ԣ������ڿ纯����¼�������߳��� */
	map<int, string> mPath;
};

#endif // !__GUIMAIN__
