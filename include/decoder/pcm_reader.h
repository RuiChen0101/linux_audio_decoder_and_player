//Copyright (c) 2020 Rui Chen
#ifndef PCM_READER_H
#define PCM_READER_H

#include "decoder.h"

#include <fcntl.h>
#include <unistd.h>

class PcmReader : public Decoder{
public:
  PcmReader(int, int);
  ~PcmReader() override;
  void openFile(char const fileName[]) override;
  void release() override;
  void decode(int samples, std::function<void(void*, int, int)> callback) override;
private:
  int channels;
  int unitSize;
  int fp;
};

#endif
