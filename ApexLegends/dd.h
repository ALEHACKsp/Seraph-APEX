#pragma once
#include <Windows.h>
#include <iostream>

#define DD_BTN_LBUTTONDOWN 1
#define DD_BTN_LBUTTONUP 2
#define DD_BTN_RBUTTONDOWN 4
#define DD_BTN_RBUTTONUP 8
#define DD_BTN_MBUTTONDOWN 16
#define DD_BTN_MBUTTONUP 32
#define DD_BTN_4BUTTONDOWN 64
#define DD_BTN_4BUTTONUP 128
#define DD_BTN_5BUTTONDOWN 256
#define DD_BTN_5BUTTONUP 512

#define DD_KEY_DOWN 1
#define DD_KEY_UP 2

typedef INT(*PFDD_BTN)(INT nParam);
typedef INT(*PFDD_MOV)(INT x, INT y);
typedef INT(*PFDD_MOVR)(INT dx, INT dy);
typedef INT(*PFDD_WHL)(INT nParam);
typedef INT(*PFDD_KEY)(INT nParam1, INT nParam2);
typedef INT(*PFDD_STR)(LPCSTR lpszSendString);
typedef INT(*PFDD_TODC)(INT nVK_Code);

class dd
{
private:
	HMODULE m_hModule;
	PFDD_BTN m_pfDD_btn = NULL;
	PFDD_MOV m_pfDD_mov = NULL;
	PFDD_MOVR m_pfDD_movR = NULL;
	PFDD_WHL m_pfDD_whl = NULL;
	PFDD_KEY m_pfDD_key = NULL;
	PFDD_STR m_pfDD_str = NULL;
	PFDD_TODC m_pfDD_todc = NULL;

public:
	dd();
	dd(LPCWSTR lpszDllPath);
	~dd();

	/*
		DD�� �ʱ�ȭ �ϴ� �Լ� �Դϴ�.
		�ݵ�� �ѹ��� ȣ���ؾ��մϴ�.

		���� :
		lpszDllPath : DLL�� ����Դϴ�.

		��ȯ�� :
		-1 : DLL�� ã�� �� ����
		-2 : LoadLibrary�� ������. GetLastError�� ���ؼ� �߰� ������ ��������
	*/
	INT Init(LPCWSTR lpszDllPath);

	/*
		DD�� Ǯ���ִ� �Լ�
		���� ȣ�� ���ص� �Ҹ��ڿ��� ȣ����
	*/
	VOID DisPose();

	/*
	=============================================================================




	DD_�� �����ϴ� �Լ����� ���ϰ��� -2�� ��쿣 �ʱ�ȭ�� �ȵ��� �� �Դϴ�



	=============================================================================
	*/

	/*
		���콺 ��ư�� ������ �Լ�

		���� :
		#define DD_BTN_LBUTTONDOWN 1	//��Ŭ�� ����
		#define DD_BTN_LBUTTONUP 2		//��Ŭ�� ��
		#define DD_BTN_RBUTTONDOWN 4	//��Ŭ�� ����
		#define DD_BTN_RBUTTONUP 8		//��Ŭ�� ��
		#define DD_BTN_MBUTTONDOWN 16
		#define DD_BTN_MBUTTONUP 32
		#define DD_BTN_4BUTTONDOWN 64
		#define DD_BTN_4BUTTONUP 128
		#define DD_BTN_5BUTTONDOWN 256
		#define DD_BTN_5BUTTONUP 512
	*/
	INT DD_btn(INT nParam);

	INT DD_mov(INT x, INT y);

	/*
		���콺�� �̵���Ű�� �Լ�

		���� :
		x : ȭ��� ���� x ��ǥ
		y : ȭ��� ���� y ��ǥ
	*/
	//INT DD_mov(INT x, INT y);

	/*
		���콺�� ��������� �̵���Ű�� �Լ�
		���� ���콺 Ŀ�� ��ġ���� ���� �� ��ŭ �̵���ŵ�ϴ�.

		���� :
		dx : dx��ŭ �ش� ��ġ���� �����Դϴ�.
		dy : dy��ŭ �ش� ��ġ���� �����Դϴ�.
	*/
	INT DD_movR(INT dx, INT dy);

	/*
		���콺 ���� �����̴� �Լ� �Դϴ�.

		���� ������ ���Ƽ� �׽�Ʈ ���غ�
	*/
	INT DD_whl(INT nParam);

	/*
		Ű�� ������ �Լ� �Դϴ�.

		���� :
		nParam1 : DD�ڵ��Դϴ�. �� �ڵ�� DD_todc�Լ��� ���� �� �ֽ��ϴ�.
		nParam2 : Ű������ ���� �����Դϴ�. 1 (����) , 2(��)

		#define DD_KEY_DOWN 1
		#define DD_KEY_UP 2
	*/
	INT DD_key(INT nParam1, INT nParam2);

	/*
		���ڿ��� �Է¹޴� �Լ��Դϴ�.
		�ѱ��� ����� �� �����ϴ�.

		���� :
		lpszSendString : �Է��� ���ڿ�
	*/
	INT DD_str(LPCSTR lpszSendString);

	/*
		���� Ű�ڵ带 DD�ڵ�� ��ȯ�ϴ� �Լ��Դϴ�.

		���� :
		nVK_Code : ��ȯ��ų ���� Ű�ڵ�
	*/
	INT DD_todc(INT nVK_Code);
};