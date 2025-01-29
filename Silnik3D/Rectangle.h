#pragma once
#include "Primitive.h"
#include "Transform.h"

/**
 * \class Rectangle
 * \brief Klasa reprezentująca prostopadłościan, dziedzicząca po klasie Primitive.
 */
class Rectangle : public Primitive {
public:
    /**
     * \brief Rysuje prostopadłościan.
     *
     * Metoda nadpisująca metodę draw() z klasy Primitive.
     */
    void draw() override;

    /**
     * \brief Zwraca transformację prostopadłościanu.
     *
     * \return Obiekt Transform reprezentujący transformację prostopadłościanu.
     */
    Transform& getTransform(); // Dostęp do transformacji

private:
    Transform transform; ///< Obiekt Transform przechowujący transformację prostopadłościanu.
};