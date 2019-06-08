#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include "func.h"
BITMAP * pic;
void refactor(){
    acquire_bitmap(pic);
    unsigned char * imgData = pic->line;
    int width = pic->w;
    int height = pic->h;
    unsigned short red, green, blue;

    /*for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            blue = (short) *imgData;
            blue &= 0xff;
            green = (short) *(imgData+1);
            green &= 0xff;
            red = (short) *(imgData+2);
            red &= 0xff;
            printf("H:%d W:%d; R%hi G%hi B%hi \n", i, j, red, green, blue);
            imgData+=3;
        }
        imgData += width%4;
    }*/

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
           // blue = (short) *imgData;      
           // blue &= 0xff;
           // green = (short) *(imgData+1);
           // green &= 0xff;
           // red = (short) *(imgData+2);
           // red &= 0xff;
           // printf("H:%d W:%d; R%hi G%hi B%hi \n", i, j, red, green, blue);
           //int p = getpixel(pic, j, i);
           int p = pic->line[i][j];
           //printf("H:%d W:%d; P %d\n", i, j, p);
           printf("H:%d W:%d; R%d G%d B%d \n", i, j, getr(p), getg(p), getb(p));
        }
    }
    release_bitmap(pic);
}
int main() {
    if(init()==-1) {
        return -1;
    }    
    //clear_to_color (pic,makecol(0,0,0));
    blit(pic, screen, 0, 0, 0, 0, pic->w, pic->h);
    
    while(!key[ KEY_ESC ]) {
        if( key [ KEY_DOWN ] ) {
            refactor();
            printf("After refactor\n");
            blit(pic, screen, 0, 0, 0, 0, pic->w, pic->h);
        }
        
        //bezier(pic->line,pic->w,pic->h,x,y);
        //blit(pic, screen, 0, 0, 0, 0, pic->w, pic->h);
        readkey();
    }
    destroy_bitmap(pic);
    allegro_exit();
    return 0;
}

int init(){
    allegro_init();
    install_keyboard();
    set_color_depth( 24 );
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 150, 150, 0, 0 );
    //set_color_conversion( COLORCONV_NONE );
    //printf("%d\n", get_color_conversion());
    PALETTE palette;
    pic = load_bitmap("redPaint.bmp", palette); //load_bmp
    if( !pic)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("error!");
        allegro_exit();
        return -1;
    }
    printf("W: %d, H: %d \n", pic->w, pic->h);
    return 0;
}