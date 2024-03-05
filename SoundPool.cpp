#include <SFML/Audio.hpp>
#include <vector>
class SoundPool {
public:
    SoundPool() {
        // Ba�lang��ta belirli say�da ses nesnesi olu�tur
        for (int i = 0; i < initialSize; ++i) {
            sf::Sound sound;
            sounds.push_back(sound);
        }
    }

    void play(const sf::SoundBuffer& buffer) {
        // Bo�ta olan bir ses nesnesi bul
        for (auto& sound : sounds) {
            if (sound.getStatus() != sf::Sound::Playing) {
                sound.setBuffer(buffer);
                sound.play();
                return;
            }
        }

        // E�er t�m sesler me�gulse, yeni bir ses nesnesi olu�tur ve oynat
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        sounds.push_back(sound); // Havuza yeni ses nesnesini ekle
    }

private:
    std::vector<sf::Sound> sounds;
    const int initialSize = 10; // �lk olu�turulacak ses nesnesi say�s�
};