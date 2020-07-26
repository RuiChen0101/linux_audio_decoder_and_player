#include "decoder/ffmpeg_decoder.h"

FFmpegDecoder::FFmpegDecoder(int channels, AVSampleFormat sampleFormat, int sampleRate):
sampleFormat(sampleFormat), sampleRate(sampleRate), channels(channels){
  if(channels == 1){
    this->channelLayout = AV_CH_LAYOUT_MONO;
  }else if(channels == 2){
    this->channelLayout = AV_CH_LAYOUT_STEREO;
  }else{
    throw(std::runtime_error("FFmpegDecoder error: channels only accept 1(MONO) or 2(STEREO)"));
  }
}

FFmpegDecoder::~FFmpegDecoder(){
  release();
}

void FFmpegDecoder::open(char* const fileName){
  av_register_all();
  if(avformat_open_input(&formatCtx, fileName, NULL, NULL) < 0){
    throw(std::runtime_error("FFmpegDecoder error: avformat_open_input()"));
  }
  if(avformat_find_stream_info(formatCtx, NULL) < 0){
    throw(std::runtime_error("FFmpegDecoder error: avformat_find_stream_info()"));
  }
  // std::cout<<LIBAVFORMAT_VERSION_INT<<" "<<avformat_version()<<std::endl;
  AVCodec *codec = nullptr;
  AVCodecParameters *codecParameters =  nullptr;
  for(int i=0 ; i < formatCtx->nb_streams ; i++){
    codecParameters = formatCtx->streams[i]->codecpar;
    if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO){
      audioStream = i;
      codec = avcodec_find_decoder(codecParameters->codec_id);
      if(!codec){
        throw(std::runtime_error("FFmpegDecoder error: codec not support"));
      }
      break;
    }
  }
  codecCtx = avcodec_alloc_context3(codec);
  if(!codecCtx){
    throw(std::runtime_error("FFmpegDecoder error: AVCodecContext alloc fail"));
  }

  if(avcodec_parameters_to_context(codecCtx, codecParameters) < 0){
    throw(std::runtime_error("FFmpegDecoder error: avcodec_parameters_to_context()"));
  }

  if (codecCtx->channel_layout == 0) {
    codecCtx->channel_layout = AV_CH_LAYOUT_STEREO;
  }

  if (avcodec_open2(codecCtx, codec, NULL) < 0){
    throw(std::runtime_error("FFmpegDecoder error: avcodec_parameters_to_context()"));
  }

  // std::cout<<codecContext->channel_layout<<std::endl;
  // std::cout<<codecContext->sample_fmt<<std::endl;
  // std::cout<<codecContext->sample_rate<<std::endl;

  swrCtx = swr_alloc_set_opts(NULL,
            channelLayout,
            sampleFormat,
            sampleRate,
            codecCtx->channel_layout,
            codecCtx->sample_fmt,
            codecCtx->sample_rate,
            0,
            NULL);
  if (!swrCtx) {
    throw(std::runtime_error("FFmpegDecoder error: Swresampler alloc fail"));
  }
  swr_init(swrCtx);
}

void FFmpegDecoder::decode(int samples, std::function<void(void*, int)> callback){
  int maxbufferSize = av_samples_get_buffer_size(NULL, codecCtx->channels, samples, codecCtx->sample_fmt, 1);
  std::cout << maxbufferSize << std::endl;
  AVPacket* packet = av_packet_alloc();
  AVFrame* frame = av_frame_alloc();
  if(packet == NULL || frame == NULL){
    throw(std::runtime_error("FFmpegDecoder error: packet or frame alloc fail"));
  }
  uint8_t* buffer = (uint8_t*)av_malloc(maxbufferSize);
  while (av_read_frame(formatCtx, packet) >= 0) {
    if (packet->stream_index == audioStream) {
      if(avcodec_send_packet(codecCtx, packet) < 0){
        throw(std::runtime_error("FFmpegDecoder error: avcodec_send_packet"));
      }
      while (avcodec_receive_frame(codecCtx, frame) >= 0){
        int outSamples = swr_convert(swrCtx, &buffer, samples,
                          (uint8_t const **) (frame->data), frame->nb_samples);
        while(outSamples > 0){
          callback(buffer, maxbufferSize);
          outSamples = swr_convert(swrCtx, &buffer, samples, NULL, 0);
        }
        av_frame_unref(frame);
      }
    }
    av_packet_unref(packet);
  }
  av_frame_free(&frame);
  av_packet_free(&packet);
  free(buffer);
  isFinished = true;
}

void FFmpegDecoder::release(){
  avformat_close_input(&formatCtx);
  avcodec_free_context(&codecCtx);
  swr_free(&swrCtx);
}