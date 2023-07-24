#pragma once

#include "stdafx.h"

#include "CustomMath.h"

// ���� ��ũ��
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

// ������ �ֿܼ� ���� switch on/off�� ��ũ�� ���
#define		_TEST_CONSOLE	0

#define		STAGE_MAPCX		0x7FFFFFFF
#define		STAGE_MAPCY		2067
#define		STAGE2_MAPCX	3024
#define		STAGE2_MAPCY	2880
#define		STAGE3_MAPCX	3027
#define		STAGE3_MAPCY	1584
#define		BOSS_MAPCX		1216
#define		BOSS_MAPCY		896

#pragma region ���� ����
extern HWND g_hWnd;					// ������ �ڵ�
extern vector<HFONT> g_vFonts;		// �ý��ۿ� ��Ʈ�� ������ �߰��ϱ� ���� �뵵
extern bool g_bWinActivate;			// â ��Ȱ��ȭ�� Ű�Է� ���ִ� �뵵(�ٵ� �������� �ȵ�) ������
extern float g_fDeltaTime;
#pragma endregion

#pragma region ���� ID �±�
// ID
enum OBJID { SYSTEM, PANEL, TILE, PLAYER, PLAYER3, BULLET, MONSTER, UNIT, SPELL, VFX, MOUSE, SHIELD, BUTTON, UI, OBJID_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_WORLD1, SC_EDIT, SC_STAGE, SC_STAGE2, SC_STAGE3, SC_STAGE_BOSS, SC_END };

enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SYSTEM_EFFECT, SOUND_PLAYER, SOUND_ENEMY, SOUND_VFX, MAXCHANNEL };

enum TILEOPTION { NORMAL = 0, WALL, FALL, SADARI, TRAP, PREPOTAL, POTAL, PRESTAGE, END };

enum TEAM_ID { TEAM_ALPHA, TEAM_BETA, TEAM_GAMMA };

enum STAGEID { LODING1, STAGE1, LODING2, STAGE2, LODING3, STAGE3, LODING4, STAGE4, STAGE_END };

#pragma endregion

#pragma region �ִϸ��̼ǿ� ������
// �̹����� ǥ���ϱ� ���� ���׷��̵� �� FRAME ����ü
typedef struct tagFrame
{
	tagFrame() : bLoop(true), bStop(false), iFrameStart(), iFrameEnd(), iFrameCur(), iMotion(),
		iWidth(), iHeight(), iOffsetX(), iOffsetY(), ulSpeed(),
		ulTime(GetTickCount64()), ulCurTime(GetTickCount64()), ulDelayTime(GetTickCount64()) {}

	bool			bLoop;
	bool			bStop;

	int				iFrameStart;	// ���� ������
	int				iFrameEnd;		// �� ������
	int				iFrameCur;		// ���� ������
	int				iMotion;		// �ִϸ��̼� ����(��������Ʈ ��Ʈ��)

	int				iOffsetX;		// �̹��� ���� X
	int				iOffsetY;		// �̹��� ���� Y
	int				iWidth;			// �̹��� �ʺ�
	int				iHeight;		// �̹��� ����

	ULONGLONG		ulSpeed;		// �ӵ�
	ULONGLONG		ulTime;			// �ð� üũ
	ULONGLONG		ulCurTime;		// ���� �ð�
	ULONGLONG		ulDelayTime;	// ������ �ִ� �ð�

	void Set_Loop(bool value) { bLoop = value; }
	void Set_Stop() { bStop = true; }
	void Set_Resume() { bStop = false; }
	bool IsFrameEnd() { return ( iFrameCur >= iFrameEnd); }
	bool IsFrameTick(int value) { return ((iFrameCur == value) && (ulTime == ulCurTime)); }
	bool IsFrameStart() { return ( iFrameCur == 0); }

	// �����ӽð� ������Ʈ �Լ�
	void Update()
	{
		ulCurTime = GetTickCount64();
		if (ulTime + ulSpeed < ulCurTime)
		{
			if (!bStop)
				++iFrameCur;

			if (iFrameCur > iFrameEnd)
			{
				if (bLoop)
					iFrameCur = 0;
				else
					iFrameCur = iFrameEnd;
			}

			ulTime = ulCurTime;
		}
	}
}FRAME;

// FRAME�� Ű�� �ִϸ��̼� Ű���� �߰��� ���� ��Ʈ
struct FRAME_TSET
{
	FRAME_TSET() {}
	~FRAME_TSET() {}

	wstring sFrameKey;
	wstring sAnimKey;
	FRAME tFrame;

	wstring& Get_FrameKey()
	{
		return sFrameKey;
	}

