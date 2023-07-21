#pragma once

#include "stdafx.h"

#include "CustomMath.h"

// 범용 매크로
#define		WINCX		800
#define		WINCY		600

#define		TILEX		30
#define		TILEY		20

#define		TILECX		64
#define		TILECY		64

#define MAP_SIZE 1920

#define		PURE		= 0

#define		OBJ_DEAD	 1
#define		OBJ_NOEVENT	 0

#define		VK_MAX		0xff

// 디버깅용 콘솔에 대한 switch on/off용 매크로 상수
#define		_TEST_CONSOLE	0

#pragma region 전역 변수
extern HWND g_hWnd;					// 윈도우 핸들
extern vector<HFONT> g_vFonts;		// 시스템에 폰트를 여러개 추가하기 위한 용도
extern bool g_bWinActivate;			// 창 비활성화시 키입력 없애는 용도(근데 언제부터 안됨) 쓰지마
#pragma endregion

#pragma region 전역 ID 태그
// ID
enum OBJID { SYSTEM, PANEL, TILE, PLAYER, BULLET, MONSTER, UNIT, SPELL, VFX, MOUSE, SHIELD, BUTTON, UI, OBJID_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_WORLD1, SC_EDIT, SC_STAGE, SC_END };

enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SYSTEM_EFFECT, SOUND_PLAYER, SOUND_ENEMY, SOUND_VFX, MAXCHANNEL };

enum TEAM_ID { TEAM_ALPHA, TEAM_BETA, TEAM_GAMMA };
#pragma endregion

#pragma region 기본
// 범용 위치, 크기속성
typedef struct tagInfo
{
	D3DXVECTOR3		vPos;

	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	//D3DXVECTOR3		vNormal;

	D3DXMATRIX		matWorld;

}INFO;
// 행렬 : 여러 개의 수를 행과 열의 상태로 정렬하여 저장한 것
// 행렬의 사용 이유 : 객체의 여러 상태를 표현하기 위함
// 정방 행렬 : 행과 열의 숫자가 일치하는 행렬
#pragma endregion

#pragma region 유틸리티
// 마우스 위치 벡터 변환
static D3DXVECTOR3		Get_Mouse()
{
	POINT		Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}
#pragma endregion

#pragma region 메모리관리 템플릿 & 함수 객체
// 안전 삭제
template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

// 객체 삭제 함수 객체
struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

// Map 동적 할당 value값 메모리 해제용 함수 객체
class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

// 문자열 태그 비교 함수객체
class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString) : m_pString(pString) {}
public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR* m_pString;
};
#pragma endregion

#pragma region 라인
typedef	struct tagLinePoint
{
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	float	fX;
	float	fY;

}LINEPOINT;


typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint)
		: tLpoint(_tLpoint), tRpoint(_tRpoint) { }

	LINEPOINT	tLpoint;
	LINEPOINT	tRpoint;

}LINE;
#pragma endregion

#pragma region 애니메이션용 프레임
// 이미지를 표시하기 위해 업그레이드 된 FRAME 구조체
typedef struct tagFrame
{
	tagFrame() : bLoop(true), bStop(false), iFrameStart(), iFrameEnd(), iFrameCur(), iMotion(),
		iWidth(), iHeight(), iOffsetX(), iOffsetY(), ulSpeed(),
		ulTime(GetTickCount64()), ulCurTime(GetTickCount64()), ulDelayTime(GetTickCount64()) {}

	bool			bLoop;
	bool			bStop;

	int				iFrameStart;	// 시작 프레임
	int				iFrameEnd;		// 끝 프레임
	int				iFrameCur;		// 현재 프레임
	int				iMotion;		// 애니메이션 종류(스프라이트 시트용)

	int				iOffsetX;		// 이미지 원점 X
	int				iOffsetY;		// 이미지 원점 Y
	int				iWidth;			// 이미지 너비
	int				iHeight;		// 이미지 높이
	
	ULONGLONG		ulSpeed;		// 속도
	ULONGLONG		ulTime;			// 시간 체크
	ULONGLONG		ulCurTime;		// 현재 시간
	ULONGLONG		ulDelayTime;	// 딜레이 주는 시간

	void Set_Loop(bool value) { bLoop = value; }
	void Set_Stop() { bStop = true; }
	void Set_Resume() { bStop = false; }
	bool IsFrameEnd() { return (iFrameCur >= iFrameEnd); }
	bool IsFrameTick(int value) { return ((iFrameCur == value) && (ulTime == ulCurTime)); }
	bool IsFrameStart() { return (iFrameCur == 0); }
}FRAME;
#pragma endregion

