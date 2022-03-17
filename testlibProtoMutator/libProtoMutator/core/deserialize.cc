#include "core.h"
#include "mutator/override_mutator.h"

/*
* Register and init of Mutator
*/

char value[4] = {0x49, 0x4D, 0x47, 0x00};

void Register_init(Mutator *mutator,uint64_t seed){

    mutator->RegisterPostProcessor(
        TEST::descriptor(),
        [](google::protobuf::Message* message, unsigned int seed) {
            TEST *t = static_cast<TEST *>(message);
            t->set_header(value);
        });
    //srand(seed);
}

/*
*   Convert Proto mutated data into Raw Data;
*/

std::string ProtoToData(const TEST &test_proto) {
    std::stringstream all;

    const auto &aa = test_proto.header();
    const auto &bb = test_proto.width();
    const auto &cc = test_proto.height();
    const auto &dd = test_proto.data();

    if(aa.size() != 0) {
        all.write(aa.c_str(), aa.size());
    }

    all.write((const char*)&bb, sizeof(bb));
    all.write((const char*)&cc, sizeof(cc));

    if(dd.size() != 0) {
        all.write(dd.c_str(), dd.size());
    }

    std::string res = all.str();
    return res;
}


/*
* Check ProtoBuf and Data if the work;
* Mutate ProtoBuf
* Memcpy the data into input;
*
* ParseFromString
* ParsePartialFromString
* ParseFromArray
* ParsePartialFromArray
*/

void Mutate_Proto(Mutator *mutator, Handle* handle, std::string data){

    TEST input;
    bool parse_ok = input.ParsePartialFromString(data);    //init the data into Protobuf
    if(!parse_ok) {
        printf("change the data of IO");
        exit(1);
    }

    mutator->Seed(handle->Seed);
    mutator->Mutate(&input, handle->MaxSize);         

    const TEST *p = &input;
    std::string save = ProtoToData(*p);

    size_t mutated_size = save.size() <= handle->MaxSize ? save.size() : handle->MaxSize; // check if raw data's size is larger than max_size

    memcpy(handle->stream,save.c_str(),mutated_size);
    handle->FileSize = mutated_size;
}

/* 
* Get data
* Get Seed
* Get input
*/

void Mutate_DeSerialize(Handle* handle, std::string data){
    Mutator *mutator = new Mutator();
    Register_init(mutator,handle->Seed);

    Mutate_Proto(mutator,handle,data);        

    delete(mutator);
}


