////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"

#include "SkyClass.h"
#include "SkyShader.h"
#include "inputclass.h"
#include "ParticleShaderClass.h"
#include "ParticleSystemClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HINSTANCE, HWND);
	void Shutdown();
	bool Frame();
	bool Frame(int, int, int, int, int, int);

	CameraClass* getCamera();
	int mousex, mousey;
	bool is_overlap;
	bool is_space;
private:
	bool Render(float, float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_Model2;
	ModelClass* m_plane;
	ModelClass* m_city;
	ModelClass* m_meca;
	ModelClass* m_ship;
	ModelClass* m_bomb;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;

	SkyClass* m_Sky;
	SkyShaderClass* m_SkyShader;

	InputClass* m_input;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
};

#endif