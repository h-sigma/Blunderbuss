#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
	};
}

namespace Para
{
	enum Paralayer
	{
		Cyberpunk_back = 0, Cyberpunk_far = 1, Cyberpunk_fore = 2
	};
}

namespace TileSet
{
	enum ID
	{

	};
}

namespace Fonts
{
	enum ID
	{
	};
}

namespace Shaders
{
	enum ID
	{
	};
}

namespace Music
{
	enum ID
	{
	};	
}

namespace SoundEffect
{
	enum ID
	{
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>		 TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>				 FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID> 		 ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;

#endif // RESOURCEIDENTIFIERS_HPP