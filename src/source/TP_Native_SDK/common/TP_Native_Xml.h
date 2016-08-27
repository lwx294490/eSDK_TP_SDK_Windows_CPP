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
 * @file  TP_Native_Xml.h  
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief  xml�����࣬Դ�����CBB ivs_xml.h (����˺Ϳͻ��˹����ļ�)
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init TP_Native_Xml.h
****************************************************/

#ifndef __TP_NATIVE_XML_H__
#define __TP_NATIVE_XML_H__

#include "tinyxml.h"
#include <string>


class CXml
{
public:
    CXml(const char *pszFileName = NULL);
    ~CXml();

private:
    CXml(const CXml &src);

    CXml& operator=(const CXml&);

public:
    /**************************************************************************
    * name       : Load
    * description: ����һ��xml�ļ�
    * input      : encode ���� TIXML_ENCODING_UNKNOWN,TIXML_ENCODING_UTF8,TIXML_ENCODING_LEGACY
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
    bool Load(TiXmlEncoding encode = TIXML_ENCODING_UNKNOWN);

    /**************************************************************************
    * name       : Load
    * description: ����һ��xml�ļ�
    * input      : pszFileName ���ص��ļ���
	               encode ���� TIXML_ENCODING_UNKNOWN,TIXML_ENCODING_UTF8,TIXML_ENCODING_LEGACY
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool Load(const char *pszFileName, TiXmlEncoding encode = TIXML_ENCODING_UNKNOWN);

    /**************************************************************************
    * name       : Parse
    * description: ����һ��xml����xml�ļ�
    * input      : pszStream xml��
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool Parse(const char *pszStream, TiXmlEncoding encode = TIXML_ENCODING_LEGACY);

    /**************************************************************************
    * name       : Save
    * description: �洢xml�ļ�
    * input      : NA
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : ��Load(const char *pszFileName)���ʹ��
    **************************************************************************/
    bool Save();

    /**************************************************************************
    * name       : Save
    * description: �洢xml�ļ�
    * input      : pszFileName �洢���ļ���
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool Save(const char *pszFileName);

    /**************************************************************************
    * name       : IntoElem
    * description: ������һ��
    * input      : NA
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool IntoElem();

    /**************************************************************************
    * name       : OutOfElem
    * description: �˳�����һ��
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	void OutOfElem();

    /**************************************************************************
    * name       : NextElem
    * description: ����ͬ����һ��Ԫ��
    * input      : NA
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
    bool NextElem();

    /**************************************************************************
    * name       : GetRootPos
    * description: �������ڵ�
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	void GetRootPos();

    /**************************************************************************
    * name       : AddDeclaration
    * description: ���xml�ļ���������
    * input      : pszVersion �汾
                   pszEncode ���뷽ʽ
                   pszStdLone �������� yes��no
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
    bool AddDeclaration(const char* pszVersion,const char* pszEncode,const char* pszStdLone);

    /**************************************************************************
    * name       : AddElem
    * description: ���Ԫ��
    * input      : pszElemName ����ӵ�Ԫ����
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool AddElem(const char *pszElemName);

	/**************************************************************************
	* name       : AddElemBeforeCurNode
	* description: �ڵ�ǰ�ڵ�ǰ���Ԫ��
	* input      : pszElemName ����ӵ�Ԫ����
	* output     : NA
	* return     : true - �ɹ���false - ʧ��
	* remark     : NA
	**************************************************************************/
	//lint -e429
	bool AddElemBeforeCurNode(const char *pszElemName);

    /**************************************************************************
    * name       : AddChildElem
    * description: �����Ԫ��
    * input      : pszElemName ����ӵ���Ԫ����
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool AddChildElem(const char *pszElemName);

    /**************************************************************************
    * name       : SetElemValue
    * description: �趨��ǰԪ��ֵ
    * input      : pszElemValue ���趨��Ԫ��ֵ
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool SetElemValue(const char* pszElemValue);
    
    /**************************************************************************
    * name       : SetElemValueCDATA
    * description: �趨��ǰԪ��CDATA,  <![CDATA[ElemValue]]> ��װ
    * input      : pszElemValue ���趨��Ԫ��ֵ
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
    bool SetElemValueCDATA(const char* pszElemValue);
    
    /**************************************************************************
    * name       : GetElem
    * description: ��ȡ��ǰԪ��
    * input      : NA
    * output     : NA
    * return     : const char*
    * remark     : NA
    **************************************************************************/
	const char* GetElem();

