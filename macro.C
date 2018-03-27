void macro(int entries) {
	//gRoot->Reset();
	TFile *_file0 = TFile::Open("latino_WpWmJJ_EWK.root");
	if(entries < 0)
		latino->Process("mios.C");
	else
		latino->Process("mios.C", "", entries);		//eseguo il selettore solamente sui primi "entries" eventi
}
