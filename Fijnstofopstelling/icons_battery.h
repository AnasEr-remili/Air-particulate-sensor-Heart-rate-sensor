// Bevat de batterij icons en de nodige gegevens om deze te weergeven op de correcte positie op de display.


#include <Pangodream_18650_CL.h>
#include "battery_01.h"
#include "battery_02.h"
#include "battery_03.h"
#include "battery_04.h"
#include "battery_05.h"
int battery_01Width = 70;
int battery_01Height = 36;
int battery_02Width = 70;
int battery_02Height = 36;
int battery_03Width = 70;
int battery_03Height = 36;
int battery_04Width = 70;
int battery_04Height = 36;
int battery_05Width = 70;
int battery_05Height = 36;
#define ICON_WIDTH 70
#define ICON_HEIGHT 36
#define STATUS_HEIGHT_BAR ICON_HEIGHT
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define ICON_POS_X (tft.width() - ICON_WIDTH)
