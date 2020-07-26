#include "decoder/decoder.h"

Decoder::~Decoder(){}

bool Decoder::finished() const{
  return isFinished;
}