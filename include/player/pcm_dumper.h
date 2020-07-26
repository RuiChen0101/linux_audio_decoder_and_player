#ifndef PCM_DUMPER_H
#define PCM_DUMPER_H

#include "player.h"

#include <fcntl.h>

#include <alsa/asoundlib.h>

class PcmDumper : public Player{
public:
  PcmDumper(char const fileName[]);
  ~PcmDumper() override;
  void play() override;
  void callBack(void* buffer, int bufferSize) override;
private:
  int fp;
};

#endif