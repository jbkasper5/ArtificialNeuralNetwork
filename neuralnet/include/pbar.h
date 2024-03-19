#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pbar_s pbar_t;

struct pbar_s{
    int length;     // progress bar length
    int ticks;      // number of ticks (<= length)
    int blocks;     // number of blocks written to str
    char* str;      // maintains the concurrent str for io display
    int log_end;    // logical end to the string
    int winsize;    // number of characters in the output space (terminal window)
};

pbar_t* pbar_create(int iters);
void pbar_destroy(pbar_t* pbar);
void pbar_tick(pbar_t* pbar);
void write_blocks(pbar_t* pbar, int target_blocks, int progress);