#include "Script.h"
#include "SdkFunction.h"

class ScriptTester {
 public:
	ScriptTest *CreateTest(SdkFunction::SQA test, PassCondition condition) {
		switch (test) {
		case SdkFunction::SQA::kT4815:
			return new StartPause(condition);
			break;
		default:
			return NULL;
			break;
		}
	}
};
