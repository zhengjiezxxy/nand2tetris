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
	if(S_ISREG(statbuf.st_mode) != 0 && (filename.substr(filename.find_last_of
	(".")+1)) == "jack"  ) // regular file
	{
		CompilationEng comEng;
		comEng.m_sifs = argv[1];
		comEng.init();
		comEng.m_ofs.open(argv[2],ios_base::out);
		comEng.compileClass();
	}
	else if(S_ISDIR(statbuf.st_mode) != 0) //directory
	{
		if((dp=opendir(argv[1])) == NULL)
			perror("cannot open directory");
		while((dirp=readdir(dp)) != NULL)  //Suppose there is no one level dirctory
		{
			filename += filename +"/" + dirp->d_name;
			if(stat(filename.c_str(),&statbuf)<0)
				perror("cannot stat file");
			if(S_ISREG(statbuf.st_mode) && (filename.substr(filename.
					find_last_of(".")+1) == "jack"))
			{
				CompilationEng comEng;
				comEng.m_sifs = filename.c_str();
				comEng.init();
				string newFile;
				newFile = filename.substr(0,filename.find_last_of("."));
				newFile += "vm";
				comEng.m_ofs.open(newFile.c_str(),ios_base::out);
				comEng.compileClass();
			}
		}
	}
}
