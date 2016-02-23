//#ifndef DRAWABLE_HPP
//#define DRAWABLE_HPP

//#include <SFML/Graphics.hpp>

//#include <memory>

//namespace graphics {

///*
// * For now it's only a convenient class for object visibility (show/hide)
// */

//template <class T>
//class Drawable final : public sf::Drawable
//{
//  public:

//    Drawable(std::shared_ptr<T>& object);

//    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    T& object() { return *_object; }

//    bool isVisible() const { return _is_visible; }
//    bool hide();
//    bool show();

//  private:

//    bool _is_visible {true};
//    std::shared_ptr<T> _object;
//};

//}

//#endif // DRAWABLE_HPP
