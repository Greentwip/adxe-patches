/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://adxeproject.github.io/

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

#include "controller.h"
#include <functional>
#include <chrono>
#include "BaseTest.h"
#include "tests.h"

USING_NS_CC;

#define TEST_TIME_OUT 50
#define CREATE_TIME_OUT 25
#define LOG_INDENTATION "  "
#define LOG_TAG "[TestController]"

static void initCrashCatch();
static void disableCrashCatch();

class RootTests : public TestList
{
public:
    RootTests()
    {
//        addTest("Node: Scene3D", [](){return new Scene3DTests(); });
#if defined(CC_PLATFORM_PC)
        addTest("ImGui", []() { return new ImGuiTests(); });
#endif
        addTest("Texture2D", []() { return new Texture2DTests(); });
        addTest("ActionManager", []() { return new ActionManagerTests(); });
        addTest("Actions - Basic", []() { return new ActionsTests(); });
        addTest("Actions - Ease", []() { return new ActionsEaseTests(); });
        addTest("Actions - Progress", []() { return new ActionsProgressTests(); });
        addTest("Audio - NewAudioEngine", []() { return new AudioEngineTests(); });

        addTest("Box2D - Basic", []() { return new Box2DTests(); });
#if defined(CC_PLATFORM_PC)
        addTest("Box2D - TestBed", []() { return new Box2DTestBedTests(); });
#endif
        addTest("Chipmunk2D - Basic", []() { return new ChipmunkTests(); });
#if defined(CC_PLATFORM_PC)
        addTest("Chipmunk2D - TestBed", []() { return new ChipmunkTestBedTests(); });
#endif
        addTest("Bugs", []() { return new BugsTests(); });
        addTest("Click and Move", []() { return new ClickAndMoveTest(); });
        addTest("Configuration", []() { return new ConfigurationTests(); });
        addTest("Console", []() { return new ConsoleTests(); });
        addTest("Curl", []() { return new CurlTests(); });
        addTest("Current Language", []() { return new CurrentLanguageTests(); });
        addTest("Network Test", []() { return new NetworkTests(); });
        addTest("EventDispatcher", []() { return new EventDispatcherTests(); });
        addTest("Effects - Advanced", []() { return new EffectAdvanceTests(); });
        addTest("Effects - Basic", []() { return new EffectTests(); });
        addTest("Extensions", []() { return new ExtensionsTests(); });
        addTest("FileUtils", []() { return new FileUtilsTests(); });
        addTest("Fonts", []() { return new FontTests(); });
        addTest("Interval", []() { return new IntervalTests(); });
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        addTest("JNIHelper", []() { return new JNITests(); });
#endif
        addTest("Material System", []() { return new MaterialSystemTest(); });
        addTest("Navigation Mesh", []() { return new NavMeshTests(); });
        addTest("Node: BillBoard Test", []() { return new BillBoardTests(); });
        addTest("Node: Camera3D Test", []() { return new Camera3DTests(); });
        addTest("Node: Clipping", []() { return new ClippingNodeTests(); });
        addTest("Node: Draw", []() { return new DrawPrimitivesTests(); });
        addTest("Node: Label - New API", []() { return new NewLabelTests(); });
        addTest("Node: Layer", []() { return new LayerTests(); });
        addTest("Node: Light", []() { return new LightTests(); });
        addTest("Node: Menu", []() { return new MenuTests(); });
        addTest("Node: MotionStreak", []() { return new MotionStreakTests(); });
        addTest("Node: Node", []() { return new CocosNodeTests(); });
        addTest("Node: Parallax", []() { return new ParallaxTests(); });
        addTest("Node: Particles", []() { return new ParticleTests(); });
        addTest("Node: Particle3D (PU)", []() { return new Particle3DTests(); });
#if CC_USE_PHYSICS
        addTest("Node: Physics", []() { return new PhysicsTests(); });
#endif
        addTest("Node: Physics3D", []() { return new Physics3DTests(); });
        addTest("Node: RenderTexture", []() { return new RenderTextureTests(); });
        addTest("Node: Scene", []() { return new SceneTests(); });
        addTest("Node: Spine", []() { return new SpineTests(); });
        addTest("Node: Sprite", []() { return new SpriteTests(); });
        addTest("Node: Sprite3D", []() { return new Sprite3DTests(); });
        addTest("Node: SpritePolygon", []() { return new SpritePolygonTest(); });
        addTest("Node: Terrain", []() { return new TerrainTests(); });
        addTest("Node: FastTileMap", []() { return new FastTileMapTests(); });
        addTest("Node: Text Input", []() { return new TextInputTests(); });
        addTest("Node: UI", []() { return new UITests(); });
        addTest("Mouse", []() { return new MouseTests(); });
        addTest("MultiTouch", []() { return new MultiTouchTests(); });
        addTest("Renderer", []() { return new NewRendererTests(); });
        addTest("ReleasePool", []() { return new ReleasePoolTests(); });
        addTest("Rotate World", []() { return new RotateWorldTests(); });
        addTest("Scheduler", []() { return new SchedulerTests(); });
        addTest("Shader - Basic", []() { return new ShaderTests(); });
        addTest("Shader - Sprite", []() { return new Shader2Tests(); });
        addTest("TextureCache", []() { return new TextureCacheTests(); });
        addTest("TexturePacker Encryption", []() { return new TextureAtlasEncryptionTests(); });
        addTest("Touches", []() { return new TouchesTests(); });
        addTest("Transitions", []() { return new TransitionsTests(); });
        addTest("Unit Test", []() { return new UnitTests(); });
        addTest("Unzip Test", []() { return new ZipTests(); });
        addTest("URL Open Test", []() { return new OpenURLTests(); });
        addTest("UserDefault", []() { return new UserDefaultTests(); });
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        addTest("Vibrate", []() { return new VibrateTests(); });
#endif
        addTest("Zwoptex", []() { return new ZwoptexTests(); });
        addTest("SpriteFrameCache", []() { return new SpriteFrameCacheTests(); });  // TODO
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || \
     CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        addTest("Window Test", []() { return new WindowTests(); });  // TODO wrong effect
#endif
    }
};

