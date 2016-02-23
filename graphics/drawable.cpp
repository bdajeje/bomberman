//#include "drawable.hpp"

//namespace graphics {

//Drawable::Drawable(std::shared_ptr<T>& object)
//  : _object {object}
//{}

//void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//  if(!isVisible())
//    return;

//  target.draw(*_object);
//}

//bool Drawable::hide()
//{
//  if( !isVisible() )
//    return false;

//  _is_visible = false;
//  return true;
//}

//bool Drawable::show()
//{
//  if( isVisible() )
//    return false;

//  _is_visible = true;
//  return true;
//}

//}
