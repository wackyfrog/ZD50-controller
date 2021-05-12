//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight/Scene.h"
#include <Arduino.h>
#include <AceRoutine.h>

#include "ZD50.h"

using namespace Backlight;

static Scene *scene = nullptr;
static Scene *instantScene = nullptr;

void Backlight::Scene::startInstantScene(Scene *newScene, uint32_t limitDuration) {
    instantScene = newScene;
    if (instantScene != nullptr) {
        instantScene->reset();
        instantScene->finishAt = limitDuration > 0 ? millis() + limitDuration : 0;
        instantScene->begin();
    }
}

void Backlight::Scene::stopInstantScene() {
    instantScene = nullptr;
}

void Scene::startScene(Scene *newScene, uint32_t limitDuration) {
    if (instantScene == nullptr) {
        if (scene != nullptr) {
            scene->end();
        }

    } else {
        instantScene = nullptr;
    }
    scene = newScene;

    if (scene != nullptr) {
        scene->reset();
        scene->finishAt = limitDuration > 0 ? millis() + limitDuration : 0;
        scene->begin();
    }
}

void Scene::nextFrameDelay(Scene::Millis newDelay) {
    waitUntil = newDelay + millis();
}

bool Scene::isFinished() {
    if (finished) {
        return true;
    }
    if (finishAt > 0 && millis()  > finishAt) {
        finished = true;
    }
    return finished;
}

bool Scene::isReady() {
    return !isFinished() && (millis() > waitUntil);
}

void Scene::reset() {
    waitUntil = 0;
    finished = false;
}

Scene *Scene::getInstance() {
    return scene;
}

uint32_t Scene::getFinishTime() const {
    return finishAt;
}

COROUTINE(scenePerformer) {
    COROUTINE_LOOP() {
        static bool resetScene = false;

        if (instantScene != nullptr && !instantScene->isFinished()) {
            if (instantScene->isReady()) {
                instantScene->frame();
                resetScene = true;
            }

        } else if (scene != nullptr) {
            if (scene->isPreviewMode()) {
                scene->preview();
                COROUTINE_DELAY(50);

            } else {
                if (resetScene) {
                    scene->reset();
                    scene->begin();
                    resetScene = false;
                    scene->frame();

                } else if (scene->isFinished()) {
                    COROUTINE_DELAY(50);

                } else if (scene->isReady()) {
                    scene->frame();
                }

            }
        } else { // nothing to do
            COROUTINE_DELAY(50);
        }

        COROUTINE_DELAY(1);
    }

}
