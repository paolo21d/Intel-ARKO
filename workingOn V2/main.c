#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

ALLEGRO_EVENT_QUEUE * kolejka;
ALLEGRO_EVENT event;
ALLEGRO_DISPLAY * okno;
ALLEGRO_BITMAP * bmp;

void refactorImage(int param, int option) {
    int width = al_get_bitmap_width(bmp);
    int height = al_get_bitmap_height(bmp);
    int pixelQuantity = width*height;
    printf("PIXEL QUANTITY: %d * %d = %d\n", width, height, pixelQuantity);
    
    ALLEGRO_LOCKED_REGION *locked_region = al_lock_bitmap(bmp, al_get_bitmap_format(bmp), ALLEGRO_LOCK_READWRITE);
    if(!locked_region) {
        al_destroy_bitmap(bmp);
        al_destroy_event_queue(kolejka);
        al_destroy_display(okno);
        exit(4);
    }
    //func(locked_region->data, width, height, param, option); //funkcja asemblerowa

    char * imgData = locked_region->data;
    if(imgData == NULL){
        printf("ERROR LOCK DATA\n");
        al_unlock_bitmap(bmp);
        return;
    }
    for(int i=0; i<pixelQuantity; ++i){
        printf("%d %hi\t", i, *imgData);
        *imgData = 0;
        imgData++;
    }

    al_unlock_bitmap(bmp);
}

int main()
{
	kolejka = NULL;
    int option=0;
    int param = 0;

    al_init();
    al_init_image_addon();
    al_install_keyboard();
    kolejka = al_create_event_queue();
    
    
    okno  = al_create_display( 150, 150 );
    bmp = al_load_bitmap( "g.bmp" );
    if(!bmp) printf("LOAD FAIL!!\n");
    
    printf("W: %d, H: %d, Flags: %d, Format: %d\n", al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), al_get_bitmap_flags(bmp),  al_get_bitmap_format(bmp));
    
    al_register_event_source( kolejka, al_get_display_event_source( okno ) );
    al_register_event_source(kolejka, al_get_keyboard_event_source());
    
    al_clear_to_color( al_map_rgb( 0,0,0 ) );    
    al_draw_bitmap( bmp, 0, 0, 0 );
    al_flip_display();
    
    bool refresh = false;
    
    while(1) {
		al_wait_for_event( kolejka, & event );
		if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
			printf("EXIT click\n");
            break;
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			printf("ESCAPE\n");
			break;
		}else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_UP){
			printf("key UP\n");
			refresh=true;
		}else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_DOWN){
			printf("key DOWN\n");
			refresh=true;
		}else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_LEFT){
			printf("key LEFT\n");
			refresh=true;
		}else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
			printf("key RIGHT\n");
			refresh=true;
		}else if(event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_R){
			printf("refresh\n");
			refresh=true;

            al_destroy_bitmap( bmp );
            bmp = al_load_bitmap( "g.bmp" );
		}	
		
		if(refresh){ //napisac wyswietlenie obrazka tutaj na nowo
			refactorImage(param, option);
            al_flip_display();
			refresh=false;
		}	
	}
    
    //al_rest( 2 );
    
    al_destroy_display( okno );
    al_destroy_bitmap( bmp );
    al_destroy_event_queue( kolejka );
    return 0;
}
