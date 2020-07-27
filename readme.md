# linux_audio_decoder_and_player

This is a small linux audio playback example using FFmpeg and alsa.

## Compilation

This project use cmake to compil, make sure you have FFmpeg/libav and libasound
installed. Default c++ version is c++17 but I think th other version would
work fine.

```
cmake .
make
build/decode_and_play {path_to_audio_file}
```

## Classes

**Decoder**
- PcmReader: read pcm data from the file and pass data to player.
- FFmpegDecoder: decode audio file and output pcm data to player.

**Player**
- PcmDumper: Dump pcm data from the decoder to file.
- AlsaPlayer: Play pcm data using alsa interface.


## Tested format
- wav
- mp3
- m4a
- aiff

## License
This library is released under the MIT License. All included dependencies have been released under identical or similarly permissive licenses.
Please note though that FFmpeg, which you will need to build this library, is not released under MIT License. Depending on how you build it, it is either LGPL or GPL. So if you use the GPL-version of FFmpeg in your project, this library will be GPL too.