#pragma region 간이 상태머신
// 대충 아무때나 쓸 수 있는 상태머신 구조체
template <typename T>
struct tagState
{
	tagState() : eState(T()), ePrevState(T()), eNextState(T())
	{
		bIsEnter = false;
		bIsExit = false;
		bIsReserved = false;
	}
	~tagState() {}

	bool	bIsEnter;
	bool	bIsExit;
	bool	bIsReserved;
	T		eState;
	T		ePrevState;
	T		eNextState;

#pragma region 상태머신 함수
	void Set_State(T _eState)
	{
		ePrevState = eState;
		eState = _eState;
		bIsExit = true;
		bIsEnter = true;
	}

	void Reserve_State(T _eState)
	{
		eNextState = _eState;
		bIsReserved = true;
	}

	// 진입할 때
	bool IsState_Entered()
	{
		if (bIsEnter && !bIsReserved)
		{
			bIsEnter = false;
			bIsExit = false;		// 상태 진입시 탈출 조건 자동 비활성화
			return true;
		}
		return false;
	}

	// 빠져나갈 때
	bool IsState_Exit()
	{
		// 예약 상태에서는 하나의 
		if (bIsReserved)
		{
			Set_State(eNextState);
			bIsReserved = false;
			bIsExit = false;
			return true;
		}

		// 이미 Entered 함수를 불러왔을 때 탈출 조건을 OFF 시킨다.
		if (!bIsEnter)
			bIsExit = false;

		if (bIsExit)
		{
			bIsExit = false;
			return true;
		}
		return false;
	}

	// 예약이 없는 상태에서만 업데이트를 할 수 있다.
	bool Can_Update()
	{
		return !bIsReserved;
	}

	bool IsOnState(T _eState)
	{
		return (eState == _eState);
	}
#pragma endregion
};

template <typename T>
using STATE_INFO = tagState<T>;

template <typename Key, typename Func>
using MAP_FUNC = map<Key, function<Func>>;

// 상태머신과 함수를 묶어 사용할 수 있는 템플릿
template<typename Key, typename Func>
struct STATE_SET
{
	STATE_SET() {}
	~STATE_SET() {}

public:
	STATE_INFO<Key> tState;
	MAP_FUNC<Key, Func> mapFunc;

public:
#pragma region 상태머신
	void Set_State(Key _eState)
	{
		tState.Set_State(_eState);
	}

	void Reserve_State(Key _eState)
	{
		tState.Reserve_State();
	}

	// 진입할 때
	bool IsState_Entered()
	{
		return tState.IsState_Entered();
	}

	// 빠져나갈 때
	bool IsState_Exit()
	{
		return tState.IsState_Exit();
	}

	// 예약이 없는 상태에서만 업데이트를 할 수 있다.
	bool Can_Update()
	{
		return tState.Can_Update();
	}

	bool IsOnState(Key _eState)
	{
		return tState.IsOnState(_eState);
	}
#pragma endregion
#pragma region 함수 맵
	void Add_Func(Key eState, function<Func>&& fn)
	{
		mapFunc.emplace(eState, fn);
	}

