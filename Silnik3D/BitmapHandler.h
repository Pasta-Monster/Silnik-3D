#ifndef BITMAPHANDLER_H
#define BITMAPHANDLER_H

#include <string>
#include <vector>

/**
 * \class BitmapHandler
 * \brief Klasa do obsługi bitmap, w tym ładowania tekstur z pliku.
 */
class BitmapHandler {
public:
    /**
     * \brief Konstruktor domyślny klasy BitmapHandler.
     */
    BitmapHandler();

    /**
     * \brief Destruktor klasy BitmapHandler.
     */
    ~BitmapHandler();

    /**
     * \brief Ładuje teksturę z pliku.
     *
     * \param filePath Ścieżka do pliku z teksturą.
     * \return Zwraca true, jeśli tekstura została załadowana pomyślnie, w przeciwnym razie false.
     */
    bool LoadTextureFromFile(const std::string& filePath);

    /**
     * \brief Zwraca dane tekstury.
     *
     * \return Stała referencja do wektora danych tekstury.
     */
    const std::vector<unsigned char>& GetTextureData() const;

    /**
     * \brief Zwraca szerokość tekstury.
     *
     * \return Szerokość tekstury.
     */
    int GetWidth() const;

    /**
     * \brief Zwraca wysokość tekstury.
     *
     * \return Wysokość tekstury.
     */
    int GetHeight() const;

    /**
     * \brief Zwraca liczbę kanałów kolorów tekstury.
     *
     * \return Liczba kanałów kolorów tekstury.
     */
    int GetChannels() const;

private:
    int width; ///< Szerokość tekstury.
    int height; ///< Wysokość tekstury.
    int channels; ///< Liczba kanałów kolorów tekstury.
    std::vector<unsigned char> textureData; ///< Dane tekstury.
};

#endif // BITMAPHANDLER_H