TestController::TestController() : _stopAutoTest(true), _isRunInBackground(false), _testSuite(nullptr)
{
    _rootTestList = new RootTests;
    _rootTestList->runThisTest();
    _director = Director::getInstance();

    _touchListener               = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(TestController::blockTouchBegan, this);
    _touchListener->setSwallowTouches(true);

    _director->getEventDispatcher()->addEventListenerWithFixedPriority(_touchListener, -200);
}

TestController::~TestController()
{
    _director->getEventDispatcher()->removeEventListener(_touchListener);

    _rootTestList->release();
    _rootTestList = nullptr;
}

void TestController::startAutoTest()
{
    if (!_autoTestThread.joinable())
    {
        _stopAutoTest   = false;
        _logIndentation = "";
        _autoTestThread = std::thread(&TestController::traverseThreadFunc, this);
        _autoTestThread.detach();
    }
}

void TestController::stopAutoTest()
{
    _stopAutoTest = true;

    if (_autoTestThread.joinable())
    {
        _sleepCondition.notify_all();
        _autoTestThread.join();
    }
}

void TestController::traverseThreadFunc()
{
    std::mutex sleepMutex;
    auto lock        = std::unique_lock<std::mutex>(sleepMutex);
    _sleepUniqueLock = &lock;
    traverseTestList(_rootTestList);
    _sleepUniqueLock = nullptr;
}

