//Copyright (c) 2020 Rui Chen
#ifndef FFMPEG_DECODER_H
#define FFMPEG_DECODER_H

#include "decoder.h"

#include <iostream>
#include <unistd.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
}

class FFmpegDecoder : public Decoder{
public:
  FFmpegDecoder(int channels, AVSampleFormat sampleFormat, int sampleRate);
  ~FFmpegDecoder() override;
  void openFile(char const fileName[]) override;
  void release() override;
  void decode(int samples, std::function<void(void*, int, int)> callback) override;
private:
  AVFormatContext* formatCtx = nullptr;
  AVCodecContext* codecCtx = nullptr;
  SwrContext* swrCtx = nullptr;
  int channels;
  int sampleRate;
  AVSampleFormat sampleFormat;
  int channelLayout;
  int audioStream = 0;
};

#endif
