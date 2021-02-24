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

void Backlight::Scene::startInstantScene(Scene *newScene) {
    instantScene = newScene;
    if (instantScene != nullptr) {
        instantScene->reset();
    }
}

void Backlight::Scene::stopInstantScene() {
    instantScene = nullptr;
}

void Scene::startScene(Scene *newScene) {
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
    }
}

void Scene::nextFrameDelay(Scene::Millis newDelay) {
    waitUntil = newDelay + millis();
}

bool Scene::isFinished() const {
    return finished;
}

bool Scene::isReady() {
    return !finished && (millis() > waitUntil);
}

void Scene::reset() {
    waitUntil = 0;
    finished = false;
    begin();
}

Scene *Scene::getInstance() {
    return scene;
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
