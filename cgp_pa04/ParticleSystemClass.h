#pragma once

//#define _WIN32_WINNT 0x0600				// <== CreateFile2  KERNEL32.dll error 해결

//#include "targetver.h"

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>



// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

using namespace std;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//#include "DxDefine.h"

class TextureClass;

class ParticleSystemClass
{
private:
	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocity;
		bool active;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 color;
	};

public:
	ParticleSystemClass();
	ParticleSystemClass(const ParticleSystemClass&);
	~ParticleSystemClass();

	bool Initialize(ID3D11Device*, const WCHAR*);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	float m_particleDeviationX = 0;
	float m_particleDeviationY = 0;
	float m_particleDeviationZ = 0;
	float m_particleVelocity = 0;
	float m_particleVelocityVariation = 0;
	float m_particleSize = 0;
	float m_particlesPerSecond = 0;
	int m_maxParticles = 0;

	int m_currentParticleCount = 0;
	float m_accumulatedTime = 0;

	TextureClass* m_Texture = nullptr;
	ParticleType* m_particleList = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	VertexType* m_vertices = nullptr;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};