    /**************************************************************************
    * name       : GetElemValue
    * description: ��ȡ��ǰԪ��ֵ
    * input      : NA
    * output     : NA
    * return     : const char*
    * remark     : NA
    **************************************************************************/
	const char* GetElemValue() const;

    /**************************************************************************
    * name       : FindElem
    * description: ����Ԫ��
    * input      : pszElemName �����ҵ�Ԫ����
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool FindElem(const char *pszElemName);

	bool FindElemValue(const char *pszElemName);

    /**************************************************************************
    * name       : ModifyElemName
    * description: �޸�Ԫ��
    * input      : pszElemName Ԫ����
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
    void ModifyElemName(const char*pszElemName);

    /**************************************************************************
    * name       : ModifyElemValue
    * description: �޸�Ԫ��ֵ
    * input      : pszElemValue Ԫ��ֵ
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
    void ModifyElemValue(const char*pszElemValue);

    /**************************************************************************
    * name       : RemoveElem
    * description: ɾ��Ԫ��
    * input      : NA
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
    bool RemoveElem();

    /**************************************************************************
    * name       : AddAttribute
    * description: ���Ԫ������
    * input      : pszAttriName ����ӵ�������
                   pszAttriValue ��Ӧ������ֵ
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	void AddAttribute(const char*pszAttriName,const char* pszAttriValue);

    /**************************************************************************
    * name       : AddChildAttrib
    * description: �����Ԫ������
    * input      : pszAttriName Ԫ��������
                   pszAttriValue Ԫ������ֵ
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool AddChildAttribute(const char*pszAttriName,const char* pszAttriValue);

    /**************************************************************************
    * name       : GetAttributeValue
    * description: ���Ԫ������ֵ
    * input      : pszAttriName Ԫ�ص�������
    * output     : NA
    * return     : const char* Ԫ�ص�����ֵ
    * remark     : NA
    **************************************************************************/
	const char* GetAttributeValue(const char*pszAttriName) const;

    /**************************************************************************
    * name       : RemoveAttribute
    * description: ɾ��Ԫ������
    * input      : pszAttriName Ԫ�ص�������
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
    void RemoveAttribute(const char*pszAttriName);

    /**************************************************************************
    * name       : ModifyAttributeValue
    * description: �޸�Ԫ������ֵ
    * input      : pszAttriName ���޸ĵ�������
                   pszAttriValue ��Ӧ������ֵ
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
    void ModifyAttributeValue(const char*pszAttriName,const char* pszAttriValue);

    /**************************************************************************
    * name       : GetXMLStream
    * description: ��ȡxml��
    * input      : NA
    * output     : nXMLStreamLength
    * return     : const char* xml��
    * remark     : NA
    **************************************************************************/
    const char*  GetXMLStream(unsigned int &uiXMLStreamLength);

    /**************************************************************************
    * name       : SetChildData
    * description: �����Ԫ��ֵ
    * input      : pValue Ԫ��ֵ
    * output     : NA
    * return     : true - �ɹ���false - ʧ��
    * remark     : NA
    **************************************************************************/
	bool SetChildData(const char *pszValue);

    /**************************************************************************
    * name       : Print
    * description: ��Win32ƽ̨��ӡ��xml�ļ�
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	void Print()const;

    /**************************************************************************
    * name       : FindElemEx
    * description: ���ݽڵ�·����ȡ�ڵ�
    * input      : XML�ڵ��·��
    * output     : NA
    * return     : �Ƿ�ɹ�
    * remark     : NA
    **************************************************************************/
    bool FindElemEx(const char *pszElemPath);
	bool MkAndFindElemEx(const char *pszElemPath);

    /**************************************************************************
    * name       : SetElemValueEx
    * description: ���ݽڵ�·�����ýڵ�����
    * input      : pszElemPath XML�ڵ��·��
	               pszElemValue XML�ڵ�ֵ
    * output     : NA
    * return     : �Ƿ�ɹ�
    * remark     : NA
    **************************************************************************/	
	bool SetElemValueEx(const char *pszElemPath,const char *pszElemValue);
	bool MkAndSetElemValueEx(const char *pszElemPath,const char *pszElemValue);

