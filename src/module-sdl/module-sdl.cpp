//==============================================================================
// module-sdl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(sdl)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// sdl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
    }
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
    Assign(VTYPE_SDL_AudioCVT);
    Assign(VTYPE_SDL_AudioSpec);
    Assign(VTYPE_SDL_AudioStream);
    Assign(VTYPE_SDL_Color);
    Assign(VTYPE_SDL_Cursor);
    Assign(VTYPE_SDL_DisplayMode);
    Assign(VTYPE_SDL_Event);
    Assign(VTYPE_SDL_FPoint);
    Assign(VTYPE_SDL_FRect);
    Assign(VTYPE_SDL_GameController);
    Assign(VTYPE_SDL_GLContext);
    Assign(VTYPE_SDL_Haptic);
    Assign(VTYPE_SDL_HapticEffect);
    Assign(VTYPE_SDL_Joystick);
    Assign(VTYPE_SDL_JoystickGUID);
    Assign(VTYPE_SDL_Point);
    Assign(VTYPE_SDL_Rect);
    Assign(VTYPE_SDL_Renderer);
    Assign(VTYPE_SDL_RendererInfo);
    Assign(VTYPE_SDL_Sensor);
    Assign(VTYPE_SDL_Surface);
    Assign(VTYPE_SDL_SysWMinfo);
    Assign(VTYPE_SDL_Texture);
    Assign(VTYPE_SDL_Window);
	// Assignment of function
    AssignFunctions(GetFrame());
	Assign(Gurax_CreateFunction(Test));
	// Assignment of constant
    AssignConsts(GetFrame());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sdl)