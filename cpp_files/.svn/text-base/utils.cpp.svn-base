#include "utils.h"

int flagverbose = 1; // flag to activate verbose messages





/* --------------------------------------------------------------------------------

Report: prints on screen and log file (dev_oss filename device)

-------------------------------------------------------------------------------- */

FILE *devlog = NULL;


void report(char *fmt,...)

{
	static int initflag=1;
	va_list ap;
	char *s,fmtemp[20];
	int ival,fmtemp_i;
	float fval;
	char *cval;

	if(initflag) {
		devlog=fopen("simu.log","w");
		if(devlog==NULL) return;
		initflag=0;
	}
	va_start(ap,fmt);

	for(s=fmt; *s; s++) {
		if(*s!='%') { if(flagverbose) printf("%c",*s); fprintf(devlog,"%c",*s); continue; }

		fmtemp_i=0; while (*s && !(*s=='s' || *s=='d' || *s=='f')) { fmtemp[fmtemp_i]=*s; s++; fmtemp_i++; }
		if(*s=='d') {  ival=va_arg(ap,int); fmtemp[fmtemp_i]='d'; fmtemp[fmtemp_i+1]=0;
		if(flagverbose) printf(fmtemp,ival); fprintf(devlog,fmtemp,ival);  }
		if(*s=='f') {  fval=va_arg(ap,double); fmtemp[fmtemp_i]='f'; fmtemp[fmtemp_i+1]=0;
		if(flagverbose) printf(fmtemp,fval); fprintf(devlog,fmtemp,fval);  }
		if(*s=='s') {  cval=va_arg(ap,char *); fmtemp[fmtemp_i]='s'; fmtemp[fmtemp_i+1]=0;
		if(flagverbose) printf(fmtemp,cval); fprintf(devlog,fmtemp,cval);  }
	} /* end for */

	va_end(ap);
}

void closeReport(){
	if (devlog!=NULL) fclose(devlog);
}

string& trim(string &str){
	string::size_type pos = str.find_last_not_of(' ');
	if(pos != string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if(pos != string::npos) str.erase(0, pos);
	}
	else str.erase(str.begin(), str.end());
	return str;
}

string& removeComments(string &str){
	// Find the first character position after excluding leading blank spaces
	size_t pos = str.find_first_of("#%"); 

    // if all spaces or empty return an empty string
	if(string::npos != pos) str.erase(pos,string::npos);
	return str;
}

