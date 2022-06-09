#ifndef MWINDOW_H
#define MWINDOW_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <panel.h>

#define WINDOW_COLOR 1
#define SPACE_WINDOW_COLOR 2
#define RESIZED_WINDOW_COLOR 3

typedef struct
{
    int y;
    int x;
}
Point;

typedef struct
{
    int height;
    int width;
}
Size;

typedef struct
{
    Point point;
    Size size;
}
Rect;

/*typedef struct panel
#if !NCURSES_OPAQUE_PANEL
{
  WINDOW *win;
  struct panel *below;
  struct panel *above;
  NCURSES_CONST void *user;
}
#endif / !NCURSES_OPAQUE_PANEL \
PANEL;
*/

extern WINDOW* creatDrawWin(Rect *rect, char* string);

void deleteDrawWin(WINDOW *win);

void startNCurces();

void stopNCurces();

bool compareSizeWithMaxWidth(Rect* rect, Rect* tmpRect);

bool compareSizeWithMinWidth(Rect* tmpRect, char *string);

bool compareSizeWithMaxHeight(Rect* rect, Rect* tmpRect);

bool compareSizeWithMinHeight(Rect* tmpRect);

bool comparePointWithMaxX(Rect* tmpRect);

bool comparePointWithMinX(Rect* tmpRect);

bool comparePointWithMaxY(Rect* tmpRect);

bool comparePointWithMinY(Rect* tmpRect);

int exec(WINDOW* win, Rect* rect, char* string);

void changingTheColorIfWindowIsOnEdge(WINDOW *win, Rect *rect, Rect* tmpRect);

#endif // MWINDOW_H
