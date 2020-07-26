#include <iostream>
#include "decoder/ffmpeg_decoder.h"
#include "player/alsa_player.h"

int main(int argc, char* argv[]){
  if(argc != 2){
    std::cout << " usage: " << argv[0] << " input_file" << std::endl;
  }
  FFmpegDecoder decoder(2, AV_SAMPLE_FMT_S16, 44100);
  decoder.open(argv[1]);
  AlsaPlayer player(2, SND_PCM_FORMAT_S16_LE, 44100);
  player.setDecoder(&decoder);
  player.play();
  return 0;
}
