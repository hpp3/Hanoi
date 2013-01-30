#include "stack.h"
#include <allegro.h>
#include <iostream>
#include "constants.h"

using namespace std;
extern BITMAP *buffer;
extern int source;

class peg : public Stack {
    private:
        int posx, which;
        
    public:
        peg();
        ~peg();
        void set_which(int w);
        void draw();
        
    
};

