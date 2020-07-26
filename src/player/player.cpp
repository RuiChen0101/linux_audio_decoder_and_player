#include "player/player.h"

Player::~Player(){}

void Player::setDecoder(Decoder* decoder){
  this->decoder = decoder;
}