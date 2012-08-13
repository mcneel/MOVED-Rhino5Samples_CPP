/////////////////////////////////////////////////////////////////////////////
// SampleBrepCommandsPlugIn.h : main header file for the SampleBrepCommands plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSampleBrepCommandsPlugIn
// See SampleBrepCommandsPlugIn.cpp for the implementation of this class
//

class CSampleBrepCommandsPlugIn : public CRhinoUtilityPlugIn
{
public:
  CSampleBrepCommandsPlugIn();
  ~CSampleBrepCommandsPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

CSampleBrepCommandsPlugIn& SampleBrepCommandsPlugIn();



