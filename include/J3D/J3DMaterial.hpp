#pragma once

#include "J3D/J3DMaterialData.hpp"

#include <GXGeometryEnums.hpp>
#include <string>
#include <vector>
#include <memory>

class GXShape;

struct J3DPixelEngineBlock {
	J3DZMode mZMode;
	J3DAlphaCompare mAlphaCompare;
	J3DBlendMode mBlendMode;
	J3DFog mFog;

	bool mZCompLoc;
	bool mDither;

	J3DPixelEngineBlock() : mZCompLoc(false), mDither(false) { }
};

struct J3DLightBlock {
	EGXCullMode mCullMode;
	glm::vec4 mMatteColor[2];
	glm::vec4 mAmbientColor[2];

	std::vector<std::shared_ptr<J3DColorChannel>> mColorChannels;

public:
	J3DLightBlock() : mCullMode(EGXCullMode::None) {}
};

struct J3DTexGenBlock {
	J3DNBTScaleInfo mNBTScale;
	std::vector<std::shared_ptr<J3DTexCoordInfo>> mTexCoordInfo;
	std::vector<std::shared_ptr<J3DTexCoordInfo>> mTexCoord2Info;
	std::vector<std::shared_ptr<J3DTexMatrixInfo>> mTexMatrix;
};

struct J3DTevBlock {
	std::vector<uint16_t> mTextureIndices;
	std::vector<std::shared_ptr<J3DTevOrderInfo>> mTevOrders;
	std::vector<std::shared_ptr<J3DTevStageInfo>> mTevStages;

	glm::vec4 mTevColors[4];
	glm::vec4 mTevKonstColors[4];

	EGXKonstColorSel mKonstColorSelection[16];
	EGXKonstAlphaSel mKonstAlphaSelection[16];
};

struct J3DIndirectBlock {
	bool mEnabled;
	uint32_t mNumStages;

	std::vector<std::shared_ptr<J3DIndirectTexOrderInfo>> mIndirectTexOrders;
	std::vector<std::shared_ptr<J3DIndirectTexMatrixInfo>> mIndirectTexMatrices;
	std::vector<std::shared_ptr<J3DIndirectTexScaleInfo>> mIndirectTexCoordScales;
	std::vector<std::shared_ptr<J3DIndirectTevStageInfo>> mIndirectTevStages;

	J3DIndirectBlock() : mEnabled(false) { }
};

class J3DMaterial {
	int32_t mShaderProgram;
	const GXShape* mShape;

public:
	J3DMaterial();
	~J3DMaterial();

	std::string Name;
	EPixelEngineMode PEMode;

	J3DPixelEngineBlock PEBlock;
	J3DLightBlock LightBlock;
	J3DTexGenBlock TexGenBlock;
	std::shared_ptr<J3DTevBlock> TevBlock;
	std::shared_ptr<J3DIndirectBlock> IndirectBlock;

	int TEVStageGenMax;

	bool AreRegisterColorsAnimating;
	glm::vec4 AnimationRegisterColors[4];
	glm::vec4 AnimationKonstColors[4];

	const GXShape* GetShape() const { return mShape; }
	void SetShape(const GXShape* shape) { mShape = shape; }

	int32_t GetShaderProgram() const { return mShaderProgram; }
	bool GenerateShaders();

	void Render(std::vector<std::shared_ptr<struct J3DTexture>>& textures);
};
