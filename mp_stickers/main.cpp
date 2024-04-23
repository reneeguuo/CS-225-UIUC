#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image keepCalm;
  keepCalm.readFromFile("KeepCalm.png");

  Image sticker1;
  sticker1.readFromFile("Maldanado.png");
  Image sticker2;
  sticker2.readFromFile("GoalKeeper.png");
  Image sticker3;
  sticker3.readFromFile("pole-vaulting.png");
  Image sticker4;
  sticker4.readFromFile("Tennis.png");



  StickerSheet finalImage(keepCalm, 4);
  sticker1.scale(0.68);
  sticker2.scale(0.40);
  sticker3.scale(0.45);
  sticker4.scale(0.38);
  finalImage.addSticker(sticker1, 1, 1);
  finalImage.addSticker(sticker2, 850, 1);
  finalImage.addSticker(sticker3, 1, 1300);
  finalImage.addSticker(sticker4, 800, 1300);
  Image picture = finalImage.render();
  picture.writeToFile("myImage.png");


  return 0;
}
