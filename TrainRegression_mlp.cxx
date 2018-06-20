// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TMVA Regression for Energy scale estimation
//
// To launch:  r00t TrainRegression_mlp.cxx
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

#include "TMVARegGui.C"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/Config.h"
#include "TMVA/TMVAGui.h"

using namespace TMVA;
   
void TrainRegression_mlp( TString myMethodList = "", TString outfileName = "TMVAReg.root" ) 
{
   TMVA::Tools::Instance();   
   
   std::cout << "\n==> Start TMVARegression" << std::endl;

   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile, 
                                               "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

   TMVA::Config::Instance();
   (TMVA::gConfig().GetIONames()).fWeightFileDir = "weightsMassVariable0Jet";

   dataloader->AddVariable( "metLHEpt" , 'F');

   dataloader->AddVariable( "std_vector_LHElepton_pt[0]" , 'F');
   dataloader->AddVariable( "std_vector_LHElepton_pt[1]" , 'F');
   dataloader->AddVariable( "LHE_mlvlv_t" , 'F');
   dataloader->AddVariable( "LHE_mllmet" , 'F');
   dataloader->AddVariable( "LHE_mll" , 'F');
   dataloader->AddVariable( "LHE_theta" , 'F');
   dataloader->AddVariable( "LHE_dphill" , 'F');
   dataloader->AddVariable( "LHE_dphill*LHE_mll" , 'F');
//    dataloader->AddVariable( "dphillmet" , 'F'); 
   dataloader->AddVariable( "LHE_dphilmet1" , 'F');
   dataloader->AddVariable( "LHE_dphilmet2" , 'F');
   dataloader->AddVariable( "LHE_dphilmet1*LHE_mll" , 'F');
   dataloader->AddVariable( "LHE_dphilmet2*LHE_mll" , 'F');  

   // Add the variable carrying the regression target
   dataloader->AddTarget( "LHE_mlvlv" ); 

  
   // Read training and test data (see TMVAClassification for reading ASCII files)
   // load the signal and background event samples from ROOT trees
   TFile *input(0);
   //TString fname = "./WpWmJJ/WpWmJJ_reduced.root";
   TString fname = "./WpWpJJ/WpWpJJ_reduced.root";
   
   if (!gSystem->AccessPathName( fname )) 
      input = TFile::Open( fname ); // check if file in local directory exists

   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegression           : Using input file: " << input->GetName() << std::endl;

   TTree *regTree = (TTree*)input->Get("latino_reduced");
   std::cout << regTree->GetEntries() << std::endl;
   // global event weights per tree (see below for setting event-wise weights)
   Double_t regWeight  = 1.0;   

   // You can add an arbitrary number of regression trees
   dataloader->AddRegressionTree( regTree, regWeight );
   std::cout << "==> Aggiunto Tree alla regressione" << std::endl;
   // This would set individual event weights (the variables defined in the 
   // expression need to exist in the original TTree)
   dataloader->SetWeightExpression( "1", "Regression" );
   
   // Neural network (MLP)

//       factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=20000:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator" );
//         factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=200:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=400:HiddenLayers=N+10:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=N:NeuronType=tanh:NCycles=200:HiddenLayers=N+10:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=200:HiddenLayers=N+5:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
// 	factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=100:HiddenLayers=N+5:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
//      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=G,N:NeuronType=tanh:NCycles=200:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
//      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "!H:!V:NeuronType=tanh:NCycles=400:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" );
   factory->BookMethod
     (
       dataloader, 
       TMVA::Types::kMLP, 
       "MLP", 
       "!H:!V:NeuronType=tanh:NCycles=100:HiddenLayers=N+7:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15" 
     );

   factory->BookMethod
      (
      dataloader,
      TMVA::Types::kBDT,
      "BDT",
      "!H:!V:NTrees=100:MinNodeSize=1.0%:BoostType=AdaBoostR2:SeparationType=RegressionVariance:nCuts=20:PruneMethod=CostComplexity:PruneStrength=30"
      );
        

   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   std::cout << "TrainAllMethods eseguito." << std::endl;


   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   std::cout << "TestAllMethods eseguito." << std::endl;


   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   std::cout << "EvaluateAllMethods eseguito." << std::endl;


   // --------------------------------------------------------------
   
   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      

   delete factory;
   delete dataloader;

   // Launch the GUI for the root macros
    if (!gROOT->IsBatch()) TMVARegGui( outfileName );
}