	wstring& Get_AnimKey()
	{
		return sAnimKey;
	}

	const TCHAR* Get_StrFrameKey()
	{
		return sFrameKey.c_str();
	}
	const TCHAR* Get_StrAnimKey()
	{
		return sAnimKey.c_str();
	}

	void Set_Keys(const TCHAR* _sFrameKey, const TCHAR* _sAnimKey)
	{
		sFrameKey = _sFrameKey;
		sAnimKey = _sAnimKey;
	}

	FRAME& Get_Frame()
	{
		return tFrame;
	}
	FRAME& operator*()
	{
		return tFrame;
	}
	FRAME* operator->()
	{
		return &tFrame;
	}

	void Update()
	{
		tFrame.Update();
	}
};

// FRAME�� Ȱ���ϱ� ���� ������ STL ����ü
template<typename T>
struct FRAME_MAP
{
	FRAME_MAP() {}
	~FRAME_MAP() {}

	map<T, FRAME_TSET> mapFrame;

	void Add_Frame(const T& tKey)
	{
		mapFrame.emplace(tKey, FRAME_TSET());
	}

	void Add_Frame(const T&& tKey)
	{
		mapFrame.emplace(tKey, FRAME_TSET());
	}

	void Update()
	{
		for (auto iter = mapFrame.begin(); iter != mapFrame.end(); ++iter)
		{
			(*iter).second.Update();
		}
	}

	map<T, FRAME_TSET>& operator() ()
	{
		return mapFrame;
	}

	FRAME_TSET& operator[](const T& tIndex)
	{
		mapFrame[tIndex];
	}

	FRAME_TSET& operator[](const T&& tIndex)
	{
		mapFrame[tIndex];
	}
};

struct FRAME_VECTOR
{
	FRAME_VECTOR() {}
	~FRAME_VECTOR() {}

	vector<FRAME_TSET> vFrame;

	void Add_Frame()
	{
		vFrame.push_back(FRAME_TSET());
	}

	void Update()
	{
		for (size_t i = 0; i < vFrame.size(); ++i)
		{
			vFrame[i].Update();
		}
	}

	vector<FRAME_TSET>& operator() ()
	{
		return vFrame;
	}

	FRAME_TSET& operator[](const int& iIndex)
	{
		return vFrame[iIndex];
	}
	FRAME_TSET& operator[](const int&& iIndex)
	{
		return vFrame[iIndex];
	}
};

#pragma endregion

#pragma region �⺻
// ���� ��ġ, ũ��Ӽ�
typedef struct tagInfo
{
	tagInfo() 
		: fCX(float()), fCY(float()), vPos(0.f, 0.f, 0.f), vDir(1.f, 0.f, 0.f), vLook(1.f, 0.f, 0.f), fAngle(0.f),
		vSize(1.f, 1.f, 1.f), vSpeed(0.f, 0.f, 0.f), vAccel(0.f, 0.f, 0.f), matWorld(*D3DXMatrixIdentity(&matWorld))
	{}
	~tagInfo() {}

	float	fCX;	// ���� ����
	float	fCY;	// ���� ����	

	// ��ġ, �ٶ󺸴� ����
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	// ȸ�� ���� (Degree)
	float			fAngle;
	// ������ (Scale)
	D3DXVECTOR3		vSize;
	//D3DXVECTOR3		vNormal;

	// ���� �ӵ�
	D3DXVECTOR3		vSpeed;
	D3DXVECTOR3		vAccel;

	// �ִϸ��̼�, �̹��� Ʋ
	FRAME_TSET		tFrameTSet;

	// ���
	D3DXMATRIX		matWorld;

}INFO;

// ��� : ���� ���� ���� ��� ���� ���·� �����Ͽ� ������ ��
// ����� ��� ���� : ��ü�� ���� ���¸� ǥ���ϱ� ����
// ���� ��� : ��� ���� ���ڰ� ��ġ�ϴ� ���
#pragma endregion

#pragma region ��ƿ��Ƽ
// ���콺 ��ġ ���� ��ȯ
static D3DXVECTOR3		Get_Mouse()
{
	POINT		Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}
#pragma endregion

#pragma region �޸𸮰��� ���ø� & �Լ� ��ü
// ���� ����
template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

// ��ü ���� �Լ� ��ü
struct CDeleteObj
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

// Map�� key, value�� �����Ҵ� ��ü ����
// % ���� ������ ���� �����Ҵ��� ��츸 ������.
class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.first)
		{
			delete Pair.first;
		}
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

