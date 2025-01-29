#pragma once
#include "Primitive.h"
#include "Transform.h"

/**
 * \class Cube
 * \brief Klasa reprezentująca sześcian, dziedzicząca po klasie Primitive.
 */
class Cube : public Primitive {
public:
    /**
     * \brief Rysuje sześcian.
     *
     * Metoda nadpisująca metodę draw() z klasy Primitive.
     */
    void draw() override;

    /**
     * \brief Zwraca transformację sześcianu.
     *
     * \return Obiekt Transform reprezentujący transformację sześcianu.
     */
    Transform& getTransform(); // Dostęp do transformacji

private:
    Transform transform; ///< Obiekt Transform przechowujący transformację sześcianu.
};