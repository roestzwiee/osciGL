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

		
		EXPECT_CALL(controlsMock, getCameraPosition()).WillRepeatedly(Return(Position { 2.0 , 3.0, 0.0 }));
	}

};

TEST_F(RenderSettingsTest, Simple)
{

	CoordinateSystemRenderSettings cut(&controlsMock);

	EXPECT_EQ(2, cut.getFieldOfView().maxX);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
