#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "CriticalArea.h"

class Supplier: public QThread {
public:
	Supplier();
	~Supplier();
	void setId(const int& id);
	void setPath(const string& path);
	void setData(CriticalArea* const criticalArea);
	void run();
private:
	CriticalArea* mCriticalArea;
	string mPath;
	int mId;
	bool flag;
};

#endif // !__SUPPLIER__