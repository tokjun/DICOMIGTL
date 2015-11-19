#include <iostream>
#include <QtGui> 

#include "DICOMIGTLApp.h"
 

#include "igtlOSUtil.h"
#include "igtlImageMessage.h"
#include "igtlServerSocket.h"
#include "igtlMultiThreader.h"
#include "igtlOSUtil.h"
#include "igtlTCPConnectorServerOIGTL.h"

const int DICOMIGTLApp::StatusColorTable[][3] = {
  {100, 100, 100},  // STOP
  {100, 100, 200},  // WAITING
  {100, 200, 100},  // CONNECTED
  {200, 100, 100}   // ERROR
};

const int DICOMIGTLApp::DataIOColorTable[][3] = {
  {50, 50, 50},        // None
  {100, 200, 100},  // Received
  {200, 100, 100}   // ERROR
};

 
DICOMIGTLApp::DICOMIGTLApp(QWidget *parent)
{
  setupUi(this); // this sets up GUI

  fScannerActive = false;
  fClientActive  = false;

  // Signals and Slots
  connect(pbQuit, SIGNAL( clicked() ), this, SLOT( quit() ));
  connect(pbAbout, SIGNAL( clicked() ), this, SLOT( about() ));
  connect(pbScannerActivate, SIGNAL( clicked() ), this, SLOT( scannerActivateClicked() ));
  connect(pbClientActivate, SIGNAL( clicked() ), this, SLOT( clientActivateClicked() ));

  connect(leScannerAddress, SIGNAL( textChanged( const QString &  ) ),
          this, SLOT( scannerAddressChanged( const QString &  ) ));
  connect(leControlPort, SIGNAL( textChanged( const QString & ) ),
          this, SLOT( controlPortChanged( const QString & ) ));
  connect(leImagePort, SIGNAL( textChanged( const QString &  ) ),
          this, SLOT( imagePortChanged( const QString & ) ));
  connect(leOpenIGTLinkPort, SIGNAL( textChanged( const QString & ) ),
          this, SLOT( igtlPortChanged( const QString &  ) ));

  // Default values
  QString qs;
  leScannerAddress->setText("localhost");
  leControlPort->setText(qs.setNum(DEFAULT_OIGTL_PORT));
  leImagePort->setText(qs.setNum(DEFAULT_OIGTL_PORT));
  leOpenIGTLinkPort->setText(qs.setNum(DEFAULT_OIGTL_PORT));

  // Time for GUI update (every 200 ms)
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateStatus()));
  timer->start(200); 
  
  //// OpenIGTLink Server Socket
  oigtlConnector = igtl::TCPConnectorServerOIGTL::New();
  oigtlConnector->SetPort(18944);
  
  // Connect connectors
  //oigtlConnector->SetOutputConnector(rmpConnector);
  //spiceConnector->SetOutputConnector(oigtlConnector);
  
  this->Threader = igtl::MultiThreader::New();
  this->Threader->SpawnThread((igtl::ThreadFunctionType) &igtl::TCPConnectorServerOIGTL::MonitorThreadFunction,
                              oigtlConnector);


}
 
 
void DICOMIGTLApp::getPath()
{
    QString path;
    
    //path = QFileDialog::getOpenFileName(
    //    this,
    //    "Choose a file to open",
    //    QString::null,
    //    QString::null);
    //
    //lineEdit->setText( path );
}
 
 
void DICOMIGTLApp::about() 
{
  QMessageBox::about(this,"About DICOMIGTL",
                     "DICOM OpenIGTLink Server\n\n"
                     "Copyright (C) 2015\n"
                     "Brigham and Women's Hospital.\n\n"
                     );
}

void DICOMIGTLApp::scannerActivateClicked()
{
  if (fScannerActive)
    {
    pbScannerActivate->setText("Activate");
    fScannerActive = false;
    //if (spiceConnector.IsNotNull())
    //  {
    //  spiceConnector->Deactivate();
    //  }
    //if (rmpConnector.IsNotNull())
    //  {
    //  rmpConnector->Deactivate();
    //  }
    }
  else
    {
    pbScannerActivate->setText("Deactivate");
    fScannerActive = true;
    }
}


void DICOMIGTLApp::clientActivateClicked()
{
  if (fClientActive)
    {
    pbClientActivate->setText("Activate");
    fClientActive = false;
    if (oigtlConnector.IsNotNull())
      {
      oigtlConnector->Deactivate();
      
      }
    }
  else
    {
    pbClientActivate->setText("Deactivate");
    fClientActive = true;
    if (oigtlConnector.IsNotNull())
      {
      std::cerr << "Activating OpenIGTLink connector with:" << std::endl;
      std::cerr << "    Port: " << igtlPort.toInt() << std::endl;
      oigtlConnector->SetPort(igtlPort.toInt());
      oigtlConnector->Activate();
      }
    }
}


void DICOMIGTLApp::scannerAddressChanged( const QString & text )
{
  scannerAddress = text;
}

void DICOMIGTLApp::imagePortChanged( const QString & text )
{
  imagePort = text;
}

void DICOMIGTLApp::controlPortChanged( const QString & text )
{
  controlPort = text;
}

void DICOMIGTLApp::igtlPortChanged( const QString & text )
{
  igtlPort = text;
}

void DICOMIGTLApp::changeStatusTextColor(QLineEdit* le, int status)
{
  if (status < igtl::TCPConnectorBase::STATUS_NUM && status >= 0)
    {
    QPalette p = le->palette();
    p.setColor( le->backgroundRole(),
                QColor(StatusColorTable[status][0],
                       StatusColorTable[status][1],
                       StatusColorTable[status][2]) );
    le->setPalette(p);
    }
}

void DICOMIGTLApp::changeDataIOTextColor(QLineEdit* le, int status)
{
  if (status < 3 && status >= 0)
    {
    QPalette p = le->palette();
    p.setColor( le->backgroundRole(),
                QColor(DataIOColorTable[status][0],
                       DataIOColorTable[status][1],
                       DataIOColorTable[status][2]) );
    le->setPalette(p);
    }
}

void DICOMIGTLApp::updateStatus() 
{
  bool editClientFlag = true;
  bool editScannerFlag = true;
  if (oigtlConnector.IsNotNull())
    {
    leStatusClient->setText(oigtlConnector->GetStatusString());
    changeStatusTextColor(leStatusClient, oigtlConnector->GetStatus());
    leOpenIGTLinkPort->setEnabled(oigtlConnector->GetStatus() == igtl::TCPConnectorBase::STATUS_STOP);
    editClientFlag &= oigtlConnector->GetStatus() == igtl::TCPConnectorBase::STATUS_STOP;
    }
  leScannerAddress->setEnabled(editScannerFlag);
  leControlPort->setEnabled(editScannerFlag);
  leImagePort->setEnabled(editClientFlag);
}

void DICOMIGTLApp::quit() 
{

  if (oigtlConnector.IsNotNull())
    {
    oigtlConnector->CloseThread();
    }
  
  std::cerr << "CLOSING..." << std::endl;
  timer->stop(); 
  close();
}


