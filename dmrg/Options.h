#pragma once
class Options
{
public:
	Options();
	~Options();


	int model;
	int sites;
	int states;
	int sweeps;

	int bigTicksX;
	int bigTicksY;
	int smallTicksX;
	int smallTicksY;

	double minEnergy;
	double maxEnergy;

	void Load();
	void Save();
protected:
	static double GetDouble(LPCTSTR param, double defval);
};

