
// AS_ProjectDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "AS_Project.h"
#include "AS_ProjectDlg.h"
#include "afxdialogex.h"
#include"Snake.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
Snake snake;//set Snake snake
Cell* PaintCell = 0;//set PaintCell as NULL
Cell* GreyCell = 0;//set GreyCell as NULL
int stateW = 0;//set stateW as 0
int stateA = 1;//set stateA as 1
int stateS = 0;//set stateS as 0
int stateD = 0;//set stateD as 0
bool Eaten = TRUE;//set Eaten as TRUE, to determine the snake eat food or not
int reset = 0;//set reset as 0 to  void radical keydown change
int foodx;//set foodx variable 
int foody;//set foody variable
BOOL CONTINUE = TRUE;//set CONTINUE when exit program when head hit wall exa
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CASProjectDlg 대화 상자



CASProjectDlg::CASProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AS_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CASProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CASProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CASProjectDlg 메시지 처리기

BOOL CASProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	if (MessageBox(L"이 게임은 뱀에 대한 잔혹한 묘사가 포함되어 있습니다.\n 무서운 것에 서투른 분은 플레이를 삼가해 주십시오. \n 게임 진행을 원하십니까?", L"경고문", MB_YESNO) == IDYES)//make message box that choose yes or no
	{
		MoveWindow(0, 0, 900, 900);//make window 
		snake.initSnake();//make snake list
		SetTimer(0, 55, nullptr);//set timer
	}
	else  this->DestroyWindow();//or exit program
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CASProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CASProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(rect);
		int x;//x coordinate to draw the one cell of snake
		int y;//y coordinate to draw the one cell of snake
		if (snake.head->x == -13 || snake.head->x == 13 || snake.head->y == -13 || snake.head->y == 13)//if coordinates is out of range
		{
			CONTINUE = FALSE;//set continue as false
			MessageBox(L"벽에 쿵!", L"실패", MB_ICONHAND);//make messagebox
			exit(0);//exit program
		}
		Cell* Cur = snake.head->next;//set Cur as snake.head->next to determine whetere there is same coordinate with head coordinate, "몸에 쿵"
		while (Cur)//loop for find "몸에 쿵"
		{
			if (snake.head->x == Cur->x && snake.head->y == Cur->y)//if there is the same coordinate with head's in snake's cell
			{
				CONTINUE = FALSE;//set continue as false
				MessageBox(L"몸에 쿵!", L"실패", MB_ICONHAND);//make messageboxx
				exit(0);//exit program
			}
			Cur = Cur->next;//Cur points next one
		}
		srand((unsigned)time(0));//srand to make different value of rand function
		Cell* foodCell = snake.head;//set foodCell as snake.head
		if (Eaten)//if Eaten is true
		{
			foodx = rand() % 25 - 12;//set foodx as random number(-12~12)
			foody = rand() % 25 - 12;//set foody as random number(-12~12)
			while (foodCell)//loop that determine whether the food's coordinate is in snake
			{
				if (foodCell->x == foodx && foodCell->y == foody)//if it is found
				{
					foodx = rand() % 25 - 12;//set foodx as new randcom value
					foody = rand() % 25 - 12;//set foody as new randcom value
					foodCell = snake.head;//set foodCell as snake,head
					continue;//continue
				}
				foodCell = foodCell->next;//foodCell points next one
			}
			Eaten = FALSE;//set Eaten as False
			CBrush snake_food(RGB(255, 0, 0));//paint red to food
			dc.SelectObject(snake_food);//object to paint
			int foodxx = ((rect.Width() + 1) / 2) + (31 * foodx);//x coordinate to paint
			int foodyy = ((rect.Height() + 1) / 2) + (31 * foody);//y coordinate to paint
			dc.Rectangle(foodxx - 15, foodyy - 15, foodxx + 15, foodyy + 15);//make red Rectangle
		}
		if (snake.head->x == foodx && snake.head->y == foody)//if head's coordinate is same with food's coordinate, it means snake eat food
		{	
			Eaten = TRUE;//set eaten as true
		}
		PaintCell = snake.head;//set PaintCell as snake.head
		while (PaintCell)//loop that paint snake
		{
			x = ((rect.Width() + 1) / 2) + (31 * (PaintCell->x));//x coordinate to paint
			y = ((rect.Height() + 1) / 2) + (31 * (PaintCell->y));//y coordinate to paint
			if (PaintCell == snake.head)//if PaintCell is head
			{
				CBrush brush_snake_head(RGB(0, 255, 0));//Set green
				dc.SelectObject(brush_snake_head);//object to paint
				dc.Ellipse(x - 15, y - 15, x + 15, y + 15);//make green circle
				PaintCell = PaintCell->next;//PaintCell points next one
				continue;//continue loop
			}
			if (PaintCell == snake.tail)//if PaintCell is tail
			{
				CBrush Grey(RGB(80, 80, 80));//set grey
				CBrush brush_snake_tail(RGB(0, 255, 255));//set blue
				dc.SelectObject(Grey);//object to paint
				dc.Rectangle(x - 15, y - 15, x + 15, y + 15);//paint grey first
				dc.SelectObject(brush_snake_tail);
				dc.Ellipse(x - 15, y - 15, x + 15, y + 15);//and then paint blue circle
				PaintCell = PaintCell->next;//PaintCell points next one
				continue;//continue loop
			}
			CBrush brush_snake_body(RGB(255, 255, 0));//set Yellow
			dc.SelectObject(brush_snake_body);//object to paint
			dc.Rectangle(x - 15, y - 15, x + 15, y + 15);//make Yellow Rectangle
			PaintCell = PaintCell->next;//PaintCell points next one
		}
		if (GreyCell)//if statement to make previous tail position grey
		{
			CBrush Grey(RGB(80, 80, 80));//set grey
			dc.SelectObject(Grey);//object to paint
			int gx = ((rect.Width() + 1) / 2) + (31 * GreyCell->x);//previous tail x coordinate
			int gy = ((rect.Height() + 1) / 2) + (31 * GreyCell->y);//previous tail y coordinate
			dc.Rectangle(gx - 15, gy - 15, gx + 15, gy + 15);//make grey rectangle
		}
		reset = 0;//set reset as 0
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CASProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CASProjectDlg::OnTimer(UINT_PTR nIDEvent)//function to make time event
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (CONTINUE)//if continue is true
	{
		switch (nIDEvent)
		{
		case 0:
		{
			GreyCell = new Cell(0, 0);//make new GreyCell, it will be used previous tail position or new head when snake eats food
			GreyCell->x = snake.tail->x;
			GreyCell->y = snake.tail->y;
			Cell* Cur = snake.tail;//set Cur as snake tail
			if (Eaten)//if snake eat food
			{
				if (stateW == 1)//if stateW is on, GreyCell has corresponding coordinate and become the head of list
				{
					GreyCell->x = snake.head->x;
					GreyCell->y = snake.head->y - 1;
					GreyCell->next = snake.head;
					snake.head->prev = GreyCell;
					snake.head = GreyCell;
					Invalidate(FALSE);
					break;
				}
				else if (stateA == 1)//if stateA is on, do same
				{
					GreyCell->x = snake.head->x - 1;
					GreyCell->y = snake.head->y;
					GreyCell->next = snake.head;
					snake.head->prev = GreyCell;
					snake.head = GreyCell;
					Invalidate(FALSE);
					break;
				}
				else if (stateS == 1)//if stateA is on, do same
				{
					GreyCell->x = snake.head->x;
					GreyCell->y = snake.head->y + 1;
					GreyCell->next = snake.head;
					snake.head->prev = GreyCell;
					snake.head = GreyCell;
					Invalidate(FALSE);
					break;
				}
				else if (stateD == 1)//if stateA is on, do same
				{
					GreyCell->x = snake.head->x + 1;
					GreyCell->y = snake.head->y;
					GreyCell->next = snake.head;
					snake.head->prev = GreyCell;
					snake.head = GreyCell;
					Invalidate(FALSE);
					break;
				}
			}
			if (stateW == 1)//if stateW is on without eaten, it means move
			{
				while (Cur)//loop that move each cell
				{
					if (Cur == snake.head)//if Cur is head, make position corresponding moving state
					{
						Cur->y--;//because of stateW
						break;
					}
					Cur->x = Cur->prev->x;//remain Cell become each previous Cell
					Cur->y = Cur->prev->y;
					Cur = Cur->prev;
				}
			}
			else if (stateA == 1)//if stateA is on
			{
				while (Cur)//loop that move each cell
				{
					if (Cur == snake.head)
					{
						Cur->x--;
						break;
					}
					Cur->x = Cur->prev->x;//remain Cell become each previous Cell
					Cur->y = Cur->prev->y;
					Cur = Cur->prev;
				}
			}
			else if (stateS == 1)//if stateS is on
			{
				while (Cur)//loop that move each cell
				{
					if (Cur == snake.head)
					{
						Cur->y++;
						break;
					}
					Cur->x = Cur->prev->x;//remain Cell become each previous Cell
					Cur->y = Cur->prev->y;
					Cur = Cur->prev;
				}
			}
			else if (stateD == 1)//if stateD is on
			{
				while (Cur)//loop that move each cell
				{
					if (Cur == snake.head)
					{
						Cur->x++;
						break;
					}
					Cur->x = Cur->prev->x;//remain Cell become each previous Cell
					Cur->y = Cur->prev->y;
					Cur = Cur->prev;
				}
			}
			Invalidate(FALSE);
			break;
		}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CASProjectDlg::OnEraseBkgnd(CDC* pDC)//function that set background
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;//object that save information of whole window size
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));//set background as black
	int x = (rect.Width() + 1) / 2;//x coord of center of window
	int y = (rect.Height() + 1) / 2;//y coord of center of window
	int w = 15;//half width of one square on map
	int h = 15;//half height of one square on map
	CBrush map(RGB(80, 80, 80));//set squares color as gray
	dc.SelectObject(map);
	for (int i = -12; i <= 12; i++)//for loop that draw 25x25 gray squares in background
	{
		y = ((rect.Height() + 1) / 2) + (31 * i);//set squares y coord
		for (int j = -12; j <= 12; j++)
		{
			x = ((rect.Width() + 1) / 2) + (31 * j);//set squares x coord
			dc.Rectangle(x - h, y - h, x + w, y + h);//draw rectangle
		}
	}
	return 0;
}


void CASProjectDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//function that user can input keydown event
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
		case 'W':case'w'://if W or w is pressed
		{
			if (stateS == 1 || reset==1)//if opposite direction is input or the value changes more than once before passing from the timer function to the Onpaint function
				break;
			stateW = 1;//stateW on
			stateA = 0;
			stateS = 0;
			stateD = 0;
			reset = 1;//set reset as 1
			break;
		}
		case 'A':case'a'://if A or a is pressed
		{
			if (stateD == 1 || reset==1)//if opposite direction is input or the value changes more than once before passing from the timer function to the Onpaint function
				break;
			stateW = 0;
			stateA = 1;//stateA on
			stateS = 0;
			stateD = 0;
			reset = 1;//set reset as 1
			break;
		}
		case 'S':case's'://if S or s is pressed
		{
			if (stateW == 1 || reset ==1)//if opposite direction is input or the value changes more than once before passing from the timer function to the Onpaint function
				break;
			stateW = 0;
			stateA = 0;
			stateS = 1;//stateS on
			stateD = 0;
			reset = 1;//set reset as 1
			break;
		}
		case 'D':case'd'://if D or d is pressed
		{
			if (stateA == 1 || reset ==1)//if opposite direction is input or the value changes more than once before passing from the timer function to the Onpaint function
				break;
			stateW = 0;
			stateA = 0;
			stateS = 0;
			stateD = 1;//stateD on
			reset = 1;//set reset as 1
			break;
		}
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}



