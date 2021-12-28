#pragma once

#include <cstdint>

#include "J3DBlock.hpp"

namespace bStream { class CStream; }
class J3DModelData;

constexpr uint32_t FLAGS_MATRIX_MASK = 0x0000000F;

class J3DModelLoader {
	J3DModelData* mModelData;

public:
	virtual J3DModelData* Load(bStream::CStream* stream, uint32_t flags);

protected:
	J3DModelLoader();
	virtual ~J3DModelLoader() {}

	void ReadInformationBlock(bStream::CStream* stream, uint32_t flags);
	void ReadVertexBlock(bStream::CStream* stream, uint32_t flags);
};