#ifndef LOCAL_SINGLETONS_H
#define LOCAL_SINGLETONS_H

#include "game/Singleton.h"
#include "game/EventManager.h"
#include "game/ResourceManager.h"

namespace huaca {

  extern game::Singleton<game::EventManager> gEventManager;
  extern game::Singleton<game::ResourceManager> gResourceManager;

}

#endif // LOCAL_SINGLETONS_H
