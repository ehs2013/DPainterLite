#include "winapi.h"

BOOL get_open_filename(char filename[], const char * filetype, char filetitle[]) {
	OPENFILENAMEA ofn; // �μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646839(v=vs.85).aspx
	char FileFilter[100] = "";
	sprintf_s(FileFilter, "ͼ���ļ� (*.%s)%c*.%s%c�����ļ� (*.*)%c*.*%c", filetype, '\0', filetype, '\0', '\0');
	ZeroMemory(&ofn, sizeof ofn);
	ofn.lStructSize = sizeof ofn;
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0'; 
	ofn.lpstrFileTitle = filetitle; 
	ofn.nMaxFileTitle = 50;
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = FileFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	BOOL ReturnValue = GetOpenFileNameA(&ofn); // �μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646927(v=vs.85).aspx
	return ReturnValue;
}


BOOL get_save_filename(char filename[], const char * filetype) {
	OPENFILENAMEA ofn; // �μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646839(v=vs.85).aspx
	char FileFilter[100] = "";
	sprintf_s(FileFilter, "ͼ���ļ� (*.%s)%c*.%s%c�����ļ� (*.*)%c*.*%c", filetype, '\0', filetype, '\0', '\0');
	ZeroMemory(&ofn, sizeof ofn);
	ofn.lStructSize = sizeof ofn;
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrDefExt = filetype;
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = FileFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = "ѡ���ļ�";
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
	BOOL ReturnValue = GetSaveFileNameA(&ofn); // �μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646928(v=vs.85).aspx
	return ReturnValue;
}


color_t get_color(void) {
	static COLORREF rgbCurrent;
	static COLORREF acrCustClr[16] = { 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0xffffff }; // Ϊ���ۣ��Զ�����ɫ��Ϊ��ɫ
	CHOOSECOLORA cc; //�μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646830(v=vs.85).aspx
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.hwndOwner = GetConsoleWindow();
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	ChooseColorA(&cc); //�μ� http://msdn.microsoft.com/en-us/library/windows/desktop/ms646912(v=vs.85).aspx 
	return EGERGB(GetRValue(cc.rgbResult), GetGValue(cc.rgbResult), GetBValue(cc.rgbResult)); // EGE �� Windows �洢��ɫ�ķ�ʽ�����෴������ǿ��ת��һ�¾ͺ�����
}