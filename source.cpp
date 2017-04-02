#include "tichucounter.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  TichuCounter window;

  window.resize(320, 190);
  window.setWindowTitle("Tichu Counter");
  window.show();

  return app.exec();
}
