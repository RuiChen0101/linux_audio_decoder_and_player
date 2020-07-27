//Copyright (c) 2020 Rui Chen
#include "player/alsa_player.h"

AlsaPlayer::AlsaPlayer(int channels, snd_pcm_format_t sampleFormat, int sampleRate, char const device[]){
  if(snd_pcm_open(&pcm, device, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
    throw(std::runtime_error("AlsaPlayer error: snd_pcm_open"));
  }
  if (snd_pcm_set_params(pcm, sampleFormat,
      SND_PCM_ACCESS_RW_INTERLEAVED, channels,
      sampleRate, 0, sampleRate / 4) < 0) {
    throw(std::runtime_error("AlsaPlayer error: snd_pcm_set_params"));
  }
  snd_pcm_uframes_t bufferSize = 0;
  if (snd_pcm_get_params(pcm, &bufferSize, &periodSize) < 0) {
    throw(std::runtime_error("AlsaPlayer error: snd_pcm_get_params"));
  }
}

AlsaPlayer::~AlsaPlayer(){
  snd_pcm_drain(pcm);
  snd_pcm_close(pcm);
}

void AlsaPlayer::play(){
  decoder->decode(periodSize, [&](void* buffer, int bufferSize, int outSamples){
    this->callBack(buffer, bufferSize, outSamples);
  });
}

void AlsaPlayer::callBack(void* buffer, int bufferSize, int outSamples){
  int ret = snd_pcm_writei(pcm, buffer, outSamples);

  if (ret < 0) {
    if ((ret = snd_pcm_recover(pcm, ret, 1)) == 0) {
      std::cout << "AlsaPlayer: recovered after xrun (overrun/underrun)" <<std::endl;
    }
  }
}