#include "UNIT_INC.h"
#include "SdkFunction.h"

#define OUTPUT_NAME_LEN 60

std::string TestSelector() {
	std::string test_select;
#define DEF_TEST_SUIT(a, b)  \
	if (b) {			     \
		test_select += #a;	 \
		test_select += "*:"; \
	}
#include "TestSelector.def"
#undef DEF
	return test_select;
}

void GetOutputPath(char* buffer) {
	std::time_t rawtime;
	std::tm* timeinfo;
	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);
	std::strftime(buffer, OUTPUT_NAME_LEN, "xml:Output\\SDKTest_%Y%m%d-%H%M.xml", timeinfo);
}

class HREnvironment : public ::testing::Environment {
 public:
	virtual ~HREnvironment() {
	}
	/* global initialization, called before RUN_ALL_TESTS()
	 * only those common functions, like parameters initializations, have to be called here
	 * Do not initialize mfc dialogue in unit test project
	 */
	virtual void SetUp() {
		//find SQA folder
		ASSERT_TRUE(SdkFunction::GetInstance()->DirExists("SQA"));
	}

	/* global close function, called after RUN_ALL_TESTS() */
	virtual void TearDown() {
	}
};

int main(int argc, char **argv) {
	char buffer[OUTPUT_NAME_LEN];
	char *filter = NULL;
	GetOutputPath(buffer);
	testing::Environment *const pHrssEnv = ::testing::AddGlobalTestEnvironment(new HREnvironment());
	for (int i = 0; i < argc; i++) {
		char *p = strstr(argv[i], "--gtest_filter=");
		if (p) {
			p = strstr(argv[i], "=");
			p++;
			filter = p;
		}
	}
	testing::GTEST_FLAG(output) = buffer;
	testing::InitGoogleTest(&argc, argv);
	testing::GTEST_FLAG(filter) = "*InitializationTest*";
	int res = RUN_ALL_TESTS();

	if (!res && filter == NULL) {
		testing::GTEST_FLAG(filter) = TestSelector().c_str();
		//testing::GTEST_FLAG(filter) = "*:-*InitializationTest*";
		res = RUN_ALL_TESTS();
	}
	//testing::GTEST_FLAG(shuffle) = 1;
	//testing::GTEST_FLAG(repeat) = 15;
	system("pause");
	delete[] filter;
	return res;
}