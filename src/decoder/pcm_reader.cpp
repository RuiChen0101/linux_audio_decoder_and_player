//Copyright (c) 2020 Rui Chen
#include "decoder/pcm_reader.h"

PcmReader::PcmReader(int channels, int unitSize):
channels(channels), unitSize(unitSize){}

PcmReader::~PcmReader(){
  release();
}

void PcmReader::openFile(char const fileName[]){
  fp = open(fileName, O_RDONLY);
}

void PcmReader::release(){
  close(fp);
}

void PcmReader::decode(int samples, std::function<void(void*, int, int)> callback){
  int bufferSize = samples * channels * unitSize;
  void* buffer = malloc(bufferSize);
  while(read(fp, buffer, bufferSize) > 0){
    callback(buffer, bufferSize, samples);
  }
  free(buffer);
  isFinished = true;
}
