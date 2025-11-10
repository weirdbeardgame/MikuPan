#include "sdl_controls.h"
#include "libpad.h"
#include <stdio.h>
#include <stdlib.h>
#include "os/pad.h"

static SDL_Gamepad *gamepad = {0};

static bool isPressed = false;

static int GetAxis(int sdlAxis)
{
    switch(sdlAxis)
    {
        case SDL_GAMEPAD_AXIS_RIGHTX: 
            return R_STICK_X_AXIS;

        case SDL_GAMEPAD_AXIS_RIGHTY:
            return R_STICK_Y_AXIS;

        case SDL_GAMEPAD_AXIS_LEFTX:
            return L_STICK_X_AXIS;

        case SDL_GAMEPAD_AXIS_LEFTY:
            return L_STICK_Y_AXIS;
        
        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
            return L2;

        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
            return R2;
    }
}

static int GetButton(int sdlButton)
{
    switch(sdlButton)
    {
        case SDL_GAMEPAD_BUTTON_SOUTH:
            return CROSS;

        case SDL_GAMEPAD_BUTTON_NORTH:
            return TRIANGLE;

        case SDL_GAMEPAD_BUTTON_EAST:
            return CIRCLE;

        case SDL_GAMEPAD_BUTTON_WEST:
            return SQUARE;

        case SDL_GAMEPAD_BUTTON_START:
            return START;

        case SDL_GAMEPAD_BUTTON_BACK:
            return SELECT;

        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
            return DPAD_DOWN;

        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
            return DPAD_LEFT;

        case SDL_GAMEPAD_BUTTON_DPAD_UP:
            return DPAD_UP;
        
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
            return DPAD_RIGHT;

        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
            return L1;

        case SDL_GAMEPAD_BUTTON_LEFT_STICK:
            return L3;

        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
            return R1;

        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
            return R3;
    }
}

bool InitGamepad()
{
    if (!SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC))
    {
        printf("Error, Controllers not initalized: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

bool OpenController(int port)
{
    if (gamepad != NULL || !SDL_HasGamepad())
    {
        return 0;
    }

    SDL_JoystickID *joysticks_id = SDL_GetGamepads(&port);

    if (joysticks_id == NULL)
    {
        return 0;
    }

    gamepad = SDL_OpenGamepad(joysticks_id[0]);
    return 1;
}

void Close()
{
    SDL_CloseGamepad(gamepad);
}

bool GetControllerEvent(const SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_GAMEPAD_ADDED:
            return OpenController(event->gdevice.which);
        case SDL_EVENT_GAMEPAD_REMOVED:
            Close();
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            //HandleButton(&event->gbutton);
            break;

        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            //HandleJoystick(&event->gaxis);
            break;
    }
}

void HandleButton(u_char *r_data, int btn)
{
    r_data[0] = 0;
    r_data[1] = 0x7A;

    u_short data = r_data[2] | (r_data[3] << 8);
    data &= ~(SDL_GetGamepadButton(gamepad, btn) << GetButton(btn)); // Verified
    r_data[2] = data;
    r_data[3] = (data >> 8) & 0xFF;
}

void HandleJoystick(u_char *r_data, int axis)
{
    r_data[0] = 0;        
    r_data[1] = 0x7A;

    if (axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER || axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) // Handling the analog case of L2 and R2
    {
            u_short data = r_data[2] | (r_data[3] << 8);
            data &= ~(SDL_GetGamepadAxis(gamepad, axis) << GetAxis(axis)); // Verified
            r_data[2] = data;
            r_data[3] = (data >> 8) & 0xFF;
    }
    else
    {
        r_data[GetAxis(axis)] = (SDL_GetGamepadAxis(gamepad, axis) + 32768) * 255 / 65535; 
    }
}

int IsConnected()
{
    if (gamepad == NULL)
    {
        return scePadStateDiscon;
    }

    return scePadStateStable;
}
