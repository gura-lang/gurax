//==============================================================================
// module-sdl.cpp
//==============================================================================
#include "stdafx.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}

Gurax_BeginModule(sdl)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// sdl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds up the given two numbers and returns the result.
)""");
}

Gurax_ImplementFunction(Test)
{
	SDL_AppInit(nullptr, 0, nullptr);
	// Run the main loop
	while (SDL_AppIterate(nullptr) == SDL_APP_CONTINUE) {
		// Handle events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			SDL_AppEvent(nullptr, &event);
		}
	}
	SDL_AppQuit(nullptr, SDL_APP_SUCCESS);
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
#if 0
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
	Assign(VTYPE_SDL_HapticConstant);
	Assign(VTYPE_SDL_HapticPeriodic);
	Assign(VTYPE_SDL_HapticCondition);
	Assign(VTYPE_SDL_HapticRamp);
	Assign(VTYPE_SDL_HapticLeftRight);
	Assign(VTYPE_SDL_HapticCustom);
	Assign(VTYPE_SDL_Joystick);
	Assign(VTYPE_SDL_JoystickGUID);
	Assign(VTYPE_SDL_Keysym);
	Assign(VTYPE_SDL_Palette);
	Assign(VTYPE_SDL_PixelFormat);
	Assign(VTYPE_SDL_Point);
	Assign(VTYPE_SDL_Rect);
	Assign(VTYPE_SDL_Renderer);
	Assign(VTYPE_SDL_RendererInfo);
	Assign(VTYPE_SDL_RWops);
	Assign(VTYPE_SDL_Sensor);
	Assign(VTYPE_SDL_Surface);
	Assign(VTYPE_SDL_SysWMinfo);
	Assign(VTYPE_SDL_Texture);
	Assign(VTYPE_SDL_version);
	Assign(VTYPE_SDL_Window);
	Assign(VTYPE_SDL_CommonEvent);
	Assign(VTYPE_SDL_WindowEvent);
	Assign(VTYPE_SDL_KeyboardEvent);
	Assign(VTYPE_SDL_TextEditingEvent);
	Assign(VTYPE_SDL_TextInputEvent);
	Assign(VTYPE_SDL_MouseMotionEvent);
	Assign(VTYPE_SDL_MouseButtonEvent);
	Assign(VTYPE_SDL_MouseWheelEvent);
	Assign(VTYPE_SDL_JoyAxisEvent);
	Assign(VTYPE_SDL_JoyBallEvent);
	Assign(VTYPE_SDL_JoyHatEvent);
	Assign(VTYPE_SDL_JoyButtonEvent);
	Assign(VTYPE_SDL_JoyDeviceEvent);
	Assign(VTYPE_SDL_ControllerAxisEvent);
	Assign(VTYPE_SDL_ControllerButtonEvent);
	Assign(VTYPE_SDL_ControllerDeviceEvent);
	Assign(VTYPE_SDL_AudioDeviceEvent);
	Assign(VTYPE_SDL_QuitEvent);
	Assign(VTYPE_SDL_UserEvent);
	Assign(VTYPE_SDL_SysWMEvent);
	Assign(VTYPE_SDL_TouchFingerEvent);
	Assign(VTYPE_SDL_MultiGestureEvent);
	Assign(VTYPE_SDL_DollarGestureEvent);
	Assign(VTYPE_SDL_DropEvent);
	Assign(VTYPE_Mix_Chunk);
	Assign(VTYPE_Mix_Music);
	Assign(VTYPE_TTF_Font);
	// Assignment of function
	AssignFunctions(GetFrame());
	// Assignment of constant
	AssignConsts(GetFrame());
#endif
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sdl)
