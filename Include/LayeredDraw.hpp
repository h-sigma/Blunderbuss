#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace sf {
	class RenderStates;
	class RenderTarget;
};

class LayeredDraw :  public sf::Drawable, public sf::NonCopyable
{
public:
	using ID_size = uint64_t;
	enum DRAWABLE_STATUS : bool {
		DRAWABLE_FOUND = true, DRAWABLE_NOT_FOUND = false
	};
	enum LAYER : short {
		B2 = -200, B1 = -100, G = 0, F1 = 100, F2 = 200,
		UNDERGROUND = B1, GROUND = G, AIR = F1
	};
public:
	explicit LayeredDraw() = default;
	LayeredDraw(const LayeredDraw&) = delete;
	LayeredDraw(LayeredDraw&&) = delete;
	ID_size addDrawable(sf::Drawable*, short);
	ID_size addDrawable(sf::Drawable&, short);

	//API for existing Drawables (Minimize usage as they're all O(n))
	void removeDrawable(ID_size);
	void changeHeight(ID_size, short);
	short getCurrentHeight(ID_size);
	DRAWABLE_STATUS getDrawableStatus(ID_size) const;

	//enhanced API
private:
	ID_size getNextID() const;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	struct HeightDrawable{
		sf::Drawable* drawable;
		ID_size ID;
		short height;
		friend bool operator==(const HeightDrawable& lhs, const HeightDrawable& rhs)
		{	//identity is ID
			return lhs.ID == rhs.ID;
		}
		friend bool operator==(const HeightDrawable& lhs, const ID_size& rhs)
		{	//identity is ID
			return lhs.ID == rhs;
		}
		friend bool operator<(const HeightDrawable& lhs, const HeightDrawable& rhs)
		{	//order is height
			return lhs.height < rhs.height;
		}
		friend bool operator<(const HeightDrawable& lhs, const short& rhs)
		{	//order is height
			return lhs.height < rhs;
		}
	};
private:
	mutable ID_size mNextID = 0;
	std::vector<HeightDrawable> mDrawables;
};
