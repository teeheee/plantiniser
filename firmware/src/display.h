#ifndef _DISPLAY_H_
#define _DISPLAY_H_

void display_init();
void display_print(const char* text);
void display_print(int text);
void display_print_at(int line, const char* text);
void display_clear();

#endif
