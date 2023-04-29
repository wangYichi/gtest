#pragma once
#ifndef SDK_FUNCTION_H
#define SDK_FUNCTION_H

#include "HRSDK.h"
#include <sys/stat.h>
#include <time.h>

#define IP "127.0.0.1"
#define ERROR 1
#define SUCCESS 0
#define CONNECT_COUNT 25
#define HRB_TEST_COUNT 100
#define JOG_HOME_TIMEOUT 60
#define HRB_NAME "Auto_test.hrb"
#define RS410_600_200_LU "RS410-600-200-LU"
#define RA605_710_GC "RA605-710-GC"

using namespace std;

class SdkFunction {
 public:
	enum SQA {
		kT4815,
		kT4884,
		kT5587,
		kT5717,
		kT5462,
		kT6083,
		kT6370,
		kT6453,
	};

	enum HRSSVersion {
		kHRSS33,
		kHRSS40,
	};

	enum OperationMode {
		kT1,
		kAUT,
		kT2,
		kEXT,
		kSDKSafety,
		kSDKAuto,
	};

	enum RobotType {
		kRA_Series,
		kRS_Series,
		kRD_Series,
	};

	SdkFunction();
	~SdkFunction();
	static SdkFunction* GetInstance() {
		static SdkFunction instance_;
		return &instance_;
	}
	bool OpenConnection();
	bool DirExists(string);
	bool CheckHrssRobotType(SQA);
	int GetHrssVersion();
	int GetRobotType();
	int GetHrssMode();
	int ClearAlarm();
	void SetScriptName(SQA);
	void SetCopyDbCommend(SQA);
	int SetCounterInital();
	int SetHrssHrb();
	int JogHome();

 private:
	void CopyDB();
	void CloseHrss();
	void OpenHrss();

	template<class T>
	bool IsPositionEqual(T[], T[], bool) const;
	bool is_connected = false;
	bool is_ra = false;
	double rs_joint_home[4] = { 0 };
	double ra_joint_home[6] = { 0, 0, 0, 0, -90, 0 };
	HRSSVersion hrss_version = kHRSS33;
	string commend = "";
	char script_name[50];
	char robot_type[50];
	int device_id = -1;
};


#endif // !SDKFUNCTION_H