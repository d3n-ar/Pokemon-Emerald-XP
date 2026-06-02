#include "global.h"
#include "rtc.h"
#include "palette.h"
#include "task.h"
#include "fieldmap.h"
#include "constants/map_types.h"
#include "constants/rgb.h"







void TintPalette_Night(u16 *buffer, u16 size)

{

    u16 i;
    u16 color;
    int r, g, b;

    for (i = 16; i < size; i++)

    {     

        if ((i % 16) == 0) continue;

        color = buffer[i];
       
        r = color & 0x1F;

        g = (color >> 5) & 0x1F;

        b = (color >> 10) & 0x1F;



        // Apply a fixed, non-relative tint
        // These constants are "hardcoded" to a blueish-night shade

        r = (r * 4) / 15;

        g = (g * 4) / 15;

        b = (b * 10) / 15;



        // Clamp the values

        if (r > 7) r = 7;

        if (g > 8) g = 8;

        if (b > 12) b = 12;

       

        buffer[i] = (r) | (g << 5) | (b << 10);

    }

}




void Task_NightCycle(u8 taskId)
{
    // 1. Declare variables at the top
    bool8 canTint;
    u8 prevState = gTasks[taskId].data[1]; // Store previous state

    // 2. Input Handling
    if (!gPaletteFade.active)
    {
        if (gMain.newKeys & R_BUTTON)
            gTasks[taskId].data[1] = 1; // Set to Night
        
        if (gMain.newKeys & L_BUTTON)
            gTasks[taskId].data[1] = 0; // Set to Day
    }

    // 3. Logic check
    canTint = (gMapHeader.mapType == MAP_TYPE_TOWN || 
               gMapHeader.mapType == MAP_TYPE_ROUTE || 
               gMapHeader.mapType == MAP_TYPE_UNDERGROUND);

    // 4. ONLY update if the state has changed
    if (gTasks[taskId].data[1] != prevState)
    {  
         if (gTasks[taskId].data[1] == 1 && canTint)
        {
            // Apply Night
            CpuCopy16(gPlttBufferUnfaded, gPlttBufferFaded, 0x700 * 2);
            TintPalette_Night(gPlttBufferFaded, 0x700);
            LoadPalette(gPlttBufferFaded, 0, 0x700 * 2);
        }
      else if (gTasks[taskId].data[1] == 0) // Specifically check for day state
        {
           // Apply Day (Restore original)
           LoadPalette(gPlttBufferUnfaded, 0, 0x700 * 2);
        }
       
    }
}
