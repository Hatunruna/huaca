#ifndef LOCAL_TIMER_H
#define LOCAL_TIMER_H

#include "game/Entity.h"

namespace huaca {

  class Timer : public game::Entity {
  public:
    Timer(float time);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    float m_totalTime;
    float m_remainingTime;
  };


}


#endif // LOCAL_TIMER_H
