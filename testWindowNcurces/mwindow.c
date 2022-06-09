#include "mwindow.h"

WINDOW* creatDrawWin(Rect *rect, char* string)
{
    WINDOW *win = newwin(rect->size.height, rect->size.width, rect->point.y, rect->point.x);

    wattron(win, COLOR_PAIR(WINDOW_COLOR));
    wbkgd(win, COLOR_PAIR(WINDOW_COLOR));
    attron(COLOR_PAIR(WINDOW_COLOR));
    mvaddstr(rect->point.y + rect->size.height/2, rect->point.x + rect->size.width/2 - (int)(strlen(string)/2), string);
    box(win, 0 , 0);
    wrefresh(win);
  return win;
}

void deleteDrawWin(WINDOW *win)
{
    wattron(win, COLOR_PAIR(SPACE_WINDOW_COLOR));
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}

void startNCurces()
{
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    noecho();

    start_color();
    init_pair(WINDOW_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(SPACE_WINDOW_COLOR, COLOR_BLACK, COLOR_BLACK);
    init_pair(RESIZED_WINDOW_COLOR, COLOR_WHITE, COLOR_RED);
}

void stopNCurces()
{
    endwin();
}

bool compareSizeWithMaxWidth(Rect* rect, Rect* tmpRect)
{
  return (tmpRect->size.width < rect->size.width) ? TRUE : FALSE;
}

bool compareSizeWithMinWidth(Rect* tmpRect, char *string)
{
  return (tmpRect->size.width > tmpRect->size.width/2 + ((int)strlen(string) + 3) /2) ? TRUE : FALSE;
}

bool compareSizeWithMaxHeight(Rect* rect, Rect* tmpRect)
{
  return (tmpRect->size.height < rect->size.height) ? TRUE : FALSE;
}

bool compareSizeWithMinHeight(Rect* tmpRect)
{
  return (tmpRect->size.height > 3) ? TRUE : FALSE;
}

bool comparePointWithMaxX(Rect* tmpRect)
{
  return (tmpRect->point.x < LINES) ? TRUE : FALSE;
}

bool comparePointWithMinX(Rect* tmpRect)
{
  return (tmpRect->point.x > 0) ? TRUE : FALSE;
}

bool comparePointWithMaxY(Rect* tmpRect)
{
  return (tmpRect->point.y < COLS) ? TRUE : FALSE;
}

bool comparePointWithMinY(Rect* tmpRect)
{
  return (tmpRect->point.y > 0) ? TRUE : FALSE;
}

int exec(WINDOW* win, Rect* rect, char* string)
{
    int ch = 0;
    Rect tmpRect = *rect;
    while( (ch = getch()) != KEY_F(2) )//
    {
        switch(ch)//
        {
            case KEY_RIGHT:                                                         //
            {
                if(comparePointWithMaxX(&tmpRect)) //1 действие - если меньше данного, увеличивайся
                {
                    if(compareSizeWithMaxWidth(rect, &tmpRect))
                    {
                        tmpRect.size.width++;
                    }
                    else
                    {
                        mvwin(win, tmpRect.point.y, tmpRect.point.x++);
                    }
                }
                else
                {
                    if(compareSizeWithMinWidth(&tmpRect, string))
                    {
                        tmpRect.size.width--;
                        mvwin(win, tmpRect.point.y, tmpRect.point.x++);
                    }
                }
            }
            break;                                                                  //
            case KEY_LEFT: //
                if(comparePointWithMinX(&tmpRect))
                {
                    mvwin(win, tmpRect.point.y, tmpRect.point.x--); //
                    if(compareSizeWithMaxWidth(rect, &tmpRect))
                    {
                        tmpRect.size.width++;
                    }
                }
                else
                {
                    if(compareSizeWithMinWidth(&tmpRect, string))
                    {
                        tmpRect.size.width--;
                    }
                }
            break; //
            case KEY_UP: //
                if(comparePointWithMinY(&tmpRect))
                {
                    mvwin(win, tmpRect.point.y--, tmpRect.point.x); //
                    if(compareSizeWithMaxHeight(rect, &tmpRect))
                    {
                        tmpRect.size.height++;
                    }
                }
                else
                {
                    if(compareSizeWithMinHeight(&tmpRect))
                    {
                        tmpRect.size.height--;
                    }
                }
            break; //
            case KEY_DOWN: //
                if(comparePointWithMaxY(&tmpRect))
                {
                    if(compareSizeWithMaxHeight(rect, &tmpRect))
                    {
                        tmpRect.size.height++;
                    }
                    else
                    {
                        mvwin(win, tmpRect.point.y++, tmpRect.point.x); //
                    }
                }
                else
                {
                    if(compareSizeWithMinHeight(&tmpRect))
                    {
                        tmpRect.size.height--;
                        mvwin(win, tmpRect.point.y++, tmpRect.point.x);
                    }
                }

            break;
            case KEY_F(3): // Увеличение диагонали
                if(tmpRect.point.y + tmpRect.size.height < LINES)// Край по у
                {
                    if(compareSizeWithMinHeight(&tmpRect))
                    {
                        tmpRect.size.height++;
                    }
                }
                if(tmpRect.point.x + tmpRect.size.width < COLS)// Край по х
                {
                    if(compareSizeWithMinWidth(&tmpRect, string))
                    {
                        tmpRect.size.width++;
                    }
                }
            break;
            case KEY_F(4): // Уменьшение диагонали
                if(compareSizeWithMinHeight(&tmpRect))
                {
                    tmpRect.size.height--;
                }
                if(compareSizeWithMinWidth(&tmpRect, string))
                {
                    tmpRect.size.width--;
                }
            break; //
        }
        refresh();
        deleteDrawWin(win); //
        wattroff(win,COLOR_PAIR(WINDOW_COLOR));
        win = creatDrawWin(&tmpRect, string); //
    }
  return ch;
}

void changingTheColorIfWindowIsOnEdge(WINDOW *win, Rect *rect, Rect* tmpRect)
{
    if(!(compareSizeWithMaxWidth(rect, tmpRect) && compareSizeWithMaxHeight(rect, tmpRect)))
    {
        wattroff(win, COLOR_PAIR(WINDOW_COLOR));
        wattron(win, COLOR_PAIR(RESIZED_WINDOW_COLOR));
    }
}
