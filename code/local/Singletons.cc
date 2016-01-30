#include "Singletons.h"

namespace huaca {

  game::Singleton<game::EventManager> gEventManager;
  game::Singleton<game::ResourceManager> gResourceManager;
  game::Singleton<game::WindowGeometry> gWindowGeometry;

}
