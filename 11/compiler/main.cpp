#include "include/include.h"
#include "CompilationEngine.h"

int main(int argc, char** argv)
{
	DIR * dp; //pointer to dirctory stream
	struct dirent* dirp;
	struct stat statbuf;
	
	if(stat(argv[1],&statbuf)<0)
		perror("cannot stat directory");
	
	string filename(argv[1]);
	if(S_ISREG(statbuf.st_mode) != 0 && (filename.substr(filename.find_last_of (".")+1)) == "jack"  ) // regular file
	{

		Tokenizer tokenizer;
		CompilationEng comEng;
		comEng.m_sifs = argv[1];
		comEng.init();
		string baseName = filename.substr(0,filename.find_last_of("."));
		string newFile = baseName + ".xml";
		comEng.m_ofs.open(newFile.c_str(),ios_base::out);
		//vm output
		string outputVM = baseName + ".vm";
		comEng.writer.m_ofs.open(outputVM.c_str(),ios_base::out);
		comEng.compileClass();

		//tokens output
		string outputT = baseName + "T.xml";
		tokenizer.m_ofs.open(outputT.c_str(),std::ios_base::out);
		tokenizer.m_ifs.open(argv[1],std::ios_base::in);
		tokenizer.printToken();

	}
	else if(S_ISDIR(statbuf.st_mode) != 0) //directory
	{
		if((dp=opendir(argv[1])) == NULL)
			perror("cannot open directory");
			string baseName = filename;
		while((dirp=readdir(dp)) != NULL)  //Suppose there is no one level dirctory
		{
			filename = baseName +"/" + dirp->d_name;
			if(stat(filename.c_str(),&statbuf)<0)
				perror("cannot stat file");
			if(S_ISREG(statbuf.st_mode) && (filename.substr(filename.  find_last_of(".")+1) == "jack"))
			{
				Tokenizer tokenizer;
				CompilationEng comEng;
				comEng.m_sifs = filename.c_str();
				comEng.init();
				string baseName;
				baseName = filename.substr(0,filename.find_last_of("."));
				string newFile = baseName + ".xml";
				comEng.m_ofs.open(newFile.c_str(),ios_base::out);
				//vm output
				string outputVM = baseName + ".vm";
				comEng.writer.m_ofs.open(outputVM.c_str(),ios_base::out);
				comEng.compileClass();

				//tokens output
				string outputT = baseName + "T.xml";
				tokenizer.m_ofs.open(outputT.c_str(),std::ios_base::out);
				tokenizer.m_ifs.open(argv[1],std::ios_base::in);
				tokenizer.printToken();
			}
		}
	}
}
