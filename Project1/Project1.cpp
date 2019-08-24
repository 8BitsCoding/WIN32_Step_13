// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"

#define MAX_COUNT 3
int g_index[MAX_COUNT] = { 0, };

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);
		HGDIOBJ h_old_brush;
		int table[2] = { WHITE_BRUSH, BLACK_BRUSH };

		for (int i = 0; i < MAX_COUNT; i++) {
			/*
			if (g_index[i] == 1) h_old_brush = SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
			Rectangle(h_dc, 0 + i * 100, 0, 101 + i * 100, 100);
			if (g_index[i] == 1) SelectObject(h_dc, h_old_brush);
			*/

			// 코드 간단화
			SelectObject(h_dc, GetStockObject(table[g_index[i]]));
			Rectangle(h_dc, i * 100, 0, 101 + i * 100, 100);
		}

		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		UINT x = LOWORD(lParam);
		UINT y = HIWORD(lParam);

		/*
		if (x >= 0 && x < 100 && y >= 0 && y < 100) g_index = 0;
		else if (x >= 100 && x < 200 && y >= 0 && y < 100) g_index = 1;
		else if (x >= 200 && x < 300 && y >= 0 && y < 100) g_index = 2;
		InvalidateRect(hWnd, NULL, TRUE);
		*/

		// 코드 간단화 - 1
		/*
		if (y >= 0 && y < 100) {
			if (x >= 0 && x < 100) g_index = 0;
			else if (x < 200) g_index = 1;
			else if (x < 300) g_index = 2;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		*/

		// 코드 간단화 - 2
		/*
		if (y >= 0 && y < 100) {
			for (UINT i = 0; i < MAX_COUNT; i++) {
				if (x < (i + 1) * 100) {
					g_index[i] = !g_index[i];
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
			}
		}
		*/

		// 코드 간단화 - 3
		if (y >= 0 && y < 100) {
			UINT index = x / 100;
			if (index < MAX_COUNT) {
				g_index[index] = !g_index[index];
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
	}
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);

	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}