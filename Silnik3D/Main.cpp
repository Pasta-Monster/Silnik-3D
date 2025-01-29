/**
 * \file main.cpp
 * \brief Główna funkcja programu uruchamiającego silnik.
 */

#include "Engine.h"

 /**
  * \brief Główna funkcja programu.
  *
  * Tworzy instancję silnika, inicjalizuje ją i uruchamia główną pętlę renderowania.
  *
  * \return Zwraca 0, jeśli program zakończy się pomyślnie, lub -1 w przypadku błędu inicjalizacji.
  */
int main() {
    Engine engine;

    // Inicjalizacja silnika
    if (!engine.init()) {
        return -1;
    }

    // Uruchomienie głównej pętli
    engine.run();
    return 0;
}