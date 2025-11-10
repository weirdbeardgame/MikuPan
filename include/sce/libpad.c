#include "libpad.h"
#include "sdl_controls.h"
#include <stdlib.h>
#include <stdio.h>

#include "os/pad.h"

#include <SDL3/SDL_gamepad.h>

#include <stddef.h>


int scePadPortOpen(int port, int slot, void* addr)
{
    return OpenController(port);
}

int scePadInit(int mode)
{
    return InitGamepad();
}

int scePadGetState(int port, int slot)
{
    return IsConnected();
}

// reads controller data and writes it to a buffer in rdata (must be at least 32 bytes large).
// returns buffer size (32) or 0 on error.
int scePadRead(int port, int slot, unsigned char *rdata)
{
    memset(rdata, 0xFF, 32);
    
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_NORTH); // Triangle
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_SOUTH); // Cross
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_EAST); // Circle
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_WEST); // Sqare
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_START);
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_BACK); // Select
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER); // L1
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER); // R1
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_LEFT_STICK); // L3
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_RIGHT_STICK); // R3
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_DPAD_UP);
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    HandleButton(rdata, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_LEFT_TRIGGER); // L2
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER); // R2
    
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_LEFTX);
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_LEFTY);
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_RIGHTX);
    HandleJoystick(rdata, SDL_GAMEPAD_AXIS_RIGHTY);

    return 32;
}

/// 4: STANDARD CONTROLLER (Dualshock)
/// 7: ANALOG CONTROLLER (Dualshock 2)
int scePadInfoMode(int port, int slot, int term, int offs)
{
    return 5;
}

int scePadSetMainMode(int port, int slot, int offs, int lock)
{
}

int scePadInfoAct(int port, int slot, int actno, int term)
{
}

int scePadSetActAlign(int port, int slot, const unsigned char* data)
{
}

int scePadGetReqState(int port, int slot)
{
}

int scePadInfoPressMode(int port, int slot)
{
}

int scePadEnterPressMode(int port, int slot)
{
}

int scePadSetActDirect(int port, int slot, const unsigned char* data)
{
}
