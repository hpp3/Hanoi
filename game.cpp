#include "game.h"

Game::Game(int n_disks) {
    moves = calls = 0;
    for (int i = 0; i<3; i++)
        t[i].set_which(i);
        // assign the pegs their identities
        
    for (;n_disks>0;n_disks--)  {  
        t[0].push(n_disks);
        // add all the disks to the first peg
        where_is[n_disks-1]=0;
        // where is [any disk]? it's on the first peg
    }
}

Game::~Game() {
}

void Game::move(int src, int dst) {
    //moves the top disk of the source peg to the destination peg
    
    if (src == dst) return;
    // don't need to move disk from peg to the same peg
    
    if (!t[src].get_length() || \
        // don't move if: a) no disk to move or 
        t[dst].get_length() && t[src].top() > t[dst].top()) 
        //b)there is a smaller disk in the destination
            return;
    
    moves++;
    int which = t[src].top();
    t[dst].push(which);
    t[src].pop();
    //move the disk
    
    where_is[which-1]=dst;
    //update the index of where the disk currently is
}


// algorithm gallery: the next 3 functions are all algorithms that were at some
// point used to solve Hanoi


// this is the classic Hanoi solution, included for historical purposes only
void Game::move_stack(int src, int dst, int n) {
    //move a stack that has a base of size n from src to dst
    
    if (!n||keypressed()) return;
    // if we have to move a stack of zero disks, don't; also allow interruption
    
    move_stack(src, 3-src-dst, n-1);
    //move the stack with base n-1 to the other peg
    
    move(src, dst);
    //move the disk of size n
    
    move_stack(3-src-dst, dst, n-1);
    //move the stack with base n-1 to the destination
    moves++;
}


// this is a variation of the classic solution; it can find an optimal solution
// even after the user has tampered with the position of the disks
// this is the preferred algorithm.
void Game::solve(int n, int dst) {
    //move the stack that has a base of size n to dst
    calls++;

    if (!n||keypressed()) return;
    // if we have to move a stack of zero disks, don't; also allow interruption
    
    if (where_is[n-1]==dst)
        solve(n-1, dst);  
        //if the base disk is already at the destination
        //then move the stack w/ base size n-1 onto it     
    else {
        solve(n-1, 3-dst-where_is[n-1]);
        //move stack of size n-1 to other peg
        
        int src = where_is[n-1];
        move(src, dst);
        //move base disk to destination
        
        drawdelta(src, dst);
        //redraw
        
        solve(n-1, dst);
        //now move the stack of size n-1 to the destination
    }    
}


// this version of the above algorithm stops after moving a single disk
// it is less efficient, but provides the user with more flexibility
bool Game::step(int n, int dst) {
    // step(n, dst) tries to move the stack with base size n to peg dst 
    // return true if a disk was moved
    calls++;
    
    if (!n) return false;
    //if we need to move disk 0, then don't
    
    if (where_is[n-1]==dst)
        return step(n-1, dst);   
        //if the base w/ size n is already at the destination
        //then move the stack w/ base size n-1 onto it
    
    else {
        //otherwise move the stack with base size n-1 to the other peg
        if (!step(n-1, 3-dst-where_is[n-1])) {
            //then move the disk w/ size n to the destination peg
            
            int src = where_is[n-1];
            move(where_is[n-1], dst);
            
            drawdelta(src, dst);
            //redraw
        }
        return true;
    }    
}



void Game::draw() {
    // draws everything; used to initialize the game
    
    rectfill(buffer, 0, 0, scrx, scry, makecol(0,0,0));
    // draw the background
    
    textprintf_ex(buffer, font, 10, 10, makecol(255, 255 , 255), \
                  -1, "Moves: %d", moves);
    textprintf_ex(buffer, font, 130, 10, makecol(255, 255, 255), \
                  -1, "Calls: %d", calls);
    textprintf_ex(buffer, font, 10, 30, makecol(255, 255, 255), \
                  -1, "ESC -> Quit     1, 2, 3 -> Manual Control");
    textprintf_ex(buffer, font, 10, 45, makecol(255, 255, 255), \
                  -1, "Tab -> Solve once     o -> Fully solve");
    
    for (int i=0; i < 3; i++) 
        t[i].draw();
        //make each peg draw itself
            
    blit(buffer, screen, 0, 0, 0, 0, scrx, scry);
    //draw buffer to screen
}

void Game::drawdelta(int src, int dst) {
    // a disk has just been moved from src to dst
    // this function redraws the necessary parts of the screen
    
    // we don't need to update these counters every frame...
    // so update every ninth frame
    if (! (moves % 9)) {
        rectfill(buffer, 0, 0, 300, 20, makecol(0, 0, 0));
        //cover up old text
        
        textprintf_ex(buffer, font, 10, 10, makecol(255, 255 , 255), \
                      -1, "Moves: %d", moves);
        textprintf_ex(buffer, font, 130, 10, makecol(255, 255, 255), \
		    -1, "Calls: %d", calls);
    }
    rectfill(buffer, src*scrx/3, int(0.1*scry), (src+1)*scrx/3, scry, makecol(0,0,0));
    // draw over the source tower to erase it 
    
    //redraw both the source and destination towers
    t[src].draw();
    t[dst].draw();
    
    blit(buffer, screen, 0, 0, 0, 0, scrx, scry);
    return;
}

