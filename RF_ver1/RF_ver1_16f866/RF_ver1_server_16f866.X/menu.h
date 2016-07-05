#ifndef MENU_H
#define	MENU_H

#include <xc.h>
#include <stdint.h>
#include "myutils.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum
{
    MENU,
    NORMAL,
} E_operation_mode;
typedef enum
{
    EDIT,
    NOTEDIT
} E_operation_submode;


#define MAX_MENUITEM 4
typedef struct {
        uint8_t  value;
        char    *name;
} MenuItem_t; 

typedef struct {
        MenuItem_t items[MAX_MENUITEM];
        uint8_t index;
} Menu_t; 

void MenuInit();
void ShowMenu();
void ClearMenu();
void MenuUp();
void MenuDown();
void ValueInc();
void Valuedec();
void SaveMenuItem(uint8_t item);
uint8_t LoadMenuItem(uint8_t item);
#define SAVE_CUR_MENU_ITEM SaveMenuItem(g_menu.index)
#define LOAD_CUR_MENU_ITEM LoadMenuItem(g_menu.index)


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

