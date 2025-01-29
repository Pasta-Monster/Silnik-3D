/**
 * \file Engine.cpp
 * \brief Implementacja klasy Engine.
 */

#include "Engine.h"
#include "Cube.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>

 // Define GL_CLAMP_TO_EDGE if it is not defined
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

/**
 * \brief Konstruktor klasy Engine.
 * Inicjalizuje parametry początkowe silnika.
 */
Engine::Engine() : window(nullptr), frameRate(60), isRunning(false), windowWidth(800), windowHeight(600), spacePressed(false), lightingEnabled(true), cubeRotationEnabled(true), autoRotate(false), shadingModel(GL_SMOOTH), angle(0.0f), timePerFrame(1.0 / 60.0), fpsKeyPressed(false), rotationKeyPressed(false), textureID(0), cubeTextureID(0), rectTextureID(0) {}

/**
 * \brief Destruktor klasy Engine.
 * Zamyka silnik i zwalnia zasoby.
 */
Engine::~Engine() {
    shutdown();
}

/**
 * \brief Inicjalizuje silnik.
 * Tworzy okno, ustawia kontekst OpenGL, ładuje tekstury i inicjalizuje oświetlenie.
 * \return Zwraca true, jeśli inicjalizacja się powiodła, w przeciwnym razie false.
 */
bool Engine::init() {
    if (!glfwInit()) {
        std::cerr << "Blad inicjalizacji GLFW" << std::endl;
        return false;
    }

    std::cout << "Tworzenie okna GLFW" << std::endl;
    window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Blad tworzenia okna GLFW!" << std::endl;
        glfwTerminate();
        return false;
    }

    std::cout << "Kontekst OpenGL zostal ustawiony" << std::endl;
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, scrollCallback);

    std::cout << "Inicjalizacja oswietlenia" << std::endl;
    initLighting();
    std::cout << "Oswietlenie zainicjalizowane" << std::endl;

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat left = -1.0f, right = 1.0f, bottom = -1.0f, top = 1.0f, near = 1.0f, far = 100.0f;
    glFrustum(left, right, bottom, top, near, far);

    glMatrixMode(GL_MODELVIEW);

    std::cout << "Silnik załadowany pomyslnie" << std::endl;
    isRunning = true;

    // Ładowanie tekstury dla sześcianu
    std::string cubeTexturePath = "D:\\OneDrive\\Desktop\\praca domowa\\Grafa2\\Silnik3D\\img\\brick.png";
    if (!bitmapHandler.LoadTextureFromFile(cubeTexturePath)) {
        std::cerr << "Blad ladowania tekstury z pliku: " << cubeTexturePath << std::endl;
        return false;
    }

    glGenTextures(1, &cubeTextureID);
    glBindTexture(GL_TEXTURE_2D, cubeTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapHandler.GetWidth(), bitmapHandler.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapHandler.GetTextureData().data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
        return false;
    }

    std::cout << "Tekstura dla szescianu załadowana pomyslnie" << std::endl;

    // Ładowanie tekstury dla prostopadłościanu
    std::string rectTexturePath = "D:\\OneDrive\\Desktop\\praca domowa\\Grafa2\\Silnik3D\\img\\texture.jpg";
    if (!bitmapHandler.LoadTextureFromFile(rectTexturePath)) {
        std::cerr << "Blad ladowania tekstury z pliku: " << rectTexturePath << std::endl;
        return false;
    }

    glGenTextures(1, &rectTextureID);
    glBindTexture(GL_TEXTURE_2D, rectTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapHandler.GetWidth(), bitmapHandler.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapHandler.GetTextureData().data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
        return false;
    }

    std::cout << "Tekstura dla prostopadloscianu zaladowana pomyslnie" << std::endl;

    return true;
}

/**
 * \brief Uruchamia główną pętlę silnika.
 * Obsługuje renderowanie, przetwarzanie wejścia i aktualizację stanu.
 */
void Engine::run() {
    cube.getTransform().translate(0.0f, 2.0f, 0.0f); // Początkowa pozycja 
    cube.getTransform().scale(0.5f, 0.5f, 0.5f); // Początkowa skala

    rect.getTransform().translate(0.0f, 0.0f, 0.0f); // Początkowa pozycja 
    rect.getTransform().scale(1.0f, 1.0f, 1.0f); // Początkowa skala

    double previousTime = glfwGetTime();
    double lag = 0.0;

    while (isRunning && !glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        processInput();

        clearScreen(0.1f, 0.1f, 0.1f, 1.0f); // Ustawia kolor ekranu 
        glLoadIdentity();

        observer.applyView(); // Zastosowanie ustawienia kamery

        if (autoRotate) {
            angle += 1.5f;
        }

        if (cubeRotationEnabled) {
            cube.getTransform().rotate(angle, 5.0f, 2.0f, 0.0f); // Obrót  
            rect.getTransform().rotate(angle, 1.0f, 5.0f, 2.0f); // Obrót    
        }

        // Włączenie tekstury dla sześcianu
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, cubeTextureID);
        cube.draw(); // Rysuje sześcian

        // Włączenie tekstury dla prostopadłościanu
        glBindTexture(GL_TEXTURE_2D, rectTextureID);
        rect.draw(); // Rysuje prostopadłościan

        // Wyłączenie tekstury
        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() - currentTime < timePerFrame) {
            // Czekanie
        }
    }

    shutdown();
}

