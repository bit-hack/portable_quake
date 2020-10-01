#pragma once
#include <stdbool.h>
#include <stdint.h>

void port_sleep(int ms);
void port_tick(void);
void port_draw(uint8_t *screen, uint8_t *palette);
float port_time(void);
bool port_init(int w, int h);
void port_quit(void);
