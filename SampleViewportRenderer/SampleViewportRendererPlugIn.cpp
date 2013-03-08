/////////////////////////////////////////////////////////////////////////////
// SampleViewportRendererPlugIn.cpp
//

#include "StdAfx.h"
#include "SampleViewportRendererPlugIn.h"
#include "SampleRenderer.h"
#include "SampleDisplayPipeline.h"

// The plug-in object must be constructed before any plug-in classes
// derived from CRhinoCommand. The #pragma init_seg(lib) ensures that
// this happens.

#pragma warning( push )
#pragma warning( disable : 4073 )
#pragma init_seg( lib )
#pragma warning( pop )

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
// Provide a short, friendly name for this plug-in.
RHINO_PLUG_IN_NAME( L"SampleViewportRenderer" );

// Rhino plug-in id
// Provide a unique uuid for this plug-in
RHINO_PLUG_IN_ID( L"76090CBE-DB04-44DF-B859-94E20B483ED7" );

// Rhino plug-in version
// Provide a version number string for this plug-in
RHINO_PLUG_IN_VERSION( __DATE__"  "__TIME__ )

// Rhino plug-in developer declarations
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION( L"Robert McNeel & Associates" );
RHINO_PLUG_IN_DEVELOPER_ADDRESS( L"3670 Woodland Park Avenue North\015\012Seattle WA 98103" );
RHINO_PLUG_IN_DEVELOPER_COUNTRY( L"United States" );
RHINO_PLUG_IN_DEVELOPER_PHONE( L"206-545-6877" );
RHINO_PLUG_IN_DEVELOPER_FAX( L"206-545-7321" );
RHINO_PLUG_IN_DEVELOPER_EMAIL( L"tech@mcneel.com" );
RHINO_PLUG_IN_DEVELOPER_WEBSITE( L"http://www.rhino3d.com" );
RHINO_PLUG_IN_UPDATE_URL( L"https://github.com/mcneel/" );

// The one and only CSampleViewportRendererPlugIn object
static CSampleViewportRendererPlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// CSampleViewportRendererPlugIn definition

CSampleViewportRendererPlugIn& SampleViewportRendererPlugIn()
{ 
  // Return a reference to the one and only CSampleViewportRendererPlugIn object
  return thePlugIn; 
}

CSampleViewportRendererPlugIn::CSampleViewportRendererPlugIn()
  : m_pRenderer(0)
{
  // Description:
  //   CSampleViewportRendererPlugIn constructor. The constructor is called when the
  //   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
  //   is loaded, CSampleViewportRendererPlugIn::OnLoadPlugIn() is called. The 
  //   constructor should be simple and solid. Do anything that might fail in
  //   CSampleViewportRendererPlugIn::OnLoadPlugIn().

  // TODO: Add construction code here

  m_plugin_version = RhinoPlugInVersion();

	// Reset everything to idle state
	m_bRedrawRequested = false;
	m_uTimerProcId = 0;

	// Create a dib to render to.
	// We want to copy this image into Rhino's viewport DC
	// and therefore we need to set select_into_mem_dc to true.
	m_renderImageDib.CreateDib( 100, 100, 24, true );
	m_renderImageDib.Clear( RGB(0, 0, 0) );

}

