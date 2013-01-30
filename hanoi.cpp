#include "game.h"
#include "constants.h"

BITMAP *buffer = new BITMAP;
int source=-1;


int main(int argc, char *argv[])
{
	allegro_init();                            // Initialize Allegro
	install_keyboard();                        // Initialize keyboard routines
			
	set_color_depth(desktop_color_depth());    // Set the color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, scrx, scry,0,0); 
    Game game(num);
    // initiate a new game
    
    buffer = create_bitmap(scrx, scry);
    // create the bitmap
   
    game.draw(); 
    
    while (!key[KEY_ESC]) {
    //let the user quit with escape
        
        if (key[KEY_1] || key[KEY_2] || key[KEY_3] || \
            key[KEY_1_PAD] || key[KEY_2_PAD] || key[KEY_3_PAD]) {
            //if the user uses a keyboard command to move disks
            
            int which_key = key[KEY_1] || key[KEY_1_PAD] ? 0 : key[KEY_2] || key[KEY_2_PAD] ? 1 : 2;
            // nested ternary operator to figure out which key was pressed
            
            if (source!=-1) {
                // if the source is already known,
                // i.e. the user is inputting the destination
                 game.move(source, which_key);
                 source=-1;
            }
            else source = which_key;
                             
            game.draw(); // ...instead of game.drawdelta(...), since we need to 
                         // redraw the highlighting of the peg anyway
            
        }
        
        if (key[KEY_TAB]) {
        //solve one step
            source = -1;
            game.step(num, 2);
            game.draw();
        }
        if (key[KEY_O]) {
        //autosolve all
            source = -1;
            game.draw();
            game.solve(num, 2);
            game.draw();
        }    
        readkey(); 
        //used to limit the key repeat rate to the OS keyboard repeat rate
    }
    destroy_bitmap(buffer); 
    return 0;
}
END_OF_MAIN()
