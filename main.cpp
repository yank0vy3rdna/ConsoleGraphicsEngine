#include <iostream>
#include <locale>
#include <ostream>
#include "drawille.hpp"
#include <curses.h>
#include <locale.h>
#include <unistd.h>

using namespace Drawille;
using std::wcout;
using std::wostream;
using std::locale;
int screen_width = 60*2;
int screen_height = 30*4;
void render(std::string& str){
     clear();
     printw("%s",str.c_str());
     refresh();
     usleep(20000);
}
void clear(Canvas& canvas, int width, int height){
    for (int i = 0; i < width; i++){
        for( int j = 0; j < height; j++){
            canvas.unset(i,j);
        }
    }
}
int main()
{
  setlocale(LC_ALL, "");
  initscr();

  Canvas canvas(screen_width / 2, screen_height/4); 
  for(int i = 0; i < screen_width; ++i) {
    for(int j = 0; j < screen_height;++j){
        canvas.set(i, j);
    }
  }

  std::string str("");
  canvas.draw(str);
  render(str);
  int x = 0;
  while(true){
      clear(canvas, screen_width, screen_height);
      if (x != screen_width -1){
          x += 1;
      }else{
          x = 0;
      }
      for(int i = 0; i < screen_height; ++i){    
          canvas.set(x, i);
      }
      //break;
      canvas.draw(str);
      render(str);
  }


  getch();
  endwin();
  return 0;
}