void TestController::traverseTestList(TestList* testList)
{
    if (testList == _rootTestList)
    {
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
    }
    else
    {
        _logIndentation += LOG_INDENTATION;
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
    }
    logEx("%s%sBegin traverse TestList:%s", LOG_TAG, _logIndentation.c_str(), testList->getTestName().c_str());

    auto scheduler = _director->getScheduler();
    int testIndex  = 0;
    for (auto& callback : testList->_testCallbacks)
    {
        if (_stopAutoTest)
            break;
        while (_isRunInBackground)
        {
            logEx("_director is paused");
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
        }
        if (callback)
        {
            auto test = callback();
            test->setTestParent(testList);
            test->setTestName(testList->_childTestNames[testIndex++]);
            if (test->isTestList())
            {
                scheduler->performFunctionInCocosThread([&]() { test->runThisTest(); });

                traverseTestList((TestList*)test);
            }
            else
            {
                traverseTestSuite((TestSuite*)test);
            }
        }
    }

    if (testList == _rootTestList)
    {
        _stopAutoTest = true;
    }
    else
    {
        if (!_stopAutoTest)
        {
            // Backs up one level and release TestList object.
            scheduler->performFunctionInCocosThread([&]() { testList->_parentTest->runThisTest(); });
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
            testList->release();
        }

        _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
    }
}

void TestController::traverseTestSuite(TestSuite* testSuite)
{
    auto scheduler         = _director->getScheduler();
    int testIndex          = 0;
    float testCaseDuration = 0.0f;
    _logIndentation += LOG_INDENTATION;
    logEx("%s%sBegin traverse TestSuite:%s", LOG_TAG, _logIndentation.c_str(), testSuite->getTestName().c_str());

    _logIndentation += LOG_INDENTATION;
    testSuite->_currTestIndex = -1;

    auto logIndentation = _logIndentation;
    for (auto& callback : testSuite->_testCallbacks)
    {
        auto testName = testSuite->_childTestNames[testIndex++];

        Scene* testScene                 = nullptr;
        TestCase* testCase               = nullptr;
        TransitionScene* transitionScene = nullptr;

        if (_stopAutoTest)
            break;

        while (_isRunInBackground)
        {
            logEx("_director is paused");
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(500));
        }
        // Run test case in the cocos[GL] thread.
        scheduler->performFunctionInCocosThread([&, logIndentation, testName]() {
            if (_stopAutoTest)
                return;
            logEx("%s%sRun test:%s.", LOG_TAG, logIndentation.c_str(), testName.c_str());

            auto scene = callback();
            if (_stopAutoTest)
                return;

            if (scene)
            {
                transitionScene = dynamic_cast<TransitionScene*>(scene);
                if (transitionScene)
                {
                    testCase         = (TestCase*)transitionScene->getInScene();
                    testCaseDuration = transitionScene->getDuration() + 0.5f;
                }
                else
                {
                    testCase         = (TestCase*)scene;
                    testCaseDuration = testCase->getDuration();
                }
                testSuite->_currTestIndex++;
                testCase->setTestSuite(testSuite);
                testCase->setTestCaseName(testName);
                _director->replaceScene(scene);

                testScene = scene;
            }
        });

        if (_stopAutoTest)
            break;

        // Wait for the test case be created.
        float waitTime = 0.0f;
        while (!testScene && !_stopAutoTest)
        {
            _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(50));
            if (!_isRunInBackground)
            {
                waitTime += 0.05f;
            }

            if (waitTime > CREATE_TIME_OUT)
            {
                logEx("%sCreate test %s time out", LOG_TAG, testName.c_str());
                _stopAutoTest = true;
                break;
            }
        }

        if (_stopAutoTest)
            break;

        // Wait for test completed.
        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(int(1000 * testCaseDuration)));

        if (transitionScene == nullptr)
        {
            waitTime = 0.0f;
            while (!_stopAutoTest && testCase->getRunTime() < testCaseDuration)
            {
                _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(50));
                if (!_isRunInBackground)
                {
                    waitTime += 0.05f;
                }

                if (waitTime > TEST_TIME_OUT)
                {
                    logEx("%sRun test %s time out", LOG_TAG, testName.c_str());
                    _stopAutoTest = true;
                    break;
                }
            }

            if (!_stopAutoTest)
            {
                // Check the result of test.
                checkTest(testCase);
            }
        }
    }

    if (!_stopAutoTest)
    {
        // Backs up one level and release TestSuite object.
        auto parentTest = testSuite->_parentTest;
        scheduler->performFunctionInCocosThread([&]() { parentTest->runThisTest(); });

        _sleepCondition.wait_for(*_sleepUniqueLock, std::chrono::milliseconds(1000));
        testSuite->release();
    }

    _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
    _logIndentation.erase(_logIndentation.rfind(LOG_INDENTATION));
}

