/*
 * Copyright (c) 2014-2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <cassert>
#include <cstdio>

#include "game/Action.h"
#include "game/Camera.h"
#include "game/Clock.h"
#include "game/EntityManager.h"
#include "game/Log.h"
#include "game/ResourceManager.h"
#include "game/WindowGeometry.h"
#include "game/WindowSettings.h"

#include "local/Events.h"
#include "local/GroundManager.h"
#include "local/Hero.h"
#include "local/ItemHUD.h"
#include "local/LevelGenerator.h"
#include "local/Singletons.h"
#include "local/Timer.h"
#include "local/WallManager.h"

#include "config.h"

static constexpr float AREA_WIDTH = 640.0f;

int main(int argc, char *argv[]) {
  game::Log::setLevel(game::Log::INFO);

  static constexpr unsigned INITIAL_WIDTH = 1024;
  static constexpr unsigned INITIAL_HEIGHT = 576;

  // set up singletons
  game::SingletonStorage<game::EventManager> storageForEventManager(huaca::gEventManager);
  game::SingletonStorage<game::ResourceManager> storageForResourceManager(huaca::gResourceManager);
  game::SingletonStorage<game::WindowGeometry> storageForWindowGeometry(huaca::gWindowGeometry, INITIAL_WIDTH, INITIAL_HEIGHT);

  // initialize

  game::WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Huaca (version " GAME_VERSION ")");

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  // load resources
  huaca::gResourceManager().addSearchDir(GAME_DATADIR);

  // add cameras
  game::CameraManager cameras;

  game::FlexibleCamera mainCamera(window, AREA_WIDTH);
  cameras.addCamera(mainCamera);

  game::HeadsUpCamera hudCamera(window);
  cameras.addCamera(hudCamera);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);

  game::Action leftAction("Go left");
  leftAction.addKeyControl(sf::Keyboard::Q); // AZERTY
  leftAction.addKeyControl(sf::Keyboard::A); // QWERTY
  leftAction.setContinuous();
  actions.addAction(leftAction);

  game::Action rightAction("Go right");
  rightAction.addKeyControl(sf::Keyboard::D); // AZERTY and QWERTY
  rightAction.setContinuous();
  actions.addAction(rightAction);

  game::Action upAction("Go up");
  upAction.addKeyControl(sf::Keyboard::Z); // AZERTY
  upAction.addKeyControl(sf::Keyboard::W); // QWERTY
  upAction.setContinuous();
  actions.addAction(upAction);

  game::Action downAction("Go down");
  downAction.addKeyControl(sf::Keyboard::S); // AZERTY and QWERTY
  downAction.setContinuous();
  actions.addAction(downAction);

  game::Action portalAction("Portal");
  portalAction.addKeyControl(sf::Keyboard::Space); // AZERTY and QWERTY
  actions.addAction(portalAction);

  // Generate first level
  huaca::LevelGenerator levelGenerator;
  levelGenerator.generateFirst();

  // Generate the managers
  huaca::GroundManager groundManager = levelGenerator.getGroundManager();
  huaca::WallManager wallManager = levelGenerator.getWallManager();

  // add entities

  game::EntityManager mainEntities;
  mainEntities.addEntity(groundManager);
  mainEntities.addEntity(wallManager);

  huaca::Hero hero({ 1280.0f, 1280.0f });
  mainEntities.addEntity(hero);


  game::EntityManager hudEntities;

  huaca::Timer timer(80);
  hudEntities.addEntity(timer);

  huaca::ItemHUD itemHud;
  hudEntities.addEntity(itemHud);

  // initialisation

  huaca::gEventManager().registerHandler<huaca::HeroPositionEvent>([&mainCamera](game::EventType type, game::Event *event) {
    assert(type == huaca::HeroPositionEvent::type);
    auto posEvent = static_cast<huaca::HeroPositionEvent*>(event);
    mainCamera.setCenter(posEvent->pos);
    return game::EventStatus::KEEP;
  });

  // main loop
  game::Clock clock;

  while (window.isOpen()) {
    // input
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      cameras.update(event);
      huaca::gWindowGeometry().update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      // fake resize event (not sent when going fullscreen before SFML 2.3.1)
      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      cameras.update(event);
      huaca::gWindowGeometry().update(event);
    }

    if (rightAction.isActive()) {
      hero.goRight();
    } else if (leftAction.isActive()) {
      hero.goLeft();
    } else if (upAction.isActive()) {
      hero.goUp();
    } else if (downAction.isActive()) {
      hero.goDown();
    } else {
      hero.stop();
    }

    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();
    mainEntities.update(dt);
    hudEntities.update(dt);

    // render
    window.clear(sf::Color::Black);

    mainCamera.configure(window);
    mainEntities.render(window);

    hudCamera.configure(window);
    hudEntities.render(window);

    window.display();

    actions.reset();
  }

  return 0;
}
