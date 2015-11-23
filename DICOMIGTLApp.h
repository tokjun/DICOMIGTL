#ifndef DICOMIGTLApp_h
#define DICOMIGTLApp_h

#include <QtGui> 

#include "ui_DICOMIGTLWindow.h"
#include "igtlMultiThreader.h"
#include "igtlTCPConnectorServerOIGTL.h"
#include "igtlTCPConnectorDICOMDirectoryMonitor.h"
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
 
  void directoryMonitorActivateClicked();
  void clientActivateClicked();
  void pbInputDirectoryClicked();
  void pbProcessedDirectoryClicked();

  void inputDirectoryChanged( const QString & text );
  void processedDirectoryChanged( const QString & text );
  void igtlPortChanged( const QString & text );
  
  void updateStatus();
  void quit();

private:

  void changeStatusTextColor(QLineEdit* le, int status);
  void changeDataIOTextColor(QLineEdit* le, int status);

  QTimer *timer;
  igtl::MultiThreader::Pointer Threader;
  igtl::TCPConnectorServerOIGTL::Pointer oigtlConnector;
  igtl::TCPConnectorDICOMDirectoryMonitor::Pointer dicomConnector;

  bool fDirectoryMonitorActive;
  bool fClientActive;

  QString scannerAddress;
  QString imagePort;
  QString controlPort;
  QString igtlPort;


};
 
 
#endif

