//
// Created by Oleksandr Degtiar on 26.01.2021.
//

#ifndef ZD50_CONTROLLER_SCENE_H
#define ZD50_CONTROLLER_SCENE_H

#include <stdint.h>
// TODO Light transition between scenes

namespace Backlight {

    class Scene {

    public:
        typedef unsigned long Millis;

        virtual void begin() {};

        virtual void end() {};

        virtual void frame() {};

        void nextFrameDelay(Millis newDelay);

        void done() {
            finished = true;
        }

        static void startInstantScene(Scene *newScene, uint32_t limitDuration = 0);

        static void stopInstantScene();

        static void startScene(Scene *newScene, uint32_t limitDuration = 0);

        static Scene *getInstance();

        bool isReady();

        void reset();

        virtual void preview() {};

        void setPreviewMode() {
            previewMode = true;
            preview();
        }

        void setNormalMode() {
            previewMode = false;
            begin();
        }

        bool isPreviewMode() {
            return previewMode;
        }

        bool isFinished();

        uint32_t getFinishTime() const;

    private:
        Millis waitUntil;
        bool previewMode = false;
        bool finished = false;
        uint32_t finishAt = 0;
    };
}

#endif //ZD50_CONTROLLER_SCENE_H