bool TestController::checkTest(TestCase* testCase)
{
    if (testCase)
    {
        switch (testCase->getTestType())
        {
        case TestCase::Type::UNIT:
        {
            if (testCase && testCase->getExpectedOutput() != testCase->getActualOutput())
            {
                logEx("%s %s test fail", LOG_TAG, testCase->getTestCaseName().c_str());
            }
            else
            {
                logEx("%s %s test pass", LOG_TAG, testCase->getTestCaseName().c_str());
            }
            break;
        }
        case TestCase::Type::ROBUSTNESS:
        {
            break;
        }
        case TestCase::Type::MANUAL:
        {
            break;
        }
        default:
            break;
        }
    }

    return true;
}

void TestController::handleCrash()
{
    disableCrashCatch();

    logEx("%sCatch an crash event", LOG_TAG);

    if (!_stopAutoTest)
    {
        stopAutoTest();
    }
}

void TestController::onEnterBackground()
{
    _isRunInBackground = true;
}

void TestController::onEnterForeground()
{
    _isRunInBackground = false;
}

void TestController::logEx(const char* format, ...)
{
    char buff[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(buff, 1020, format, args);
    strcat(buff, "\n");

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info", "%s", buff);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    WCHAR wszBuf[1024] = {0};
    MultiByteToWideChar(CP_UTF8, 0, buff, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);

#else
    // Linux, Mac, iOS, etc
    fprintf(stdout, "%s", buff);
    fflush(stdout);
#endif
    va_end(args);
}

static TestController* s_testController = nullptr;

TestController* TestController::getInstance()
{
    if (s_testController == nullptr)
    {
        s_testController = new TestController;

        initCrashCatch();
    }

    return s_testController;
}

void TestController::destroyInstance()
{
    if (s_testController)
    {
        s_testController->stopAutoTest();
        delete s_testController;
        s_testController = nullptr;
    }

    disableCrashCatch();
}

bool TestController::blockTouchBegan(Touch* touch, Event* event)
{
    return !_stopAutoTest;
}

//==================================================================================================
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#    include <windows.h>

static long __stdcall windowExceptionFilter(_EXCEPTION_POINTERS* excp)
{
    if (s_testController)
    {
        s_testController->handleCrash();
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

static void initCrashCatch()
{
    SetUnhandledExceptionFilter(windowExceptionFilter);
}
static void disableCrashCatch()
{
    SetUnhandledExceptionFilter(UnhandledExceptionFilter);
}

#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || \
    CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#    if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
static int s_fatal_signals[] = {
    SIGILL, SIGABRT, SIGBUS, SIGFPE, SIGSEGV, SIGSTKFLT, SIGPIPE,
};
#    else
static int s_fatal_signals[] = {
    SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV, SIGTRAP, SIGTERM, SIGKILL,
};
#    endif

static void signalHandler(int sig)
{
    if (s_testController)
    {
        s_testController->handleCrash();
    }
}

static void initCrashCatch()
{
    for (auto sig : s_fatal_signals)
    {
        signal(sig, signalHandler);
    }
}

static void disableCrashCatch()
{
    for (auto sig : s_fatal_signals)
    {
        signal(sig, SIG_DFL);
    }
}

#else

static void initCrashCatch() {}

static void disableCrashCatch() {}

#endif
