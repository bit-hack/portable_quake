#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include <SDL.h>

#include "quakedef.h"
#include "d_local.h"
#include "port.h"


static SDL_Surface *screen;


bool port_init(int width, int height) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  screen = SDL_SetVideoMode(width, height, 32, 0);
  if (!screen) {
    return false;
  }

  return true;
}

void port_draw(uint8_t *buf, uint8_t *palette) {

  if (!screen) {
    return;
  }

  uint32_t *d = (uint32_t*)screen->pixels;
  const uint8_t *p = buf;
  for (int y = 0; y < screen->h; ++y) {
    for (int x = 0; x < screen->w; ++x) {
      const uint8_t c = p[x];
      const uint8_t *lut = palette + (c * 3);
      d[x] = (lut[0] << 16) | (lut[1] << 8) | lut[2];
    }
    p += screen->w;
    d += screen->w;
  }

  SDL_Flip(screen);
}

void port_sleep(int ms) {
  SDL_Delay(1);
}

float port_time(void) {
  static clock_t starttime = 0;
  if (!starttime)
    starttime = clock();
  return (float)(clock() - starttime) / (float)CLOCKS_PER_SEC;
}

void port_quit(void) {
  SDL_FreeSurface(screen);
  screen = NULL;
  SDL_Quit();
}

void port_tick(void) {
  SDL_Event event;
  int sym, state;
  int modstate;

  while (SDL_PollEvent(&event))
  {
    switch (event.type) {

    case SDL_KEYDOWN:
    case SDL_KEYUP:
      sym = event.key.keysym.sym;
      state = event.key.state;
      modstate = SDL_GetModState();
      switch (sym)
      {
      case SDLK_DELETE: sym = K_DEL; break;
      case SDLK_BACKSPACE: sym = K_BACKSPACE; break;
      case SDLK_F1: sym = K_F1; break;
      case SDLK_F2: sym = K_F2; break;
      case SDLK_F3: sym = K_F3; break;
      case SDLK_F4: sym = K_F4; break;
      case SDLK_F5: sym = K_F5; break;
      case SDLK_F6: sym = K_F6; break;
      case SDLK_F7: sym = K_F7; break;
      case SDLK_F8: sym = K_F8; break;
      case SDLK_F9: sym = K_F9; break;
      case SDLK_F10: sym = K_F10; break;
      case SDLK_F11: sym = K_F11; break;
      case SDLK_F12: sym = K_F12; break;
      case SDLK_BREAK:
      case SDLK_PAUSE: sym = K_PAUSE; break;
      case SDLK_UP: sym = K_UPARROW; break;
      case SDLK_DOWN: sym = K_DOWNARROW; break;
      case SDLK_RIGHT: sym = K_RIGHTARROW; break;
      case SDLK_LEFT: sym = K_LEFTARROW; break;
      case SDLK_INSERT: sym = K_INS; break;
      case SDLK_HOME: sym = K_HOME; break;
      case SDLK_END: sym = K_END; break;
      case SDLK_PAGEUP: sym = K_PGUP; break;
      case SDLK_PAGEDOWN: sym = K_PGDN; break;
      case SDLK_RSHIFT:
      case SDLK_LSHIFT: sym = K_SHIFT; break;
      case SDLK_RCTRL:
      case SDLK_LCTRL: sym = K_CTRL; break;
      case SDLK_RALT:
      case SDLK_LALT: sym = K_ALT; break;
      case SDLK_KP0:
        if (modstate & KMOD_NUM) sym = K_INS;
        else sym = SDLK_0;
        break;
      case SDLK_KP1:
        if (modstate & KMOD_NUM) sym = K_END;
        else sym = SDLK_1;
        break;
      case SDLK_KP2:
        if (modstate & KMOD_NUM) sym = K_DOWNARROW;
        else sym = SDLK_2;
        break;
      case SDLK_KP3:
        if (modstate & KMOD_NUM) sym = K_PGDN;
        else sym = SDLK_3;
        break;
      case SDLK_KP4:
        if (modstate & KMOD_NUM) sym = K_LEFTARROW;
        else sym = SDLK_4;
        break;
      case SDLK_KP5: sym = SDLK_5; break;
      case SDLK_KP6:
        if (modstate & KMOD_NUM) sym = K_RIGHTARROW;
        else sym = SDLK_6;
        break;
      case SDLK_KP7:
        if (modstate & KMOD_NUM) sym = K_HOME;
        else sym = SDLK_7;
        break;
      case SDLK_KP8:
        if (modstate & KMOD_NUM) sym = K_UPARROW;
        else sym = SDLK_8;
        break;
      case SDLK_KP9:
        if (modstate & KMOD_NUM) sym = K_PGUP;
        else sym = SDLK_9;
        break;
      case SDLK_KP_PERIOD:
        if (modstate & KMOD_NUM) sym = K_DEL;
        else sym = SDLK_PERIOD;
        break;
      case SDLK_KP_DIVIDE: sym = SDLK_SLASH; break;
      case SDLK_KP_MULTIPLY: sym = SDLK_ASTERISK; break;
      case SDLK_KP_MINUS: sym = SDLK_MINUS; break;
      case SDLK_KP_PLUS: sym = SDLK_PLUS; break;
      case SDLK_KP_ENTER: sym = SDLK_RETURN; break;
      case SDLK_KP_EQUALS: sym = SDLK_EQUALS; break;
      }
      // If we're not directly handled and still above 255
      // just force it to 0
      if (sym > 255) sym = 0;
      Key_Event(sym, state);
      break;

    case SDL_QUIT:
      CL_Disconnect();
      Host_ShutdownServer(false);
      port_quit();
      break;
    default:
      break;
    }
  }
}
