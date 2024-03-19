#include "pbar.h"

pbar_t* pbar_create(int iters){
    pbar_t* pbar = malloc(sizeof(pbar_t));
    pbar->length = iters;
    pbar->ticks = 0;
    pbar->blocks = 0;

    // assume window is fixed after running program
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    int pbar_len = 3 * w.ws_col;
    pbar->str = malloc(sizeof(char) * (pbar_len + 1));
    for(int i = 0; i < pbar_len; i++){
        pbar->str[i] = ' ';
    }
    pbar->str[w.ws_col - 6] = '\0';
    pbar->log_end = w.ws_col - 6;
    pbar->winsize = w.ws_col;
    return pbar;
}

void pbar_tick(pbar_t* pbar){
    char block[] = "\xe2\x96\x88";
    // printf("Number of spaces to fill with blocks: %d\n", pbar->winsize - 6);
    int blockspace = pbar->winsize - 6;
    int percent;
    pbar->ticks++;
    if(pbar->ticks == pbar->length){
        write_blocks(pbar, blockspace, 100);
        printf("\n");
    }else if(pbar->ticks < pbar->length){
        double progress = (double) pbar->ticks / pbar->length;
        int num_blocks = floor(progress * blockspace);
        write_blocks(pbar, num_blocks, round(progress * 100));
    }
}

void write_blocks(pbar_t* pbar, int target_blocks, int progress){
    while(pbar->blocks < target_blocks){
        int idx = 3 * pbar->blocks;
        pbar->str[pbar->log_end] = ' ';
        pbar->str[idx++] = '\xe2';
        pbar->str[idx++] = '\x96';
        pbar->str[idx++] = '\x88';
        pbar->log_end += 2;
        pbar->str[pbar->log_end] = '\0';
        pbar->blocks++;
    }
    printf("\33[2K\r%*d%%|%s|", (int)floor(log10(100) + 1), progress, pbar->str);
    fflush(stdout);
}