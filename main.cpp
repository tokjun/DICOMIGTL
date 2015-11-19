#include <QApplication>
 
#include "DICOMIGTLApp.h"
 
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  DICOMIGTLApp *window = new DICOMIGTLApp;
  
  window->show();
  return app.exec();
}


