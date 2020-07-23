#ifndef FFMPEG_DECODER_H
#define FFMPEG_DECODER_H

#include "decoder.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
}

class FFmpegDecoder : public Decoder{
public:
  FFmpegDecoder(int, AVSampleFormat, int);
  ~FFmpegDecoder() override;
  void open(char* const) override;
  void setOutputBufferSize(int) override;
  void* getSample() override;
  bool finished() override;
  void release() override;
private:
  bool getPacket();
  bool getFrameAndFillBuffer();
  AVFormatContext* formatCtx = nullptr;
  AVCodecContext* codecCtx = nullptr;
  SwrContext* swrCtx = nullptr;
  AVPacket* packet = nullptr;
  uint8_t* buffer = nullptr;
  AVFrame* frame = nullptr;
  int channels;
  int sampleRate;
  AVSampleFormat sampleFormat;
  int channelLayout;
  int audioStream = 0;
};

#endif