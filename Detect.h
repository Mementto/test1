#ifndef __DETECT__
#define __DETECT__

#include "VideoLoader.h"
#include "CParseIniFile.h"

struct FileAndSectionName {
    string fileName = "config.ini";
    string section1 = "base_param";
    string section2 = "camera_wifi_path";
    string section3 = "camera_loacal_path";
};

struct BasicParamKey1 {
    string handleNum = "handle_num";
    string bufferSize_1 = "buffer_size_1";
    string bufferSize_2 = "buffer_size_2";
    string lessNum = "less_num";
    string videoCaptureReadTime = "video_capture_read_time";
};

class Detect {
public:
	Detect();
	~Detect();
private:
	
    void startAllThread();

    void receiveImage();
};

#endif // !__DETECT__

