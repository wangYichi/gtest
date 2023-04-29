#include "UNIT_INC.h"
#include "SdkFunction.h"

class TEST_T4884 : public ::testing::Test {
 public: // NOLINT
	virtual void SetUp() {
		SdkFunction::GetInstance()->SetScriptName(SdkFunction::kT4884);
		SdkFunction::GetInstance()->SetCopyDbCommend(SdkFunction::kT4884);
		ASSERT_EQ(SdkFunction::GetInstance()->CheckHrssRobotType(SdkFunction::kT4884), SUCCESS);
		ASSERT_EQ(SdkFunction::GetInstance()->SetCounterInital(), SUCCESS);
	}

	virtual void TearDown() {
	}
};

TEST_F(TEST_T4884, JogHome) {
	EXPECT_EQ(SdkFunction::GetInstance()->JogHome(), SUCCESS);
}

TEST_F(TEST_T4884, SetHrssHrb) {
	ASSERT_EQ(SdkFunction::GetInstance()->SetHrssHrb(), SUCCESS);
}