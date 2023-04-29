#include "UNIT_INC.h"
#include "SdkFunction.h"

class InitializationTest : public ::testing::Test {
 public: // NOLINT
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST(InitializationTest, HRSSConnect) {
	ASSERT_TRUE(SdkFunction::GetInstance()->OpenConnection());
}

TEST(InitializationTest, CheckHrssExtMode) {
	ASSERT_EQ(SdkFunction::GetInstance()->GetHrssMode(), SdkFunction::kEXT);
}

TEST(InitializationTest, ClearAlarm) {
	ASSERT_EQ(SdkFunction::GetInstance()->ClearAlarm(), SUCCESS);
}

TEST(InitializationTest, GetHrssVersion) {
	ASSERT_TRUE(!SdkFunction::GetInstance()->GetHrssVersion());
}

TEST(InitializationTest, GetRobotType) {
	ASSERT_EQ(SdkFunction::GetInstance()->GetRobotType(), SUCCESS);
}