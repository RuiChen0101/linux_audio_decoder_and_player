//Copyright (c) 2020 Rui Chen
#ifndef PLAYER_H
#define PLAYER_H

#include "decoder/decoder.h"

#include <functional>

class Player{
public:
  virtual ~Player();
  void setDecoder(Decoder* decoder);
  virtual void play() = 0;
  virtual void callBack(void* buffer, int bufferSize, int outSamples) = 0;
protected:
  Decoder* decoder;
};

#endif
