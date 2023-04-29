#include "SdkFunction.h"

enum PassCondition {
	kCount,
	kTime,
};

class ScriptTest {
 protected:
	PassCondition pass_condition = kCount;
 public:
	virtual bool GetResult() = 0;
};

class StartPause : public ScriptTest {
 public:
	StartPause(PassCondition condition) {
		pass_condition = condition;
	}

	bool GetResult() override {

		return SUCCESS;
	};
};

