#ifndef DICOMIGTLApp_h
#define DICOMIGTLApp_h

#include <QtGui> 

#include "ui_DICOMIGTLWindow.h"
#include "igtlMultiThreader.h"
#include "igtlTCPConnectorServerOIGTL.h"
//#include "igtlDICOMStorageObserver.h"

#define DEFAULT_OIGTL_PORT   18944
 
class DICOMIGTLApp : public QMainWindow, private Ui::DICOMIGTLWindow
{
  Q_OBJECT

public:
  static const int StatusColorTable[][3];
  static const int DataIOColorTable[][3];
    
public:
  DICOMIGTLApp(QWidget *parent = 0);

  
public slots:
  void getPath();
  void about();

  void scannerActivateClicked();
  void clientActivateClicked();

  void scannerAddressChanged( const QString & text );
  void imagePortChanged( const QString & text );
  void controlPortChanged( const QString & text );
  void igtlPortChanged( const QString & text );
  
  void updateStatus();
  void quit();

private:

  void changeStatusTextColor(QLineEdit* le, int status);
  void changeDataIOTextColor(QLineEdit* le, int status);

  QTimer *timer;
  igtl::MultiThreader::Pointer Threader;
  igtl::TCPConnectorServerOIGTL::Pointer oigtlConnector;

  bool fScannerActive;
  bool fClientActive;

  QString scannerAddress;
  QString imagePort;
  QString controlPort;
  QString igtlPort;


};
 
 
#endif

