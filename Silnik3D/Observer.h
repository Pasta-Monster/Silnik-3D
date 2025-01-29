#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * \class Observer
 * \brief Klasa reprezentująca obserwatora (kamerę) w przestrzeni 3D.
 */
class Observer {
public:
    /**
     * \brief Konstruktor domyślny klasy Observer.
     * Inicjalizuje pozycję obserwatora na (0.0f, 0.0f, -5.0f).
     */
    Observer();

    /**
     * \brief Ustawia pozycję obserwatora.
     *
     * \param x Pozycja w osi X.
     * \param y Pozycja w osi Y.
     * \param z Pozycja w osi Z.
     */
    void setPosition(float x, float y, float z);

    /**
     * \brief Przesuwa obserwatora o zadane wartości.
     *
     * \param dx Przesunięcie w osi X.
     * \param dy Przesunięcie w osi Y.
     * \param dz Przesunięcie w osi Z.
     */
    void move(float dx, float dy, float dz);

    /**
     * \brief Zastosowuje widok obserwatora.
     * Przesuwa scenę o pozycję obserwatora.
     */
    void applyView();

private:
    float posX, posY, posZ; ///< Pozycja obserwatora w osiach X, Y, Z.
};

#endif // OBSERVER_H