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
 * @file  TP_Native_SDK.cpp   
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TP Native SDK Interface
 * @details TP Native SDK Interface:
 * @author p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init TP Native SDK Interface
****************************************************/
// TP_Native_SDK.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TP_Native_SDK.h"
#include "SDKInterface.h"
#include "TP_Error.h"

CSDKInterface g_SDKInterface;

/**************************************************
 * @fn         login
 * @brief      登录认证请求
 * @param[in]  username    eSDK登录用户名，取值为安装eSDK TP后添加的登录eSDK用户ID
 * @param[in]  password    eSDK登录密码。
 * @return     成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL login(const std::string &username, const std::string &password)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	sprintf_s(strParameter,PARAMETER_LEN-1,"username:%s",username.c_str());
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPCommon().Login(username, password);
	return retVal;
}

/**************************************************
 * @fn         logout
 * @brief      用户登出
 * @return     成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL logout()
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");

	retVal = g_SDKInterface.GetTPCommon().Logout();
	return retVal;

}

/**************************************************
 * @fn         keepAlive
 * @brief      保持心跳
 * @return     成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL keepAlive()
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");

	retVal =  g_SDKInterface.GetTPCommon().KeepAlive();
	return retVal;
}

/**************************************************
 * @fn         scheduleConfEx
 * @brief      召集或预约非周期性会议
 * @param[in]  scheduleConf 		准备预约的会议参数，包含会场列表和参数, 预约时 ConferenceInfoEx 必填参数包括：
 *									name：会议名称
 *									beginTime：会议开始时间
 *									rate：速率
 *									duration：会议时长
 *									sites：会场信息列表
 *									其中会场列表参数中的 SiteInfoEx 必填参数为：
 *									uri 会场标识。当 uri 为空时，预约匿名会议
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回预约成功后会议基本信息，包括系统分配的会议 ID，会议的接入码等信息。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<ConferenceInfoEx> __SDK_CALL  scheduleConfEx(const ConferenceInfoEx& scheduleConf)
{
	TPSDKResponseEx<ConferenceInfoEx>  retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal =  g_SDKInterface.GetTPConfMgr().scheduleConfEx(&scheduleConf);
	sprintf_s(strParameter,PARAMETER_LEN-1,"name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,confId:%s"
		,scheduleConf.name.c_str(),scheduleConf.beginTime.wYear,scheduleConf.beginTime.wMonth,scheduleConf.beginTime.wDay
		,scheduleConf.beginTime.wHour,scheduleConf.beginTime.wMinute,scheduleConf.beginTime.wSecond,scheduleConf.beginTime.wMilliseconds
		,scheduleConf.rate.c_str(),scheduleConf.duration.c_str(),scheduleConf.sites.size(),retVal.result.confId.c_str());
	return retVal;
}

/**************************************************
 * @fn         scheduleRecurrenceConferenceEx
 * @brief     召集或预约周期性会议
 * @param[in]  scheduleConf 		准备预约的会议参数，包含会场列表和会场的参数，预约时 ConferenceInfoEx 必填参数包括：
 *									name：会议名称
 *									beginTime：会议开始时间
 *									duration：会议时长
 *									rate：速率
 *									sites：会场信息列表
 *									frequency：周期会议周期类型
 *									interval：周期会议的周期间隔
 *									count：重复次数，当endTime和count同时赋值时，以由系统计算出次数最少的条件为准，如count为3，endTime为5天后，frequency为每天，则具体周期会议召开3次，第三天结束。
 *									weekDays、weekDay、monthDay（这三个参数至少需要填写一个）。
 *									其中会场列表参数中的 SiteInfoEx 必填参数为：
 *									uri 会场标识。当 uri 为空时，预约匿名会议
 *									name：会场名称
 *									type：会场类型
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回预约成功后会议基本信息，包括系统分配的会议 ID，会议的接入码等信息。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<RecurrenceConfInfoEx> __SDK_CALL scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx& scheduleConf)
{
	TPSDKResponseEx<RecurrenceConfInfoEx>  retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().scheduleRecurrenceConferenceEx(&scheduleConf);
	sprintf_s(strParameter,PARAMETER_LEN-1,"name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,frequency:%d,interval:%d,count:%d,confId:%s"
		,scheduleConf.base_info.name.c_str(),scheduleConf.base_info.beginTime.wYear,scheduleConf.base_info.beginTime.wMonth,scheduleConf.base_info.beginTime.wDay
		,scheduleConf.base_info.beginTime.wHour,scheduleConf.base_info.beginTime.wMinute,scheduleConf.base_info.beginTime.wSecond,scheduleConf.base_info.beginTime.wMilliseconds
		,scheduleConf.base_info.rate.c_str(),scheduleConf.base_info.duration.c_str(),scheduleConf.base_info.sites.size(),scheduleConf.frequency,scheduleConf.interval,scheduleConf.count,retVal.result.base_info.confId.c_str());
	return retVal;
}

/**************************************************
 * @fn         editScheduledConfEx
 * @brief      编辑已预约的普通会议
 * @param[in]  editConf 			已经预约但未召开的会议信息。ConferenceInfoEx 必填参数包括：
 *									confId：会议ID
 *									name：会议名称
 *									beginTime：会议开始时间
 *									rate：速率
 *									duration：会议时长
 *									sites：会场信息列表
 *									其中会场列表参数中的 SiteInfoEx 必填参数为：
 *									uri 会场标识。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	 操作成功则 response.result返回会议修改成功后，输出的会议、会场信息。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<ConferenceInfoEx> __SDK_CALL editScheduledConfEx(const ConferenceInfoEx& scheduleConf)
{
	TPSDKResponseEx<ConferenceInfoEx>  retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().editScheduledConfEx(&scheduleConf);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,confId:%s"
		,scheduleConf.confId.c_str(),scheduleConf.name.c_str(),scheduleConf.beginTime.wYear,scheduleConf.beginTime.wMonth,scheduleConf.beginTime.wDay
		,scheduleConf.beginTime.wHour,scheduleConf.beginTime.wMinute,scheduleConf.beginTime.wSecond,scheduleConf.beginTime.wMilliseconds
		,scheduleConf.rate.c_str(),scheduleConf.duration.c_str(),scheduleConf.sites.size(),retVal.result.confId.c_str());
	return retVal;
}

/**************************************************
 * @fn         editRecurrenceConferenceEx
 * @brief     召集或预约周期性会议
 * @param[in]  scheduleConf 		已经预约但未召开的会议信息。ConferenceInfoEx 必填参数如下：
 *									confId：会议 ID
 *									name：会议名称
 *									beginTime：会议开始时间
 *									rate：速率
 *									frequency：周期会议周期类型
 *									interval：周期会议的周期间隔
 *									count：重复次数，若开始时间（beginTime）为过去的某个时间，则系统会默认将开始时间设置为当前时间。weekDays、weekDay、monthDay（这三个参数至少需要填写一个）
 *									其中会场列表参数中的 SiteInfoEx 必填参数为：
 *									uri 会场标识。当 uri 为空时，预约匿名会议
 *									name：会场名称
 *									type：会场类型
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回会议修改成功后，输出的会议、会场信息。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<RecurrenceConfInfoEx> __SDK_CALL editRecurrenceConferenceEx(const RecurrenceConfInfoEx& scheduleConf, const SYSTEMTIME &beginDateTime)
{
	TPSDKResponseEx<RecurrenceConfInfoEx>  retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().editRecurrenceConferenceEx(&scheduleConf, beginDateTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,frequency:%d,interval:%d,count:%d,confId:%s"
		,scheduleConf.base_info.confId.c_str(),scheduleConf.base_info.name.c_str(),scheduleConf.base_info.beginTime.wYear,scheduleConf.base_info.beginTime.wMonth,scheduleConf.base_info.beginTime.wDay
		,scheduleConf.base_info.beginTime.wHour,scheduleConf.base_info.beginTime.wMinute,scheduleConf.base_info.beginTime.wSecond,scheduleConf.base_info.beginTime.wMilliseconds
		,scheduleConf.base_info.rate.c_str(),scheduleConf.base_info.duration.c_str(),scheduleConf.base_info.sites.size(),scheduleConf.frequency,scheduleConf.interval,scheduleConf.count,retVal.result.base_info.confId.c_str());
	return retVal;
}

/**************************************************
 * @fn         querySitesEx
 * @brief     查询所有会场列表
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回所有会场列表。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteInfoEx>> __SDK_CALL querySitesEx()
{
	TPSDKResponseEx<list<SiteInfoEx>>  retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().querySitesEx();
	sprintf_s(strParameter,PARAMETER_LEN-1,"Sites size:%d"
		,retVal.result.size());
	return retVal;

}

/**************************************************
 * @fn         prolongScheduledConfEx
 * @brief     延长已预约会议时间
 * @param[in]  confId 				会议 ID。
 * @param[in]  beginDateTime 		会议开始时间。参数说明如下：
 *									对周期会议中的单个会议进行延长。
 *									如果是普通会议，或者对周期会议的所有会议进行延长，则可以不用输入。
 * @param[in]  prolongTime			准备延长的时间。每次延长时长介于 SMC 后台配置的“最小延长会议时长”和“最大延长会议时长”之间。延长后会议总时长不受限制。
 *									关于SMC 中延长会议时长的配置请参考SMC 相关配置文档。
 * @return      resultCode 			成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfMgr().prolongScheduledConfEx(confId, beginDateTime, prolongTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,beginDateTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),beginDateTime.wYear,beginDateTime.wMonth,beginDateTime.wDay
		,beginDateTime.wHour,beginDateTime.wMinute,beginDateTime.wSecond,beginDateTime.wMilliseconds);
	return retVal;
}

/**************************************************
 * @fn         querySiteStatusEx
 * @brief     查询指定会场在指定时间范围内的忙闲状态
 * @param[in]  siteUris 			需要查询忙闲状态的会场 URI 列表。可以是H.323的号码，或 SIP 的 URI，或电话号码等。
 * @param[in]  beginDateTime 		查询开始时间。
 * @param[in]  duration				查询时间范围。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回指定会场查询时间段范围内的忙闲状态。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> __SDK_CALL querySiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");

	retVal = g_SDKInterface.GetTPConfMgr().querySiteStatusEx(siteUris, beginTime, duration);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUris number:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s,map size:%d"
		,siteUris.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay
		,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         queryConferencesStatusEx
 * @brief     查询已调度会议的状态
 * @param[in]  confIds 				会议ID列表。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回会议状态列表。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<ConferenceStatusEx>> __SDK_CALL queryConferencesStatusEx(const list<string> &confIds)
{
	TPSDKResponseEx<list<ConferenceStatusEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryConferencesStatusEx(confIds);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confIds size:%d,conf status size:%d"
		,confIds.size(),retVal.result.size());
	return retVal;
}


/**************************************************
 * @fn        queryScheduleConferencesEx
 * @brief     查询所有的调度会议状态，支持过滤、翻页
 * @param[in]   queryConfig 		过滤条件
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回会议状态信息。
 *				response.pagesInfo	页码信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseWithPageEx<list<ConferenceStatusEx>> queryScheduleConferencesEx(const QueryConfigEx &queryConfig)
{
	TPSDKResponseWithPageEx<list<ConferenceStatusEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryScheduleConferencesEx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"sortItems size:%d,filters size:%d focusItem:%d conference status size:%d"
		,queryConfig.sortItems.size(),queryConfig.filters.size(),queryConfig.focusItem,retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn        addAdhocConfTemplateEx
 * @brief     添加Adhoc会议模板
 * @param[in]   orgId 				会议模板添加到的组织
 * @param[in]   adhocConfTemplate 	Adhoc会议模板参数
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	添加Adhoc会议模板成功后的模板ID，供索引
 *				response.pagesInfo	页码信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<std::string> addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate)
{
	TPSDKResponseEx<std::string> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().addAdhocConfTemplateEx(orgId, adhocConfTemplate);
	sprintf_s(strParameter,PARAMETER_LEN-1,"orgId:%s adhocConfTemplate.adhocConfTemplateId:%s"
		,orgId.c_str(),retVal.result.c_str());
	return retVal;
}


/**************************************************
 * @fn        editAdhocConfTemplateEx
 * @brief     修改Adhoc会议模板
 * @param[in]   adhocConfTemplate 	Adhoc会议模板参数
 * @return      resultCode 		成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate)
{
	int retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfMgr().editAdhocConfTemplateEx(adhocConfTemplate);
	sprintf_s(strParameter,PARAMETER_LEN-1,"adhocConfTemplate.adhocConfTemplateId:%s"
		,adhocConfTemplate.adhocConfTemplateId.c_str());
	return retVal;
}

/**************************************************
 * @fn        delAdhocConfTemplateEx
 * @brief     删除Adhoc会议模板
 * @param[in]   adhocConfTemplateId 	Adhoc会议模板ID
 * @return      resultCode 		成功返回0，失败返回错误码
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int delAdhocConfTemplateEx(const std::string &adhocConfTemplateId)
{
	int retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfMgr().delAdhocConfTemplateEx(adhocConfTemplateId);
	sprintf_s(strParameter,PARAMETER_LEN-1,"adhocConfTemplateId:%s"
		,adhocConfTemplateId.c_str());
	return retVal;
}


/**************************************************
 * @fn			queryAdhocConfTemplateListEx
 * @brief		查询Ad hoc会议
 * @param[in]   queryConfig 	查询Ad hoc会议时使用的过滤、排序、翻页条件
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	输出符合查询条件的Ad hoc会议列表
 *				response.pagesInfo	页码信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig)
{
	TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryAdhocConfTemplateListEx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"query number:%d"
		,retVal.result.size());
	return retVal;
}


/**************************************************
 * @fn         queryConfSitesStatusEx
 * @brief     查询指定会议中的会场状态
 * @param[in]  confIds 				会议ID列表。
 * @param[in]  siteUris 			准备查询的会场列表。如果查询列表为空，则表示查询会议中所有（有号码或 URI 的）会场的状态。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回指定会场状态。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteStatusEx>> __SDK_CALL queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris)
{
	TPSDKResponseEx<list<SiteStatusEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryConfSitesStatusEx(confId, siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d,site status size:%d"
		,confId.c_str(),siteUris.size(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         synchSiteStatusEx
 * @brief     指定会场忙闲状态同步
 * @param[in]  siteUris 			需要同步忙闲状态的会场 URI 列表。可以是H.323的号码，或 SIP 的 URI，或电话号码等。
 * @param[in]  beginTime 			查询数据发生变化的开始时间。
 * @param[in]  duration				查询数据发生变化的时间范围。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result返回指定会场同步多个会场的忙闲状态，具体说明如下：
 *										每个会场忙闲状态包含忙闲列表。同时包含该会场的会议信息，具体包含信息如下：
 *											会议的名称
 *											会议开始时间
 *											会议结束时间
 *										如果有状态是“闲”，但同时有会议 Id，则表示该会议已经被删除，或者这个会场不在这个会议中。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> __SDK_CALL synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal =  g_SDKInterface.GetTPConfMgr().synchSiteStatusEx(siteUris, beginTime, duration);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUris size:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s,map size:%d"
		,siteUris.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay
		,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str(),retVal.result.size());
	return retVal;
}


/**************************************************
 * @fn         addSiteToConfEx
 * @brief     向会议添加会场
 * @param[in]  confId 				会议 ID。
 * @param[in]  siteInfo 			准备添加到会议的会场信息。
 * @param[in]  beginTime			会议开始时间。具体说明如下：
 *										如果只向周期会议中的单个会议添加会场，则需要提供周期会议 ID 和单个会议的开始时间。
 *										如果是普通会议，或者对周期会议的所有会议添加会场，不能输入会议开始时间。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result输出新会场接入到会议的接入号信息。
 *									因为周期会议中的子会议接入号可能不同，所以可能存在多个接入号的情况。每个接入号信息内都有对应的会议开始时间。
 *									格式如：2013-05-07T22:46:31.235+08:00，其中2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteAccessInfoEx>> __SDK_CALL addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime)
{
	TPSDKResponseEx<list<SiteAccessInfoEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal =  g_SDKInterface.GetTPConfMgr().addSiteToConfEx(confId, siteInfo, beginTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteInfo.name:%s,siteInfo.uri:%s,siteInfo.type:%d,siteInfo.dialingMode:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,Site Access Info size:%d"
		,confId.c_str(),siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type,siteInfo.dialingMode,
		beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,retVal.result.size());
	return retVal;

}

/**************************************************
 * @fn         delSiteFromConfEx
 * @brief     删除会议中的会场
 * @param[in]  confId 				会议 ID。
 * @param[in]  siteUri 				会场 URI。
 * @param[in]  beginTime			会议开始时间。具体说明如下：
 *										只删除周期会议中的单个会议的信息，则需要提供周期会议 Id和单个会议的开始时间。
 *										删除普通会议信息，或者对周期会议的所有会议进行修改，则可以不用输入。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功则 response.result输出新会场接入到会议的接入号信息。
 *									因为周期会议中的子会议接入号可能不同，所以可能存在多个接入号的情况。每个接入号信息内都有对应的会议开始时间。
 *									格式如：2013-05-07T22:46:31.235+08:00，其中2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfMgr().delSiteFromConfEx(confId, siteUri, beginTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUri:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),siteUri.c_str()
		,beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	return retVal;
}


/**************************************************
 * @fn         connectSitesEx
 * @brief     呼叫一个或多个会场
 * @param[in]  confId 				会议 ID
 * @param[in]  siteUris 			准备呼叫的会场列表
 * @return      resultCode			操作结果。具体说明如下：
 *										指定的部分会场不存在，不会返回错误码。
 *										指定会场全部不存在，则返回会场不存在的错误码。
 *										指定的会场已经入会或已经处于呼叫状态，则不进行呼叫操作。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL connectSitesEx(const std::string &confId, const list<std::string> &siteUris)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");

	retVal = g_SDKInterface.GetTPConfMgr().connectSitesEx(confId, siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d"
		,confId.c_str(),siteUris.size());
	return retVal;
}


/**************************************************
 * @fn         disconnectSitesEx
 * @brief     断开指定会议的一个或多个会场
 * @param[in]  confId 				会议 ID
 * @param[in]  siteUris 			准备断开的会议URI列表
 * @return      resultCode			操作结果。具体说明如下：
 *										指定的部分会场不存在，不会返回错误码。
 *										指定会场全部不存在，则返回会场不存在的错误码。
 *										指定的会场已经离开会议，则不进行断开操作。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal =  g_SDKInterface.GetTPConfMgr().disconnectSitesEx(confId, siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d"
		,confId.c_str(),siteUris.size());
	return retVal;
}


/**************************************************
 * @fn         delScheduledConfEx
 * @brief     删除预约会议&结束会议
 * @param[in]  confId 				会议 ID
 * @param[in]  beginTime 			会议开始时间。具体说明如下：
 *										结束周期会议中的单个会议，则需要提供单个会议的开始时间。
 *										删除的是普通会议，或者整个周期会议，则可以不用输入。
 * @return      resultCode			操作结果。具体说明如下：
 *										该方法对未召开和已经召开的会议都有效。
 *										已经召开的会议执行该方法后，会议将被结束。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfMgr().delScheduledConfEx(confId, beginTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	return retVal;
}


/**************************************************
 * @fn         queryMultiPointCDREx
 * @brief     查询多点CDR话单
 * @param[in]  queryConfig 			多点CDR话单查询条件
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，cdr：查询的多点CDR话单数据；pageInfo：输出查询结果的翻页信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryMultiPointCDRExResponse> __SDK_CALL queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig)
{
	TPSDKResponseEx<QueryMultiPointCDRExResponse> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryMultiPointCDREx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,queryConfig.beginTime.wYear,queryConfig.beginTime.wMonth,queryConfig.beginTime.wDay,queryConfig.beginTime.wHour,queryConfig.beginTime.wMinute,queryConfig.beginTime.wSecond,queryConfig.beginTime.wMilliseconds
		,queryConfig.duration.c_str());
	return retVal;
}


/**************************************************
 * @fn         queryPointToPointCDREx
 * @brief     查询点对点CDR话单
 * @param[in]  queryConfig 			点对点CDR话单查询条件
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，cdr：查询的点对点CDR话单数据；pageInfo：输出查询结果的翻页信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryPointToPointCDRExResponse> __SDK_CALL queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig)
{
	TPSDKResponseEx<QueryPointToPointCDRExResponse> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryPointToPointCDREx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,queryConfig.beginTime.wYear,queryConfig.beginTime.wMonth,queryConfig.beginTime.wDay,queryConfig.beginTime.wHour,queryConfig.beginTime.wMinute,queryConfig.beginTime.wSecond,queryConfig.beginTime.wMilliseconds
		,queryConfig.duration.c_str());
	return retVal;

}

/**************************************************
 * @fn         queryAdhocConfFreeBusyEx
 * @brief     查询Adhoc会议忙闲状态
 * @param[in]  confAccessCodes 		Ad hoc会议接入号列表，可以同时查询多个Ad hoc的忙闲状态
 * @param[in]  beginTime 			查询开始时间。格式如：2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差
 * @param[in]  duration 			查询间隔时长，如：P0Y0M0DT1H0M0.000S或者PT1H：表示1小时。其中PT为标志位，YMDHMS分别代表年月日时分秒
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，输出Ad hoc会议的忙闲状态信息。如果指定的Ad hoc会议不存在，则对应的Ad hoc会议没有忙闲状态
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> __SDK_CALL queryAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryAdhocConfFreeBusyEx(confAccessCodes, beginTime, duration);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confAccessCodes size:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s AdhocConf size:%d"
		,confAccessCodes.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
		,duration.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         synchAdhocConfFreeBusyEx
 * @brief     查询Adhoc会议忙闲状态变化的数据
 * @param[in]  confAccessCodes 		Ad hoc会议接入号列表，可以同时查询多个Ad hoc的忙闲状态
 * @param[in]  beginTime 			查询开始时间。格式如：2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差
 * @param[in]  duration 			查询间隔时长，如：P0Y0M0DT1H0M0.000S或者PT1H：表示1小时。其中PT为标志位，YMDHMS分别代表年月日时分秒
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作结果，输出Ad hoc会议的忙闲状态信息。如果指定的Ad hoc会议不存在，则对应的Ad hoc会议没有忙闲状态
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> __SDK_CALL synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().synchAdhocConfFreeBusyEx(confAccessCodes, beginTime, duration);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confAccessCodes size:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s,AdhocConf size:%d"
		,confAccessCodes.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
		,duration.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         queryAdhocConferencesEx
 * @brief     查询Adhoc类型的会议模板列表
 * @param[in]  queryConfig 			查询Ad hoc会议时使用的过滤、排序、翻页条件。排序过滤使用的字段、排序类型，过滤方式
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，adhocConferences：输出符合查询条件的Ad hoc会议列表；pageInfo：输出查询结果的翻页信息
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryAdhocConferenceExResponse> __SDK_CALL queryAdhocConferencesEx(const QueryConfigEx &queryConfig)
{
	TPSDKResponseEx<QueryAdhocConferenceExResponse> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryAdhocConferencesEx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"QueryAhocConf size:%d",retVal.result.adhocConferences.size());
	return retVal;
}


/**************************************************
 * @fn         	queryConfSiteMCUEx
 * @brief     	查询指定会议中的会场所属MCU
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUris 			准备查询的会场列表。如果查询列表为空，则表示查询会议中所有（有号码或Uri的）会场的MCU
 * @param[in]  	beginTime 			可选。会议开始时间。用于查询周期会议中的单个会议。若周期会议不输入时间，则返回周期会议中第一个会议的会场所属MCU信息。
 *									如果是普通会议，则该项置空。
 *									格式如：2013-05-07T22:46:31.235+08:00，2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作结果，返回会场所属MCU信息。
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteMCUEx>> __SDK_CALL queryConfSiteMCUEx(const std::string &confId, const list<std::string> &siteUris, const SYSTEMTIME &beginTime)
{
	TPSDKResponseEx<list<SiteMCUEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().queryConfSiteMCUEx(confId, siteUris, beginTime);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,AdhocConf size:%d"
		,confId.c_str(),siteUris.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
		,retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	getContinuousPresenceInfoEx
 * @brief     	查询多画面模式资源数
 * @param[in]  	confId 				会议 ID
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作结果，targets：输出会议支持的多画面类型，具体格式请参考“设置多画面参数”接口中的target描述；
 *									cpResource：输出会议多画面资源数，该值决定同时有多少个不同的子画面存在
 *									supportCPModes：输出当前会议能支持的多画面模式列表
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> __SDK_CALL getContinuousPresenceInfoEx(const std::string &confId)
{
	TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().getContinuousPresenceInfoEx(confId);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,targets size:%d,cpResource:%d,supportCPModes size:%d"
		,confId.c_str(),retVal.result.targets.size(),retVal.result.cpResource,retVal.result.supportCPModes.size());
	return retVal;
}

/**************************************************
 * @fn         	getContinuousPresenceParamEx
 * @brief     	读取指定会议的多画面参数
 * @param[in]  	confId 				会议 ID
 * @param[in]  	target 				读取的多画面类型，具体格式请参考设置多画面参数接口中的target描述。如果读取的会议不支持指定的类型，将返回失败提示
 * @return     	response.code 		成功返回0，失败返回错误码
 *				response.result 	操作结果，presenceMode：多画面模式；
 *									subPics：子画面会场标识顺序列表
 * @attention  无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<GetContinuousPresenceParamResponseEx> __SDK_CALL getContinuousPresenceParamEx(const std::string &confId, const std::string &target)
{
	TPSDKResponseEx<GetContinuousPresenceParamResponseEx> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPConfMgr().getContinuousPresenceParamEx(confId,target);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,target:%s,presenceMode:%d,subPics size:%d"
		,confId.c_str(),target.c_str(),retVal.result.presenceMode,retVal.result.subPics.size());
	return retVal;
}

/**************************************************
 * @fn         	setVideoSourceEx
 * @brief     	设置指定会场的视频源
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUri 			会场标识
 * @param[in]  	videoSourceUri 		视频源所在会场标识
 * @param[in]  	isLock		 		是否锁定视频源(字段暂不支持)
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setVideoSourceEx(confId, siteUri, videoSourceUri, isLock);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUri:%s,videoSourceUri:%s,subPics isLock:%d"
		,confId.c_str(),siteUri.c_str(),videoSourceUri.c_str(),isLock);
	return retVal;
}

/**************************************************
 * @fn         	setAudioSwitchEx
 * @brief     	设置会议的声控切换
 * @param[in]  	confId 				会议 ID
 * @param[in]  	switchGate 			声控切换门限值。取值范围为0～100。
 *									如果开启声控切换时设置为0，表示启用默认值或当前会议的历史设置，当声音强度达到设置好的阈值时，会场图像将被广播。
 *									关闭声控切换时，该参数可不输入。
 * @param[in]  	isSwitch 			是否启用声控切换。具体说明如下：
 *										1：启用声控切换
 *										0：关闭声控切换
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setAudioSwitchEx(confId, switchGate, isSwitch);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,switchGate:%d,isSwitch:%d"
		,confId.c_str(),switchGate,isSwitch);
	return retVal;
}

/**************************************************
 * @fn         	setBroadcastSiteEx
 * @brief     	设置广播会场
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUri 			会场标识
 * @param[in]  	isBroadcast 		取值说明如下：
 *										0：开始广播会场
 *										1：停止广播会场
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setBroadcastSiteEx(confId, siteUri, isBroadcast);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUri:%s,isBroadcast:%d"
		,confId.c_str(),siteUri.c_str(),isBroadcast);
	return retVal;
}

/**************************************************
 * @fn         	setBroadcastContinuousPresenceEx
 * @brief     	设置广播多画面
 * @param[in]  	confId 				会议 ID
 * @param[in]  	isBroadcast 		取值说明如下：
 *										0：开始广播会场
 *										1：停止广播会场
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setBroadcastContinuousPresenceEx(confId,  isBroadcast);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,isBroadcast:%d"
		,confId.c_str(),isBroadcast);
	return retVal;
}


/**************************************************
 * @fn         	setSitesMuteEx
 * @brief     	指定会场闭音
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUris 			会场 URI 列表
 * @param[in]  	isMute 				是否闭音，取值说明如下：
 *										0：闭音
 *										1：不闭音
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setSitesMuteEx(const std::string &confId, const list<std::string> &siteUris, int isMute)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setSitesMuteEx(confId,  siteUris, isMute);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d isMute:%d"
		,confId.c_str(),siteUris.size(),isMute);
	return retVal;
}

/**************************************************
 * @fn         	setSitesQuietEx
 * @brief     	指定会场静音
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUris 			会场 URI 列表
 * @param[in]  	isQuiet 			是否静音，取值说明如下：
 *										0：静音
 *										1：不静音
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setSitesQuietEx(const std::string &confId, const list<std::string> &siteUris, int isQuiet)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setSitesQuietEx(confId,  siteUris, isQuiet);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d isQuiet:%d"
		,confId.c_str(),siteUris.size(),isQuiet);
	return retVal;
}

/**************************************************
 * @fn         	setContinuousPresenceEx
 * @brief     	设置多画面参数
 * @param[in]  	confId 				会议 ID
 * @param[in]  	target 				多画面标识，取值说明如下：
 *										空串：会议多画面
 *										0：第一组或默认的那组多画面
 *										N：第N组多画面（暂不支持）
 *										(siteUri)，如(01010086)、(sip:test@huawei.com)：每端口多画面(同一个会议中每个会场可以观看不同的多画面
 *									说明：如果取值是siteUri，需要按照如下格式：(siteUri)，用以和第N组多画面区分。同时需要注意只有9系列的MCU支持每端口多画面。
 * @param[in]  	presenceMode 		多画面模式
 * @param[in]  	subPics 			子画面会场标识顺序列表。
 *									说明：该字段用于描述子画面在多画面中的排列顺序。例如多画面模式为2，subPics为{“01010086”,”01010010”}，则表示从左到右的画面为会场01010086和会场01010010。
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setContinuousPresenceEx(const std::string &confId, const std::string &target, int presenceMode, const list<std::string> &subPics)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setContinuousPresenceEx(confId,  target, presenceMode, subPics);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,target:%s,presenceMode:%d,subPics size:%d"
		,confId.c_str(),target.c_str(),presenceMode,subPics.size());
	return retVal;
}

/**************************************************
 * @fn         	requestConfChairEx
 * @brief     	申请主席
 * @param[in]  	confId 				会议 ID
 * @param[in]  	chairmanUri 		主席会场标识。
 *									说明： 
 *										如果是智真三屏会场，只能设置中屏为主席。
 *										主席会场可进行点名发言等操作。
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL requestConfChairEx(const std::string &confId, const std::string &chairmanUri)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().requestConfChairEx(confId,  chairmanUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,chairmanUri:%s"
		,confId.c_str(),chairmanUri.c_str());
	return retVal;
}

/**************************************************
 * @fn         	releaseConfChairEx
 * @brief     	释放主席
 * @param[in]  	confId 				会议 ID
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releaseConfChairEx(const std::string &confId)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().releaseConfChairEx(confId);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s",confId.c_str());
	return retVal;
}


/**************************************************
 * @fn         	setFloorEx
 * @brief     	指定会场发言（点名发言）
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUri 			被指定发言的会场URI
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setFloorEx(const std::string &confId, const std::string &siteUri)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setFloorEx(confId, siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUri:%s",confId.c_str(),siteUri.c_str());
	return retVal;
}

/**************************************************
 * @fn         	setConfSiteVolumeEx
 * @brief     	设置会场音量值
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteVolumes 		设置会场的音量值
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx> &siteVolumes)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().setConfSiteVolumeEx(confId, siteVolumes);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteVolumes size:%d",confId.c_str(),siteVolumes.size());
	return retVal;
}

/**************************************************
 * @fn         	displayConfSiteLocalVideoEx
 * @brief     	打开会议中会场的视频
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUris	 		打开视频会场的URI列表
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL displayConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().displayConfSiteLocalVideoEx(confId, siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d",confId.c_str(),siteUris.size());
	return retVal;
}

/**************************************************
 * @fn         	hideConfSiteLocalVideoEx
 * @brief     	关闭会议中会场的视频
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUris	 		关闭视频会场的URI列表
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL hideConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().hideConfSiteLocalVideoEx(confId, siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUris size:%d",confId.c_str(),siteUris.size());
	return retVal;

}

/**************************************************
 * @fn         	lockPresentationEx
 * @brief     	锁定演示者令牌
 * @param[in]  	confId 				会议 ID
 * @param[in]  	siteUri		 		锁定辅流令牌的会场URI
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL lockPresentationEx(const std::string &confId, const std::string &siteUri)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().lockPresentationEx(confId, siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s,siteUri:%s",confId.c_str(),siteUri.c_str());
	return retVal;
}

/**************************************************
 * @fn         	unlockPresentationEx
 * @brief     	解锁演示者令牌
 * @param[in]  	confId 				会议 ID
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL unlockPresentationEx(const std::string &confId)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPConfCtrl().unlockPresentationEx(confId);
	sprintf_s(strParameter,PARAMETER_LEN-1,"confId:%s",confId.c_str());
	return retVal;
}

/**************************************************
 * @fn         	addSiteInfoEx
 * @brief     	添加会场信息
 * @param[in]  	orgId				准备将会场添加到的组织节点的ID
 * @param[in]  	siteInfo			准备添加的会场数据
 *									说明：本版本只支持添加的会场类型为：H323、SIP两种，且多屏智真会场的URI类型必须一致，即如果是3屏智真会场，则3个URI必须全是号码，或者全是IP，或者全是URI。
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL addSiteInfoEx(const std::string &orgId, const TerminalInfoEx& siteInfo)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().addSiteInfoEx(orgId, siteInfo);
	sprintf_s(strParameter,PARAMETER_LEN-1,"orgId:%s,siteInfo name:%s,siteInfo uri:%s,siteInfo type:%d",orgId.c_str(),siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type);
	return retVal;
}

/**************************************************
 * @fn         	editSiteInfoEx
 * @brief     	编辑会场信息
 * @param[in]  	siteInfo			准备修改的会场数据
 *									说明：本版本只支持添加的会场类型为：H323、SIP两种，且多屏智真会场的URI类型必须一致，即如果是3屏智真会场，则3个URI必须全是号码，或者全是IP，或者全是URI。
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL editSiteInfoEx(const TerminalInfoEx &siteInfo)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().editSiteInfoEx(siteInfo);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteInfo name:%s,siteInfo uri:%s,siteInfo type:%d",siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type);
	return retVal;
}

/**************************************************
 * @fn         	deleteSiteInfoEx
 * @brief     	删除会场信息
 * @param[in]  	siteUris			准备删除会场的URI。
 *									如果是智真三屏会场，只需要填写中屏标识即可。
 * @return     	resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL deleteSiteInfoEx(const list<std::string> &siteUris)
{
	int retVal = 0;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().deleteSiteInfoEx(siteUris);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUris size:%d",siteUris.size());
	return retVal;
}

/**************************************************
 * @fn         	querySitesInfoEx
 * @brief     	查询会场信息
 * @param[in]  	queryConfig			查询预定义会场时使用的过滤、排序、翻页条件
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，sites：则根据查询条件，返回查询的会场信息列表；pageInfo：输出查询结果的翻页信息
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QuerySitesInfoExResponse> __SDK_CALL querySitesInfoEx(const QueryConfigEx &queryConfig)
{
	TPSDKResponseEx<QuerySitesInfoExResponse> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().querySitesInfoEx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"query sites number:%d",retVal.result.sites.size());
	return retVal;
}


/**************************************************
 * @fn         	queryMCUInfoEx
 * @brief     	查询MCU信息列表
 * @param[in]  	queryConfig			查询MCU信息时使用的过滤、排序、翻页条件
 *									排序过滤使用的字段、排序类型，过滤方式参考前面的类描述
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，mcus：输出符合查询条件的MCU列表；pageInfo：输出查询结果的翻页信息
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryMCUInfoExResponse> __SDK_CALL queryMCUInfoEx(const QueryConfigEx &queryConfig)
{
	TPSDKResponseEx<QueryMCUInfoExResponse> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPMCUMgr().queryMCUInfoEx(queryConfig);
	sprintf_s(strParameter,PARAMETER_LEN-1,"query mcus number:%d",retVal.result.mcus.size());
	return retVal;
}

/**************************************************
 * @fn         	queryMCUFutureResourceEx
 * @brief     	查询未来时间MCU的资源占用情况
 * @param[in]  	mcus				待查询资源的MCU ID列表
 * @param[in]  	beginTime			查询开始时间。格式如：2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235为格林威治时间（GMT时间），+08:00为中国大陆与GMT的时差。
 * @param[in]  	duration			查询间隔时长，如：P0Y0M0DT1H0M0.000S或者PT1H：表示1小时。其中PT为标志位，YMDHMS分别代表年月日时分秒。
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功，MCU未来时间资源占用数据
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<MCUResourceEx>> __SDK_CALL queryMCUFutureResourceEx(const list<int> &mcus, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TPSDKResponseEx<list<MCUResourceEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPMCUMgr().queryMCUFutureResourceEx(mcus, beginTime, duration);
	sprintf_s(strParameter,PARAMETER_LEN-1,"mcus number:%d,begintTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s,mcu resource number:%d"
		,mcus.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	queryOrganizationEx
 * @brief     	查询系统的组织节点
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	输出系统中所有组织节点信息
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<OrganizationItemEx>>  __SDK_CALL queryOrganizationEx()
{
	TPSDKResponseEx<list<OrganizationItemEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPOrgaMgr().queryOrganizationEx();
	sprintf_s(strParameter,PARAMETER_LEN-1,"organization number:%d"
		,retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	requestChairEx
 * @brief     	申请主席
 * @param[in]  	siteUri				会场标识
 * @return     	resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL requestChairEx(const std::string &siteUri)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().requestChairEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s"
		,siteUri.c_str());
	return retVal;
}

/**************************************************
 * @fn         	releaseChairEx
 * @brief     	释放主席
 * @param[in]  	siteUri				会场标识
 * @return     	resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releaseChairEx(const std::string &siteUri)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().releaseChairEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s"
		,siteUri.c_str());
	return retVal;
	
}

/**************************************************
 * @fn         	queryConfCtrlPwdEx
 * @brief     	查询会场所在会议是否存在密码
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	返回会议是否存在密码。取值说明如下：0：不存在，1：存在
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL queryConfCtrlPwdEx(const std::string &siteUri)
{
	TPSDKResponseEx<int> retVal={0,0};
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().queryConfCtrlPwdEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,result:%d"
		,siteUri.c_str(),retVal.result);
	return retVal;

}

/**************************************************
 * @fn         	queryBroadInfoEx
 * @brief     	查询指定会场所在会议中录播和直播的信息
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回直播状态、录播状态
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<BroadInfoEx> __SDK_CALL queryBroadInfoEx(const std::string &siteUri)
{
	TPSDKResponseEx<BroadInfoEx> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().queryBroadInfoEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,BroadInfoEx directBroad:%d,directBroadStatus:%d,recordBroad:%d,recordBroadStatus:%d"
		,siteUri.c_str(),retVal.result.directBroad,retVal.result.directBroadStatus,retVal.result.recordBroad,retVal.result.recordBroadStatus);
	return retVal;
}

/**************************************************
 * @fn         	setRecordBroadEx
 * @brief     	设置启动或停止录播
 * @param[in]  	siteUri				会场标识
 * @param[in]  	action				取值说明如下：0：“startRecord”（开始录播）；1：“stopRecord”（停止录播）
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setRecordBroadEx(const std::string &siteUri, int action)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().setRecordBroadEx(siteUri,action);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,action:%d",siteUri.c_str(),action);
	return retVal;
}

/**************************************************
 * @fn         	setDirectBroadEx
 * @brief     	设置启动或停止直播
 * @param[in]  	siteUri				会场标识
 * @param[in]  	action				取值说明如下：0：“startDirect”（开始直播）；1：“stopDirect”（停止直播）
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setDirectBroadEx(const std::string &siteUri, int action)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPTermConfMgr().setDirectBroadEx(siteUri,action);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,action:%d",siteUri.c_str(),action);
	return retVal;
}

/**************************************************
 * @fn         	isConnectAuxSourceEx
 * @brief     	查询是否接入辅流输入源
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回是否接入辅流输入源，取值说明如下：0：未接入；1：接入
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isConnectAuxSourceEx(const std::string &siteUri)
{
	TPSDKResponseEx<int> retVal={0,0};
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().isConnectAuxSourceEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,result:%d",siteUri.c_str(),retVal.result);
	return retVal;
}

/**************************************************
 * @fn         	isSendAuxStreamEx
 * @brief     	查询当前是否正在发送辅流
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回是否正在发送辅流，取值说明如下：0：没有发送辅流；1：正在发送辅流
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isSendAuxStreamEx(const std::string &siteUri)
{
	TPSDKResponseEx<int> retVal={0,0};
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().isSendAuxStreamEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,result:%d",siteUri.c_str(),retVal.result);
	return retVal;
}

/**************************************************
 * @fn         	isReceiveRemAuxStrmEx
 * @brief     	查询指定会场是否正在接收远端辅流
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回是否正在接收远端辅流，取值说明如下：0：未在接收远端辅流；1：正在接收远端辅流
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isReceiveRemAuxStrmEx(const std::string &siteUri)
{
	TPSDKResponseEx<int> retVal={0,0};
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().isReceiveRemAuxStrmEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,result:%d",siteUri.c_str(),retVal.result);
	return retVal;
}

/**************************************************
 * @fn         	setAuxStreamEx
 * @brief     	设置开始或停止发送辅流
 * @param[in]  	siteUri				会场标识
 * @param[in]  	controlCode			辅流开始发送及停止发送方式，取值说明如下：0：开始发送；1：停止发送
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setAuxStreamEx(const std::string &siteUri, int controlCode)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().setAuxStreamEx(siteUri,controlCode);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,controlCode:%d",siteUri.c_str(),controlCode);
	return retVal;
}

/**************************************************
 * @fn         	queryAuxStreamSourcesEx
 * @brief     	获取辅流视频源列表
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回辅流视频源列表
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AuxStreamInfoEx>> __SDK_CALL queryAuxStreamSourcesEx(const std::string &siteUri)
{
	TPSDKResponseEx<list<AuxStreamInfoEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().queryAuxStreamSourcesEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,AuxStreamInfo number:%d",siteUri.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	queryVideoOutSrcStateEx
 * @brief     	查询视频输入口接入视频源状态
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回视频输入口接入视频源信息
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<VideoSourcesInfoEx>> __SDK_CALL queryVideoOutSrcStateEx(const std::string &siteUri)
{
	TPSDKResponseEx<list<VideoSourcesInfoEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().queryVideoOutSrcStateEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,VideoSourcesInfoEx number:%d",siteUri.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	ctrlCameraEx
 * @brief     	摄像机控制操作
 * @param[in]  	siteUri				会场标识
 * @param[in]  	cameraControl		摄像头控制参数。必填参数说明如下：camState：摄像机位置；camAction：操作动作；camPos：摄像机预置位置号；camSrc：输入口 id
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().ctrlCameraEx(siteUri,cameraControl);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,camState:%d,camAction:%d,camPos:%d,camSrc:%d"
		,siteUri.c_str(),cameraControl.camState,cameraControl.camAction,cameraControl.camPos,cameraControl.camSrc);
	return retVal;
}

/**************************************************
 * @fn         	setMainAuxStreamSourcesEx
 * @brief     	设置主流视频源、辅流视频源
 * @param[in]  	siteUri				会场标识
 * @param[in]  	localMainSrcs		本端主流视频源
 * @param[in]  	localAuxSrc			本端辅流视频源
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int> &localMainSrcs, int localAuxSrc)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().setMainAuxStreamSourcesEx(siteUri,localMainSrcs, localAuxSrc);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,localMainSrcs number:%d,localAuxSrc:%d"
		,siteUri.c_str(),localMainSrcs.size(),localAuxSrc);
	return retVal;
}

/**************************************************
 * @fn         	queryMainStreamSourcesEx
 * @brief     	获取主流视频源的下拉列表框内容
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	操作成功返回辅流视频源列表
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AuxStreamInfoEx>> __SDK_CALL queryMainStreamSourcesEx(const std::string &siteUri)
{
	TPSDKResponseEx<list<AuxStreamInfoEx>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().queryMainStreamSourcesEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,AuxStreamInfoEx number:%d"
		,siteUri.c_str(),retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	setVideoOutSrcEx
 * @brief     	设置输出口显示内容
 * @param[in]  	siteUri				会场标识
 * @param[in]  	hdOut				本端视频源输出口 ID：0：HD1；1：HD2；2：HD3；3：HD4；4：HD5；5：SD1；6：SD2
 * @param[in]  	videoSrc			取值说明如下：0：“local_main”（本地主流）；1：“local_aux”（本地辅流）；2：“remote_main”（远端主流）；3：“remote_aux”（远端辅流）
 * @return      resultCode			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc)
{
	int retVal=TP_SDK_ERR_SUCCESS;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPSiteMgr().setVideoOutSrcEx(siteUri,hdOut, videoSrc);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,hdOut:%d,videoSrc:%d"
		,siteUri.c_str(),hdOut,videoSrc);
	return retVal;
}

/**************************************************
 * @fn         	querySiteVersionInfoEx
 * @brief     	查询获取终端型号/版本信息
 * @param[in]  	siteUri				会场标识
 * @return      response.code 		成功返回0，失败返回错误码
 *				response.result 	如果操作成功返回终端型号/版本信息
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<SiteDeviceVersionInfoEx> __SDK_CALL querySiteVersionInfoEx(const std::string &siteUri)
{
	TPSDKResponseEx<SiteDeviceVersionInfoEx> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPSiteMgr().querySiteVersionInfoEx(siteUri);
	sprintf_s(strParameter,PARAMETER_LEN-1,"siteUri:%s,model:%s,license:%s,softVersion:%s,hardVersion:%s,logicVersion:%s,manufacturer:%s"
		,siteUri.c_str(),retVal.result.model.c_str(),retVal.result.license.c_str(),retVal.result.softVersion.c_str(),retVal.result.hardVersion.c_str(),retVal.result.logicVersion.c_str(),retVal.result.manufacturer.c_str());
	return retVal;
}


/**************************************************
 * @fn         	enablePushEx
 * @brief     	开启推送功能
 * @param[in]  	pushMode			推送机制:0: NONE 1: PULL 2: CALLBACK
 * @param[in]  	extendParameter		None和Pull模式下，无用。 Push模式下，提供SMC 2.0回调的URI地址
 * @return      resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL enablePushEx(int pushMode, const std::string &extendParameter)
{
	int retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPScribMgr().enablePushEx(pushMode, extendParameter);
	if ( 0 == retVal )
	{
		if ( extendParameter.length() != 0 )
		{
			sprintf_s(strParameter,PARAMETER_LEN-1,"pushMode:%d,extendParameter:%s"
				,pushMode,extendParameter.c_str());
		}
		else
		{
			sprintf_s(strParameter,PARAMETER_LEN-1,"pushMode:%d,extendParameter:NULL"
				,pushMode);
		}
	}
	return retVal;
}


/**************************************************
 * @fn         	subscribeEx
 * @brief     	开启推送功能
 * @param[in]  	subscribeInfos		订阅或取消订阅信息的列表。
 * @return      resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL subscribeEx(list<SubscribeInfoEx *> subscribeInfos)
{
	int retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal,"");
	retVal = g_SDKInterface.GetTPScribMgr().subscribeEx(subscribeInfos);
	if ( 0 == retVal )
	{
		sprintf_s(strParameter,PARAMETER_LEN-1,"subscribeInfos number:%d"
			,subscribeInfos.size());
	}
	return retVal;
}


/**************************************************
 * @fn         	queryNotificationEx
 * @brief     	读取通知消息
 * @param[in]  	无
 * @return      resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<NotificationEx *>> __SDK_CALL queryNotificationEx()
{
	TPSDKResponseEx<list<NotificationEx *>> retVal;
	char strParameter[PARAMETER_LEN]={0};
	TP_INFO_TRACE(strParameter,&retVal.resultCode,"");
	retVal = g_SDKInterface.GetTPScribMgr().queryNotificationEx();
	sprintf_s(strParameter,PARAMETER_LEN-1,"queryNotificationEx number:%d"
		,retVal.result.size());
	return retVal;
}

/**************************************************
 * @fn         	releasequeryNotificationMemery
 * @brief     	释放接口queryNotificationEx申请的内存
 * @param[in]  	listNotificationEx  信息的指针列表
 * @return      resultCode 			成功返回0，失败返回错误码
 * @attention  	无
 * @par 示例
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releasequeryNotificationMemery(list<NotificationEx *> &listNotificationEx)
{
		for ( list<NotificationEx *>::iterator ite = listNotificationEx.begin(); ite != listNotificationEx.end(); ite++ )
		{
			if ( TP_D_OVERFLOW_NOTIFICATION_TYPE == (*ite)->type  )
			{
				OverflowNotificationEx *pOverflowNtf = (OverflowNotificationEx *)*ite;
				delete pOverflowNtf;
				pOverflowNtf = NULL;
				*ite = NULL;
			} 
			else if (  TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE == (*ite)->type )
			{
				ScheduledConfNotificationEx *pScheduledConfNtf = (ScheduledConfNotificationEx *)*ite;
				delete pScheduledConfNtf;
				pScheduledConfNtf = NULL;
				*ite = NULL;
			} 
			else if ( TP_D_ONGOING_CONF_NOTIFICATION_TYPE == (*ite)->type )
			{
				OngoingConfNotificationEx *pOngoingConfNtf = (OngoingConfNotificationEx *)*ite;
				for ( list<NotificationStatusEx *>::iterator iter = pOngoingConfNtf->changes.begin(); iter != pOngoingConfNtf->changes.end(); iter++ )
				{
					if ( TP_D_CONFERENCE_STATUS_TYPE == (*iter)->structtype )
					{
						ConferenceStatusEx *pConferenceStatusEx = (ConferenceStatusEx *)*iter;
						delete pConferenceStatusEx;
						pConferenceStatusEx = NULL;
						*iter = NULL;
					} 
					else if ( TP_D_SITE_STATUS_TYPE == (*iter)->structtype )
					{
						SiteStatusEx *pSiteStatusEx = (SiteStatusEx *)*iter;
						//delete pSiteStatusEx;
						pSiteStatusEx = NULL;
						//*iter = NULL;
						delete *iter;
						*iter = NULL;
					}

				}
				pOngoingConfNtf->changes.clear();	//清空changes list
				delete pOngoingConfNtf;
				pOngoingConfNtf = NULL;
				*ite = NULL;
			}
		}
		listNotificationEx.clear();	//清空result list
		return 0;
}