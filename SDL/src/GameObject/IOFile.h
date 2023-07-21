#pragma once
#include "Define.h"

class IOFile
{
public:
	IOFile();
	IOFile(const char* _fileName);
	~IOFile();
	bool WriteToFile(const char* _fileName);
	void ReadFromFile(const char* _fileName);
protected:
	const char* m_fileName;
};