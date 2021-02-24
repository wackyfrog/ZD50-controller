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


        static void startInstantScene(Scene *newScene);

        static void stopInstantScene();

        static void startScene(Scene *newScene);

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

        bool isFinished() const;

    private:
        Millis waitUntil;
        bool previewMode = false;
        bool finished = false;
    };
}

#endif //ZD50_CONTROLLER_SCENE_H
