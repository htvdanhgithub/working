#include <xc.h>
#include "menu.h"


Menu_t g_menu;

void MenuInit()
{
    g_menu.items[0].name = "ID1:";
    g_menu.items[0].value = LoadMenuItem(0);

    g_menu.items[1].name = "ID2:";
    g_menu.items[1].value = LoadMenuItem(1);

    g_menu.items[2].name = "ID3:";
    g_menu.items[2].value = LoadMenuItem(2);

    g_menu.items[3].name = "ID4:";
    g_menu.items[3].value = LoadMenuItem(3);
    
    g_menu.index = 0;
}
void ShowMenu()
{
    LCDWriteStringXYCLEAR(0, 0, g_menu.items[g_menu.index].name);
    LCDWriteIntXY(4, 0, g_menu.items[g_menu.index].value, 3);
}
void ClearMenu()
{
    LCDWriteStringXYCLEAR(0, 0, "");
}
void SaveMenuItem(uint8_t item)
{
    eeprom_write(item, g_menu.items[item].value);
}
uint8_t LoadMenuItem(uint8_t item)
{
    g_menu.items[item].value = eeprom_read(item);
}
void MenuUp()
{
    if(g_menu.index == 0)
    {
        g_menu.index = MAX_MENUITEM - 1;
    }
    else
    {
        g_menu.index--;
    }
}
void MenuDown()
{
    if(g_menu.index == MAX_MENUITEM - 1)
    {
        g_menu.index = 0;
    }
    else
    {
        g_menu.index++;
    }
}
void ValueInc()
{
    g_menu.items[g_menu.index].value++;
    SAVE_CUR_MENU_ITEM;
}
void ValueDec()
{
    g_menu.items[g_menu.index].value--;
    SAVE_CUR_MENU_ITEM;
}