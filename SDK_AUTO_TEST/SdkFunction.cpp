#include "UNIT_INC.h"
#include "SdkFunction.h"

template bool SdkFunction::IsPositionEqual<double>(double compare_point[], double home_point[], bool is_ra) const;
template bool SdkFunction::IsPositionEqual<int>(int compare_point[], int home_point[], bool is_ra) const;
void __stdcall CallBack(uint16_t cmd, uint16_t rlt, uint16_t* Msg, int len) {}

SdkFunction::SdkFunction() {
}

SdkFunction::~SdkFunction() {
}

void SdkFunction::CloseHrss() {
	system("taskkill /f /im HRSS.exe");
}

void SdkFunction::OpenHrss() {
	system("cd.. & start HRSS.exe");
}

void SdkFunction::CopyDB() {
	system(commend.c_str());
}

bool CheckRobotType(SdkFunction::SQA task, std::string robot_type) {
	string temp_robot_type = "";
	switch (task) {
	case SdkFunction::SQA::kT4815:
		temp_robot_type = RS410_600_200_LU;
		break;
	case SdkFunction::SQA::kT4884:
		temp_robot_type = RA605_710_GC;
		break;
	default:
		temp_robot_type = RA605_710_GC;
		break;
	}

	return robot_type == temp_robot_type;
}

bool SdkFunction::OpenConnection() {
	device_id = open_connection(IP, 1, CallBack);
	is_connected = device_id >= 0 ? true : false;

	return is_connected;
}

bool SdkFunction::DirExists(string path) {
	struct stat info;
	if (stat(path.c_str(), &info) == 0 && info.st_mode & S_IFDIR) {
		return true;
	}
	return false;
}

bool SdkFunction::CheckHrssRobotType(SQA task) {
	int get_robot = -1, connect_count = 0;
	bool is_connected = false;

	if (GetRobotType() != SUCCESS) {
		return ERROR;
	}

	if (CheckRobotType(task, string(robot_type))) {
		return SUCCESS;
	} else {
		CloseHrss();
		CopyDB();
		OpenHrss();

		do {
			is_connected = OpenConnection();
			if (connect_count >= CONNECT_COUNT) {
				return ERROR;
			}
			connect_count++;
		} while (!is_connected);

		if (is_connected) {
			return GetRobotType();
		}
	}
}

template<class T>
bool SdkFunction::IsPositionEqual(T compare_point[], T home_point[], bool is_ra) const {
	bool check = false;
	switch (is_ra) {
	case true:
		check = (compare_point[0] == home_point[0]) && (compare_point[1] == home_point[1]) &&
		        (compare_point[2] == home_point[2]) && (compare_point[3] == home_point[3]) &&
		        (compare_point[4] == home_point[4]) && (compare_point[5] == home_point[5]);
		break;
	case false:
		check = (compare_point[0] == home_point[0]) && (compare_point[1] == home_point[1]) &&
		        (compare_point[2] == home_point[2]) && (compare_point[3] == home_point[3]);
		break;
	default:
		break;
	}
	return check;
}

int SdkFunction::GetRobotType() {
	int check = get_robot_type(device_id, robot_type);
	string temp(robot_type);
	if (check == SUCCESS) {
		if (temp.find("RA") != string::npos) {
			is_ra = true;
		} else if (temp.find("RS") != string::npos) {
			is_ra = false;
		}
	}
	return check;
}

int SdkFunction::GetHrssVersion() {
	char* version = new char[256];
	int rlt = get_hrss_version(device_id, version);
	string temp(version);

	if (temp.find("3.3.") != string::npos) {
		hrss_version = kHRSS33;
	} else if (temp.find("3.4.") != string::npos) {
		hrss_version = kHRSS40;
	}
	delete[] version;
	return rlt;
}

int SdkFunction::GetHrssMode() {
	return get_hrss_mode(device_id);
}

int SdkFunction::ClearAlarm() {
	int check = clear_alarm(device_id);
	return !(check == 0 || check == 300);
}

void SdkFunction::SetScriptName(SQA task) {
	std::string temp_script;
	switch (task) {
	case kT4815:
		temp_script = "SQA\\T4815\\T4815.hrb";
		break;
	case kT4884:
		temp_script = "SQA\\T4884\\T4884.hrb";
		break;
	default:
		temp_script = "";
		break;
	}

	strcpy_s(script_name, temp_script.c_str());
}

void SdkFunction::SetCopyDbCommend(SQA task) {
	switch (task) {
	case kT4815:
		commend = "copy SQA\\T4815\\*.db ..\\ /Y /V";
		break;
	case kT4884:
		commend = "copy SQA\\T4884\\*.db ..\\ /Y /V";
		break;
	default:
		commend = "";
		break;
	}
}

int SdkFunction::SetCounterInital() {
	int counter_index[20] { 0 };
	int value_index[20] { 0 };
	for (int i = 0; i < sizeof(counter_index) / sizeof(int); i++) {
		counter_index[i] = i + 1;
	}
	return set_counter_array(device_id, counter_index, value_index, sizeof(counter_index) / sizeof(int));;
}

int SdkFunction::JogHome() {
	time_t begin_time, end_time;
	double current_position[6] = { 0 };
	time(&begin_time);
	int check = jog_home(device_id);
	if (check) {
		return ERROR;
	}

	do {
		auto wait_time = difftime(time(&end_time), begin_time);;//unit:SEC
		if (wait_time > JOG_HOME_TIMEOUT) {
			return ERROR;
		}
		get_current_joint(device_id, current_position);
	} while (!IsPositionEqual(current_position, (is_ra ? ra_joint_home : rs_joint_home), is_ra));

	return SUCCESS;
}

int SdkFunction::SetHrssHrb() {
	return send_file(device_id, script_name, HRB_NAME);
}
