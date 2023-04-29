#include "UNIT_INC.h"
#include "SdkFunction.h"
#include "ScriptTester.h"


class TEST_T4815 : public ::testing::Test {
 public: // NOLINT
	virtual void SetUp() {
		SdkFunction::GetInstance()->SetScriptName(SdkFunction::kT4815);
		SdkFunction::GetInstance()->SetCopyDbCommend(SdkFunction::kT4815);
		ASSERT_EQ(SdkFunction::GetInstance()->CheckHrssRobotType(SdkFunction::kT4815), SUCCESS);
		ASSERT_EQ(SdkFunction::GetInstance()->SetCounterInital(), SUCCESS);
	}

	virtual void TearDown() {
	}
};

TEST_F(TEST_T4815, JogHome) {
	EXPECT_EQ(SdkFunction::GetInstance()->JogHome(), SUCCESS);
}

TEST_F(TEST_T4815, SetHrssHrb) {
	ASSERT_EQ(SdkFunction::GetInstance()->SetHrssHrb(), SUCCESS);
}

TEST_F(TEST_T4815, StartTest) {
	ScriptTester scripttester;
	ScriptTest *task = scripttester.CreateTest(SdkFunction::SQA::kT4815, kCount);
	ASSERT_EQ(task->GetResult(), SUCCESS);
	delete task;
}