    /**************************************************************************
    * name       : GetElemValueEx
    * description: ���ݽڵ�·����ȡ�ڵ�����
    * input      : pszElemPath XML�ڵ��·��
	               pszElemValue XML�ڵ�ֵ
    * output     : NA
    * return     : �Ƿ�ɹ�
    * remark     : NA
    **************************************************************************/
	const char* GetElemValueEx(const char* pszElemPath);
    // ���û�׼�ڵ�
    bool SetBaseElem(const char* pszElemPath = NULL);
    bool GetBasePos();

	/**************************************************************************
    * name       : NextElemEx
    * description: ����ȡcount���ڵ�
    * input      : count XML�ڵ����
    * output     : NA
    * return     : �Ƿ�ɹ�
    * remark     : NA
    **************************************************************************/
	bool NextElemEx(int count);
	bool MkAndNextElemEx(int count);

	/**************************************************************************
    * name       : SetElemValueCDATAEx
    * description: ���ݽڵ�·�����ýڵ�����(CDATA)
    * input      : pszElemPath XML�ڵ��·��
	               pszElemValue XML�ڵ�ֵ
    * output     : NA
    * return     : �Ƿ�ɹ�
    * remark     : NA
    **************************************************************************/	
	bool SetElemValueCDATAEx(const char *pszElemPath,const char *pszElemValue);
	void ModifyElemValueCDATA(const char *pszElemValue);
		
	/**************************************************************************
    * name       : SetCondenseWhiteSpace
    * description: �ո��Ƿ񱻼�
    * input      : bCondenseWhiteSpace true ΪҪ�򻯣�falseΪ����
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/	
	static bool SetCondenseWhiteSpace(bool bCondenseWhiteSpace);
	static bool IsWhiteSpaceCondensed();


private:
	TiXmlDocument       *m_pXMlDoc;         //xml�ļ�ָ��
    TiXmlNode           *m_pXmlNode;        //xml�ڵ�ָ��
	TiXmlElement        *m_pXmlElem;        //xmlԪ��ָ��
    const char          *m_pszFileName;     //xml�ļ��ļ���ָ��
    //TiXmlPrinter        m_XmlPrinter;       //xml�ļ���ӡ����
	std::string			m_strStream;
    TiXmlNode           *m_pBaseXmlNode;    //xml��׼�ڵ�ָ��
    TiXmlElement        *m_pBaseXmlElem;    //xml��׼Ԫ��ָ��

	static bool         m_bFistInit;        //�Ƿ��ǵ�һ�γ�ʼ��
	static bool         m_bCondenseWhiteSpace; //�Ƿ���Ҫ�򻯿ո�
};

//////////////////////////////////////////////////////////////////////////
// ��ȫ�����ڴ�
#define SAFE_NEW(p, Type)			\
	try								\
	{								\
		p = new Type;				\
	}								\
	catch ( ... )					\
	{								\
		p = NULL;					\
	}

// ��ȫ�����ڴ�
#define SAFE_NEW_A(p, Type, size)	\
	try								\
	{								\
		p = new Type[size];			\
	}								\
	catch ( ... )					\
	{								\
		p = NULL;					\
	}

// ��ȫ�����ڴ�
#define SAFE_DELETE(p)				\
	try								\
	{								\
		if (NULL != p)				\
		{							\
			delete (p);				\
			p = NULL;				\
		}							\
	}								\
	catch ( ... )					\
	{								\
		p = NULL;					\
	}

// ��ȫ�����ڴ�
#define SAFE_DELETE_A(p)			\
	try								\
	{								\
		if (NULL != p)				\
		{							\
			delete [] (p);			\
			p = NULL;				\
		}							\
	}								\
	catch ( ... )					\
	{								\
		p = NULL;					\
	}

// ��ָ����
#define CHECK_POINTER(p, Ret)		\
	if (NULL == p)					\
	{								\
		return Ret;					\
	}

// ��ָ����
#define CHECK_POINTER_VOID(p)		\
	if (NULL == p)					\
	{								\
		return ;					\
	}

#ifdef WIN32
#define STRTOK  strtok_s
#else
#define STRTOK  strtok_r
#endif

#endif
