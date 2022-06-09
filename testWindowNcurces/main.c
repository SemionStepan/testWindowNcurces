#include "mwindow.h"

int main()
{
    startNCurces(); //
    curs_set(0); //

    refresh(); //

    Rect rect = { {10, 10}, {20, 50} }; //

    char* hello = "Hello, world!"; //

    WINDOW* win = creatDrawWin(&rect, hello); //

    exec(win, &rect, hello);

    deleteDrawWin(win); //
    stopNCurces(); //
  return 0;
}
/*
    (WINDOW*)panel_window (const PANEL *); // pan->win      below - ниже/ above - выше
    update_panels (void); // Типа refresh
    hide_panel (PANEL *); // В стеке вниз
    show_panel (PANEL *); // В стеке наверх
    del_panel (PANEL *); // Делает фри
    top_panel (PANEL *); // Делает show panel
    bottom_panel (PANEL *); //  pan->below = _nc_bottom_panel;
                                pan->above = _nc_bottom_panel->above;
                                if (pan->above)
                                pan->above->below = pan;
                                _nc_bottom_panel->above = pan;
    (PANEL*) new_panel (WINDOW *); // Всё присваивается в панель
    (PANEL*) panel_above (const PANEL *); // Если стек пустой, то панель наверх
    (PANEL*) panel_below (const PANEL *); // панель вниз
    set_panel_userptr (PANEL *, NCURSES_CONST void *); //  pan->user = uptr;
    (NCURSES_CONST void*) panel_userptr (const PANEL *); // pan->user
    move_panel (PANEL *, int, int); // mvwin(pan->win, starty, startx)
    replace_panel (PANEL *,WINDOW *); //  pan->win = win;
    panel_hidden (const PANEL *); // IS_LINKED(pan) ? FALSE : TRUE
*/
