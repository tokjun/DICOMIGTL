/*=========================================================================

  Program:   
  Module:    $HeadURL: http://svn.na-mic.org/NAMICSandBox/trunk/OpenIGTLink/Source/igtlSocket.cxx $
  Language:  C++
  Date:      $Date: 2010-06-09 16:16:36 -0400 (Wed, 09 Jun 2010) $
  Version:   $Revision: 6525 $

  Copyright (c) Brigham and Women's Hospital. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "igtlSocket.h"

#include <string.h>

#include "igtlTCPConnectorDICOMDirectoryMonitor.h"
#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"

namespace igtl
{

//-----------------------------------------------------------------------------
TCPConnectorDICOMDirectoryMonitor::TCPConnectorDICOMDirectoryMonitor()
{
}


//-----------------------------------------------------------------------------
TCPConnectorDICOMDirectoryMonitor::~TCPConnectorDICOMDirectoryMonitor()
{
}


//-----------------------------------------------------------------------------
void TCPConnectorDICOMDirectoryMonitor::PrintSelf(std::ostream& os) const
{
  this->Superclass::PrintSelf(os);
}


//-----------------------------------------------------------------------------
int TCPConnectorDICOMDirectoryMonitor::PushMessage(igtl::MessageBase * message)
{
  if (this->Status == STATUS_CONNECTED)
    {
    }

  return 0;
}


//-----------------------------------------------------------------------------
int TCPConnectorDICOMDirectoryMonitor::Initialize()
{
  if (TCPConnectorServer::Initialize())
    {
    return 1;
    }
  else
    {
    return 0;
    }
}

//-----------------------------------------------------------------------------
int TCPConnectorDICOMDirectoryMonitor::ReceiveMessage()
{

  if (this->Active)
    {
    std::cerr << "int TCPConnectorDICOMDirectoryMonitor::ReceiveMessage()" << std::endl;
    igtl::Sleep(100);
    return 1;
    }
  else
    {
    return 0;
    }

}


//-----------------------------------------------------------------------------
int TCPConnectorDICOMDirectoryMonitor::Finalize()
{
  if (TCPConnectorServer::Finalize())
    {
    return 1;
    }
  return 0;
}


} // End of igtl namespace






