#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>

#include "func.h"
int main()

{
    allegro_init();
    install_keyboard();
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 150, 150, 0, 0 );
    PALETTE palette;
    BITMAP * pic = load_bmp("test.bmp", palette); //load_bmp
    if( !pic)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("error!");
        allegro_exit();
        return 1;
    }

    //clear_to_color (pic,makecol(0,0,0));


    blit(pic, screen, 0, 0, 0, 0, pic->w, pic->h);
    
    while(!key[ KEY_ESC ])
    {
        
        
        //bezier(pic->line,pic->w,pic->h,x,y);
        blit(pic, screen, 0, 0, 0, 0, pic->w, pic->h);

        readkey();
    }
    destroy_bitmap(pic);
    allegro_exit();
    return 0;
}
