#include "IOFile.h"

IOFile::IOFile()
{
}

IOFile::IOFile(const char* _fileName)
{
	m_fileName = _fileName;
}

bool IOFile::WriteToFile(const char* _fileName)
{
	FILE* fp;
	fopen_s(&fp, _fileName, "w");
	if (fp == NULL)
	{
		printf("File does not exists \n");
		return false;
	}

	if (fprintf(fp, "%d %d %d", m_iHighest_process_level_1, m_iHighest_process_level_2, m_iHighest_process_level_3) < 0)
	{
		return false;
	}
	
	fclose(fp);
	return true;
}

void IOFile::ReadFromFile(const char* _fileName)
{
	FILE* fp;
	fopen_s(&fp, _fileName, "r");
	if (fp == NULL)
	{
		printf("File does not exists \n");
		return;
	}

	fscanf_s(fp, "%d %d %d", &m_iHighest_process_level_1, &m_iHighest_process_level_2, &m_iHighest_process_level_3);
	
	fclose(fp);
}