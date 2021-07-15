#pragma once

class SdProp
{
public:
	CString  m_Name;
	double   m_stas, m_stae;

public:
	SdProp();
	~SdProp();

public:
	virtual BOOL Read(CFile* pFile);
	virtual BOOL Write(CFile* pFile);
	virtual BOOL Modify();
};


class SdNeiKuo
{
public:
	double R1 = 0.0;
	double R2 = 0.0;
	double R3 = 0.0;
	double R4 = 0.0;
	double R5 = 0.0;
	double H1 = 0.0;
	double H2 = 0.0;
	double H_2 = 0.0;
	double RADIUS1 = 0.0;
	double RADIUS_1 = 0.0;
	double RADIUS2 = 0.0;
	double RADIUS3 = 0.0;
	double RADIUS4 = 0.0;
	double RADIUS5 = 0.0;

public:
	SdNeiKuo();
	~SdNeiKuo();

public:
	SdNeiKuo& operator=(const SdNeiKuo& data);
	virtual BOOL  Read(CFile* pFile);
	virtual void  Write(CFile* pFile);
	virtual BOOL  Modify();
};


class Tunnel
{
public:
	static Tunnel  m_Sd;

public:
	SdNeiKuo  m_nk;

public:
	Tunnel();
	~Tunnel();

public:
	virtual BOOL  Read(CFile* pFile);
	virtual void  Write(CFile* pFile);
};

class Draw_Tunnel
{
public:
	Tunnel  m_data;

	BOOL  Draw();

};


class Draw_SdNeiKuo
{
public:
	SdNeiKuo  m_data;
	BOOL  Draw();

};

