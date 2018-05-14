/*
Questa macro apre il file WpWmJJ/latino_WpWmJJ_EWK.root, salva il TTree "latino" contenuto nel file
e definisce le variabili associate ad ogni TBranch, che vengono attivate per essere salvate in un secondo TTree.
Il risultato è un nuovo file, "small.root", che contiene solamente il TTree "latinino" con le variabili necessarie all'MVA...
*/
void mvatree() {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile("WpWmJJ/latino_WpWmJJ_EWK.root");
   if(oldfile->IsOpen())	std::cout << "Apertura file riuscita." << std::endl;
   std::cout << "Lista dei contenuti del file WpWmJJ/latino_WpWmJJ_EWK.root:" << std::endl;
   oldfile->ls();		//List file contents
   TTree *oldtree = (TTree*)oldfile->Get("latino");			//"oldtree" sarà uguale al mio TTree "latino"

   //TObjArray *lista = oldtree->GetListOfBranches();		//Stampo la lista dei Branches
   //lista->Print();
   Float_t LHE_mlvlv_t;
   Float_t LHE_mllmet;
   Float_t LHE_mll;
   Float_t LHE_theta;
   Float_t LHE_dphill;
   Float_t LHE_dphilmet1;
   Float_t LHE_dphilmet2;
   TBranch *b_LHE_mlvlv_t;
   TBranch *b_LHE_mllmet;
   TBranch *b_LHE_mll;
   TBranch *b_LHE_theta;
   TBranch *b_LHE_dphill;
   TBranch *b_LHE_dphilmet1;
   TBranch *b_LHE_dphilmet2;
   oldtree->SetBranchAddress("LHE_mlvlv_t", &LHE_mlvlv_t, &b_LHE_mlvlv_t);
   oldtree->SetBranchAddress("LHE_mllmet", &LHE_mllmet, &b_LHE_mllmet);
   oldtree->SetBranchAddress("LHE_mll", &LHE_mll, &b_LHE_mll);
   oldtree->SetBranchAddress("LHE_theta", &LHE_theta, &b_LHE_theta);
   oldtree->SetBranchAddress("LHE_dphill", &LHE_dphill, &b_LHE_dphill);
   oldtree->SetBranchAddress("LHE_dphilmet1", &LHE_dphilmet1, &b_LHE_dphilmet1);
   oldtree->SetBranchAddress("LHE_dphilmet2", &LHE_dphilmet2, &b_LHE_dphilmet2);
   
   oldtree->SetBranchStatus("*", 0);
   oldtree->SetBranchStatus("std_vector_LHElepton_pt", 1);
   oldtree->SetBranchStatus("metLHEpt", 1);
   oldtree->SetBranchStatus("LHE_mlvlv_t", 1);
   oldtree->SetBranchStatus("LHE_mllmet", 1);
   oldtree->SetBranchStatus("LHE_mll", 1);
   oldtree->SetBranchStatus("LHE_theta", 1);
   oldtree->SetBranchStatus("LHE_dphill", 1);
   oldtree->SetBranchStatus("LHE_dphilmet1", 1);
   oldtree->SetBranchStatus("LHE_dphilmet2", 1);

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("small.root","recreate");
   TTree *newtree = oldtree->CloneTree();
   newtree->SetName("latino_reduced");

   std::cout << "Nuovo TTree salvato." << std::endl;
   newtree->Print();
   newfile->Write();
   std::cout << "Lista dei contenuti del file small.root:" << std::endl;
   newfile->ls();
   delete oldfile;
   delete newfile;
}
