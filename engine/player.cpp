#include "engine.h"
#include "player.h"

player::player(){
  return;
}

player::~player(){
  return;
}

local_p :: local_p(std::string _nickname){
  nickname = _nickname;
  for(unsigned int i = 0; i < _default_bindings.size(); i++)
    control_scheme.push_back(_default_bindings[i]);
  return;
}

local_p :: ~local_p(){
  return;
}

int player :: get_ping(){
  return 0;
}

int local_p :: get_ping(){
  return 0;
}
