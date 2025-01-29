/**
 * \file Cube.cpp
 * \brief Implementacja klasy Cube.
 */

#include "Cube.h"
#include <GL/gl.h>

 // Ensure GL_CLAMP_TO_EDGE is defined
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

/**
 * \brief Rysuje sześcian.
 *
 * Metoda ta rysuje sześcian z użyciem OpenGL, stosując ustawienia wierzchołków, normalnych i współrzędnych tekstury.
 * Każda ściana sześcianu jest teksturowana niezależnie.
 */
void Cube::draw() {
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Ustaw kolor na czerwony (RGB)
    transform.apply(); // Zastosuj transformacje

    /**
     * \var vertices
     * \brief Tablica współrzędnych wierzchołków sześcianu.
     */
    const GLfloat vertices[] = {
        // Przód
        -1.0f, -1.0f, -1.0f, // 0
         1.0f, -1.0f, -1.0f, // 1
         1.0f,  1.0f, -1.0f, // 2
        -1.0f,  1.0f, -1.0f, // 3
        // Tyl
        -1.0f, -1.0f,  1.0f, // 4
         1.0f, -1.0f,  1.0f, // 5
         1.0f,  1.0f,  1.0f, // 6
        -1.0f,  1.0f,  1.0f, // 7
        // Lewa
        -1.0f, -1.0f, -1.0f, // 8
        -1.0f,  1.0f, -1.0f, // 9
        -1.0f,  1.0f,  1.0f, // 10
        -1.0f, -1.0f,  1.0f, // 11
        // Prawa
         1.0f, -1.0f, -1.0f, // 12
         1.0f,  1.0f, -1.0f, // 13
         1.0f,  1.0f,  1.0f, // 14
         1.0f, -1.0f,  1.0f, // 15
         // Dół
         -1.0f, -1.0f, -1.0f, // 16
          1.0f, -1.0f, -1.0f, // 17
          1.0f, -1.0f,  1.0f, // 18
         -1.0f, -1.0f,  1.0f, // 19
         // Góra
         -1.0f,  1.0f, -1.0f, // 20
          1.0f,  1.0f, -1.0f, // 21
          1.0f,  1.0f,  1.0f, // 22
         -1.0f,  1.0f,  1.0f  // 23
    };

    /**
     * \var texCoords
     * \brief Tablica współrzędnych tekstury dla każdej ściany sześcianu.
     */
    const GLfloat texCoords[] = {
        // Przód
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Tył
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Lewa
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Prawa
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Dół
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Góra
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    /**
     * \var indices
     * \brief Tablica indeksów dla każdej ściany sześcianu.
     */
    const GLuint indices[] = {
        // Przód
        0, 1, 2, 3,
        // Tył
        4, 5, 6, 7,
        // Lewa
        8, 9, 10, 11,
        // Prawa
        12, 13, 14, 15,
        // Dół
        16, 17, 18, 19,
        // Góra
        20, 21, 22, 23
    };

    /**
     * \var normals
     * \brief Tablica wektorów normalnych dla każdej ściany sześcianu.
     */
    const GLfloat normals[] = {
        0.0f,  0.0f, -1.0f, // Przód
        0.0f,  0.0f,  1.0f, // Tyl
       -1.0f,  0.0f,  0.0f, // Lewa
        1.0f,  0.0f,  0.0f, // Prawa
        0.0f, -1.0f,  0.0f, // Dół
        0.0f,  1.0f,  0.0f  // Góra
    };

    // Włącz tablice wierzchołków, normalnych i współrzędnych tekstury
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    // Rysuj sześcian
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);

    // Wyłącz tablice wierzchołków, normalnych i współrzędnych tekstury
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

/**
 * \brief Zwraca transformację sześcianu.
 * \return Obiekt Transform reprezentujący transformację sześcianu.
 */
Transform& Cube::getTransform() {
    return transform;
}