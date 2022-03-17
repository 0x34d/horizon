#include "core.h"

/*** Serialize Data into ProtoBuf
* SerializeToString
* SerializePartialToString
* 
* SerializeToArray
* SerializePartialToArray
*/

struct Image
{
	char header[4];
	int  width;
	int  height;
	char data[10];
};
//Input

std::string Mutate_Serialize(uint8_t* stream){

    TEST test;
    std::string data;

    struct Image input_str;
    std::memcpy(&input_str,stream, sizeof(Image));

    test.Clear();
    test.set_header(input_str.header);
    test.set_width(input_str.width);
    test.set_height(input_str.height);
    test.set_data(input_str.data);

    test.SerializePartialToString(&data);
    return data;
}
