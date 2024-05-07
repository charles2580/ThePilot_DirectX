////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_city = 0;
	m_meca = 0;
	m_ship = 0;

	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

	m_Text = 0;
	m_input = 0;

	mousex = 0;
	mousey = 0;
	m_plane = 0;

	m_bomb = 0;
	is_space = true;

	is_overlap = false;

	m_ParticleShader = 0;
	m_ParticleSystem = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HINSTANCE m_hinstance, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_input = new InputClass;
	if (!m_input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_input->Initialize(m_hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair
		
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/aircraft.obj", L"./data/aircraft.dds");

	m_meca = new ModelClass;
	if (!m_meca)
	{
		return false;
	}

	// Initialize the model object.
	result = m_meca->Initialize(m_D3D->GetDevice(), L"./data/meca.obj", L"./data/ship.dds");

	m_ship = new ModelClass;
	if (!m_ship)
	{
		return false;
	}

	// Initialize the model object.
	result = m_ship->Initialize4(m_D3D->GetDevice(), L"./data/ship.obj", L"./data/ship.dds");

	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model2->Initialize2(m_D3D->GetDevice(), L"./data/ship.obj", L"./data/ship.dds");
//	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_city = new ModelClass;
	if (!m_city)
	{
		return false;
	}

	result = m_city->Initialize(m_D3D->GetDevice(), L"./data/plan.obj", L"./data/water.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_plane = new ModelClass;
	if (!m_plane)
	{
		return false;
	}
	result = m_plane->Initialize3(m_D3D->GetDevice(), L"./data/aircraft.obj", L"./data/aircraft.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_bomb = new ModelClass;
	if (!m_bomb)
	{
		return false;
	}
	result = m_bomb->Initialize3(m_D3D->GetDevice(), L"./data/bomb.obj", L"./data/aircraft.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"./data/star.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
//	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/title.dds", 1280, 720);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// 스카이 돔 객체를 생성합니다.
	m_Sky = new SkyClass;
	if (!m_Sky)
	{
		return false;
	}

	// 스카이 돔 객체를 초기화 합니다.
	result = m_Sky->Initialize(m_D3D->GetDevice(),L"./data/sphere.obj", L"./data/sky.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// 스카이 돔 쉐이더 객체를 생성합니다.
	m_SkyShader = new SkyShaderClass;
	if (!m_SkyShader)
	{
		return false;
	}

	// 스카이 돔 쉐이더 객체를 초기화 합니다.
	result = m_SkyShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	if (m_SkyShader)
	{
		m_SkyShader->Shutdown();
		delete m_SkyShader;
		m_SkyShader = 0;
	}

	if (m_Sky)
	{
		m_Sky->Shutdown();
		delete m_Sky;
		m_Sky = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if (m_city)
	{
		m_city->Shutdown();
		delete m_city;
		m_city = 0;
	}

	if (m_ship)
	{
		m_ship->Shutdown();
		delete m_ship;
		m_ship = 0;
	}

	if (m_plane)
	{
		m_plane->Shutdown();
		delete m_plane;
		m_plane = 0;
	}

	if (m_bomb)
	{
		m_bomb->Shutdown();
		delete m_bomb;
		m_bomb = 0;
	}

	if (m_meca)
	{
		m_meca->Shutdown();
		delete m_meca;
		m_meca = 0;
	}

	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;
	static float move_z;

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation, move_z);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, int mouseX, int mouseY, int screenWidth, int screenHeight)
{
	bool result;
	static float rotation = 0.0f;
	static float move_z = 0.0f;

	move_z += 0.1f;
	if (move_z > 200.0f)
	{
		is_overlap = false;
		move_z = 0.0f;
	}

	m_ParticleSystem->Frame(move_z, m_D3D->GetDeviceContext());

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreenSize(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}


	// Render the graphics scene.
	result = Render(rotation, move_z);
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.
//	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_input->GetMouseLocation(mousex, mousey);

	return true;
}

bool GraphicsClass::Render(float rotation, float move_z)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	XMVECTOR objPosition;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	XMFLOAT3 cameraPosition = m_Camera->GetPosition();
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	m_D3D->TurnOffCulling();

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	m_Sky->Render(m_D3D->GetDeviceContext());

	m_SkyShader->Render(m_D3D->GetDeviceContext(), m_Sky->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Sky->GetTexture());

	m_D3D->TurnOnCulling();

	m_D3D->TurnZBufferOn();

	m_D3D->GetWorldMatrix(worldMatrix);

	if (is_space)
	{
		XMMATRIX title = XMMatrixTranslation(0, 0, 0.1f);
		//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}

		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, title, orthoMatrix, m_Bitmap->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	int NumPoly = m_city->m_faceCount + m_meca->m_faceCount + m_Model->m_faceCount + m_ship->m_faceCount +
		m_Model2->m_faceCount + m_plane->m_faceCount + m_Sky->m_faceCount;
	result = m_Text->SetNumPolygon(NumPoly, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	XMMATRIX rotationMatrix;
	m_Camera->GetRotaionMatrix(rotationMatrix);

	objPosition = XMVectorSet(0, -3.0f, 7.0f, 0);
	XMVECTOR campos = XMVectorSet(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0);

	XMVECTOR obj = XMVector3TransformCoord(objPosition, rotationMatrix);
	obj = XMVectorAdd(obj, campos);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	worldMatrix = XMMatrixTranslationFromVector(obj);
	XMMATRIX objMatrix = XMMatrixMultiply(rotationMatrix, worldMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), 1,
		objMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), 
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	m_Model2->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixTranslation(0.0f, 0.0f, move_z);
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), 100,
		worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	m_city->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixTranslation(0, -200.0f, 0);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_city->GetIndexCount(), 1,
		worldMatrix, viewMatrix, projectionMatrix,
		m_city->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	if (!result)
	{
		return false;
	}

	m_plane->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixTranslation(0.0f, 0.0f, move_z*10);
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_plane->GetIndexCount(), 100,
		worldMatrix, viewMatrix, projectionMatrix,
		m_plane->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	m_bomb->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);
	XMVECTOR bombPos = XMVectorSet(-10.0f, -100.0f, move_z * 8.0f, 0.0f);
	worldMatrix =  XMMatrixTranslation(-10.0f, -80.0f, move_z*8.0f);
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_bomb->GetIndexCount(), 1,
		worldMatrix, viewMatrix, projectionMatrix,
		m_bomb->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}


	m_meca->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);
	XMVECTOR modelPosition = XMVectorSet(0.0f, -250.0f, 750.0f, 0.0f);

	XMVECTOR toCam = XMVector3Normalize(XMVectorSubtract(campos, modelPosition));

	// Compute the new rotation of m_meca to face the camera
	float mecaYaw = atan2f(XMVectorGetX(toCam), XMVectorGetZ(toCam));

	// Create the rotation matrix for the model.
	XMMATRIX rot = XMMatrixRotationY(mecaYaw);

	// Multiply the model's rotation matrix by the rotation matrix.
	worldMatrix = XMMatrixMultiply(rot, XMMatrixTranslationFromVector(modelPosition));


	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_meca->GetIndexCount(), 1,
		worldMatrix, viewMatrix, projectionMatrix,
		m_meca->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());



	if (!result)
	{
		return false;
	}

	if (is_overlap)
	{
		m_D3D->TurnOnAlphaBlending();

		m_ParticleSystem->Render(m_D3D->GetDeviceContext());

		m_D3D->GetWorldMatrix(worldMatrix);
		worldMatrix = XMMatrixScaling(50.0f,50.0f,50.0f) * XMMatrixTranslation(0.0f, 100.0f, 800.0f);

		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());

		if (!result)
		{
			return false;
		}

		m_D3D->TurnOffAlphaBlending();
	}
	m_ship->Render(m_D3D->GetDeviceContext());

	m_D3D->GetWorldMatrix(worldMatrix);

	XMVECTOR rotationCenter = XMVectorSet(0.0f, 0.0f, 500.0f, 0.0f);
	XMVECTOR modelPos = XMVectorSet(0.0f, 0.0f, 500.0f, 0.0f);
	XMVECTOR relativePosition = XMVectorSubtract(modelPos, rotationCenter);
	XMMATRIX translationToCenter = XMMatrixTranslationFromVector(XMVectorNegate(rotationCenter));
	XMMATRIX rMatrix = XMMatrixRotationY(rotation);
	XMMATRIX translationBack = XMMatrixTranslationFromVector(rotationCenter);
	XMMATRIX scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
	worldMatrix = XMMatrixMultiply(scale,XMMatrixMultiply(XMMatrixMultiply(translationToCenter, rMatrix), translationBack));

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_ship->GetIndexCount(), 10,
		worldMatrix, viewMatrix, projectionMatrix,
		m_ship->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	if (XMVectorGetX(XMVector3Length(modelPosition - bombPos)) < 250.0f)
	{
		is_overlap = true;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

CameraClass* GraphicsClass::getCamera()
{
	return m_Camera;
}