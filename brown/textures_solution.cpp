#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "textures_common.h"

using namespace std;

class Rectangle : public IShape {
private:
  shared_ptr<ITexture> texture;
  Point position;
  Size size;
public:
  Rectangle() = default;

  explicit Rectangle(shared_ptr<ITexture> t, Point p, Size s)
    : texture(move(t)), position(p), size(s) {};

  std::unique_ptr<IShape> Clone() const {
    return make_unique<Rectangle>(texture, position, size);
  };

  void SetPosition(Point p) {
    position = p;
  };

  Point GetPosition() const {
    return position;
  };

  void SetSize(Size s) {
    size = s;
  };

  Size GetSize() const {
    return size;
  };

  void SetTexture(std::shared_ptr<ITexture> t) {
    texture = move(t);
  };

  ITexture* GetTexture() const {
    return texture.get();
  };

  void Draw(Image& img) const {
    int right_x = min(position.x + size.width, static_cast<int>(img[0].size()));
    int right_y = min(position.y + size.height, static_cast<int>(img.size()));

    for (int y = position.y; y < right_y; ++y) {
      for (int x = position.x; x < right_x; ++x) {
        char pixel = GetPixelOnPoint({x - position.x, y - position.y});
        img[y][x] = pixel;
      }
    }
  };
private:
  char GetPixelOnPoint(Point p) const {
    if (GetTexture() == nullptr) {
      return '.';
    }

    if (p.x >= texture->GetSize().width || p.y >= texture->GetSize().height) {
      return '.';
    }

    return texture->GetImage().at(p.y).at(p.x);
  }
};

class Ellipse : public IShape {
private:
  shared_ptr<ITexture> texture;
  Point position;
  Size size;
public:
  Ellipse() = default;

  explicit Ellipse(shared_ptr<ITexture> t, Point p, Size s)
    : texture(move(t)), position(p), size(s) {};

  std::unique_ptr<IShape> Clone() const {
    return make_unique<Ellipse>(texture, position, size);
  };

  void SetPosition(Point p) {
    position = p;
  };

  Point GetPosition() const {
    return position;
  };

  void SetSize(Size s) {
    size = s;
  };

  Size GetSize() const {
    return size;
  };

  void SetTexture(std::shared_ptr<ITexture> t) {
    texture = move(t);
  };

  ITexture* GetTexture() const {
    return texture.get();
  };

  void Draw(Image& img) const {
    int right_x = min(position.x + size.width, static_cast<int>(img[0].size()));
    int right_y = min(position.y + size.height, static_cast<int>(img.size()));

    for (int y = position.y; y < right_y; ++y) {
      for (int x = position.x; x < right_x; ++x) {
        Point p{x - position.x, y - position.y};
        if (!IsPointInEllipse(p, size)) {
          continue;
        }

        char pixel = GetPixelOnPoint(p);
        img[y][x] = pixel;
      }
    }
  };
private:
  char GetPixelOnPoint(Point p) const {
    if (GetTexture() == nullptr) {
      return '.';
    }

    if (p.x >= texture->GetSize().width || p.y >= texture->GetSize().height) {
      return '.';
    }

    return texture->GetImage().at(p.y).at(p.x);
  }
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  if (shape_type == ShapeType::Rectangle) {
    return make_unique<Rectangle>();
  } else if (shape_type == ShapeType::Ellipse) {
    return make_unique<Ellipse>();
  } else {
    throw invalid_argument("");
  }
}