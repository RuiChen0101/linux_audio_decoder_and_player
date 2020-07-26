#include "player/pcm_dumper.h"

PcmDumper::PcmDumper(char const fileName[]){
  fp = open(fileName, O_WRONLY|O_CREAT);
}

PcmDumper::~PcmDumper(){
  close(fp);
}

void PcmDumper::play(){
  decoder->decode(512, [&](void* buffer, int bufferSize){
    this->callBack(buffer, bufferSize);
  });
}

void PcmDumper::callBack(void* buffer, int bufferSize){
  write(fp, buffer, bufferSize);
}