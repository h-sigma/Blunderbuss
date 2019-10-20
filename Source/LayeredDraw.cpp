#include <LayeredDraw.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <algorithm>

//std::basic_string<HeightDrawable> mDrawables;

LayeredDraw::ID_size LayeredDraw::addDrawable(sf::Drawable* drawable, short height)
{
	ID_size recentID = getNextID();
	auto insert_here = std::lower_bound(mDrawables.begin(), mDrawables.end(), height);	//using binary search
	mDrawables.insert(insert_here, { drawable, recentID, height });
	return recentID;
}

LayeredDraw::ID_size LayeredDraw::addDrawable(sf::Drawable& drawable, short height)
{
	return addDrawable(&drawable, height);
}

void LayeredDraw::removeDrawable(ID_size id)
{
	auto erase_this = std::remove(mDrawables.begin(), mDrawables.end(), id);
	mDrawables.erase(erase_this, mDrawables.end());
}

void LayeredDraw::changeHeight(ID_size id, short h)
{
	auto mutate_this = std::find(mDrawables.begin(), mDrawables.end(), id);
	mutate_this->height = h;
    (void)mutate_this;
}

short LayeredDraw::getCurrentHeight(ID_size id)
{
	return std::find(mDrawables.begin(), mDrawables.end(), id)->height;
}

LayeredDraw::ID_size LayeredDraw::getNextID() const
{
	return mNextID++;
}

//minimize usage of this function
LayeredDraw::DRAWABLE_STATUS LayeredDraw::getDrawableStatus(ID_size id) const
{
	auto found_it = std::find(mDrawables.begin(), mDrawables.end(), id);
	if (found_it == mDrawables.end())
		return DRAWABLE_NOT_FOUND;
	else
		return DRAWABLE_FOUND;
}


void LayeredDraw::draw(sf::RenderTarget& target, sf::RenderStates states)  const
{
	for (auto& HD : mDrawables)
		target.draw(*HD.drawable, states);
}