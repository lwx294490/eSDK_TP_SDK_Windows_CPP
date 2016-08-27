/********************************************************************
filename	: 	securec_win.h
author		:	zwx211831
created		:	2015/9/17	
description	:	���� DLL Ӧ�ó���ĵ�������;
copyright	:	Copyright (C) 2014-2016
history		:	2015/9/17 ��ʼ�汾;
*********************************************************************/
#ifndef __SECUREC_WIN_H__
#define __SECUREC_WIN_H__

#if defined WIN32 || defined _MSC_VER
#ifdef ESDK_SECURE_C_EXPORTS
#define ESDK_SECURE_API __declspec(dllexport)
#else
#define ESDK_SECURE_API __declspec(dllimport)
#endif
#endif

#if defined WIN32 || defined _MSC_VER
#define __SECUREC_CALL __stdcall
#else
#define __SECUREC_CALL
#endif

#ifndef errno_t
typedef int errno_t;
#endif

/* for performance consideration, the following macro will the corresponding API 
* of libC for memcpy, memmove and memset
*/
#define CALL_LIBC_COR_API


/*define error code*/

/* success */
#define EOK (0)

/* invalid parameter */
#ifdef EINVAL
#undef EINVAL
#endif
#define EINVAL (22)
#define EINVAL_AND_RESET (22 | 0X80)
/* invalid parameter range */
#ifdef ERANGE
#undef ERANGE  /* to avoid redefinition */
#endif
#define ERANGE (34)
#define ERANGE_AND_RESET  (34 | 0X80)

#ifdef __cplusplus
extern "C"
{
#endif

	/**************************************************************************
	* name			: memset_s
	* description	: �ڴ��ʼ������
	* input			: 1)destĿ�ĵ�ַ��2)Ŀ�ĵ�ַ���ȣ�3)��ʼ���ַ���4)��ʼ������
	* output		: ��ʼ������ڴ�
	* remark		: 
	**************************************************************************/
	ESDK_SECURE_API errno_t __SECUREC_CALL memset_s(void* dest, size_t destMax, int c, size_t count);


#ifdef __cplusplus
};
#endif


#endif	//__SECUREC_WIN_H__

