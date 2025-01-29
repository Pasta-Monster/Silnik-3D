#pragma once

/**
 * \class Transform
 * \brief Klasa reprezentująca transformacje w przestrzeni 3D, takie jak translacja, rotacja i skalowanie.
 */
class Transform {
public:
    /**
     * \brief Konstruktor domyślny klasy Transform.
     * Inicjalizuje przemieszczenie, rotację i skalowanie.
     */
    Transform();

    /**
     * \brief Przemieszcza obiekt.
     *
     * \param dx Przemieszczenie w osi X.
     * \param dy Przemieszczenie w osi Y.
     * \param dz Przemieszczenie w osi Z.
     */
    void translate(float dx, float dy, float dz);

    /**
     * \brief Obraca obiekt.
     *
     * \param angle Kąt obrotu w stopniach.
     * \param x Wektor obrotu w osi X.
     * \param y Wektor obrotu w osi Y.
     * \param z Wektor obrotu w osi Z.
     */
    void rotate(float angle, float x, float y, float z);

    /**
     * \brief Skaluje obiekt.
     *
     * \param sx Skalowanie w osi X.
     * \param sy Skalowanie w osi Y.
     * \param sz Skalowanie w osi Z.
     */
    void scale(float sx, float sy, float sz);

    /**
     * \brief Zastosowuje transformacje w OpenGL.
     */
    void apply(); // Zastosowanie transformacji w OpenGL

private:
    float translationX, translationY, translationZ; ///< Przemieszczenie w osiach X, Y, Z.
    float rotationAngle, rotationX, rotationY, rotationZ; ///< Rotacja: kąt i wektor w osiach X, Y, Z.
    float scaleX, scaleY, scaleZ; ///< Skalowanie w osiach X, Y, Z.
};