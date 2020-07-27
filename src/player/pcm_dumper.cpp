//Copyright (c) 2020 Rui Chen
#include "player/pcm_dumper.h"

PcmDumper::PcmDumper(char const fileName[]){
  fp = open(fileName, O_WRONLY|O_CREAT);
}

PcmDumper::~PcmDumper(){
  close(fp);
}

void PcmDumper::play(){
  decoder->decode(512, [&](void* buffer, int bufferSize, int outSamples){
    this->callBack(buffer, bufferSize, outSamples);
  });
}

void PcmDumper::callBack(void* buffer, int bufferSize, int outSamples){
  write(fp, buffer, bufferSize);
}