#include "Timer.h"

#include "Events.h"
#include "Singletons.h"

namespace huaca {

  Timer::Timer(float time)
  : game::Entity(10)
  , m_totalTime(time)
  , m_remainingTime(time)
  {
    gEventManager().registerHandler<NewLevelEvent>(&Timer::onNewLevelEvent, this);
  }

  game::EventStatus Timer::onNewLevelEvent(game::EventType type, game::Event *event) {
    m_remainingTime = m_totalTime;
    return game::EventStatus::KEEP;
  }

  void Timer::update(float dt) {
    m_remainingTime -= dt;

    if (m_remainingTime < 0) {
      ResetLevelEvent event;
      gEventManager().triggerEvent(&event);

      m_remainingTime = m_totalTime;
    }
  }

  static constexpr float WIDGET_WIDTH = 10.0f;
  static constexpr float WIDGET_HEIGHT = 300.0f;
  static constexpr float WIDGET_PADDING = 20.0f;

  void Timer::render(sf::RenderWindow& window) {
    sf::Vector2f totalPos;
    sf::Vector2f remainingPos;

    totalPos.x = gWindowGeometry().getXFromRight(WIDGET_WIDTH + WIDGET_PADDING);
    totalPos.y = gWindowGeometry().getYFromBottom(WIDGET_HEIGHT + WIDGET_PADDING);

    float remainingHeight = m_remainingTime / m_totalTime * WIDGET_HEIGHT;

    remainingPos.x = totalPos.x;
    remainingPos.y = totalPos.y + WIDGET_HEIGHT - remainingHeight;

    sf::RectangleShape totalShape({ WIDGET_WIDTH, WIDGET_HEIGHT });
    totalShape.setPosition(totalPos);
    totalShape.setFillColor(sf::Color(0xFF, 0x00, 0x00, 0x80));
    window.draw(totalShape);

    sf::RectangleShape remainingShape({ WIDGET_WIDTH, remainingHeight });
    remainingShape.setPosition(remainingPos);
    remainingShape.setFillColor(sf::Color::Red);
    window.draw(remainingShape);

  }

}
