void macro(int entries, TString option) {
	//gRoot->Reset();
	TFile *_file0 = TFile::Open("latino_WpWmJJ_EWK.root");

	if(entries < 0)
		latino->Process("myselector.C", option);				//eseguo il selettore su tutti gli eventi del TTree
	else
		latino->Process("myselector.C", option, entries);			//eseguo il selettore solamente sui primi "entries" eventi del TTree
}
