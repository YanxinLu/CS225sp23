#include "StickerSheet.h"

int main() {
  //test
  /*
  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");
  Image xc;
  xc.readFromFile("stickers/xc.png");
  xc.scale(0.5);
  //xc.grayscale();
  //xc.illinify();
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 250);
  // sheet.addSticker(i, 80, 300);
  // sheet.addSticker(i, 100, 300);
  // sheet.addSticker(i, 150, 300);
  // sheet.changeMaxStickers(6);
  // sheet.addSticker(i, 200, 300);
  // sheet.removeSticker(3);
  Image* change = sheet.getSticker(1);
  *change = xc;
  sheet.translate(0,200,200);
  std::cout<<alma.width()<<"     "<<alma.height()<<std::endl;
  std::cout<<i.width()<<"     "<<i.height()<<std::endl;
  Image mine;
  mine = sheet.render();
  std::cout<<mine.width()<<"     "<<mine.height()<<std::endl;
  mine.writeToFile("xctest2.png");
  */
  Image dog,man,background,expr,zjui;
  background.readFromFile("mystickers/background.png");
  dog.readFromFile("mystickers/dog.png");
  man.readFromFile("mystickers/man.png");
  expr.readFromFile("mystickers/expression.png");
  zjui.readFromFile("mystickers/zjui.png");
  StickerSheet sheet(background,6);
  sheet.addSticker(man,320,42);
  sheet.addSticker(dog,30,145);
  sheet.addSticker(dog,45,466);
  sheet.addSticker(dog,355,446);
  sheet.addSticker(expr,15,360);
  sheet.addSticker(zjui,330,355);
  Image* dog1 = sheet.getSticker(1);
  Image* dog2 = sheet.getSticker(2);
  dog1->scale(0.8);
  dog2->scale(0.9);
  Image myImage;
  myImage = sheet.render();
  myImage.writeToFile("myImage.png");
  return 0;
}
