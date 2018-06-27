#include "TrainRegression_bdtg.cxx"
#include "ApplyRegression.cxx"
#include "PlotRegression.cxx"
//#include "substr.C"

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

//#include "TMVARegGui.C"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Config.h"
#include "TMVA/TMVAGui.h"

using namespace TMVA;

#include <vector>
#include "TStopwatch.h"
#include "TMVA/Reader.h"

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
#define devbins 50

void regression(TString Shrinkage) {
	TString subname;
	subname = TrainRegression_bdtg("800", Shrinkage, "0.6", "3", 1);
	ApplyRegression("BDTG", subname, 1);
	PlotRegression("SK", subname);
}