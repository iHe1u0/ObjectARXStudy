#pragma once

class SdProp {
    public:
	CString m_Name;
	double m_stas, m_stae;

    public:
	SdProp();
	~SdProp();

    public:
	virtual BOOL Read(CStdioFile *pFile);
	virtual BOOL Write(CStdioFile *pFile);
	virtual BOOL Modify();
};

class SdNeiKuo {
    public:
	double Version = 0.0;
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
	SdNeiKuo &operator=(const SdNeiKuo &data);

	virtual BOOL Read(CString filePath,SdNeiKuo *data); //传入路径读取文件内容
	virtual BOOL Modify(CString filePath); //修改
	virtual BOOL Write(CStdioFile *pFile); //新建/写入一个文件
};

class Tunnel {
    public:
	static Tunnel m_Sd;

    public:
	SdNeiKuo m_nk;

    public:
	Tunnel();
	~Tunnel();

    public:
	virtual BOOL Read(CStdioFile *pFile);
	virtual BOOL Write(CStdioFile *pFile);
};

class Draw_Tunnel {
    public:
	Tunnel m_data;

	BOOL Draw();
};

class Draw_SdNeiKuo {
    public:
	SdNeiKuo m_data;
	BOOL Draw();
};
