#ifndef DECODER_H
#define DECODER_H

class Decoder{
public:
  virtual ~Decoder();
  virtual void open(char* const) = 0;
  virtual void setOutputBufferSize(int);
  virtual void* getSample() = 0;
  virtual bool finished() = 0;
  virtual void release() = 0;
protected:
  int outputBufferSize;
};

#endif
