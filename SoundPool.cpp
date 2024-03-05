#include <SFML/Audio.hpp>
#include <vector>
class SoundPool {
public:
    SoundPool() {
        // Baþlangýçta belirli sayýda ses nesnesi oluþtur
        for (int i = 0; i < initialSize; ++i) {
            sf::Sound sound;
            sounds.push_back(sound);
        }
    }

    void play(const sf::SoundBuffer& buffer) {
        // Boþta olan bir ses nesnesi bul
        for (auto& sound : sounds) {
            if (sound.getStatus() != sf::Sound::Playing) {
                sound.setBuffer(buffer);
                sound.play();
                return;
            }
        }

        // Eðer tüm sesler meþgulse, yeni bir ses nesnesi oluþtur ve oynat
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        sounds.push_back(sound); // Havuza yeni ses nesnesini ekle
    }

private:
    std::vector<sf::Sound> sounds;
    const int initialSize = 10; // Ýlk oluþturulacak ses nesnesi sayýsý
};