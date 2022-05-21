#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include "GUI.h"
#include "Text.h"

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;

	Camara *camara;
	TerrenoRR *terreno;
	SkyDome *skydome;

	BillboardRR* arbusto;
	BillboardRR* arbol3;
	BillboardRR* arbol8;
	
	ModeloRR* botella;
	ModeloRR* kit;
	ModeloRR* tanque;
	ModeloRR* jeep;
	ModeloRR* elefante;
	ModeloRR* tent;
	ModeloRR* campaña;
	ModeloRR* rhino;
	ModeloRR* serpiente;
	ModeloRR* linterna;
	ModeloRR* llanta;
	ModeloRR* hipo;
	ModeloRR* leon;
	ModeloRR* coco;

	ModeloRR* agua;

	GUI* fullvida;
	GUI* halfvida;
	GUI* lastvida;
	GUI* gameover;
	Text* text;
	
	float izqder;
	float arriaba;
	float vel;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	float rotCam;
	bool interactua = 0;
	int tipoCam;
	float segundos;
	int hora;

	bool vehiculo = 0;
	bool llantaB = 0;
	bool linternaB = 0;
	bool kitB = 0;
	bool tanqueB = 0;
	bool botellaB = 0;

	bool win = 0;

	float vida = 4;

	
	DXRR(HWND hWnd, int Ancho, int Alto)
	{
		rotCam = 0;
		tipoCam = 1;
		segundos = 301;

		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		camara = new Camara(D3DXVECTOR3(0, 80, 6), D3DXVECTOR3(0, 80, 0), D3DXVECTOR3(0, 1, 0), Ancho, Alto);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext, L"Assets/Terreno/alturas3.jpg", L"Assets/Terreno/Grass.jpg", L"Assets/Terreno/Grass.jpg"/*normal*/, L"Assets/Terreno/Dirth.jpg", L"Assets/Terreno/Dirth.jpg"/*normal*/, L"Assets/Terreno/GrassDead.jpg", L"Assets/Terreno/GrassDead.jpg"/*normal*/, L"Assets/Terreno/alturas3.png");
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"Assets/SkyDome/dia.png");

		//----------------------------BILLBOARDS--------------------------------
		arbusto = new BillboardRR(L"Assets/Billboards/arbusto.png", L"Assets/Billboards/arbustoN.png", d3dDevice, d3dContext, 5);
		arbol3 = new BillboardRR(L"Assets/Billboards/arbol3.png", L"Assets/Billboards/arbol3N.png", d3dDevice, d3dContext, 5);
		arbol8 = new BillboardRR(L"Assets/Billboards/arbol8.png", L"Assets/noSpecMap.jpg", d3dDevice, d3dContext, 5);


		//------------------------------MODELS-------------------------------
		botella = new ModeloRR(d3dDevice, d3dContext, "Assets/Botella/botella.obj", L"Assets/Botella/botella.png", L"Assets/Botella/botella.png", L"Assets/Botella/botella.png", -107, 9);
		kit = new ModeloRR(d3dDevice, d3dContext, "Assets/Kit/kit.obj", L"Assets/Kit/kit.png", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", -107, -106);
		tanque = new ModeloRR(d3dDevice, d3dContext, "Assets/Tanque/tanque.obj", L"Assets/Tanque/tanque.jpg", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", 91, -22);
		jeep = new ModeloRR(d3dDevice, d3dContext, "Assets/Jeep/jeep.obj", L"Assets/Jeep/jeep3.jpg", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", -30, -22);
		elefante = new ModeloRR(d3dDevice, d3dContext, "Assets/Elefante/elefante.obj", L"Assets/Elefante/elefante.jpg", L"Assets/Elefante/elefanteN.jpg", L"Assets/noSpecMap.jpg", 44, 77);
		tent = new ModeloRR(d3dDevice, d3dContext, "Assets/Tent/Tent.obj", L"Assets/Tent/campaña.png", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", -103, -108);
		campaña = new ModeloRR(d3dDevice, d3dContext, "Assets/Campaña/Campaña.obj", L"Assets/Campaña/campaña.png", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", -56, 110);
		rhino = new ModeloRR(d3dDevice, d3dContext, "Assets/Rhino/Rhino.obj", L"Assets/Rhino/Rhino.jpg", L"Assets/Rhino/RhinoN.jpg", L"Assets/noSpecMap.jpg", 96, -112);
		serpiente = new ModeloRR(d3dDevice, d3dContext, "Assets/Serpiente/Serpiente.obj", L"Assets/Serpiente/Serpiente.jpg", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", -98, 7);
		linterna = new ModeloRR(d3dDevice, d3dContext, "Assets/Linterna/Linterna.obj", L"Assets/Linterna/Linterna.png", L"Assets/noSpecMap.jpg", L"Assets/noSpecMap.jpg", 111, -107);
		llanta = new ModeloRR(d3dDevice, d3dContext, "Assets/Llanta/Llanta.obj", L"Assets/Llanta/Llanta.png", L"Assets/Llanta/LlantaN.png", L"Assets/noSpecMap.jpg", -52, 110);
		hipo = new ModeloRR(d3dDevice, d3dContext, "Assets/Hipo/hipo.obj", L"Assets/Hipo/hipo.jpg", L"Assets/Hipo/hipoN.jpg", L"Assets/noSpecMap.jpg", 47, -57);
		leon = new ModeloRR(d3dDevice, d3dContext, "Assets/Leon/leon.obj", L"Assets/Leon/leon.jpg", L"Assets/Leon/leonN.jpg", L"Assets/noSpecMap.jpg", 65, 32);
		coco = new ModeloRR(d3dDevice, d3dContext, "Assets/Cocodrilo/cocodrilo.obj", L"Assets/Cocodrilo/cocodrilo.jpg", L"Assets/Cocodrilo/cocodriloN.jpg", L"Assets/noSpecMap.jpg", -56, -85);

		agua = new ModeloRR(d3dDevice, d3dContext, "Assets/Agua/agua.obj", L"Assets/Agua/agua.jpg", L"Assets/Agua/aguaN.jpg", L"Assets/noSpecMap.jpg", 100, -110);

		//--------------------------------GUI--------------------------------
		fullvida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/health_full.png");
		halfvida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/health_2.png");
		lastvida = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/health_1.png");
		gameover = new GUI(d3dDevice, d3dContext, 1.0, 1.0, L"Assets/GUI/gameover.png");	
		text = new Text(d3dDevice, d3dContext, 4.6, 2.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.39f, 0.79f, 0.18f, 1.0f));

	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{
		if (breakpoint) {
			bool x = false;
			camara->posCam;
		}

		skydome->hora;

		rotCam += izqder;

		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if( d3dContext == 0 )
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
		
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 4.5 ;
		camara->posCam3P.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 7;

		camara->UpdateCam(vel, arriaba, izqder, tipoCam);

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);

		arbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
			35, 76, 3, 4, uv1, uv2, uv3, uv4, frameBillboard, false);

		arbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
			42, -56, 1.5, 2, uv1, uv2, uv3, uv4, frameBillboard, false);

		arbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
			96, -105, 3, 2, uv1, uv2, uv3, uv4, frameBillboard, false);

		arbusto->Draw(camara->vista, camara->proyeccion, camara->posCam,
			35, 76, 5, 4, uv1, uv2, uv3, uv4, frameBillboard, false);

		arbol3->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-14, 6, 4.5, 20, uv1, uv2, uv3, uv4, frameBillboard, false);

		arbol8->Draw(camara->vista, camara->proyeccion, camara->posCam,
			85, -24, 6, 15, uv1, uv2, uv3, uv4, frameBillboard, false);

		//TurnOffAlphaBlending();
		elefante->Draw(camara->vista, camara->proyeccion, terreno->Superficie(elefante->getPosX(), elefante->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);
		tent->Draw(camara->vista, camara->proyeccion, terreno->Superficie(tent->getPosX(), tent->getPosZ()), camara->posCam, 10.0f, XM_PI, 'Y', 1, false, tipoCam);
		campaña->Draw(camara->vista, camara->proyeccion, terreno->Superficie(campaña->getPosX(), campaña->getPosZ()), camara->posCam, 10.0f, 3 * XM_PI, 'Y', 1, false, tipoCam);
		rhino->Draw(camara->vista, camara->proyeccion, terreno->Superficie(rhino->getPosX(), rhino->getPosZ()), camara->posCam, 10.0f, XM_PIDIV2, 'Y', 1, false, tipoCam);
		serpiente->Draw(camara->vista, camara->proyeccion, terreno->Superficie(serpiente->getPosX(), serpiente->getPosZ()), camara->posCam, 10.0f, XM_PIDIV2, 'Y', 1, false, tipoCam);
		hipo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(hipo->getPosX(), hipo->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);
		leon->Draw(camara->vista, camara->proyeccion, terreno->Superficie(leon->getPosX(), leon->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);
		coco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(coco->getPosX(), coco->getPosZ()), camara->posCam, 10.0f, XM_PI, 'Y', 1, false, tipoCam);

		//agua->Draw(camara->vista, camara->proyeccion, 0, camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

		//-----------------------Colisiones---------------------

		if (!vehiculo) {
			jeep->Draw(camara->vista, camara->proyeccion, terreno->Superficie(jeep->getPosX(), jeep->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

			if (isPointInsideSphere(camara->getPos(), jeep->getSphere(5))) {
				camara->posCam = camara->pastPosCam;
				if (interactua && llantaB && tanqueB) {
					vehiculo = 1;
				}
			}
		}
		else {

			jeep->setPosX(camara->hdveo.x);
			jeep->setPosZ(camara->hdveo.z);
			jeep->Draw(camara->vista, camara->proyeccion,
				terreno->Superficie(jeep->getPosX(), jeep->getPosZ()) + 2.5,
				camara->posCam, 10.0f, rotCam + XM_PI, 'Y', 1, true, tipoCam);

		}

		if (!llantaB) {
			llanta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(llanta->getPosX(), llanta->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);
			
			if (isPointInsideSphere(camara->getPos(), llanta->getSphere(2))) {
				camara->posCam = camara->pastPosCam;
				if (interactua) {
					llantaB = 1;
				}
			}
		}

		if (!linternaB) {
			linterna->Draw(camara->vista, camara->proyeccion, terreno->Superficie(linterna->getPosX(), linterna->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

			if (isPointInsideSphere(camara->getPos(), linterna->getSphere(2))) {
				camara->posCam = camara->pastPosCam;
				if (interactua) {
					linternaB = 1;
				}
			}
		}

		if (!botellaB) {
			botella->Draw(camara->vista, camara->proyeccion, terreno->Superficie(botella->getPosX(), botella->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

			if (isPointInsideSphere(camara->getPos(), botella->getSphere(2))) {
				camara->posCam = camara->pastPosCam;
				if (interactua) {
					botellaB = 1;
				}
			}
		}

		if (!tanqueB) {
			tanque->Draw(camara->vista, camara->proyeccion, terreno->Superficie(tanque->getPosX(), tanque->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

			if (isPointInsideSphere(camara->getPos(), tanque->getSphere(2))) {
				camara->posCam = camara->pastPosCam;
				if (interactua) {
					tanqueB = 1;
				}
			}
		}

		if (!kitB) {
			kit->Draw(camara->vista, camara->proyeccion, terreno->Superficie(kit->getPosX(), kit->getPosZ()), camara->posCam, 10.0f, 0, 'A', 1, false, tipoCam);

			if (isPointInsideSphere(camara->getPos(), kit->getSphere(2))) {
				camara->posCam = camara->pastPosCam;
				if (interactua) {
					kitB = 1;
				}
			}
		}

		if (isPointInsideSphere(camara->getPos(), elefante->getSphere(6))) {
			camara->posCam = camara->pastPosCam;
			vida -= 0.03;
		}

		if (isPointInsideSphere(camara->getPos(), rhino->getSphere(5))) {
			camara->posCam = camara->pastPosCam;
			vida -= 0.03;
		}

		if (isPointInsideSphere(camara->getPos(), hipo->getSphere(5))) {
			camara->posCam = camara->pastPosCam;
			vida -= 0.03;
		}

		if (isPointInsideSphere(camara->getPos(), coco->getSphere(6))) {
			camara->posCam = camara->pastPosCam;
			vida -= 0.03;
		}

		if (isPointInsideSphere(camara->getPos(), serpiente->getSphere(3))) {
			camara->posCam = camara->pastPosCam;
			vida -= 0.03;
		}

		//---------------------------GUI------------------------

		if (vida > 3) {
			fullvida->Draw(-.8, .8);
		} 
		if (vida < 3 && vida >= 2) {
			halfvida->Draw(-.8, .8);
		}
		if (vida < 2) {
			lastvida->Draw(-.8, .8);
		}

		if (segundos < .02 || vida < 1) {
			gameover->Draw(0,0);
		}
		else {
			if(!win)
			segundos -= 0.02;
		}

		text->DrawText(0.4, 0.85, "Anochecer: " + text->Time(segundos), 0.015);

		if (llantaB && tanqueB && kitB && botellaB && linternaB) {
			win = true;
			text->DrawText(-0.95, -0.80, "Recuperaste todo lo necesario", 0.015);
		}
		else {

			text->DrawText(-0.95, -0.30, "Cosas a recuperar:", 0.015);
			if (!llantaB)
				text->DrawText(-0.95, -0.40, "Llanta", 0.015);
			if (!tanqueB)
				text->DrawText(-0.95, -0.50, "Gasolina", 0.015);
			if (!kitB)
				text->DrawText(-0.95, -0.60, "Botiquin", 0.015);
			if (!botellaB)
				text->DrawText(-0.95, -0.70, "Agua", 0.015);
			if (!linternaB)
				text->DrawText(-0.95, -0.80, "Linterna", 0.015);
		}

		text->DrawText(-0.20, -0.80, "PosX:" + text->Pos(camara->posCam.x) + " PosZ:" + text->Pos(camara->posCam.z), 0.015);

		//Globales
		interactua = 0;
		breakpoint = false;

		swapChain->Present( 1, 0 );		
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2]) {
			collition = true;
		}

		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif