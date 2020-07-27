//Copyright (c) 2020 Rui Chen
#include "decoder/decoder.h"

Decoder::~Decoder(){}

bool Decoder::finished() const{
  return isFinished;
}