// Map ���� �Ҵ� key�� �޸� ������ �Լ� ��ü
// ���� key�� �����Ҵ��� ��츸 ������.
class CDeleteMap_Key
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.first)
		{
			delete Pair.first;
		}
	}
};

// Map ���� �Ҵ� value�� �޸� ������ �Լ� ��ü
// ���� value�� �����Ҵ��� ��츸 ������.
class CDeleteMap_Value
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



// ���ڿ� �±� �� �Լ���ü
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

#pragma region ����
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



#pragma region ���� ���¸ӽ�
// ���� �ƹ����� �� �� �ִ� ���¸ӽ� ����ü
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

#pragma region ���¸ӽ� �Լ�
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

	// ������ ��
	bool IsState_Entered()
	{
		if (bIsEnter && !bIsReserved)
		{
			bIsEnter = false;
			bIsExit = false;		// ���� ���Խ� Ż�� ���� �ڵ� ��Ȱ��ȭ
			return true;
		}
		return false;
	}

	// �������� ��
	bool IsState_Exit()
	{
		// ���� ���¿����� �ϳ��� 
		if (bIsReserved)
		{
			Set_State(eNextState);
			bIsReserved = false;
			bIsExit = false;
			return true;
		}

		// �̹� Entered �Լ��� �ҷ����� �� Ż�� ������ OFF ��Ų��.
		if (!bIsEnter)
			bIsExit = false;

		if (bIsExit)
		{
			bIsExit = false;
			return true;
		}
		return false;
	}

	// ������ ���� ���¿����� ������Ʈ�� �� �� �ִ�.
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
using MAP_FUNC = unordered_map<Key, function<Func>>;

// ���¸ӽŰ� �Լ��� ���� ����� �� �ִ� ���ø�
template<typename Key, typename Func>
struct STATE_SET
{
	STATE_SET() {}
	~STATE_SET() {}

public:
	STATE_INFO<Key> tState;
	MAP_FUNC<Key, Func> mapFunc;

public:
#pragma region ���¸ӽ�
	void Set_State(Key _eState)
	{
		tState.Set_State(_eState);
	}

	void Reserve_State(Key _eState)
	{
		tState.Reserve_State();
	}

	// ������ ��
	bool IsState_Entered()
	{
		return tState.IsState_Entered();
	}

	// �������� ��
	bool IsState_Exit()
	{
		return tState.IsState_Exit();
	}

	// ������ ���� ���¿����� ������Ʈ�� �� �� �ִ�.
	bool Can_Update()
	{
		return tState.Can_Update();
	}

	bool IsOnState(Key _eState)
	{
		return tState.IsOnState(_eState);
	}
#pragma endregion
#pragma region �Լ� ��
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

#pragma region ������, ������, Max & Cur ǥ���� ����ü
// ������ �뵵�� ���� ����ü
template<typename T = float>
struct _DELAY
{
	static_assert(std::is_arithmetic<T>::value, "T�� ���� Ÿ���̾�߸� �մϴ�.");

public:
	T Max, Cur;
private:
	T PrevCur;


public:
	_DELAY() : Max(T()), Cur(T()), PrevCur(Cur) {}
	_DELAY(T _Max, bool bMax = false) : Max(_Max), Cur(T(T(bMax)* T(_Max))), PrevCur(Cur) {}
	~_DELAY() {}

	// �� ������Ʈ �� �ƽ��� ���޽� ��ȯ
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

	// ���簪 �ʱ�ȭ
	void Reset()
	{
		Cur = T();
	}
	void Reset(T value)
	{
		Cur = value;
	}

	// Max �� �缳�� �� ���簪 �ʱ�ȭ
	void ReAdjust(T max)
	{
		Max = max;
		Cur = T();
	}

	bool IsReach(T point)
	{
		return (Cur >= point);
	}

	// �������� üũ�ϰ��� �ϴ� ������ �ѹ��� ������ ���� üũ�մϴ�.
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

// �����̿����� ���� ���� ��Ī
template <typename T = float>
using DELAY = _DELAY<T>;

// ������������ ���� ���� ��Ī
template <typename T = float>
using GAUGE = _DELAY<T>;
#pragma endregion

#pragma region �׼�Ű
// ACTION Ű�� �⺻����
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

// �Լ���ü - ������Ʈ��
template<typename Key>
class CMapAction_Updator
{
public:
	void operator() (pair<const Key, ACTION>& Action)
	{
		Action.second.Update();
	}
};

// ACTION ����ü�� ���� ����ϴ� ����ü.
// ACTION ���Ϸ� ���� �ͺ��� �̰��� ���� ���� ������� Ȯ�强 �鿡�� ����.
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


