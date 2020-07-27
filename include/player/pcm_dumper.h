//Copyright (c) 2020 Rui Chen
#ifndef PCM_DUMPER_H
#define PCM_DUMPER_H

#include "player.h"

#include <fcntl.h>
#include <unistd.h>

class PcmDumper : public Player{
public:
  PcmDumper(char const fileName[]);
  ~PcmDumper() override;
  void play() override;
  void callBack(void* buffer, int bufferSize, int outSamples) override;
private:
  int fp;
};

#endif
