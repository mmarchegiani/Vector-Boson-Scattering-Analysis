TString substr(TString name, int start) {
	const int size = (const int)name.Length();
	char stringa[size];
	int i = 0;
	for(i = 0; i < name.Length(); i++) {
		stringa[i] = name[i];
	}
	stringa[i] = '\0';
	std::cout << stringa << std::endl;

	char buffer[10];
	i = start;
	while(stringa[i] != '.') {
		buffer[i-start] = stringa[i];
		i++;
	}
	buffer[i-start] = '\0';
	
	//std::cout << buffer << std::endl;
	TString substr(buffer);
	//std::cout << substr << std::endl;

	return substr;
}
