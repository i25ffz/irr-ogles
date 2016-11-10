// This is a Demo of the Irrlicht Engine (c) 2005-2009 by N.Gebhardt.
// This file is not documented.

#include <irrlicht.h>

#ifdef _IRR_WINDOWS_
#include <windows.h>
#endif

#include <stdio.h>

#ifndef _IRR_ANDROID_PLATFORM_ 
// android don't need CMainMenu class
#include "CMainMenu.h"
#endif // end of _IRR_ANDROID_PLATFORM_
#include "CDemo.h"

using namespace irr;

#ifdef _IRR_ANDROID_PLATFORM_
void android_main(android_app* app)
#elif defined(_MSC_VER)
#pragma comment(lib, "Irrlicht.lib")
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char* argv[])
#endif
{
#ifdef _IRR_ANDROID_PLATFORM_
	bool fullscreen = true;
	bool music = false;
#else
	bool fullscreen = false;
	bool music = true;
#endif
	bool shadows = false;
	bool additive = false;
	bool vsync = false;
	bool aa = false;

#ifdef _IRR_ANDROID_PLATFORM_

	// Make sure glue isn't stripped.
	app_dummy();

	video::E_DRIVER_TYPE driverType = video::EDT_OGLES2;
#elif defined(_IRR_WINDOWS_)
	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;
#else
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;
#endif

#ifndef _IRR_ANDROID_PLATFORM_  // android don't need CMainMenu class
	CMainMenu menu;

//#ifndef _DEBUG
	if (menu.run(fullscreen, music, shadows, additive, vsync, aa, driverType))
//#endif
	{
		CDemo demo(fullscreen, music, shadows, additive, vsync, aa, driverType);
#else
		CDemo demo(fullscreen, music, shadows, additive, vsync, aa, driverType, app);
#endif
		// run the demo!
		demo.run();
#ifndef _IRR_ANDROID_PLATFORM_  // android don't need CMainMenu class
	}

	return 0;
#endif
}

