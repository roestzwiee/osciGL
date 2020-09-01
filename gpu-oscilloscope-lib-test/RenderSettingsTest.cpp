#include "MockCudaInput.h"
#include "MockUserControls.h"
#include "../gpu-oscilloscope-lib/src/AdditionalRenderer/CoordinateSystemRenderSettings.h"

using testing::AtLeast;
using testing::Return;

MockUserControls controlsMock;

class RenderSettingsTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// Camera Setup:
		//
		//			3			   3
		// |  ~~~~~~~~~~~~~~|~~~~~~~~~~~~~~|
		//	  \				|
		//		\			|
		//		  \ 		|
		//			\		|	2
		//			  \ 	|
		//		45°		\	|
		//				  \ |

		// Angle of View 45°
		// Screen Width 3
		// Screen Height 2

		
		EXPECT_CALL(controlsMock, getTranslationInZ()).WillOnce(Return(2.0));
		EXPECT_CALL(controlsMock, getTranslationInX()).WillOnce(Return(0.0));
	}

};

TEST_F(RenderSettingsTest, Simple)
{

	// EXPECT_CALL(controlsMock, getTranslationInZ()).WillOnce(Return(1.0));
	// EXPECT_CALL(controlsMock, getTranslationInX()).WillOnce(Return(2.0));

	CoordinateSystemRenderSettings cut(&controlsMock);

	EXPECT_EQ(-3, cut.getBiggestDisplayedX());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}