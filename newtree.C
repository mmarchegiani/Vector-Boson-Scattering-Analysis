void newtree() {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile("WpWmJJ/latino_WpWmJJ_EWK.root");
   TTree *oldtree = (TTree*)oldfile->Get("T");

   oldtree->SetBranchAddress("metLHEeta", &metLHEeta);		//non so che indirizzo passare
   oldtree->SetBranchStatus("*",0);
   oldtree->SetBranchStatus("event",1);
   oldtree->SetBranchStatus("metLHEeta",1);

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile("small.root","recreate");
   TTree *newtree = oldtree->CloneTree();

   newtree->Print();
   newfile->Write();
   delete oldfile;
   delete newfile;
}
