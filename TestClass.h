#ifndef __TESTCLASS__
#define __TESTCLASS__

#include "CriticalArea.h"

class TestClass: public QThread {
public:
	TestClass(CriticalArea* criticalArea);
	~TestClass();
	void run();
private:
	CriticalArea* mCriticalArea;
};

#endif // !__TESTCLASS__