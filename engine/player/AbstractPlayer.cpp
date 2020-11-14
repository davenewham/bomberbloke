#include "AbstractPlayer.hpp"
#include "actor.hpp"
#include "engine.hpp"
#include "GamePlayerProperties.hpp"

AbstractPlayer::AbstractPlayer(std::string _nickname){
  mNickname = _nickname;
  return;
}

void AbstractPlayer::setCharacter(std::shared_ptr<actor> a){
  mpCharacter = a;
}

void AbstractPlayer::setId(int id){
  mId = id;
  for(auto i = _pScene->mActors.begin(); i != _pScene->mActors.end(); i++){
    if((*i)->getId() == id){
      mpCharacter = *i;
      return;
    }
  }
}

void AbstractPlayer::resetPlayerProperties(std::shared_ptr<AbstractPlayerProperties> p_properties){
  if(mpProperties){
     /*  TODO: send EVENT_PROPERTIES message to the relevant player */
     mpProperties->reset(p_properties);
   }
   else
     mpProperties = std::make_shared<GamePlayerProperties>();
}
