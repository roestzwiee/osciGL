#pragma once

#include "../gpu-oscilloscope-lib/src/Headers/ICudaInput.h"
#include "gmock/gmock.h"

struct cudaGraphicsResource;

class UserCudaInput : public ICudaInput
{
public:
	MOCK_METHOD(void, computeInput, (cudaGraphicsResource** cuda_vbo_resource, float g_fAnim), (override));

	/**
	 * Used to actually draw.
	 */
	MOCK_METHOD(unsigned int, getCurrentMeshWidth, (), (override));


	/**
	 * Used for allocations.
	 */
	MOCK_METHOD(unsigned int, getMeshWidth, (), (override));
	MOCK_METHOD(unsigned int, getMeshHeight, (), (override));

};
