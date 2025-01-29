Sprawozdanie Silnik 3D

Wstęp
Sprawozdanie przedstawia instrukcję obsługi dla silnika 3D. Nasz silnik umożliwia renderowanie obiektów 3D, takich jak sześciany i prostopadłościany, z obsługą transformacji, oświetlenia, teksturowania oraz cieniowania. Silnik obsługuje również klawiaturę i mysz, zmienną szybkość odświeżania i tekstury obiektów.

Opis Silnika 3D
Silnik 3D jest napisany w języku C++ z wykorzystaniem bibliotek OpenGL i GLFW. Umożliwia renderowanie prymitywów 3D, takich jak sześciany i prostopadłościany, z obsługą ich transformacji (przemieszczanie, rotacja, skalowanie.. Silnik obsługuje również teksturowanie obiektów, oświetlenie, cieniowanie oraz różnorodne interakcje użytkownika.


Użytkowanie
Podstawowe Funkcje
- Rysowanie Prymitywów - Aplikacja umożliwia rysowanie sześcianów i prostopadłościanów z wykorzystaniem klas `Cube` i `Rectangle`.
- Transformacje - Obiekty mogą być przemieszczane, obracane i skalowane za pomocą metod klasy `Transform`.
- Oświetlenie - Aplikacja obsługuje oświetlenie, które można włączyć i wyłączyć.
- Cieniowanie - Aplikacja obsługuje cieniowanie, które można włączyć i wyłączyć.
- Teksturowanie - Obiekty mogą być teksturowane za pomocą klasy `BitmapHandler`, poprzez dodawanie tekstur z pliku.
- Poruszanie Kamerą - Dzięki klasie ‘Observer’, możliwe jest poruszanie kamerą i obserwowanie sceny z różnych perspektyw.
Obsługa Klawiszy
- Escape - Naciśnięcie klawisza Escape zamyka aplikację.
- Oświetlenie - Naciśnięcie klawisza `PPM` na myszce przełącza oświetlenie.
- Cieniowanie - Naciśnięcie klawisza `SPACJA` przełącza cieniowanie.
- Rotacja - Naciśnięcie klawisza `R` przełącza automatyczną rotację obiektów. Użycie ‘SCROLL’ na myszce pozwala na manualne rotowanie obiektów.
- Zmiana FPS - Naciśnięcie klawisza ‘-’ lub ‘_’ zmniejsza ilość FPSów, naciśnięcie klawisza ‘+’ lub ‘=’ umożliwia zwiększenie ilości FPSów (o 10 FPSów za każdym kliknięciem w obu przypadkach)
- Poruszanie Kamerą - Naciśnięcie klawiszy ‘W’, ‘S’, ‘A’, ‘D’ pozwala na poruszanie kamerą odpowiednio: do przodu, do tyłu, w lewo, w prawo.
- Poruszanie Szczęściem- Naciśnięcie klawiszy ’Arrow Up’, ‘Arrow Down’, ‘Arrow Left’, ‘Arrow Right’ pozwala na poruszanie sześcianem odpowiednio: do przodu, do tyłu, w lewo, w prawo.
- Poruszanie Prostopadłościanem- Naciśnięcie klawiszy ‘I’, ‘K’, ‘J’, ‘L’ pozwala na poruszanie prostopadłościanem odpowiednio: do przodu, do tyłu, w lewo, w prawo.

Podsumowanie
Niniejsza instrukcja obsługi ma na celu ułatwienie użytkowania silnika 3D.


