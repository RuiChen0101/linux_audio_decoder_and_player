//Copyright (c) 2020 Rui Chen
#ifndef DECODER_H
#define DECODER_H

#include <functional>

class Decoder{
public:
  virtual ~Decoder();
  virtual void openFile(char const fileName[]) = 0;
  virtual void release() = 0;
  virtual void decode(int samples, std::function<void(void*, int, int)> callback) = 0;
  bool finished() const;
protected:
  bool isFinished = false;
};

#endif