/**
 * \brief Inicjalizuje oświetlenie dla silnika.
 * Ustawia właściwości światła i materiału.
 */
void Engine::initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Właściwości światła
    GLfloat lightPosition[] = { 4.0f, 0.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Właściwości materiału
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.5f, 0.35f, 0.2f, 1.0f };
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat shininess = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    std::cout << "Oswietlenie zainicjalizowane pomyslnie" << std::endl;
}

/**
 * \brief Przełącza stan oświetlenia.
 */
void Engine::toggleLighting() {
    if (lightingEnabled) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        std::cout << "Oswietlenie wylaczone" << std::endl;
    }
    else {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        std::cout << "Oswietlenie wlaczone" << std::endl;
    }

    lightingEnabled = !lightingEnabled;  // Zmieniamy stan zmiennej lightingEnabled
}

/**
 * \brief Przełącza stan obrotu sześcianu.
 */
void Engine::toggleCubeRotation() {
    cubeRotationEnabled = !cubeRotationEnabled;
    if (cubeRotationEnabled) {
        std::cout << "Obrot szescianu wlaczony" << std::endl;
    }
    else {
        std::cout << "Obrot szescianu wylaczony" << std::endl;
    }
}

/**
 * \brief Przełącza tryb cieniowania.
 */
void Engine::toggleShadingModel() {
    if (shadingModel == GL_FLAT) {
        shadingModel = GL_SMOOTH;
        std::cout << "Zmieniono cieniowanie na: Smooth" << std::endl;
    }
    else {
        shadingModel = GL_FLAT;
        std::cout << "Zmieniono cieniowanie na: Flat" << std::endl;
    }
    glShadeModel(shadingModel); // Aktualizacja trybu w OpenGL
}

/**
 * \brief Obsługuje zdarzenia przewijania.
 * \param window Wskaźnik na okno GLFW.
 * \param xOffset Przesunięcie w osi X.
 * \param yOffset Przesunięcie w osi Y.
 */
void Engine::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->angle += static_cast<float>(yOffset) * 10.0f; // kat rotowania skrolem
    }
}

/**
 * \brief Czyści ekran.
 * \param r Wartość koloru czerwonego.
 * \param g Wartość koloru zielonego.
 * \param b Wartość koloru niebieskiego.
 * \param a Wartość przezroczystości.
 */
void Engine::clearScreen(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * \brief Zamyka silnik i zwalnia zasoby.
 */
void Engine::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    std::cout << "Silnik wyczyszczony" << std::endl;
}

/**
 * \brief Ustawia liczbę klatek na sekundę (FPS).
 * \param fps Liczba klatek na sekundę.
 */
void Engine::setFrameRate(int fps) {
    frameRate = fps;
    timePerFrame = 1.0 / fps;
    std::cout << "Liczba FPS: " << frameRate << std::endl;
}

/**
 * \brief Przetwarza dane wejściowe.
 */
void Engine::processInput() {
    static bool lightingKeyPressed = false;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);  // Pobierz pozycję kursora

    static double prevYPos = yPos;
    if (yPos != prevYPos) {
        // Obrót w zależności od ruchu kółka myszy
        float rotationDelta = static_cast<float>(yPos - prevYPos) * 0.5f;
        cube.getTransform().rotate(rotationDelta, 1.0f, 0.0f, 0.0f); // Zmieniamy kąt obrotu sześcianu
    }
    prevYPos = yPos;  // Aktualizujemy poprzednią pozycję kursora

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        isRunning = false;
    }

    // Poruszanie kamerą
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        observer.move(0.0f, 0.0f, 0.01f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        observer.move(0.0f, 0.0f, -0.01f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        observer.move(0.01f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        observer.move(-0.01f, 0.0f, 0.0f);
    }

    // Poruszanie sześcianem
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cube.getTransform().translate(0.0f, 0.01f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cube.getTransform().translate(0.0f, -0.01f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cube.getTransform().translate(-0.01f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cube.getTransform().translate(0.01f, 0.0f, 0.0f);
    }

    // Poruszanie prostopadloscianem
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        rect.getTransform().translate(0.0f, 0.01f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        rect.getTransform().translate(0.0f, -0.01f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        rect.getTransform().translate(-0.01f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        rect.getTransform().translate(0.01f, 0.0f, 0.0f);
    }

    // Zmiana trybu cieniowania za pomocą spacji
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!spacePressed) {
            toggleShadingModel();
            spacePressed = true;
        }
    }
    else {
        spacePressed = false;
    }

    // Włączanie/wyłączanie oświetlenia klawiszem PPM
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!lightingKeyPressed) {
            toggleLighting();  // Przełączenie stanu oświetlenia
            lightingKeyPressed = true; // Zmieniamy stan zmiennej, aby nie wykonywać akcji wielokrotnie
        }
    }
    else {
        lightingKeyPressed = false; // Resetujemy stan po puszczeniu klawisza
    }

    // Zmiana FPS
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) { //  + lub =
        if (!fpsKeyPressed) {
            setFrameRate(frameRate + 10);
            fpsKeyPressed = true;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) { //  - lub _
        if (!fpsKeyPressed) {
            setFrameRate(frameRate - 10);
            fpsKeyPressed = true;
        }
    }
    else {
        fpsKeyPressed = false;
    }

    // Auto rotacja
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!rotationKeyPressed) {
            autoRotate = !autoRotate;
            rotationKeyPressed = true;
        }
    }
    else {
        rotationKeyPressed = false;
    }
}