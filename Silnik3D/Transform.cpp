/**
 * \file Transform.cpp
 * \brief Implementacja klasy Transform.
 */

#include "Transform.h"
#include <windows.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

 /**
  * \brief Konstruktor domyślny klasy Transform.
  * Inicjalizuje przemieszczenie, rotację i skalowanie.
  */
Transform::Transform()
    :
    translationX(0.0f), translationY(0.0f), translationZ(0.0f), // Zmienia położenie sześcianu względem XYZ, translation = PRZEMIESZCZANIE
    rotationAngle(0.0f), rotationX(0.0f), rotationY(0.0f), rotationZ(0.0f), // Za to jest to co jest w engine.cpp
    scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f) {
} // Wielkość sześcianu

/**
 * \brief Przemieszcza obiekt.
 *
 * \param dx Przemieszczenie w osi X.
 * \param dy Przemieszczenie w osi Y.
 * \param dz Przemieszczenie w osi Z.
 */
void Transform::translate(float dx, float dy, float dz) {
    translationX += dx;
    translationY += dy;
    translationZ += dz;
}

/**
 * \brief Obraca obiekt.
 *
 * \param angle Kąt obrotu w stopniach.
 * \param x Wektor obrotu w osi X.
 * \param y Wektor obrotu w osi Y.
 * \param z Wektor obrotu w osi Z.
 */
void Transform::rotate(float angle, float x, float y, float z) {
    rotationAngle = angle;
    rotationX = x;
    rotationY = y;
    rotationZ = z;
}

/**
 * \brief Skaluje obiekt.
 *
 * \param sx Skalowanie w osi X.
 * \param sy Skalowanie w osi Y.
 * \param sz Skalowanie w osi Z.
 */
void Transform::scale(float sx, float sy, float sz) {
    scaleX *= sx;
    scaleY *= sy;
    scaleZ *= sz;
}

/**
 * \brief Zastosowuje transformacje.
 *
 * Zastosowuje przemieszczenie, rotację i skalowanie do obiektu w przestrzeni 3D.
 */
void Transform::apply() {
    glTranslatef(translationX, translationY, translationZ);
    glRotatef(rotationAngle, rotationX, rotationY, rotationZ);
    glScalef(scaleX, scaleY, scaleZ);
}