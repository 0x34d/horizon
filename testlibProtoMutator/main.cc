#include <bits/stdc++.h>
#include <iostream>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "honggfuzz.h"
#include "libProtoMutator/main.h"

/*
*DEF
*/

#define MAX_SIZE 10240


/*
* Pareser
run->dynfile->size
run->dynfile->data
run->global->mutate.maxInputSz
*/

void parse(char *file){
    FILE*               infile;
    honggfuzz_t         global;
    struct _dynfile_t   dynfile;
    run_t *run = (run_t*)malloc(sizeof(run_t));

    run->dynfile = &dynfile;
    run->global = &global;
    run->global->mutate.maxInputSz = MAX_SIZE;

    infile = fopen(file,"rb");

    fseek(infile, 0L, SEEK_END);    // Get the number of bytes
    run->dynfile->size = ftell(infile);
    fseek(infile, 0L, SEEK_SET);    //reset the file position indicator to the beginning of the file

    run->dynfile->data = (uint8_t*)malloc(run->global->mutate.maxInputSz);
    fread(run->dynfile->data, sizeof(uint8_t), run->dynfile->size, infile);

    MutateCall(run,0);

    fclose(infile);
    free(run->dynfile->data);
    free(run);

}


int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Phz input a file");
        return 0;
    }else{
        parse(argv[1]);
        return 0;
    }
}