/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

/****************************************************   
 * @file   SDKInterface.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   SDK�ӿڹ�����
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init SDKInterface.h
****************************************************/

#ifndef _SDK_INTERFACE_H_
#define _SDK_INTERFACE_H_

#include "tpCommon.h"
#include "tpProfessionalConfMgr.h"
#include "tpProfessionalConfCtrl.h"
#include "tpProfessionalSiteMgr.h"
#include "tpProfessionalMCUMgr.h"
#include "tpProfessionalOrgaMgr.h"
#include "tpProfessionalTerminalConfCtr.h"
#include "tpProfessionalScribMgr.h"

typedef struct tagTP_S_CONFIG_INFO
{
	char cURL[TP_D_URI_LEN+1];
	char cCommonInterface[TP_D_INTERFACE_LEN+1];
	char cConfCtrlInterface[TP_D_INTERFACE_LEN+1];
	char cConfMgrInterface[TP_D_INTERFACE_LEN+1];
	char cSiteMgrInterface[TP_D_INTERFACE_LEN+1];
	char cMCUMgrInterface[TP_D_INTERFACE_LEN+1];
	char cORGAMgrInterface[TP_D_INTERFACE_LEN+1];
	char cTermConfCtrInterface[TP_D_INTERFACE_LEN+1];
	char cPlatformKeyMgrInterface[TP_D_INTERFACE_LEN+1];
	char cSubscribeServiceMgrInterface[TP_D_INTERFACE_LEN+1];
}TP_S_CONFIG_INFO;

//lint -e1536
class CSDKInterface
{
public:
	CSDKInterface(void);
	~CSDKInterface(void);

	//��ȡ����Url
	std::string GetUrl() const {return m_Url;}

	//��������Url
	void SetUrl(const std::string &url) {m_Url = url;}

	//��ȡCookie
	std::string GetCookie() const {return m_Cookie;}

	//����Cookie
	void SetCookie(const std::string &cookie) {m_Cookie = cookie;}

	//��ȡCTPCommon����
	CTPCommon& GetTPCommon() {return m_TPCommon;}


	//��ȡCTPConfMgr����
	CTPConfMgr& GetTPConfMgr() {return m_TPConfMgr;}

	//obtain TPConfCtrl Object
	CTPConfCtrl& GetTPConfCtrl() {return m_TPConfCtrl;}

	//obtain TPSiteMgr object
	CTPSiteMgr& GetTPSiteMgr() {return m_TPSiteMgr;}

	CTPMCUMgr& GetTPMCUMgr() {return m_TPMCUMgr;}

	CTPOrgaMgr& GetTPOrgaMgr() {return m_TPOrgaMgr;}

	CTPTermConfMgr& GetTPTermConfMgr() {return m_TPTermConfMgr;}

	CTPScribMgr& GetTPScribMgr() {return m_TPScribMgr;}

private:
	//��ȡDll·��
	std::string GetDllPath(const std::string &dllName);
	int GetConfigInfo(const std::string &strPath);

private:
	std::string m_Url;
	std::string m_Cookie;
	CTPCommon m_TPCommon;
	CTPConfMgr m_TPConfMgr;
	CTPConfCtrl m_TPConfCtrl;
	CTPSiteMgr m_TPSiteMgr;
	CTPMCUMgr m_TPMCUMgr;
	CTPOrgaMgr m_TPOrgaMgr;
	CTPTermConfMgr m_TPTermConfMgr;
	CTPScribMgr m_TPScribMgr;
	TP_S_CONFIG_INFO m_configInfo;

};

#endif //_SDK_INTERFACE_H_
