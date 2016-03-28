/****************************** Module Header ******************************\
* Module Name:  SampleService.h
* Project:      CppWindowsService
* Copyright (c) Microsoft Corporation.
* 
* Provides a sample service class that derives from the service base class - 
* CServiceBase. The sample service logs the service start and stop 
* information to the Application event log, and shows how to run the main 
* function of the service in a thread pool worker thread.
* 
* This source is subject to the Microsoft Public License.
* See http://www.microsoft.com/en-us/openness/resources/licenses.aspx#MPL.
* All other rights reserved.
* 
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
\***************************************************************************/

#pragma once

#include <Windows.h>
#include "service/serviceBase.h"
#include "raumserver/raumserver.h"
#include "tools/threadPool.h"


class RaumserverService : public CServiceBase
{
public:

    RaumserverService(std::string pszServiceName,
        BOOL fCanStop = TRUE, 
        BOOL fCanShutdown = TRUE, 
        BOOL fCanPauseContinue = FALSE);
    virtual ~RaumserverService(void);

protected:

    std::unique_ptr<Raumserver::Raumserver> raumserverObject;

    virtual void onStart(DWORD dwArgc, PWSTR *pszArgv) override;
    virtual void onStop() override;
    virtual void onLog(Raumkernel::Log::LogData _logData);

    void serviceWorkerThread(void);

private:

    BOOL m_fStopping;
    HANDLE m_hStoppedEvent;

    sigs::connections connections;
};