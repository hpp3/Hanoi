#include "peg.h"

void peg::set_which(int w) {
    //this function sets the identity of the peg
    which = w;
    posx = int((which) * (scrx / 3) + scrx/6);
    //posx is the x position of the peg in pixels
}

void peg::draw() {
    rectfill(buffer, posx-scrx/64, scry, posx+scrx/64, int(scry*0.1), \
             which == source ? makecol(255, 89, 23) : makecol(255, 255, 255));
    //draw the peg
    
    int *larray = array();
    // get an array from the stack (linked list), this is an optimization
    
    for (int i = get_length()-1; i >= 0; i--) {
        //loop through all the disks and draw each one
        
        int width = larray[i] * scrx / (8 * num) + scrx/64;
        int color = makecol(255*(larray[i]-1)/num, abs(127-255*(larray[i]-1)/num), \
                            255-255*(larray[i]-1)/num);
        // color is a gradient according to a "sunset" colour scheme
        
        rectfill(buffer, posx-width, scry - (get_length()-(i+1))*disk_height-1, \
                         posx+width, scry - (get_length()-i)*disk_height, color);
        //draw the disk
    }
    delete[] larray;
}

peg::peg() {
    Stack();
}

peg::~peg() {
}
