#pragma once

#define USE_D2D 1

#include "QDxWidget.h"

class QD2DWidget : public QDxWidget
{
public:
	QD2DWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0) : QDxWidget(parent, flags), m_pD2DFactory(0)
	{
		initialize();
	}

	virtual ~QD2DWidget()
	{
		uninitialize();
	}


	//-----------------------------------------------------------------------------
	// Name: invalidateDeviceObjects()
	// Desc: If the lost device can be restored, the application prepares the 
	//       device by destroying all video-memory resources and any 
	//       swap chains. This is typically accomplished by using the SAFE_RELEASE 
	//       macro.
	//-----------------------------------------------------------------------------
	HRESULT	invalidateDeviceObjects()
	{
		if (!m_pD2DFactory || !m_pDWriteFactory) return E_FAIL;

		SAFE_RELEASE(m_pBlackBrush);
		SAFE_RELEASE(m_pTextFormat);

		return S_OK;
	}

	//-----------------------------------------------------------------------------
	// Name: initialize()
	// Desc: This function will only be called once during the application's 
	//       initialization phase. Therefore, it can't contain any resources that 
	//       need to be restored every time the Direct3D device is lost or the 
	//       window is resized.
	//-----------------------------------------------------------------------------
	HRESULT	initialize()
	{
		HRESULT hr = S_OK;

		m_pD2DFactory = 0;
		m_pWICFactory = 0;
		m_pDWriteFactory = 0;
		m_pHwndRenderTarget = 0;

		// Create D2D factory
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (SUCCEEDED(hr))
		{
			// Create a WIC factory
			hr = CoCreateInstance(
				CLSID_WICImagingFactory,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_IWICImagingFactory,
				reinterpret_cast<void **>(&m_pWICFactory)
				);
		}
		if (SUCCEEDED(hr))
		{
			// Create DWrite factory
			hr = DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(m_pDWriteFactory),
				reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
				);
		}

		if (SUCCEEDED(hr))
		{
			D2D1_SIZE_U size = D2D1::SizeU(width(), height());

			// Create a Direct2D render target.
			hr = m_pD2DFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties((HWND)this->winId(), size),
				&m_pHwndRenderTarget
				);
		}

		if (SUCCEEDED(hr))
		{
			hr = restoreDeviceObjects();
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// Name: uninitialize()
	// Desc: Releases all previously initialized objects
	//-----------------------------------------------------------------------------
	void	uninitialize()
	{
		invalidateDeviceObjects();

		SAFE_RELEASE(m_pHwndRenderTarget);
		SAFE_RELEASE(m_pD2DFactory);
		SAFE_RELEASE(m_pWICFactory);
		SAFE_RELEASE(m_pDWriteFactory);
	}

	//-----------------------------------------------------------------------------
	// Name: restoreDeviceObjects()
	// Desc: You are encouraged to develop applications with a single code path to 
	//       respond to device loss. This code path is likely to be similar, if not 
	//       identical, to the code path taken to initialize the device at startup.
	//-----------------------------------------------------------------------------
	HRESULT	restoreDeviceObjects()
	{
		if (!m_pD2DFactory || !m_pDWriteFactory) return E_FAIL;

		static const WCHAR msc_fontName[] = L"Verdana";
		static const FLOAT msc_fontSize = 50;
		HRESULT hr;

		// Create a DirectWrite text format object.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
			);

		if (SUCCEEDED(hr))
		{
			// Center the text horizontally and vertically.
			m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

			m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}

		// Create a black brush.
		hr = m_pHwndRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pBlackBrush
			);

		return S_OK;
	}

private:
	ID2D1Factory*			m_pD2DFactory;

	IWICImagingFactory*		m_pWICFactory;

	IDWriteFactory*			m_pDWriteFactory;

	ID2D1HwndRenderTarget*	m_pHwndRenderTarget;

	ID2D1SolidColorBrush*	m_pBlackBrush;

	IDWriteTextFormat*		m_pTextFormat;
};