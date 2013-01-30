#include <string>
#include <cstdlib>
#include "peg.h"
#include "constants.h"

extern BITMAP *buffer;
extern BITMAP *erase;

class Game {
    private:
        peg t[3];
        int where_is[num];
        int moves, calls;
         
    public:
        Game(int n_disks);
        ~Game();
        void move_stack(int src, int dst, int n);
        void move(int src, int dst);
        bool step(int n, int dst);
        void solve(int n, int dst);
        void draw();
        void drawdelta(int src, int dst);
};


