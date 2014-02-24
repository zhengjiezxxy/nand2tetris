#include "./include/include.h"
#include "codewriter.h"
#ifndef PARSER_H
#include "parser.h"
#endif
int main(int argc, char* argv[])
{
	string sourcefile,outfile;
  struct stat  stBuf;
  struct dirent * p_dir;
  DIR* dp;

	if(argc < 2)
	{
		cout << "Usage tm sourcefile/or dirctory if source files are more than one" << endl;
	}
	else
	{
		string t1(argv[1]);
		sourcefile = t1;
	}

	Parser parser; //ifstream has move constructor since c++11, I have
                 // g++ 4.6 only!
	CodeWriter writer;
   
  //determine whether argv[1] is a regular file or directory
  if(stat(argv[1],&stBuf))
  {
      perror("cannot stat input file");
  }
  else
  {
      if(sourcefile.find(".") != std::string::npos)
    {
      if(S_ISREG(stBuf.st_mode) && (sourcefile.substr(sourcefile.find_last_of(".")+1)== "vm"))
      {
        string baseName = sourcefile.substr(0,sourcefile.find_last_of("."));
        outfile = baseName + ".asm";
        parser.m_ifs.open(sourcefile.c_str(),std::ios_base::in);
        writer.m_ofs.open(outfile.c_str(),std::ios_base::out);
        writer.Init();
        while(parser.HasNext())
        {
          trivec tvec = parser.Advance();
          writer.WriteCom(tvec);
        }
      }
    }

    if(S_ISDIR(stBuf.st_mode))
    {
      if((dp =opendir(sourcefile.c_str())) == NULL)
        perror("cannot open directory");
      //
      //assume there is only one level of dirctory,so needn't cd to next dirctory
      string tmpfile = sourcefile + "/tmp";
      std::ofstream ofs(tmpfile,std::ios_base::binary);

        while((p_dir=readdir(dp))!=NULL)
        {
          string filename =sourcefile + "/" + p_dir->d_name;
          if(stat(filename.c_str(),&stBuf))
          {
            perror("cannot stat file");
          }
          else
          {
            if(filename.find(".") != std::string::npos)
           {
              if(S_ISREG(stBuf.st_mode) && (filename.substr(filename.find_last_of(".")+1)  == "vm"))
              {//concate files
                std::ifstream ifs(filename.c_str(),std::ios_base::binary);
                ofs  << ifs.rdbuf();
              }
            }
          }
         }
           outfile = sourcefile    +".asm";
            parser.m_ifs.open(tmpfile.c_str(),std::ios_base::in);
            writer.m_ofs.open(outfile.c_str(),std::ios_base::out);
            writer.Init();
            while(parser.HasNext())
            {
              trivec tvec = parser.Advance();
              writer.WriteCom(tvec);
            }
    }
  }

    return 0;
  }
      

    

    
