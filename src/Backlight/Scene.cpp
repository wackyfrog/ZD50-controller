//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#include "Backlight/Scene.h"
#include <Arduino.h>
#include <AceRoutine.h>

#include "ZD50.h"
using namespace Backlight;

static Scene::Millis now = 0;
static Scene *scene = nullptr;
static Scene *instantScene = nullptr;

void Backlight::Scene::startInstantScene(Scene *newScene) {
    instantScene = newScene;
    if (instantScene != nullptr) {
        instantScene->reset();
    }
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
    waitUntil = newDelay + now;
}

bool Scene::isReady() {
    return now > waitUntil;
}

void Scene::reset() {
    waitUntil = 0;
    isFinished = false;
    begin();
}

COROUTINE(scenePerformer) {
    COROUTINE_LOOP() {
        static bool resetScene = false;
        if (instantScene != nullptr && !instantScene->isFinished) {
            now = millis();
            if (instantScene->isReady()) {
                instantScene->frame();
                resetScene = true;
            }

        } else if (scene != nullptr && !scene->isFinished) {
            now = millis();
            if (resetScene) {
                scene->reset();
                resetScene = false;
            }
            if (scene->isReady()) {
                scene->frame();
            }

        } else {
            COROUTINE_DELAY(50);
        }
        COROUTINE_DELAY(1);

    }
}
