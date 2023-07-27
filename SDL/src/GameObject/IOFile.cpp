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

	
	for (int i = 0; i < m_iMapTexture_index; i++)
	{
		if (fprintf(fp, "%d ", m_Highscore[i]) < 0)
		{
			return false;
		}
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

	for (int i = 0; i < m_iMapTexture_index; i++)
	{
		fscanf_s(fp, "%d ", &m_Highscore[i]);
	}
	
	fclose(fp);
}