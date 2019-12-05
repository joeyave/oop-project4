#ifndef SFML_DRAWABLE_HPP
#define SFML_DRAWABLE_HPP
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>


namespace sf
{
	class RenderTarget;
	class SFML_GRAPHICS_API Drawable
	{
	public:
		virtual ~Drawable() {}

	protected:

		friend class RenderTarget;
		virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	};

}

#endif