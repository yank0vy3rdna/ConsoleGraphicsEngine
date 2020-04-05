#ifndef DRAWILLE_HPP
#define DRAWILLE_HPP

#include <vector>
#include <ostream>

namespace Drawille {
    std::string unicode_to_utf8(int unicode)
    {
        std::string s;

        if (unicode>=0 and unicode <= 0x7f)  // 7F(16) = 127(10)
        {
            s = static_cast<char>(unicode);
            return s;
        }
        else if (unicode <= 0x7ff)  // 7FF(16) = 2047(10)
        {
            unsigned char c1 = 192, c2 = 128;

            for (int k=0; k<11; ++k)
            {
                if (k < 6)  c2 |= (unicode % 64) & (1 << k);
                else c1 |= (unicode >> 6) & (1 << (k - 6));
            }

            s = c1;    s += c2;

            return s;
        }
        else if (unicode <= 0xffff)  // FFFF(16) = 65535(10)
        {
            unsigned char c1 = 224, c2 = 128, c3 = 128;

            for (int k=0; k<16; ++k)
            {
                if (k < 6)  c3 |= (unicode % 64) & (1 << k);
                else if (k < 12) c2 |= (unicode >> 6) & (1 << (k - 6));
                else c1 |= (unicode >> 12) & (1 << (k - 12));
            }
            s = c1;    s += c2;    s += c3;
            return s;
        }
        else if (unicode <= 0x1fffff)  // 1FFFFF(16) = 2097151(10)
        {
            unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

            for (int k=0; k<21; ++k)
            {
                if (k < 6)  c4 |= (unicode % 64) & (1 << k);
                else if (k < 12) c3 |= (unicode >> 6) & (1 << (k - 6));
                else if (k < 18) c2 |= (unicode >> 12) & (1 << (k - 12));
                else c1 |= (unicode >> 18) & (1 << (k - 18));
            }
            s = c1;    s += c2;    s += c3;    s += c4;
            return s;
        }
        else if (unicode <= 0x3ffffff)  // 3FFFFFF(16) = 67108863(10)
        {
            ;  // actually, there are no 5-bytes unicodes
        }
        else if (unicode <= 0x7fffffff)  // 7FFFFFFF(16) = 2147483647(10)
        {
            ;  // actually, there are no 6-bytes unicodes
        }
        else  ;  // incorrect unicode (< 0 or > 2147483647)
        return "";
    }
  using std::vector;
  using std::wostream;

  constexpr size_t pixmap[4][2] = {
    {0x01, 0x08},
    {0x02, 0x10},
    {0x04, 0x20},
    {0x40, 0x80}
  };

  constexpr int braille = 10240;

  class Canvas {
  public:
    Canvas(size_t width, size_t height) {
      this->canvas.resize(height);
      for(auto& v: this->canvas)
        v.resize(width);
    }

    void set(size_t x, size_t y) {
      if(x > (this->canvas[0].size() * 2) or x < 1) x = 0;
      if(y > (this->canvas.size() * 4) or y < 1)    y = 0;
      this->canvas[y / 4][x / 2] |= pixmap[y % 4][x % 2];
    }

    void unset(size_t x, size_t y) {
      if(x > (this->canvas[0].size() * 2) or x < 1) x = 0;
      if(y > (this->canvas.size() * 4) or y < 1)    y = 0;
      this->canvas[y / 4][x / 2] &= ~pixmap[y % 4][x % 2];
    }

    void draw(std::string& result) {
      result = "";
      for(auto& v: this->canvas) {
        for(auto& c: v) {
          if(c == 0) result.push_back(' ');
          else result += unicode_to_utf8(braille+c);
        }
        result += "\n";
      }
    }

  protected:
    vector<vector<int>> canvas;
  };
}

#endif
