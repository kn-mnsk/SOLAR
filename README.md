# SOLAR SYSTEM - 03Solar

## Note:
1. SolarSystem resources are placed in the localResources Folder

# Reference
## 1. Dialog window  
1. [manipulate DLGTEMPLATE programatically](https://stackoverflow.com/questions/204334/how-to-manipulate-dlgtemplate-programmatically)  

    ## sample coding  c++ 
    
   
    LPWORD lpwAlign(LPWORD lpIn)
    {
        ULONG ul;

        ul = (ULONG)lpIn;
        ul++;
        ul >>= 1;
        ul <<= 1;
        return (LPWORD)ul;
    }

    LPWORD AlignDwordPtr(LPWORD lpIn)  
    {  
        ULONG ul;  

        ul = (ULONG)lpIn;
        ul += 3;
        ul >>= 2;
        return (LPWORD)ul;
    }

    LPWORD AddStringOrOrdinalToWordMem(LPWORD lpw, char* sz_Or_Ord)  
    {  
        
	LPWSTR  lpwsz;
	int     BufferSize;

	if (sz_Or_Ord == NULL)
	{
		*lpw++ = 0;
	}
	else
	{
		if (HIWORD(sz_Or_Ord) == 0) //MAKEINTRESOURCE macro 
		{
			*lpw++ = 0xFFFF;
			*lpw++ = LOWORD(sz_Or_Ord);
		}
		else
		{
			if (strlen(sz_Or_Ord))
			{
				lpwsz = (LPWSTR)lpw;
				BufferSize = MultiByteToWideChar(CP_ACP, 0, sz_Or_Ord, -1, lpwsz, 0);
				MultiByteToWideChar(CP_ACP, 0, sz_Or_Ord, -1, lpwsz, BufferSize);
				lpw = lpw + BufferSize;
			}
			else
			{
				*lpw++ = 0;
			}
		}
	}
	return(lpw);
}


2. [DialogBox template](http://winapi.freetechsecrets.com/win32/WIN32Dialog_Box_Template.htm)

    ## sample coding  c++  

    ```c++
    LRESULT CreateDialogTemplate(HINSTANCE hInst, HWND hWndOwner, DLGPROC DialogProc) {
	//Dialog template https://www.pg-fl.jp/program/tips/dlgmem.htm

	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPDLGITEMTEMPLATE lpdit;
	LPWORD lpw;
	LPBYTE lpb;
	LPWSTR lpwsz;
	int nChar;

	// 実際は、サイズはデータが収まりきるように
	// あらかじめ計算しておく必要があります。
	// GMEM_ZEROINIT であらかじめデータを 0 に設定しておきます。
	// (省略されているメンバは 0 になります)
	hgbl = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 1024);
	if (!hgbl)
		return -1;
		//ErrorAndExit();

	// ダイアログボックスの初期値を設定します。
	// ※ hgbl と lpdt のアドレスは同じになります (GMEM_FIXED のため)。
	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);
	//lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION | DS_SETFONT;  // フォント付き
	lpdt->style = WS_POPUPWINDOW | WS_DLGFRAME | WS_VSCROLL | WS_MINIMIZEBOX| DS_SETFONT | WS_EX_TOPMOST;  // フォント付き
	//lpdt->cdit = 2;  // コントロールの数
	lpdt->cdit = 0;  // コントロールの数
	lpdt->x = 10;   lpdt->y = 10;
	lpdt->cx = 100; lpdt->cy = 100;

	// 次のメンバの設定に移ります。
	lpw = (LPWORD)(lpdt + 1);

	// <Menu ID>
	//   *lpw++ = の文は、その位置に値を設定した後 ++ を行います。
	//   (つまり *lpw = 0; lpw++; と同じ)
	//   正式には lpw++ がインクリメントする前のアドレスを返し、
	//   そのアドレスに対して *XXX = 0 を行っています。
	*lpw++ = 0;

	// <Window Class>
	*lpw++ = 0;

	// <Dialog Title>
	lpwsz = (LPWSTR)lpw;

	// MultiByteToWideChar 関数で ANSI 文字列を Unicode 文字列に変換します。
	// 戻り値 (書き込んだ文字列の長さ) に NULL 文字が含まれているので + 1 しません。
	nChar = MultiByteToWideChar(CP_ACP, 0, "ダイアログ テスト", -1, lpwsz, 50);

	// lpw = (LPWORD) lpwsz は必要ありません (アドレスが同じであるため)。
	lpw += nChar;

	// WORD fontSize
	// ※ DS_SETFONT を指定しなかった場合、コントロールの設定に
	// 　 移るまでのデータ設定は行いません。
	*lpw++ = 9;

	// WCHAR fontName[]
	lpwsz = (LPWSTR)lpw;
	nChar = MultiByteToWideChar(CP_ACP, 0, "ＭＳ Ｐ明朝", -1, lpwsz, 50);
	lpw += nChar;

	//{
	//	// コントロールの設定に移ります。
	////   移る前に DWORD 境界に揃えます。
	//	lpw = (LPWORD)(((DWORD_PTR)lpw + 3) & ~((DWORD_PTR)3));
	//	lpdit = (LPDLGITEMTEMPLATE)lpw;

	//	// OK ボタンを作ります。
	//	lpdit->x = 10;  lpdit->y = 70;
	//	lpdit->cx = 60; lpdit->cy = 14;
	//	lpdit->id = IDOK;  // OK ボタンの ID
	//	lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

	//	// 次のメンバの設定に移ります。
	//	lpw = (LPWORD)(lpdit + 1);

	//	// <Window Class>
	//	//   これでも構いません。
	//	//     lpwsz = (LPWSTR) lpw;
	//	//     nChar = MultiByteToWideChar(CP_ACP, 0, "Button", -1, lpwsz, 50);
	//	//     lpw += nChar;
	//	*lpw++ = 0xFFFF;  // 数値指定に必要
	//	*lpw++ = 0x0080;  // ボタンのウィンドウクラスを指定します。

	//	// <Control Text>
	//	lpwsz = (LPWSTR)lpw;
	//	nChar = MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
	//	lpw += nChar;

	//	// WORD SizeOfCreationData
	//	//   特にデータは無いため、0 で終わります。
	//	//   ※ データがある場合、データのサイズ + sizeof(WORD) (= 2) を設定します。
	//	*lpw++ = 0;
	//}

	// 次のコントロールの設定に移ります。
	lpw = (LPWORD)(((DWORD_PTR)lpw + 3) & ~((DWORD_PTR)3));
	lpdit = (LPDLGITEMTEMPLATE)lpw;

	lpdit->x = 10;  lpdit->y = 10;
	lpdit->cx = 40; lpdit->cy = 9;
	lpdit->id = IDC_STATIC;  // スタティックコントロールによくある ID (IDC_STATIC = -1)
	lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

	lpw = (LPWORD)(lpdit + 1);

	// <Window Class>
	//   これでも構いません。
	//     lpwsz = (LPWSTR) lpw;
	//     nChar = MultiByteToWideChar(CP_ACP, 0, "Static", -1, lpwsz, 50);
	//     lpw += nChar;
	*lpw++ = 0xFFFF;
	*lpw++ = 0x0082;  // スタティックコントロールのウィンドウクラスを指定します。

	// <Control Text>
	lpwsz = (LPWSTR)lpw;
	nChar = MultiByteToWideChar(CP_ACP, 0, "メッセージ", -1, lpwsz, 50);
	lpw += nChar;

	// WORD SizeOfCreationData
	//   特にデータは無いため、0 で終わります。
	*lpw++ = 0;

	// データ設定は終了しました。ロックを解除します。
	GlobalUnlock(hgbl);

	// DialogBoxIndirect を呼び出して作成します。GMEM_FIXED なので
	// LPDLGTEMPLATE の引数には hgbl をそのまま指定します。
	// (hInst、hWndOwner、DialogProc は既に定義されているものとします。)
	DialogBoxIndirect(hInst, (LPDLGTEMPLATE)hgbl, hWndOwner, (DLGPROC)DialogProc);

	// メモリを解放します。
	GlobalFree(hgbl);
}
    ```


```c++
LRESULT DisplayMyMessage(HINSTANCE hinst, HWND hwndOwner, LPSTR lpszMessage)
{
	//https://learn.microsoft.com/en-us/windows/win32/dlgbox/using-dialog-boxes#creating-a-template-in-memory
	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPDLGITEMTEMPLATE lpdit;
	LPWORD lpw;
	LPWSTR lpwsz;
	LRESULT ret;
	int nchar; // original
	//WORD nchar; // test

	//hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024); // original
	hgbl = GlobalAlloc(GMEM_ZEROINIT, 2048); // test
	//HANDLE hHeap = GetProcessHeap(); // test
	//hgbl = HeapAlloc(hHeap, HEAP_GENERATE_EXCEPTIONS, 1024);// test
	if (!hgbl)
		return -1;

	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);
	if (!lpdt)
	{
		return -1;
	}
	// Define a dialog box.

	lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION;
	lpdt->cdit = 3;         // Number of controls
	lpdt->x = 10;  lpdt->y = 10;
	lpdt->cx = 100; lpdt->cy = 100;

	lpw = (LPWORD)(lpdt+1); // original
	//lpw = (LPWORD)lpdt; // test
	//lpw++; // test
	//lpw = (LPWORD)lpdt + 1; // test

	*lpw++ = 0;             // No menu
	*lpw++ = 0;             // Predefined dialog box class (by default)
	//*lpw++ = 0x0000;             // No menu
	//*lpw++ = 0x0000;             // Predefined dialog box class (by default)

	//WORD temp = *lpw;  // test
	{
		lpw = AddStringOrOrdinalToWordMem(lpw, "My Dialog");
	}
	
	//{
	//	lpwsz = (LPWSTR)lpw;
	//	//nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "My Dialog", -1, lpwsz, 50);// original
	//	char* title = "My Dialog";
	//	nchar = MultiByteToWideChar(CP_ACP, 0, title, -1, lpwsz, 0); // test
	//	MultiByteToWideChar(CP_ACP, 0, title, -1, lpwsz, nchar);

	//	//nchar = 1 + MultiByteToWideChar(CP_UTF8, 0, "My Dialog", -1, lpwsz, 50);
	//	//ERROR_EXIT("DisplayMyMessage");
	//	lpw += nchar; // original
	//	//*lpw += nchar; // test
	//	//*lpw++ += nchar; // test

	//	//WORD temp = *--lpw; // test
	//	//temp = *--lpw; // test
	//	//temp = *--lpw;// test

	//}

	//{
	//	//-----------------------
	//// Define an OK button.
	////-----------------------
	////lpw = lpwAlign(lpw) ;    // original// Align DLGITEMTEMPLATE on DWORD boundary
	//	lpw = AlignDwordPtr(lpw);
	//	lpdit = (LPDLGITEMTEMPLATE)lpw; // original
	//	//lpdit = (LPDLGITEMTEMPLATE)GlobalLock(lpwAlign(lpw));    // test // Align DLGITEMTEMPLATE on DWORD boundary
	//	if (!lpdit)
	//		return -1;
	//	//*lpw++; // test
	//	//lpdit = (LPDLGITEMTEMPLATE)lpwAlign(lpw); // test

	//	lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;
	//	lpdit->dwExtendedStyle = 0;
	//	lpdit->x = 10; lpdit->y = 70;
	//	//lpdit->x = 15; lpdit->y = 70; // test
	//	lpdit->cx = 80; lpdit->cy = 20;
	//	lpdit->id = IDOK;       // OK button identifier
	//	//

	//	lpw = (LPWORD)(lpdit + 1);
	//	*lpw++ = 0xFFFF;
	//	*lpw++ = 0x0080;        // Button class

	//	//lpwsz = (LPWSTR)lpw;
	//	//nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
	//	//lpw += nchar;
	//	//*lpw++ = 0;             // No creation data

	//}
	
	////-----------------------
	//// Define a Help button.
	//https://learn.microsoft.com/en-us/windows/win32/api/Winuser/ns-winuser-dlgitemtemplate)
	//lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
	//lpdit = (LPDLGITEMTEMPLATE)lpw;
	//lpdit->x = 55; lpdit->y = 10;
	//lpdit->cx = 40; lpdit->cy = 20;
	//lpdit->id = ID_HELP;    // Help button identifier
	//lpdit->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

	//lpw = (LPWORD)(lpdit + 1);
	//*lpw++ = 0xFFFF;
	//*lpw++ = 0x0080;        // Button class atom

	//lpwsz = (LPWSTR)lpw;
	//nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "Help", -1, lpwsz, 50);
	//lpw += nchar;
	//*lpw++ = 0;             // No creation data

	////-----------------------
	//// Define a static text control.
	////-----------------------
	//lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
	//lpdit = (LPDLGITEMTEMPLATE)lpw;
	//lpdit->x = 10; lpdit->y = 10;
	//lpdit->cx = 40; lpdit->cy = 20;
	//lpdit->id = ID_TEXT;    // Text identifier
	//lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

	//{

	//	lpw = (LPWORD)(lpdit + 1);
	//	*lpw++ = 0xFFFF;
	//	*lpw++ = 0x0082;        // Static class
	//}

	for (lpwsz = (LPWSTR)lpw; *lpwsz++ = (WCHAR)*lpszMessage++;);
	lpw = (LPWORD)lpwsz;
	*lpw++ = 0;             // No creation data

	GlobalUnlock(hgbl);
	ret = DialogBoxIndirect(hinst,
		(LPDLGTEMPLATE)hgbl,
		hwndOwner,
		(DLGPROC)dialogWndProc);
	GlobalFree(hgbl);
	return ret;
}

```

