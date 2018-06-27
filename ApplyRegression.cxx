// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t ApplyRegression.cxx\(\"BDT\"\,\"100\"\)
// To launch:  r00t ApplyRegression.cxx\(\"BDT,MLP\"\)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "substr.C"
using namespace TMVA;

#define ptbins 200
#define etabins 100
#define phibins 100
#define mbins 200
#define devbins 50

void ApplyRegression( TString myMethodList = "BDT", TString SubName = "", int Opt = -1) 
{
   // This loads the library
   TMVA::Tools::Instance();
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 1; 
   Use["KNN"]             = 1;
   // 
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1;
   // 
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 1;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   // 
   // --- Neural Network
   Use["MLP"]             = 1; 
   // 
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 1;
   //
   // --- Configuration of parameters

   // ---------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);
         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --- Create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t 	metLHEpt, std_vector_LHElepton_pt[2], LHE_mlvlv_t, LHE_mllmet, LHE_mll,
   			LHE_theta, LHE_dphill, LHE_dphilmet1, LHE_dphilmet2, LHE_dphillxLHE_mll, LHE_dphilmet1xLHE_mll, LHE_dphilmet2xLHE_mll;

   // Target
   Float_t LHE_mlvlv;

   
   reader->AddVariable( "LHE_mlvlv_t" , &LHE_mlvlv_t);
   reader->AddVariable( "LHE_mllmet" , &LHE_mllmet);
   reader->AddVariable( "LHE_mll" , &LHE_mll);
   //reader->AddVariable( "metLHEpt" , &metLHEpt);
   //reader->AddVariable( "std_vector_LHElepton_pt[0]" , &std_vector_LHElepton_pt[0]);
   //reader->AddVariable( "std_vector_LHElepton_pt[1]" , &std_vector_LHElepton_pt[1]);
   //reader->AddVariable( "LHE_theta" , &LHE_theta);
   //reader->AddVariable( "LHE_dphill" , &LHE_dphill);
   //reader->AddVariable( "LHE_dphill*LHE_mll" , &LHE_dphillxLHE_mll);
	//reader->AddVariable( "dphillmet" , 'F'); 
   //reader->AddVariable( "LHE_dphilmet1" , &LHE_dphilmet1);
   //reader->AddVariable( "LHE_dphilmet2" , &LHE_dphilmet2);
   //reader->AddVariable( "LHE_dphilmet1*LHE_mll" , &LHE_dphilmet1xLHE_mll);
   //reader->AddVariable( "LHE_dphilmet2*LHE_mll" , &LHE_dphilmet2xLHE_mll);

   //Dichiaro i nomi delle variabili così come verranno passati nei plot
   //La seguente riga è HARDCODED!

   TString variable_name[20] = {"M^{T}_{l#nul#nu}", "M_{ll, MET}", "M_{ll}"};
   TString target_name = "M_{l#nul#nu}";
   Int_t nvariables = 0;
   for(int i = 0; i < 14; i++) {
   		if(variable_name[i] == "") {
   			nvariables = i;
   			break;
   		}
   		else
   			std::cout << "variable_name[" << i << "] = " << variable_name[i] << std::endl;

   }

   // --- Book the MVA methods
   TString path, dir;
   //if(Use["BDT"] && Opt == -1)	path = "Test_Methods/BDT_AdaBoost/";
   //if(Use["BDTG"] && Opt == -1)	path = "Test_Methods/BDT_Grad/";
   if(Use["BDTG"] && Opt < 0)	path = "";
   if(Use["BDTG"] && Opt == 0)	path = "NTrees/";
   if(Use["BDTG"] && Opt == 1)	path = "Shrinkage/";
   if(Use["BDTG"] && Opt == 2)	path = "Fraction/";
   if(Use["BDTG"] && Opt == 3)	path = "MaxDepth/";
   dir = path + "dataset_" + SubName + "/weightsMassVariable0Jet_" + SubName + "/";
   TString prefix = "TMVARegression";
   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         reader->BookMVA( methodName, weightfile ); 
      }
   }
   
   // Book output histograms
   TH1* hists[10];
   TH2* plots[20];
   Int_t nhists = -1;
   Int_t nplots = 0;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 200, 0., 1000.);
      if (it->second) hists[++nhists] = h;

      
   }
   nhists++;

   std::cout << "nvariables = " << nvariables << std::endl;
   std::cout << "nhists = " << nhists << std::endl;
   std::cout << "nplots = " << nplots << std::endl;
   
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
   TString fname = "./WpWmJJ/WpWmJJ_reduced.root";
   //TString fname = "./WpWpJJ/WpWpJJ_reduced.root";

   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   } 
   else { 
      input = TFile::Open( "http://root.cern.ch/files/tmva_reg_example.root" ); // if not: download from ROOT server
   }
   
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;
   // --- Event loop
   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   TTree* theTree = (TTree*)input->Get("latino_reduced");
   //input->Close();
   TFile *target  = new TFile( path + "TMVARegApp" + SubName + ".root","RECREATE" );
   TTree *newtree = theTree->CloneTree();
   newtree->SetName("latino_reg");

   std::cout << "--- Select signal sample" << std::endl;

   newtree->SetBranchAddress("LHE_mlvlv", &LHE_mlvlv);
   newtree->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t);
   newtree->SetBranchAddress("LHE_mllmet", &LHE_mllmet);
   newtree->SetBranchAddress("LHE_mll", &LHE_mll);
   //newtree->SetBranchAddress("LHE_theta", &LHE_theta);
   //newtree->SetBranchAddress("LHE_dphill", &LHE_dphill);
   //newtree->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1);
   //newtree->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2);

   Float_t REG_mlvlv;
   TBranch *b_REG_mlvlv = newtree->Branch("REG_mlvlv", &REG_mlvlv, "REG_mlvlv/F");
   newtree->SetBranchAddress("REG_mlvlv", &REG_mlvlv);
   std::cout << "--- Processing: " << newtree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<newtree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      newtree->GetEntry(ievt);
      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression
      for (Int_t ih=0; ih<nhists; ih++) {
         TString title = hists[ih]->GetTitle();
         Float_t val = (reader->EvaluateRegression( title ))[0];
         REG_mlvlv = val;
         b_REG_mlvlv->Fill(); 
         hists[ih]->Fill( val );
      }
      //std::cout << "fill istogrammi 1D eseguito" << std::endl;
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
   // --- Write histograms
   //TFile *target  = new TFile( "TMVARegApp" + SubName + ".root","RECREATE" );
   for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
   for (Int_t ih=0; ih<nplots; ih++) plots[ih]->Write();
   
   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   target->Write();
   //newtree->Delete("latino;1");
   std::cout << "Lista dei contenuti del file " << target->GetName() << ":" << std::endl;
   target->ls();

   target->Close();
   std::cout << "--- Created root file: \"" << target->GetName() 
             << "\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}
int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList; 
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(","); 
      methodList += regMethod;
   }
   ApplyRegression(methodList);
   return 0;
}