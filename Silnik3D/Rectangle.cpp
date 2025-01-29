/**
 * \file Rectangle.cpp
 * \brief Implementacja klasy Rectangle.
 */

#include "Rectangle.h"
#include <GL/gl.h>

 // Ensure GL_CLAMP_TO_EDGE is defined
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

/**
 * \brief Rysuje prostopadłościan.
 *
 * Metoda ta rysuje prostopadłościan z użyciem OpenGL, stosując ustawienia wierzchołków, normalnych i współrzędnych tekstury.
 * Każda ściana prostopadłościanu jest teksturowana niezależnie.
 */
void Rectangle::draw() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // Ustaw kolor na biały (RGB)
    transform.apply(); // Zastosuj transformacje

    /**
     * \var vertices
     * \brief Tablica współrzędnych wierzchołków prostopadłościanu.
     */
    const GLfloat vertices[] = {
        // Przednia ściana
        -1.5f, -0.5f, -0.5f, // 0
         1.5f, -0.5f, -0.5f, // 1
         1.5f,  0.5f, -0.5f, // 2
        -1.5f,  0.5f, -0.5f, // 3
        // Tylna ściana
        -1.5f, -0.5f,  0.5f, // 4
         1.5f, -0.5f,  0.5f, // 5
         1.5f,  0.5f,  0.5f, // 6
        -1.5f,  0.5f,  0.5f, // 7
        // Lewa ściana
        -1.5f, -0.5f, -0.5f, // 8
        -1.5f,  0.5f, -0.5f, // 9
        -1.5f,  0.5f,  0.5f, // 10
        -1.5f, -0.5f,  0.5f, // 11
        // Prawa ściana
         1.5f, -0.5f, -0.5f, // 12
         1.5f,  0.5f, -0.5f, // 13
         1.5f,  0.5f,  0.5f, // 14
         1.5f, -0.5f,  0.5f, // 15
         // Dolna ściana
         -1.5f, -0.5f, -0.5f, // 16
          1.5f, -0.5f, -0.5f, // 17
          1.5f, -0.5f,  0.5f, // 18
         -1.5f, -0.5f,  0.5f, // 19
         // Górna ściana
         -1.5f,  0.5f, -0.5f, // 20
          1.5f,  0.5f, -0.5f, // 21
          1.5f,  0.5f,  0.5f, // 22
         -1.5f,  0.5f,  0.5f  // 23
    };

    /**
     * \var texCoords
     * \brief Tablica współrzędnych tekstury dla każdej ściany prostopadłościanu.
     */
    const GLfloat texCoords[] = {
        // Przednia ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Tylna ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Lewa ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Prawa ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Dolna ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Górna ściana
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    /**
     * \var indices
     * \brief Tablica indeksów dla każdej ściany prostopadłościanu.
     */
    const GLuint indices[] = {
        // Przednia ściana
        0, 1, 2, 3,
        // Tylna ściana
        4, 5, 6, 7,
        // Lewa ściana
        8, 9, 10, 11,
        // Prawa ściana
        12, 13, 14, 15,
        // Dolna ściana
        16, 17, 18, 19,
        // Górna ściana
        20, 21, 22, 23
    };

    /**
     * \var normals
     * \brief Tablica wektorów normalnych dla każdej ściany prostopadłościanu.
     */
    const GLfloat normals[] = {
        0.0f,  0.0f, -1.0f, // Przednia
        0.0f,  0.0f,  1.0f, // Tylna
       -1.0f,  0.0f,  0.0f, // Lewa
        1.0f,  0.0f,  0.0f, // Prawa
        0.0f, -1.0f,  0.0f, // Dolna
        0.0f,  1.0f,  0.0f  // Górna
    };

    // Włącz tablice wierzchołków, normalnych i współrzędnych tekstury
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    // Rysuj prostopadłościan
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);

    // Wyłącz tablice wierzchołków, normalnych i współrzędnych tekstury
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

/**
 * \brief Zwraca transformację prostopadłościanu.
 * \return Obiekt Transform reprezentujący transformację prostopadłościanu.
 */
Transform& Rectangle::getTransform() {
    return transform;
}