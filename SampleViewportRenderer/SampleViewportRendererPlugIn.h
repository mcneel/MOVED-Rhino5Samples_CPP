/////////////////////////////////////////////////////////////////////////////
// SampleViewportRendererPlugIn.h
//

#pragma once

class CSampleRenderer;

class CSampleViewportRendererPlugIn : public CRhinoUtilityPlugIn
{
public:
  CSampleViewportRendererPlugIn();
  ~CSampleViewportRendererPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

	// Online help overrides
	BOOL AddToPlugInHelpMenu() const;
	BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

	// Load time override
	CRhinoPlugIn::plugin_load_time PlugInLoadTime();

	// Rendered image access
	CRhinoUiDib* LockRenderImage();
	void UnlockRenderImage( CRhinoUiDib* pRenderImage );

	// Viewport updating
	void RequestRedraw();
	void AcknowledgeRedraw();
	void OnRedrawTimer();

private:
	ON_wString m_plugin_version;

	// Critical section for rendered image access
	CCriticalSection m_cs;

	// Dib to contain the rendered image
	CRhinoUiDib m_renderImageDib;

	// Renderer
	CSampleRenderer* m_pRenderer;

	// Viewport update request flag
	bool m_bRedrawRequested;

	// Viewport update timer id
	UINT_PTR m_uTimerProcId;

	// Viewport update timer event
  static UINT s_uTimerProcEvent;

	// Viewport update timer callback
  static void CALLBACK RedrawTimerProc( HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime );
};

CSampleViewportRendererPlugIn& SampleViewportRendererPlugIn();



