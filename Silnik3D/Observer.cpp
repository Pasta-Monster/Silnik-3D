/**
 * \file Observer.cpp
 * \brief Implementacja klasy Observer.
 */

#include "Observer.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GLFW/glfw3.h>

 /**
  * \brief Konstruktor domyślny klasy Observer.
  * Inicjalizuje pozycję obserwatora na (0.0f, 0.0f, -5.0f).
  */
Observer::Observer() : posX(0.0f), posY(0.0f), posZ(-5.0f) {} // Odległość obserwatora (kamery) względem sześcianu

/**
 * \brief Ustawia pozycję obserwatora.
 *
 * \param x Pozycja X.
 * \param y Pozycja Y.
 * \param z Pozycja Z.
 */
void Observer::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

/**
 * \brief Przesuwa obserwatora o zadane wartości.
 *
 * \param dx Przesunięcie w osi X.
 * \param dy Przesunięcie w osi Y.
 * \param dz Przesunięcie w osi Z.
 */
void Observer::move(float dx, float dy, float dz) {
    posX += dx;
    posY += dy;
    posZ += dz;
}

/**
 * \brief Zastosowuje widok obserwatora.
 * Przesuwa scenę o pozycję obserwatora.
 */
void Observer::applyView() {
    glTranslatef(posX, posY, posZ);
}