/*=========================================================================

  Program:   Connector Server Class for DICOM OpenIGTLink Server
  Module:    $RCSfile: $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// NOTE: 
//  This class monitors a specfied directory to find new DICOM images
//  exported by medical imaging scanners or other software.
//  Although the class is implemented as a chlid class of TCP server,
//  it does not work as a DICOM listener at this moment.


#ifndef __TCPConnectorDICOMDirectoryMonitor_H
#define __TCPConnectorDICOMDirectoryMonitor_H

#include "igtlWin32Header.h"
#include "igtlMultiThreader.h"
#include "igtlServerSocket.h"
#include "igtlMessageHeader.h"

#include "igtlTCPConnectorServer.h"

namespace igtl
{

class IGTLCommon_EXPORT TCPConnectorDICOMDirectoryMonitor : public TCPConnectorServer
{
public:
  
  typedef TCPConnectorDICOMDirectoryMonitor   Self;
  typedef Object  Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  igtlTypeMacro(igtl::TCPConnectorDICOMDirectoryMonitor, igtl::TCPConnectorServer)
  igtlNewMacro(igtl::TCPConnectorDICOMDirectoryMonitor);

public:

  virtual const char * GetClassName() { return "OpenIGTLink"; };
  int SetMessageHandler();
  virtual int    PushMessage(igtl::MessageBase * message);

protected:

  TCPConnectorDICOMDirectoryMonitor();
  ~TCPConnectorDICOMDirectoryMonitor();

  void PrintSelf(std::ostream& os) const;

  virtual int Initialize();
  virtual int ReceiveMessage();
  virtual int Finalize();

  // WaitForConnection() is overrode to always return 1. 
  virtual int WaitForConnection() { return 1; };

private:
  
  igtl::MessageHeader::Pointer HeaderMsg;

};

}

#endif //__THREAD_H
