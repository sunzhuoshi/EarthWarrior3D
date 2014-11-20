/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://github.com/chukong/EarthWarrior3D

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "RealSense\CCCamera.h"
#include "RealSense\CCCursor.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    //glview->setDesignResolutionSize(480,800,ResolutionPolicy::FIXED_HEIGHT);
    if(!glview) {
        int height, width;
        height = 800;
        width = height*(640.0/960.0);
        
        glview = GLView::createWithRect("EarthWarrior3D", Rect(0, 0, width, height));
        
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//add realsense 
	Camera *camera = Camera::getInstance();
	camera->enableDepthImage(true, 50);
	camera->start();

	/*
	//case 1: depth image will be display fullscreen
	Cursor *cursor = Cursor::create("cursor/click_up.png", "cursor/click_down.png", "cursor");
	cursor->setDepthImagePositon(Cursor::DepthImagePosition::Center, 2);
	director->setNotificationNode(cursor);
	*/
	//case 2: depth image will be display at left bottom,with scale factor 0.4
	Cursor *cursor = Cursor::create("cursor/click_up.png", "cursor/click_down.png", "cursor");
	cursor->setDepthImagePositon(Cursor::DepthImagePosition::LeftBottom, 0.4);
	director->setNotificationNode(cursor);	


	director->getScheduler()->schedule(schedule_selector(RealSenseEventCenter::tick), RealSenseEventCenter::getInstance(), 0, false);

    // create a scene. it's an autorelease object
    //auto scene = LoadingScene::createScene();
    auto scene = MainMenuScene::createScene();
    //auto scene = HelloWorld::createScene();
    // run
    director->runWithScene(scene);
    glEnable(GL_CULL_FACE);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->stopAnimation();
    
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    SimpleAudioEngine::getInstance()->resumeAllEffects();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
 
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