CSampleViewportRendererPlugIn::~CSampleViewportRendererPlugIn()
{
  // Description:
  //   CSampleViewportRendererPlugIn destructor. The destructor is called to destroy
  //   "thePlugIn" when the plug-in is unloaded. Immediately before the
  //   DLL is unloaded, CSampleViewportRendererPlugIn::OnUnloadPlugin() is called. Do
  //   not do too much here. Be sure to clean up any memory you have allocated
  //   with onmalloc(), onrealloc(), oncalloc(), or onstrdup().

  // TODO: Add destruction code here
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* CSampleViewportRendererPlugIn::PlugInName() const
{
  // Description:
  //   Plug-in name display string.  This name is displayed by Rhino when
  //   loading the plug-in, in the plug-in help menu, and in the Rhino 
  //   interface for managing plug-ins.

  // TODO: Return a short, friendly name for the plug-in.
  return RhinoPlugInName();
}

const wchar_t* CSampleViewportRendererPlugIn::PlugInVersion() const
{
  // Description:
  //   Plug-in version display string. This name is displayed by Rhino 
  //   when loading the plug-in and in the Rhino interface for managing
  //   plug-ins.

  // TODO: Return the version number of the plug-in.
  return m_plugin_version;
}

GUID CSampleViewportRendererPlugIn::PlugInID() const
{
  // Description:
  //   Plug-in unique identifier. The identifier is used by Rhino to
  //   manage the plug-ins.

  // TODO: Return a unique identifier for the plug-in.
  // {76090CBE-DB04-44DF-B859-94E20B483ED7}
  return ON_UuidFromString( RhinoPlugInId() );
}

BOOL CSampleViewportRendererPlugIn::OnLoadPlugIn()
{
  // Description:
  //   Called after the plug-in is loaded and the constructor has been
  //   run. This is a good place to perform any significant initialization,
  //   license checking, and so on.  This function must return TRUE for
  //   the plug-in to continue to load.

  // TODO: Add plug-in initialization code here.

	// Guid for our custom display mode
  // {9913CEEE-8E5C-4F69-909D-79B73F54EAFE}
	static const GUID SampleViewportRendererDisplayAttrs_UUID = { 0x9913CEEE, 0x8E5C, 0x4F69, { 0x90, 0x9D, 0x79, 0xB7, 0x3F, 0x54, 0xEA, 0xFE } };

	// Look if the display mode is already added...
	DisplayAttrsMgrListDesc* pDisplayAttrsMgrListDesc = CRhinoDisplayAttrsMgr::FindDisplayAttrsDesc( SampleViewportRendererDisplayAttrs_UUID );

	// ... and if it isn't then add it.
	if( 0 == pDisplayAttrsMgrListDesc )
	{
		pDisplayAttrsMgrListDesc = CRhinoDisplayAttrsMgr::AppendNewEntry();
		if( 0 != pDisplayAttrsMgrListDesc && 0 != pDisplayAttrsMgrListDesc->m_pAttrs )
		{
			// Show it in the drop down menu
			pDisplayAttrsMgrListDesc->m_bAddToMenu = true;

			// Set it's guid, name and pipeline class
			pDisplayAttrsMgrListDesc->m_pAttrs->SetUuid( SampleViewportRendererDisplayAttrs_UUID );
			pDisplayAttrsMgrListDesc->m_pAttrs->SetName( PlugInName() );
			pDisplayAttrsMgrListDesc->m_pAttrs->SetPipeline( RUNTIME_CLASS(CSampleDisplayPipeline) );
		}
	}

	// Create and start the renderer
	m_pRenderer = new CSampleRenderer();
	if( 0 != m_pRenderer )
		m_pRenderer->StartRenderProcess();

	// Set timer for the viewport updating
	CWnd* pMainWnd = RhinoApp().GetMainWnd();
	if( 0 != pMainWnd )
		m_uTimerProcId = pMainWnd->SetTimer( CSampleViewportRendererPlugIn::s_uTimerProcEvent, 100, CSampleViewportRendererPlugIn::RedrawTimerProc );

  return CRhinoUtilityPlugIn::OnLoadPlugIn();
}

void CSampleViewportRendererPlugIn::OnUnloadPlugIn()
{
  // Description:
  //   Called when the plug-in is about to be unloaded.  After
  //   this function is called, the destructor will be called.

  // TODO: Add plug-in cleanup code here.

	// Kill the timer
	CWnd* pMainWnd = RhinoApp().GetMainWnd();
	if( 0 != pMainWnd )
		pMainWnd->KillTimer( m_uTimerProcId );

	// Stop renderer and delete it
	if( 0 != m_pRenderer )
  {
		m_pRenderer->StopRenderProcess();

  	delete m_pRenderer;
	  m_pRenderer = 0;
  }

  CRhinoUtilityPlugIn::OnUnloadPlugIn();
}

/////////////////////////////////////////////////////////////////////////////
// Online help overrides

BOOL CSampleViewportRendererPlugIn::AddToPlugInHelpMenu() const
{
	return TRUE;
}

BOOL CSampleViewportRendererPlugIn::OnDisplayPlugInHelp( HWND hWnd ) const
{
	return CRhinoUtilityPlugIn::OnDisplayPlugInHelp( hWnd );
}

/////////////////////////////////////////////////////////////////////////////
// Load time override

CRhinoPlugIn::plugin_load_time CSampleViewportRendererPlugIn::PlugInLoadTime()
{
  // This plugin has to be loaded at startup in order to register the pipeline.
	return CRhinoPlugIn::load_plugin_at_startup;
}


/////////////////////////////////////////////////////////////////////////////
// Rendered image access

CRhinoUiDib* CSampleViewportRendererPlugIn::LockRenderImage()
{
	// Lock to prevent two threads from accessing the render image
  // simultaniously and return pointer to it.
	m_cs.Lock();
	return &m_renderImageDib;
}

void CSampleViewportRendererPlugIn::UnlockRenderImage( CRhinoUiDib* pRenderImage )
{
	// Allow access to render image again.
	m_cs.Unlock();
}

/////////////////////////////////////////////////////////////////////////////
// Viewport updating

void CSampleViewportRendererPlugIn::RequestRedraw()
{
	// Set flag so that the timer proc in main thread knows to update the viewport
	m_bRedrawRequested = true;
}

void CSampleViewportRendererPlugIn::AcknowledgeRedraw()
{
	// Viewport is updated
	m_bRedrawRequested = false;
}

void CSampleViewportRendererPlugIn::OnRedrawTimer()
{
	// This method gets called from the timer procedure.
	// Redraw if the flag is set.
	if( m_bRedrawRequested )
	{
		CRhinoDoc* pDoc = RhinoApp().ActiveDoc();
		if( 0 != pDoc )
			pDoc->DeferredRedraw();
	}
}

UINT CSampleViewportRendererPlugIn::s_uTimerProcEvent = 6060;

void CALLBACK CSampleViewportRendererPlugIn::RedrawTimerProc( HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime )
{
	// Call the OnRedrawTimer of our plugin instance
	SampleViewportRendererPlugIn().OnRedrawTimer();
}
