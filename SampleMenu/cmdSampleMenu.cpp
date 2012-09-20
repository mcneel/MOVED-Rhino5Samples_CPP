/////////////////////////////////////////////////////////////////////////////
// cmdSampleMenu.cpp : command file
//

#include "StdAfx.h"
#include "SampleMenuPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SampleMenuCommand1 command
//

class CCommandSampleMenuCommand1 : public CRhinoCommand
{
public:
	CCommandSampleMenuCommand1() {}
	~CCommandSampleMenuCommand1() {}
	UUID CommandUUID()
	{
		// {281EE457-82E8-4053-ADDF-685878B87DC5}
		static const GUID SampleMenuCommand1Command_UUID =
		{ 0x281EE457, 0x82E8, 0x4053, { 0xAD, 0xDF, 0x68, 0x58, 0x78, 0xB8, 0x7D, 0xC5 } };
		return SampleMenuCommand1Command_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"SampleMenuCommand1"; }
	const wchar_t* LocalCommandName() { return L"SampleMenuCommand1"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandSampleMenuCommand1 object
static class CCommandSampleMenuCommand1 theSampleMenuCommand1Command;

CRhinoCommand::result CCommandSampleMenuCommand1::RunCommand( const CRhinoCommandContext& context )
{
	ON_wString wStr;
	wStr.Format( L"The \"%s\" command is under construction.\n", EnglishCommandName() );
	if( context.IsInteractive() )
		RhinoMessageBox( wStr, EnglishCommandName(), MB_OK );
	else
		RhinoApp().Print( wStr );
	return CRhinoCommand::success;
}

//
// END SampleMenuCommand1 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SampleMenuCommand2 command
//

class CCommandSampleMenuCommand2 : public CRhinoCommand
{
public:
	CCommandSampleMenuCommand2() {}
	~CCommandSampleMenuCommand2() {}
	UUID CommandUUID()
	{
		// {B96253EF-B140-495E-B127-2D8DA7AECE10}
		static const GUID SampleMenuCommand2Command_UUID =
		{ 0xB96253EF, 0xB140, 0x495E, { 0xB1, 0x27, 0x2D, 0x8D, 0xA7, 0xAE, 0xCE, 0x10 } };
		return SampleMenuCommand2Command_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"SampleMenuCommand2"; }
	const wchar_t* LocalCommandName() { return L"SampleMenuCommand2"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandSampleMenuCommand2 object
static class CCommandSampleMenuCommand2 theSampleMenuCommand2Command;

CRhinoCommand::result CCommandSampleMenuCommand2::RunCommand( const CRhinoCommandContext& context )
{
	ON_wString wStr;
	wStr.Format( L"The \"%s\" command is under construction.\n", EnglishCommandName() );
	if( context.IsInteractive() )
		RhinoMessageBox( wStr, EnglishCommandName(), MB_OK );
	else
		RhinoApp().Print( wStr );
	return CRhinoCommand::success;
}

//
// END SampleMenuCommand2 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

