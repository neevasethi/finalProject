#include "TextureManager.h"
#include <string>
std::unordered_map<std::string, sf::Texture> TextureManager::texture;
void TextureManager::LoadTexture(const char* FileName) {
	std::string path = "images/";
	path += FileName;
	path += ".png";
	texture[FileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(const char* textureKey) {
	if (texture.find(textureKey) == texture.end())
		LoadTexture(textureKey);
	return texture[textureKey];
}

void TextureManager::Clear() {
	texture.clear();
}
