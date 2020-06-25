/* Abstract class for events to be sent to the client/server.*/

#include <cereal/types/base_class.hpp>
#include <cereal/types/vector.hpp>

#ifndef ABSTRACTEVENT_HPP

#define ABSTRACTEVENT_HPP


enum EventType{
  EVENT_JOIN,
  EVENT_MESSAGE,
  EVENT_QUERY,
  EVENT_INFO,
  EVENT_MOVE,
  EVENT_CREATE,
  EVENT_DESTROY,
  EVENT_SYNC,
  EVENT_NEWGAME,
  EVENT_COMMAND,
  EVENT_ERROR,
  EVENT_ACCEPT
};



class AbstractEvent{
public:
  virtual int getType() const = 0;

  /** For printing displaying printing debug messages mainly */
  virtual std::string output(){return "";};

  /* This is required for cereal */
  template <class Archive>
  void serialize(Archive&){}
};

#endif
