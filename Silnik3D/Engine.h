#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "Cube.h"
#include "Rectangle.h"
#include "Observer.h"
#include "BitmapHandler.h"

/**
 * \class Engine
 * \brief Klasa zarządzająca działaniem silnika graficznego.
 */
class Engine {
public:
    /**
     * \brief Konstruktor domyślny klasy Engine.
     */
    Engine();

    /**
     * \brief Destruktor klasy Engine.
     */
    ~Engine();

    /**
     * \brief Inicjalizuje silnik.
     *
     * \return Zwraca true, jeśli inicjalizacja się powiodła, w przeciwnym razie false.
     */
    bool init();

    /**
     * \brief Uruchamia główną pętlę silnika.
     */
    void run();

    /**
     * \brief Zamyka silnik i zwalnia zasoby.
     */
    void shutdown();

    /**
     * \brief Ustawia liczbę klatek na sekundę (FPS).
     *
     * \param fps Liczba klatek na sekundę.
     */
    void setFrameRate(int fps);

private:
    GLFWwindow* window; ///< Wskaźnik na okno GLFW.
    int frameRate; ///< Liczba klatek na sekundę.
    bool isRunning; ///< Flaga wskazująca, czy silnik jest uruchomiony.
    int windowWidth, windowHeight; ///< Wymiary okna.
    bool spacePressed; ///< Flaga wskazująca, czy spacja została naciśnięta.
    bool lightingEnabled; ///< Flaga wskazująca, czy oświetlenie jest włączone.
    bool cubeRotationEnabled; ///< Flaga wskazująca, czy obrót sześcianu jest włączony.
    bool autoRotate; ///< Flaga wskazująca, czy automatyczny obrót jest włączony.
    bool fpsKeyPressed; ///< Flaga wskazująca, czy klawisz zmiany FPS został naciśnięty.
    bool rotationKeyPressed; ///< Flaga wskazująca, czy klawisz zmiany rotacji został naciśnięty.
    GLenum shadingModel; ///< Model cieniowania.
    float angle; ///< Kąt obrotu.
    double timePerFrame; ///< Czas na jedną klatkę.

    /**
     * \brief Przetwarza dane wejściowe.
     */
    void processInput();

    /**
     * \brief Inicjalizuje oświetlenie.
     */
    void initLighting();

    /**
     * \brief Przełącza stan oświetlenia.
     */
    void toggleLighting();

    /**
     * \brief Przełącza stan obrotu sześcianu.
     */
    void toggleCubeRotation();

    /**
     * \brief Przełącza tryb cieniowania.
     */
    void toggleShadingModel();

    /**
     * \brief Czyści ekran.
     *
     * \param r Wartość koloru czerwonego.
     * \param g Wartość koloru zielonego.
     * \param b Wartość koloru niebieskiego.
     * \param a Wartość przezroczystości.
     */
    void clearScreen(float r, float g, float b, float a);

    /**
     * \brief Obsługuje zdarzenia przewijania.
     *
     * \param window Wskaźnik na okno GLFW.
     * \param xOffset Przesunięcie w osi X.
     * \param yOffset Przesunięcie w osi Y.
     */
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    Cube cube; ///< Obiekt sześcianu.
    Rectangle rect; ///< Obiekt prostopadłościanu.
    Observer observer; ///< Obiekt obserwatora (kamery).
    BitmapHandler bitmapHandler; ///< Obiekt do obsługi bitmap.
    GLuint cubeTextureID; ///< ID tekstury sześcianu.
    GLuint rectTextureID; ///< ID tekstury prostopadłościanu.
    GLuint textureID; ///< ID tekstury.
};

#endif // ENGINE_H