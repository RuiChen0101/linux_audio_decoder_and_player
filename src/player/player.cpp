//Copyright (c) 2020 Rui Chen
#include "player/player.h"

Player::~Player(){}

void Player::setDecoder(Decoder* decoder){
  this->decoder = decoder;
}