#include <thread>
#include "core/core.h"
#include "main.h"

void CopyData(Handle* handle,run_t* run,uint64_t Seed){
    handle->Seed      = Seed;
    handle->FileSize = run->dynfile->size;
    handle->MaxSize  = run->global->mutate.maxInputSz;
    handle->stream   = (uint8_t*)calloc(handle->MaxSize,sizeof(uint8_t));
    std::memcpy(handle->stream,run->dynfile->data,run->dynfile->size);
}

void ProtoMutate(Handle* handle){
    std::string parse;
    parse = Mutate_Serialize(handle->stream);
    Mutate_DeSerialize(handle,parse);
}

void SaveData(Handle* handle,run_t* run,size_t MaxSize){
    run->dynfile->size =  handle->FileSize;
    run->global->mutate.maxInputSz = MaxSize;
    std::memcpy(run->dynfile->data,handle->stream,run->dynfile->size);
}

void FreeHandle(Handle* handle){
    free(handle->stream);
    free(handle);
}

void MutateCall(run_t* run, uint64_t Seed){
    Handle* handle    = (Handle*) malloc(sizeof(Handle));
    size_t MaxSize  = run->global->mutate.maxInputSz;

    CopyData(handle,run,Seed);
    ProtoMutate(handle);
    SaveData(handle,run,MaxSize);

    FreeHandle(handle);
}
