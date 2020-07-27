//Copyright (c) 2020 Rui Chen
#ifndef ALSA_PLAYER_H
#define ALSA_PLAYER_H

#include "player.h"

#include <iostream>
#include <alsa/asoundlib.h>

class AlsaPlayer : public Player{
public:
  AlsaPlayer(int channels, snd_pcm_format_t sampleFormat, int sampleRate, char const device[] = "default");
  ~AlsaPlayer() override;
  void play() override;
  void callBack(void* buffer, int bufferSize, int outSamples) override;
private:
  snd_pcm_t* pcm = nullptr;
  snd_pcm_uframes_t periodSize;
};

#endif