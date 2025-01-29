#pragma once
#include <GLFW/glfw3.h>

/**
 * \class Primitive
 * \brief Abstrakcyjna klasa bazowa dla prymitywów graficznych.
 */
class Primitive {
public:
    /**
     * \brief Wirtualna funkcja do rysowania prymitywu.
     *
     * Metoda ta musi być zaimplementowana przez klasy dziedziczące.
     */
    virtual void draw() = 0;  // Wirtualna funkcja do rysowania
};