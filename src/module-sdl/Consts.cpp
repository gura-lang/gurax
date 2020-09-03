//==============================================================================
// Consts.cpp
//==============================================================================
#include "stdafx.h"

#define AssignConst(name) frame.Assign(#name, new Value_Number(name))

Gurax_BeginModuleScope(sdl)

void AssignConsts(Frame& frame)
{
	// SDL_AssertState
	AssignConst(SDL_ASSERTION_RETRY);
	AssignConst(SDL_ASSERTION_BREAK);
	AssignConst(SDL_ASSERTION_ABORT);
	AssignConst(SDL_ASSERTION_IGNORE);
	AssignConst(SDL_ASSERTION_ALWAYS_IGNORE);
	// SDL_AudioFormat	
	// SDL_AudioStatus
	AssignConst(SDL_AUDIO_STOPPED);
	AssignConst(SDL_AUDIO_PLAYING);
	AssignConst(SDL_AUDIO_PAUSED);
	// SDL_BlendFactor
	AssignConst(SDL_BLENDFACTOR_ZERO);
	AssignConst(SDL_BLENDFACTOR_ONE);
	AssignConst(SDL_BLENDFACTOR_SRC_COLOR);
	AssignConst(SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR);
	AssignConst(SDL_BLENDFACTOR_SRC_ALPHA);
	AssignConst(SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA);
	AssignConst(SDL_BLENDFACTOR_DST_COLOR);
	AssignConst(SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR);
	AssignConst(SDL_BLENDFACTOR_DST_ALPHA);
	AssignConst(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA);
	// SDL_BlendMode
	AssignConst(SDL_BLENDMODE_NONE);
	AssignConst(SDL_BLENDMODE_BLEND);
	AssignConst(SDL_BLENDMODE_ADD);
	AssignConst(SDL_BLENDMODE_MOD);
	// SDL_BlendOperation
	AssignConst(SDL_BLENDOPERATION_ADD);
	AssignConst(SDL_BLENDOPERATION_SUBTRACT);
	AssignConst(SDL_BLENDOPERATION_REV_SUBTRACT);
	AssignConst(SDL_BLENDOPERATION_MINIMUM);
	AssignConst(SDL_BLENDOPERATION_MAXIMUM);
	// SDL_EventType
	AssignConst(SDL_FIRSTEVENT);
	AssignConst(SDL_QUIT);
	AssignConst(SDL_APP_TERMINATING);
	AssignConst(SDL_APP_LOWMEMORY);
	AssignConst(SDL_APP_WILLENTERBACKGROUND);
	AssignConst(SDL_APP_DIDENTERBACKGROUND);
	AssignConst(SDL_APP_WILLENTERFOREGROUND);
	AssignConst(SDL_APP_DIDENTERFOREGROUND);
	AssignConst(SDL_WINDOWEVENT);
	AssignConst(SDL_SYSWMEVENT);
	AssignConst(SDL_KEYDOWN);
	AssignConst(SDL_KEYUP);
	AssignConst(SDL_TEXTEDITING);
	AssignConst(SDL_TEXTINPUT);
	AssignConst(SDL_KEYMAPCHANGED);
	AssignConst(SDL_MOUSEMOTION);
	AssignConst(SDL_MOUSEBUTTONDOWN);
	AssignConst(SDL_MOUSEBUTTONUP);
	AssignConst(SDL_MOUSEWHEEL);
	AssignConst(SDL_JOYAXISMOTION);
	AssignConst(SDL_JOYBALLMOTION);
	AssignConst(SDL_JOYHATMOTION);
	AssignConst(SDL_JOYBUTTONDOWN);
	AssignConst(SDL_JOYBUTTONUP);
	AssignConst(SDL_JOYDEVICEADDED);
	AssignConst(SDL_JOYDEVICEREMOVED);
	AssignConst(SDL_CONTROLLERAXISMOTION);
	AssignConst(SDL_CONTROLLERBUTTONDOWN);
	AssignConst(SDL_CONTROLLERBUTTONUP);
	AssignConst(SDL_CONTROLLERDEVICEADDED);
	AssignConst(SDL_CONTROLLERDEVICEREMOVED);
	AssignConst(SDL_CONTROLLERDEVICEREMAPPED);
	AssignConst(SDL_FINGERDOWN);
	AssignConst(SDL_FINGERUP);
	AssignConst(SDL_FINGERMOTION);
	AssignConst(SDL_DOLLARGESTURE);
	AssignConst(SDL_DOLLARRECORD);
	AssignConst(SDL_MULTIGESTURE);
	AssignConst(SDL_CLIPBOARDUPDATE);
	AssignConst(SDL_DROPFILE);
	AssignConst(SDL_DROPTEXT);
	AssignConst(SDL_DROPBEGIN);
	AssignConst(SDL_DROPCOMPLETE);
	AssignConst(SDL_AUDIODEVICEADDED);
	AssignConst(SDL_AUDIODEVICEREMOVED);
	AssignConst(SDL_RENDER_TARGETS_RESET);
	AssignConst(SDL_RENDER_DEVICE_RESET);
	AssignConst(SDL_USEREVENT);
	AssignConst(SDL_LASTEVENT);
	// SDL_GLattr
	AssignConst(SDL_GL_RED_SIZE);
	AssignConst(SDL_GL_GREEN_SIZE);
	AssignConst(SDL_GL_BLUE_SIZE);
	AssignConst(SDL_GL_ALPHA_SIZE);
	AssignConst(SDL_GL_BUFFER_SIZE);
	AssignConst(SDL_GL_DOUBLEBUFFER);
	AssignConst(SDL_GL_DEPTH_SIZE);
	AssignConst(SDL_GL_STENCIL_SIZE);
	AssignConst(SDL_GL_ACCUM_RED_SIZE);
	AssignConst(SDL_GL_ACCUM_GREEN_SIZE);
	AssignConst(SDL_GL_ACCUM_BLUE_SIZE);
	AssignConst(SDL_GL_ACCUM_ALPHA_SIZE);
	AssignConst(SDL_GL_STEREO);
	AssignConst(SDL_GL_MULTISAMPLEBUFFERS);
	AssignConst(SDL_GL_MULTISAMPLESAMPLES);
	AssignConst(SDL_GL_ACCELERATED_VISUAL);
	AssignConst(SDL_GL_RETAINED_BACKING);
	AssignConst(SDL_GL_CONTEXT_MAJOR_VERSION);
	AssignConst(SDL_GL_CONTEXT_MINOR_VERSION);
	AssignConst(SDL_GL_CONTEXT_FLAGS);
	AssignConst(SDL_GL_CONTEXT_PROFILE_MASK);
	AssignConst(SDL_GL_SHARE_WITH_CURRENT_CONTEXT);
	AssignConst(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
	AssignConst(SDL_GL_CONTEXT_RELEASE_BEHAVIOR);
	AssignConst(SDL_GL_CONTEXT_EGL);
	// SDL_GLcontextFlag
	AssignConst(SDL_GL_CONTEXT_DEBUG_FLAG);
	AssignConst(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	AssignConst(SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);
	AssignConst(SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);
	// SDL_GLprofile
	AssignConst(SDL_GL_CONTEXT_PROFILE_CORE);
	AssignConst(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	AssignConst(SDL_GL_CONTEXT_PROFILE_ES);
	// SDL_GameControllerAxis
	AssignConst(SDL_CONTROLLER_AXIS_INVALID);
	AssignConst(SDL_CONTROLLER_AXIS_LEFTX);
	AssignConst(SDL_CONTROLLER_AXIS_LEFTY);
	AssignConst(SDL_CONTROLLER_AXIS_RIGHTX);
	AssignConst(SDL_CONTROLLER_AXIS_RIGHTY);
	AssignConst(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
	AssignConst(SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
	AssignConst(SDL_CONTROLLER_AXIS_MAX);
	// SDL_GameControllerButton
	AssignConst(SDL_CONTROLLER_BUTTON_INVALID);
	AssignConst(SDL_CONTROLLER_BUTTON_A);
	AssignConst(SDL_CONTROLLER_BUTTON_B);
	AssignConst(SDL_CONTROLLER_BUTTON_X);
	AssignConst(SDL_CONTROLLER_BUTTON_Y);
	AssignConst(SDL_CONTROLLER_BUTTON_BACK);
	AssignConst(SDL_CONTROLLER_BUTTON_GUIDE);
	AssignConst(SDL_CONTROLLER_BUTTON_START);
	AssignConst(SDL_CONTROLLER_BUTTON_LEFTSTICK);
	AssignConst(SDL_CONTROLLER_BUTTON_RIGHTSTICK);
	AssignConst(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	AssignConst(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	AssignConst(SDL_CONTROLLER_BUTTON_DPAD_UP);
	AssignConst(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	AssignConst(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	AssignConst(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	AssignConst(SDL_CONTROLLER_BUTTON_MAX);
	// SDL_HintPriority
	AssignConst(SDL_HINT_DEFAULT);
	AssignConst(SDL_HINT_NORMAL);
	AssignConst(SDL_HINT_OVERRIDE);
	// SDL_HitTestResult
	AssignConst(SDL_HITTEST_NORMAL);
	AssignConst(SDL_HITTEST_DRAGGABLE);
	AssignConst(SDL_HITTEST_RESIZE_TOPLEFT);
	AssignConst(SDL_HITTEST_RESIZE_TOP);
	AssignConst(SDL_HITTEST_RESIZE_TOPRIGHT);
	AssignConst(SDL_HITTEST_RESIZE_RIGHT);
	AssignConst(SDL_HITTEST_RESIZE_BOTTOMRIGHT);
	AssignConst(SDL_HITTEST_RESIZE_BOTTOM);
	AssignConst(SDL_HITTEST_RESIZE_BOTTOMLEFT);
	AssignConst(SDL_HITTEST_RESIZE_LEFT);
	// SDL_JoystickPowerLevel
	AssignConst(SDL_JOYSTICK_POWER_UNKNOWN);
	AssignConst(SDL_JOYSTICK_POWER_EMPTY);
	AssignConst(SDL_JOYSTICK_POWER_LOW);
	AssignConst(SDL_JOYSTICK_POWER_MEDIUM);
	AssignConst(SDL_JOYSTICK_POWER_FULL);
	AssignConst(SDL_JOYSTICK_POWER_WIRED);
	AssignConst(SDL_JOYSTICK_POWER_MAX);
	// SDL_Scancode
	AssignConst(SDL_SCANCODE_0);
	AssignConst(SDL_SCANCODE_1);
	AssignConst(SDL_SCANCODE_2);
	AssignConst(SDL_SCANCODE_3);
	AssignConst(SDL_SCANCODE_4);
	AssignConst(SDL_SCANCODE_5);
	AssignConst(SDL_SCANCODE_6);
	AssignConst(SDL_SCANCODE_7);
	AssignConst(SDL_SCANCODE_8);
	AssignConst(SDL_SCANCODE_9);
	AssignConst(SDL_SCANCODE_A);
	AssignConst(SDL_SCANCODE_AC_BACK);
	AssignConst(SDL_SCANCODE_AC_BOOKMARKS);
	AssignConst(SDL_SCANCODE_AC_FORWARD);
	AssignConst(SDL_SCANCODE_AC_HOME);
	AssignConst(SDL_SCANCODE_AC_REFRESH);
	AssignConst(SDL_SCANCODE_AC_SEARCH);
	AssignConst(SDL_SCANCODE_AC_STOP);
	AssignConst(SDL_SCANCODE_AGAIN);
	AssignConst(SDL_SCANCODE_ALTERASE);
	AssignConst(SDL_SCANCODE_APOSTROPHE);
	AssignConst(SDL_SCANCODE_APPLICATION);
	AssignConst(SDL_SCANCODE_AUDIOMUTE);
	AssignConst(SDL_SCANCODE_AUDIONEXT);
	AssignConst(SDL_SCANCODE_AUDIOPLAY);
	AssignConst(SDL_SCANCODE_AUDIOPREV);
	AssignConst(SDL_SCANCODE_AUDIOSTOP);
	AssignConst(SDL_SCANCODE_B);
	AssignConst(SDL_SCANCODE_BACKSLASH);
	AssignConst(SDL_SCANCODE_BACKSPACE);
	AssignConst(SDL_SCANCODE_BRIGHTNESSDOWN);
	AssignConst(SDL_SCANCODE_BRIGHTNESSUP);
	AssignConst(SDL_SCANCODE_C);
	AssignConst(SDL_SCANCODE_CALCULATOR);
	AssignConst(SDL_SCANCODE_CANCEL);
	AssignConst(SDL_SCANCODE_CAPSLOCK);
	AssignConst(SDL_SCANCODE_CLEAR);
	AssignConst(SDL_SCANCODE_CLEARAGAIN);
	AssignConst(SDL_SCANCODE_COMMA);
	AssignConst(SDL_SCANCODE_COMPUTER);
	AssignConst(SDL_SCANCODE_COPY);
	AssignConst(SDL_SCANCODE_CRSEL);
	AssignConst(SDL_SCANCODE_CURRENCYSUBUNIT);
	AssignConst(SDL_SCANCODE_CURRENCYUNIT);
	AssignConst(SDL_SCANCODE_CUT);
	AssignConst(SDL_SCANCODE_D);
	AssignConst(SDL_SCANCODE_DECIMALSEPARATOR);
	AssignConst(SDL_SCANCODE_DELETE);
	AssignConst(SDL_SCANCODE_DISPLAYSWITCH);
	AssignConst(SDL_SCANCODE_DOWN);
	AssignConst(SDL_SCANCODE_E);
	AssignConst(SDL_SCANCODE_EJECT);
	AssignConst(SDL_SCANCODE_END);
	AssignConst(SDL_SCANCODE_EQUALS);
	AssignConst(SDL_SCANCODE_ESCAPE);
	AssignConst(SDL_SCANCODE_EXECUTE);
	AssignConst(SDL_SCANCODE_EXSEL);
	AssignConst(SDL_SCANCODE_F);
	AssignConst(SDL_SCANCODE_F1);
	AssignConst(SDL_SCANCODE_F10);
	AssignConst(SDL_SCANCODE_F11);
	AssignConst(SDL_SCANCODE_F12);
	AssignConst(SDL_SCANCODE_F13);
	AssignConst(SDL_SCANCODE_F14);
	AssignConst(SDL_SCANCODE_F15);
	AssignConst(SDL_SCANCODE_F16);
	AssignConst(SDL_SCANCODE_F17);
	AssignConst(SDL_SCANCODE_F18);
	AssignConst(SDL_SCANCODE_F19);
	AssignConst(SDL_SCANCODE_F2);
	AssignConst(SDL_SCANCODE_F20);
	AssignConst(SDL_SCANCODE_F21);
	AssignConst(SDL_SCANCODE_F22);
	AssignConst(SDL_SCANCODE_F23);
	AssignConst(SDL_SCANCODE_F24);
	AssignConst(SDL_SCANCODE_F3);
	AssignConst(SDL_SCANCODE_F4);
	AssignConst(SDL_SCANCODE_F5);
	AssignConst(SDL_SCANCODE_F6);
	AssignConst(SDL_SCANCODE_F7);
	AssignConst(SDL_SCANCODE_F8);
	AssignConst(SDL_SCANCODE_F9);
	AssignConst(SDL_SCANCODE_FIND);
	AssignConst(SDL_SCANCODE_G);
	AssignConst(SDL_SCANCODE_GRAVE);
	AssignConst(SDL_SCANCODE_H);
	AssignConst(SDL_SCANCODE_HELP);
	AssignConst(SDL_SCANCODE_HOME);
	AssignConst(SDL_SCANCODE_I);
	AssignConst(SDL_SCANCODE_INSERT);
	AssignConst(SDL_SCANCODE_J);
	AssignConst(SDL_SCANCODE_K);
	AssignConst(SDL_SCANCODE_KBDILLUMDOWN);
	AssignConst(SDL_SCANCODE_KBDILLUMTOGGLE);
	AssignConst(SDL_SCANCODE_KBDILLUMUP);
	AssignConst(SDL_SCANCODE_KP_0);
	AssignConst(SDL_SCANCODE_KP_00);
	AssignConst(SDL_SCANCODE_KP_000);
	AssignConst(SDL_SCANCODE_KP_1);
	AssignConst(SDL_SCANCODE_KP_2);
	AssignConst(SDL_SCANCODE_KP_3);
	AssignConst(SDL_SCANCODE_KP_4);
	AssignConst(SDL_SCANCODE_KP_5);
	AssignConst(SDL_SCANCODE_KP_6);
	AssignConst(SDL_SCANCODE_KP_7);
	AssignConst(SDL_SCANCODE_KP_8);
	AssignConst(SDL_SCANCODE_KP_9);
	AssignConst(SDL_SCANCODE_KP_A);
	AssignConst(SDL_SCANCODE_KP_AMPERSAND);
	AssignConst(SDL_SCANCODE_KP_AT);
	AssignConst(SDL_SCANCODE_KP_B);
	AssignConst(SDL_SCANCODE_KP_BACKSPACE);
	AssignConst(SDL_SCANCODE_KP_BINARY);
	AssignConst(SDL_SCANCODE_KP_C);
	AssignConst(SDL_SCANCODE_KP_CLEAR);
	AssignConst(SDL_SCANCODE_KP_CLEARENTRY);
	AssignConst(SDL_SCANCODE_KP_COLON);
	AssignConst(SDL_SCANCODE_KP_COMMA);
	AssignConst(SDL_SCANCODE_KP_D);
	AssignConst(SDL_SCANCODE_KP_DBLAMPERSAND);
	AssignConst(SDL_SCANCODE_KP_DBLVERTICALBAR);
	AssignConst(SDL_SCANCODE_KP_DECIMAL);
	AssignConst(SDL_SCANCODE_KP_DIVIDE);
	AssignConst(SDL_SCANCODE_KP_E);
	AssignConst(SDL_SCANCODE_KP_ENTER);
	AssignConst(SDL_SCANCODE_KP_EQUALS);
	AssignConst(SDL_SCANCODE_KP_EQUALSAS400);
	AssignConst(SDL_SCANCODE_KP_EXCLAM);
	AssignConst(SDL_SCANCODE_KP_F);
	AssignConst(SDL_SCANCODE_KP_GREATER);
	AssignConst(SDL_SCANCODE_KP_HASH);
	AssignConst(SDL_SCANCODE_KP_HEXADECIMAL);
	AssignConst(SDL_SCANCODE_KP_LEFTBRACE);
	AssignConst(SDL_SCANCODE_KP_LEFTPAREN);
	AssignConst(SDL_SCANCODE_KP_LESS);
	AssignConst(SDL_SCANCODE_KP_MEMADD);
	AssignConst(SDL_SCANCODE_KP_MEMCLEAR);
	AssignConst(SDL_SCANCODE_KP_MEMDIVIDE);
	AssignConst(SDL_SCANCODE_KP_MEMMULTIPLY);
	AssignConst(SDL_SCANCODE_KP_MEMRECALL);
	AssignConst(SDL_SCANCODE_KP_MEMSTORE);
	AssignConst(SDL_SCANCODE_KP_MEMSUBTRACT);
	AssignConst(SDL_SCANCODE_KP_MINUS);
	AssignConst(SDL_SCANCODE_KP_MULTIPLY);
	AssignConst(SDL_SCANCODE_KP_OCTAL);
	AssignConst(SDL_SCANCODE_KP_PERCENT);
	AssignConst(SDL_SCANCODE_KP_PERIOD);
	AssignConst(SDL_SCANCODE_KP_PLUS);
	AssignConst(SDL_SCANCODE_KP_PLUSMINUS);
	AssignConst(SDL_SCANCODE_KP_POWER);
	AssignConst(SDL_SCANCODE_KP_RIGHTBRACE);
	AssignConst(SDL_SCANCODE_KP_RIGHTPAREN);
	AssignConst(SDL_SCANCODE_KP_SPACE);
	AssignConst(SDL_SCANCODE_KP_TAB);
	AssignConst(SDL_SCANCODE_KP_VERTICALBAR);
	AssignConst(SDL_SCANCODE_KP_XOR);
	AssignConst(SDL_SCANCODE_L);
	AssignConst(SDL_SCANCODE_LALT);
	AssignConst(SDL_SCANCODE_LCTRL);
	AssignConst(SDL_SCANCODE_LEFT);
	AssignConst(SDL_SCANCODE_LEFTBRACKET);
	AssignConst(SDL_SCANCODE_LGUI);
	AssignConst(SDL_SCANCODE_LSHIFT);
	AssignConst(SDL_SCANCODE_M);
	AssignConst(SDL_SCANCODE_MAIL);
	AssignConst(SDL_SCANCODE_MEDIASELECT);
	AssignConst(SDL_SCANCODE_MENU);
	AssignConst(SDL_SCANCODE_MINUS);
	AssignConst(SDL_SCANCODE_MODE);
	AssignConst(SDL_SCANCODE_MUTE);
	AssignConst(SDL_SCANCODE_N);
	AssignConst(SDL_SCANCODE_NUMLOCKCLEAR);
	AssignConst(SDL_SCANCODE_O);
	AssignConst(SDL_SCANCODE_OPER);
	AssignConst(SDL_SCANCODE_OUT);
	AssignConst(SDL_SCANCODE_P);
	AssignConst(SDL_SCANCODE_PAGEDOWN);
	AssignConst(SDL_SCANCODE_PAGEUP);
	AssignConst(SDL_SCANCODE_PASTE);
	AssignConst(SDL_SCANCODE_PAUSE);
	AssignConst(SDL_SCANCODE_PERIOD);
	AssignConst(SDL_SCANCODE_POWER);
	AssignConst(SDL_SCANCODE_PRINTSCREEN);
	AssignConst(SDL_SCANCODE_PRIOR);
	AssignConst(SDL_SCANCODE_Q);
	AssignConst(SDL_SCANCODE_R);
	AssignConst(SDL_SCANCODE_RALT);
	AssignConst(SDL_SCANCODE_RCTRL);
	AssignConst(SDL_SCANCODE_RETURN);
	AssignConst(SDL_SCANCODE_RETURN2);
	AssignConst(SDL_SCANCODE_RGUI);
	AssignConst(SDL_SCANCODE_RIGHT);
	AssignConst(SDL_SCANCODE_RIGHTBRACKET);
	AssignConst(SDL_SCANCODE_RSHIFT);
	AssignConst(SDL_SCANCODE_S);
	AssignConst(SDL_SCANCODE_SCROLLLOCK);
	AssignConst(SDL_SCANCODE_SELECT);
	AssignConst(SDL_SCANCODE_SEMICOLON);
	AssignConst(SDL_SCANCODE_SEPARATOR);
	AssignConst(SDL_SCANCODE_SLASH);
	AssignConst(SDL_SCANCODE_SLEEP);
	AssignConst(SDL_SCANCODE_SPACE);
	AssignConst(SDL_SCANCODE_STOP);
	AssignConst(SDL_SCANCODE_SYSREQ);
	AssignConst(SDL_SCANCODE_T);
	AssignConst(SDL_SCANCODE_TAB);
	AssignConst(SDL_SCANCODE_THOUSANDSSEPARATOR);
	AssignConst(SDL_SCANCODE_U);
	AssignConst(SDL_SCANCODE_UNDO);
	AssignConst(SDL_SCANCODE_UNKNOWN);
	AssignConst(SDL_SCANCODE_UP);
	AssignConst(SDL_SCANCODE_V);
	AssignConst(SDL_SCANCODE_VOLUMEDOWN);
	AssignConst(SDL_SCANCODE_VOLUMEUP);
	AssignConst(SDL_SCANCODE_W);
	AssignConst(SDL_SCANCODE_WWW);
	AssignConst(SDL_SCANCODE_X);
	AssignConst(SDL_SCANCODE_Y);
	AssignConst(SDL_SCANCODE_Z);
	AssignConst(SDL_SCANCODE_INTERNATIONAL1);
	AssignConst(SDL_SCANCODE_INTERNATIONAL2);
	AssignConst(SDL_SCANCODE_INTERNATIONAL3);
	AssignConst(SDL_SCANCODE_INTERNATIONAL4);
	AssignConst(SDL_SCANCODE_INTERNATIONAL5);
	AssignConst(SDL_SCANCODE_INTERNATIONAL6);
	AssignConst(SDL_SCANCODE_INTERNATIONAL7);
	AssignConst(SDL_SCANCODE_INTERNATIONAL8);
	AssignConst(SDL_SCANCODE_INTERNATIONAL9);
	AssignConst(SDL_SCANCODE_LANG1);
	AssignConst(SDL_SCANCODE_LANG2);
	AssignConst(SDL_SCANCODE_LANG3);
	AssignConst(SDL_SCANCODE_LANG4);
	AssignConst(SDL_SCANCODE_LANG5);
	AssignConst(SDL_SCANCODE_LANG6);
	AssignConst(SDL_SCANCODE_LANG7);
	AssignConst(SDL_SCANCODE_LANG8);
	AssignConst(SDL_SCANCODE_LANG9);
	//AssignConst(SDL_SCANCODE_LOCKINGCAPSLOCK);
	//AssignConst(SDL_SCANCODE_LOCKINGNUMLOCK);
	//AssignConst(SDL_SCANCODE_LOCKINGSCROLLLOCK);
	AssignConst(SDL_SCANCODE_NONUSBACKSLASH);
	AssignConst(SDL_SCANCODE_NONUSHASH);
	// SDL_Keycode
	AssignConst(SDLK_0);
	AssignConst(SDLK_1);
	AssignConst(SDLK_2);
	AssignConst(SDLK_3);
	AssignConst(SDLK_4);
	AssignConst(SDLK_5);
	AssignConst(SDLK_6);
	AssignConst(SDLK_7);
	AssignConst(SDLK_8);
	AssignConst(SDLK_9);
	AssignConst(SDLK_a);
	AssignConst(SDLK_AC_BACK);
	AssignConst(SDLK_AC_BOOKMARKS);
	AssignConst(SDLK_AC_FORWARD);
	AssignConst(SDLK_AC_HOME);
	AssignConst(SDLK_AC_REFRESH);
	AssignConst(SDLK_AC_SEARCH);
	AssignConst(SDLK_AC_STOP);
	AssignConst(SDLK_AGAIN);
	AssignConst(SDLK_ALTERASE);
	AssignConst(SDLK_QUOTE);
	AssignConst(SDLK_APPLICATION);
	AssignConst(SDLK_AUDIOMUTE);
	AssignConst(SDLK_AUDIONEXT);
	AssignConst(SDLK_AUDIOPLAY);
	AssignConst(SDLK_AUDIOPREV);
	AssignConst(SDLK_AUDIOSTOP);
	AssignConst(SDLK_b);
	AssignConst(SDLK_BACKSLASH);
	AssignConst(SDLK_BACKSPACE);
	AssignConst(SDLK_BRIGHTNESSDOWN);
	AssignConst(SDLK_BRIGHTNESSUP);
	AssignConst(SDLK_c);
	AssignConst(SDLK_CALCULATOR);
	AssignConst(SDLK_CANCEL);
	AssignConst(SDLK_CAPSLOCK);
	AssignConst(SDLK_CLEAR);
	AssignConst(SDLK_CLEARAGAIN);
	AssignConst(SDLK_COMMA);
	AssignConst(SDLK_COMPUTER);
	AssignConst(SDLK_COPY);
	AssignConst(SDLK_CRSEL);
	AssignConst(SDLK_CURRENCYSUBUNIT);
	AssignConst(SDLK_CURRENCYUNIT);
	AssignConst(SDLK_CUT);
	AssignConst(SDLK_d);
	AssignConst(SDLK_DECIMALSEPARATOR);
	AssignConst(SDLK_DELETE);
	AssignConst(SDLK_DISPLAYSWITCH);
	AssignConst(SDLK_DOWN);
	AssignConst(SDLK_e);
	AssignConst(SDLK_EJECT);
	AssignConst(SDLK_END);
	AssignConst(SDLK_EQUALS);
	AssignConst(SDLK_ESCAPE);
	AssignConst(SDLK_EXECUTE);
	AssignConst(SDLK_EXSEL);
	AssignConst(SDLK_f);
	AssignConst(SDLK_F1);
	AssignConst(SDLK_F10);
	AssignConst(SDLK_F11);
	AssignConst(SDLK_F12);
	AssignConst(SDLK_F13);
	AssignConst(SDLK_F14);
	AssignConst(SDLK_F15);
	AssignConst(SDLK_F16);
	AssignConst(SDLK_F17);
	AssignConst(SDLK_F18);
	AssignConst(SDLK_F19);
	AssignConst(SDLK_F2);
	AssignConst(SDLK_F20);
	AssignConst(SDLK_F21);
	AssignConst(SDLK_F22);
	AssignConst(SDLK_F23);
	AssignConst(SDLK_F24);
	AssignConst(SDLK_F3);
	AssignConst(SDLK_F4);
	AssignConst(SDLK_F5);
	AssignConst(SDLK_F6);
	AssignConst(SDLK_F7);
	AssignConst(SDLK_F8);
	AssignConst(SDLK_F9);
	AssignConst(SDLK_FIND);
	AssignConst(SDLK_g);
	AssignConst(SDLK_BACKQUOTE);
	AssignConst(SDLK_h);
	AssignConst(SDLK_HELP);
	AssignConst(SDLK_HOME);
	AssignConst(SDLK_i);
	AssignConst(SDLK_INSERT);
	AssignConst(SDLK_j);
	AssignConst(SDLK_k);
	AssignConst(SDLK_KBDILLUMDOWN);
	AssignConst(SDLK_KBDILLUMTOGGLE);
	AssignConst(SDLK_KBDILLUMUP);
	AssignConst(SDLK_KP_0);
	AssignConst(SDLK_KP_00);
	AssignConst(SDLK_KP_000);
	AssignConst(SDLK_KP_1);
	AssignConst(SDLK_KP_2);
	AssignConst(SDLK_KP_3);
	AssignConst(SDLK_KP_4);
	AssignConst(SDLK_KP_5);
	AssignConst(SDLK_KP_6);
	AssignConst(SDLK_KP_7);
	AssignConst(SDLK_KP_8);
	AssignConst(SDLK_KP_9);
	AssignConst(SDLK_KP_A);
	AssignConst(SDLK_KP_AMPERSAND);
	AssignConst(SDLK_KP_AT);
	AssignConst(SDLK_KP_B);
	AssignConst(SDLK_KP_BACKSPACE);
	AssignConst(SDLK_KP_BINARY);
	AssignConst(SDLK_KP_C);
	AssignConst(SDLK_KP_CLEAR);
	AssignConst(SDLK_KP_CLEARENTRY);
	AssignConst(SDLK_KP_COLON);
	AssignConst(SDLK_KP_COMMA);
	AssignConst(SDLK_KP_D);
	AssignConst(SDLK_KP_DBLAMPERSAND);
	AssignConst(SDLK_KP_DBLVERTICALBAR);
	AssignConst(SDLK_KP_DECIMAL);
	AssignConst(SDLK_KP_DIVIDE);
	AssignConst(SDLK_KP_E);
	AssignConst(SDLK_KP_ENTER);
	AssignConst(SDLK_KP_EQUALS);
	AssignConst(SDLK_KP_EQUALSAS400);
	AssignConst(SDLK_KP_EXCLAM);
	AssignConst(SDLK_KP_F);
	AssignConst(SDLK_KP_GREATER);
	AssignConst(SDLK_KP_HASH);
	AssignConst(SDLK_KP_HEXADECIMAL);
	AssignConst(SDLK_KP_LEFTBRACE);
	AssignConst(SDLK_KP_LEFTPAREN);
	AssignConst(SDLK_KP_LESS);
	AssignConst(SDLK_KP_MEMADD);
	AssignConst(SDLK_KP_MEMCLEAR);
	AssignConst(SDLK_KP_MEMDIVIDE);
	AssignConst(SDLK_KP_MEMMULTIPLY);
	AssignConst(SDLK_KP_MEMRECALL);
	AssignConst(SDLK_KP_MEMSTORE);
	AssignConst(SDLK_KP_MEMSUBTRACT);
	AssignConst(SDLK_KP_MINUS);
	AssignConst(SDLK_KP_MULTIPLY);
	AssignConst(SDLK_KP_OCTAL);
	AssignConst(SDLK_KP_PERCENT);
	AssignConst(SDLK_KP_PERIOD);
	AssignConst(SDLK_KP_PLUS);
	AssignConst(SDLK_KP_PLUSMINUS);
	AssignConst(SDLK_KP_POWER);
	AssignConst(SDLK_KP_RIGHTBRACE);
	AssignConst(SDLK_KP_RIGHTPAREN);
	AssignConst(SDLK_KP_SPACE);
	AssignConst(SDLK_KP_TAB);
	AssignConst(SDLK_KP_VERTICALBAR);
	AssignConst(SDLK_KP_XOR);
	AssignConst(SDLK_l);
	AssignConst(SDLK_LALT);
	AssignConst(SDLK_LCTRL);
	AssignConst(SDLK_LEFT);
	AssignConst(SDLK_LEFTBRACKET);
	AssignConst(SDLK_LGUI);
	AssignConst(SDLK_LSHIFT);
	AssignConst(SDLK_m);
	AssignConst(SDLK_MAIL);
	AssignConst(SDLK_MEDIASELECT);
	AssignConst(SDLK_MENU);
	AssignConst(SDLK_MINUS);
	AssignConst(SDLK_MODE);
	AssignConst(SDLK_MUTE);
	AssignConst(SDLK_n);
	AssignConst(SDLK_NUMLOCKCLEAR);
	AssignConst(SDLK_o);
	AssignConst(SDLK_OPER);
	AssignConst(SDLK_OUT);
	AssignConst(SDLK_p);
	AssignConst(SDLK_PAGEDOWN);
	AssignConst(SDLK_PAGEUP);
	AssignConst(SDLK_PASTE);
	AssignConst(SDLK_PAUSE);
	AssignConst(SDLK_PERIOD);
	AssignConst(SDLK_POWER);
	AssignConst(SDLK_PRINTSCREEN);
	AssignConst(SDLK_PRIOR);
	AssignConst(SDLK_q);
	AssignConst(SDLK_r);
	AssignConst(SDLK_RALT);
	AssignConst(SDLK_RCTRL);
	AssignConst(SDLK_RETURN);
	AssignConst(SDLK_RETURN2);
	AssignConst(SDLK_RGUI);
	AssignConst(SDLK_RIGHT);
	AssignConst(SDLK_RIGHTBRACKET);
	AssignConst(SDLK_RSHIFT);
	AssignConst(SDLK_s);
	AssignConst(SDLK_SCROLLLOCK);
	AssignConst(SDLK_SELECT);
	AssignConst(SDLK_SEMICOLON);
	AssignConst(SDLK_SEPARATOR);
	AssignConst(SDLK_SLASH);
	AssignConst(SDLK_SLEEP);
	AssignConst(SDLK_SPACE);
	AssignConst(SDLK_STOP);
	AssignConst(SDLK_SYSREQ);
	AssignConst(SDLK_t);
	AssignConst(SDLK_TAB);
	AssignConst(SDLK_THOUSANDSSEPARATOR);
	AssignConst(SDLK_u);
	AssignConst(SDLK_UNDO);
	AssignConst(SDLK_UNKNOWN);
	AssignConst(SDLK_UP);
	AssignConst(SDLK_v);
	AssignConst(SDLK_VOLUMEDOWN);
	AssignConst(SDLK_VOLUMEUP);
	AssignConst(SDLK_w);
	AssignConst(SDLK_WWW);
	AssignConst(SDLK_x);
	AssignConst(SDLK_y);
	AssignConst(SDLK_z);
	AssignConst(SDLK_AMPERSAND);
	AssignConst(SDLK_ASTERISK);
	AssignConst(SDLK_AT);
	AssignConst(SDLK_CARET);
	AssignConst(SDLK_COLON);
	AssignConst(SDLK_DOLLAR);
	AssignConst(SDLK_EXCLAIM);
	AssignConst(SDLK_GREATER);
	AssignConst(SDLK_HASH);
	AssignConst(SDLK_LEFTPAREN);
	AssignConst(SDLK_LESS);
	AssignConst(SDLK_PERCENT);
	AssignConst(SDLK_PLUS);
	AssignConst(SDLK_QUESTION);
	AssignConst(SDLK_QUOTEDBL);
	AssignConst(SDLK_RIGHTPAREN);
	AssignConst(SDLK_UNDERSCORE);


}

Gurax_EndModuleScope(sdl)
