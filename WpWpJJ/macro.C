void macro(int entries, char * option) {
	//gRoot->Reset();
	TFile *_file0 = TFile::Open("latino_WpWpJJ_EWK.root");

	if(option == "raw") {	//tutti gli eventi
		if(entries < 0)
			latino->Process("raw.C");				//eseguo il selettore su tutt gli eventi del TTree
		else
			latino->Process("raw.C", "", entries);			//eseguo il selettore solamente sui primi "entries" eventi del TTree
	}
	if(option == "") {	//eventi selezionati
		if(entries < 0)
			latino->Process("myselector.C");			//eseguo il selettore su tutt gli eventi del TTree
		else
			latino->Process("myselector.C", "", entries);		//eseguo il selettore solamente sui primi "entries" eventi del TTree
	}
}
