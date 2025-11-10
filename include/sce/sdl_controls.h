#ifndef MIKUPAN_SDL_CONTROLS_H
#define MIKUPAN_SDL_CONTROLS_H
#include "typedefs.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_gamepad.h"
#include "SDL3/SDL_init.h"

// Stick Values
#define R_STICK_X_AXIS 4
#define R_STICK_Y_AXIS 5
#define L_STICK_X_AXIS 6
#define L_STICK_Y_AXIS 7

// Buttons
#define SELECT 0
#define L3 1
#define R3 2
#define START 3
#define DPAD_UP 4
#define DPAD_RIGHT 5
#define DPAD_DOWN 6
#define DPAD_LEFT 7
#define L2 8
#define R2 9
#define L1 10
#define R1 11
#define TRIANGLE 12
#define CIRCLE 13
#define CROSS 14
#define SQUARE 15

bool InitGamepad();
void Close();
int IsConnected();
char * GetName(int btnID);
bool OpenController(int port);
bool GetControllerEvent(const SDL_Event *event);
void ReadController(u_char* controller_state);
void RunController();
void HandleButton(u_char* r_data, int btn);
void HandleJoystick(u_char *r_data, int axis);

u_char GetButtonValue(int i);
#endif // MIKUPAN_SDL_CONTROLS_H