	function<Func> Get_StateFunc()
	{
		return mapFunc[tState.eState];
	}
#pragma endregion

};
#pragma endregion

#pragma region 딜레이, 게이지, Max & Cur 표현용 구조체
// 딜레이 용도로 만든 구조체
template<typename T = float>
struct _DELAY
{
	static_assert(std::is_arithmetic<T>::value, "T는 원시 타입이어야만 합니다.");

public:
	T Max, Cur;
private:
	T PrevCur;


public:
	_DELAY() : Max(T()), Cur(T()), PrevCur(Cur) {}
	_DELAY(T _Max, bool bMax = false) : Max(_Max), Cur(T(T(bMax)* T(_Max))), PrevCur(Cur) {}
	~_DELAY() {}

	// 값 업데이트 및 맥스값 도달시 반환
	bool Update(T increase, bool bAutoReset = false)
	{
		PrevCur = Cur;
		Cur += increase;
		if (Cur >= Max)
		{
			if (bAutoReset)
				Cur = T();
			else
				Cur = Max;
			return true;
		}

		return false;
	}

	bool Update(T increase, T point, bool bAutoReset = false)
	{
		PrevCur = Cur;
		Cur += increase;
		if (Cur >= point)
		{
			if (bAutoReset)
				Cur = T();
			else
				Cur = Max;
			return true;
		}

		return false;
	}

	// 현재값 초기화
	void Reset()
	{
		Cur = T();
	}

	// Max 값 재설정 및 현재값 초기화
	void ReAdjust(T max)
	{
		Max = max;
		Cur = T();
	}

	bool IsReach(T point)
	{
		return (Cur >= point);
	}

	// 증가값과 체크하고자 하는 값으로 한번만 지나갈 때를 체크합니다.
	bool IsReach_Once(T point, T increase)
	{
		return (Cur >= point - increase * (T)0.5f && Cur < point + increase * (T)0.5f);
	}

	bool IsMax()
	{
		return (Cur >= Max);
	}

	bool IsMax_Once()
	{
		return (Cur >= Max && PrevCur != Cur);
	}

	float Get_Percent()
	{
		return (static_cast<float>(Cur) / static_cast<float>(Max));
	}
};

// 딜레이용으로 쓰기 위한 별칭
template <typename T = float>
using DELAY = _DELAY<T>;

// 게이지용으로 쓰기 위한 별칭
template <typename T = float>
using GAUGE = _DELAY<T>;
#pragma endregion

#pragma region 액션키
// ACTION 키의 기본단위
typedef struct _ACTION
{
	_ACTION() : bAction() {}
	~_ACTION() {}

	bool bAction;

	void Act()
	{
		bAction = true;
	}

	void Update()
	{
		bAction = false;
	}

	bool Sync()
	{
		if (bAction)
		{
			bAction = false;
			return true;
		}
		return false;
	}

	bool IsOnAct()
	{
		return bAction;
	}
}ACTION;

template<typename Key>
using MAP_ACTION = map<Key, ACTION>;

// 함수객체 - 업데이트용
template<typename Key>
class CMapAction_Updator
{
public:
	void operator() (pair<const Key, ACTION>& Action)
	{
		Action.second.Update();
	}
};

// ACTION 구조체를 묶어 사용하는 구조체.
// ACTION 단일로 쓰는 것보다 이것을 쓰는 것이 여러모로 확장성 면에서 좋다.
template<typename Key>
struct ACTION_SET
{
	ACTION_SET() {}
	~ACTION_SET() {}

public:
	map<Key, ACTION> mapAction;

	void Add_Action(Key&& tKey)
	{
		mapAction.emplace(tKey, ACTION());
	}

	ACTION& operator[] (Key&& tKey)
	{
		return mapAction[tKey];
	}

	void Update()
	{
		for_each(mapAction.begin(), mapAction.end(), CMapAction_Updator<Key>());
	}
};
#pragma endregion


