#include "decoder/decoder.h"

Decoder::~Decoder(){}

void Decoder::setOutputBufferSize(int size){
  outputBufferSize = size;
}