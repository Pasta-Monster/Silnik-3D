/**
 * \file BitmapHandler.cpp
 * \brief Implementacja klasy BitmapHandler.
 */

#include "BitmapHandler.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

 /**
  * \brief Konstruktor domyślny klasy BitmapHandler.
  * Ustawia początkowe wartości szerokości, wysokości i liczby kanałów na 0.
  */
BitmapHandler::BitmapHandler() : width(0), height(0), channels(0) {}

/**
 * \brief Destruktor klasy BitmapHandler.
 * Nie ma potrzeby jawnego zwalniania pamięci tekstury, ponieważ std::vector zarządza pamięcią automatycznie.
 */
BitmapHandler::~BitmapHandler() {}

/**
 * \brief Ładuje teksturę z pliku.
 *
 * Funkcja próbuje załadować teksturę z pliku o podanej ścieżce. Jeśli operacja się powiedzie,
 * dane tekstury są przechowywane w wektorze textureData.
 *
 * \param filePath Ścieżka do pliku z teksturą.
 * \return Zwraca true, jeśli tekstura została załadowana pomyślnie, w przeciwnym razie false.
 */
bool BitmapHandler::LoadTextureFromFile(const std::string& filePath) {
    std::cout << "Proba załadowania pliku: " << filePath << std::endl;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (data) {
        std::cout << "Plik załadowany pomyslnie: " << filePath << std::endl;
        textureData.assign(data, data + (width * height * channels));
        stbi_image_free(data);
        return true;
    }
    else {
        std::cerr << "Blad ladowania pliku: " << filePath << " - " << stbi_failure_reason() << std::endl;
        return false;
    }
}

/**
 * \brief Zwraca dane tekstury.
 *
 * \return Referencja do wektora przechowującego dane tekstury.
 */
const std::vector<unsigned char>& BitmapHandler::GetTextureData() const {
    return textureData;
}

/**
 * \brief Zwraca szerokość tekstury.
 *
 * \return Szerokość tekstury w pikselach.
 */
int BitmapHandler::GetWidth() const {
    return width;
}

/**
 * \brief Zwraca wysokość tekstury.
 *
 * \return Wysokość tekstury w pikselach.
 */
int BitmapHandler::GetHeight() const {
    return height;
}

/**
 * \brief Zwraca liczbę kanałów tekstury.
 *
 * \return Liczba kanałów tekstury.
 */
int BitmapHandler::GetChannels() const {
    return channels;
}