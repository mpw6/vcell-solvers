/*
 * (C) Copyright University of Connecticut Health Center 2001.
 * All rights reserved.
 */
/////////////////////////////////////////////////////////////
// SimTool.h
///////////////////////////////////////////////////////////
#ifndef SIMTOOL_H
#define SIMTOOL_H

#include <VCELL/Simulation.h>
#include <VCELL/SimTypes.h>
#include <VCELL/Timer.h>

#ifndef DIRECTORY_SEPARATOR
#if ( defined(WIN32) || defined(WIN64) )
#define DIRECTORY_SEPARATOR '\\'
#else
#define DIRECTORY_SEPARATOR '/'
#endif
#endif

class VCellModel;
class Mesh;
class Simulation;

class SimTool {
public:	
	static SimTool* getInstance();
	static void create();
	~SimTool();

	virtual void start();
	virtual void loadFinal();

	void setModel(VCellModel* model);
	void setSimulation(Simulation* sim);
	void setTimeStep(double period);
	void setEndTimeSec(double timeSec) { simEndTime = timeSec; }
	void setKeepEvery(int ke) { keepEvery = ke; }
	void setBaseFilename(char *fname); 
	void setStoreEnable(bool enable) { 
		bStoreEnable = enable; 
	}
	void setFileCompress(bool compress) { 
		bSimFileCompress = compress; 
	}
	void requestNoZip();

	Simulation* getSimulation() { return simulation; }
	VCellModel* getModel() { return vcellModel; }
	bool checkStopRequested();
	TimerHandle getTimerHandle(string& timerName);
	void        startTimer(TimerHandle hnd);
	void        stopTimer(TimerHandle hnd);
	double      getElapsedTimeSec(TimerHandle hnd);
	virtual void showSummary(FILE *fp);

private:
	static SimTool* instance;

	bool bSimZip;
	VCellModel* vcellModel;
	Simulation  *simulation;
	Timer  *_timer;

	void updateLog(double progress,double time,int iteration);
	void clearLog();
	int	getZipCount(char* zipFileName);

	bool bSimFileCompress;
	double simEndTime;
	double simDeltaTime;
	int keepEvery;
	bool bStoreEnable;	
	char* baseFileName;
	int simFileCount;
	char* baseSimName;
	char* baseDirName;
	int zipFileCount;

	SimTool();
};

#endif
