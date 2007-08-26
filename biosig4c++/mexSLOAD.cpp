/*

    $Id: mexSLOAD.cpp,v 1.3 2007-08-26 20:39:16 schloegl Exp $
    Copyright (C) 2007 Alois Schloegl <a.schloegl@ieee.org>
    This file is part of the "BioSig for C/C++" repository 
    (biosig4c++) at http://biosig.sf.net/ 


    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 */

#include "biosig.h"
#include "mex.h"
#include <stdlib.h>
#include <string.h>


void mexFunction(
    int           nlhs,           /* number of expected outputs */
    mxArray       *plhs[],        /* array of pointers to output arguments */
    int           nrhs,           /* number of inputs */
    const mxArray *prhs[]         /* array of pointers to input arguments */
)
{
	int k;
	const mxArray	*arg;
	HDRTYPE		*hdr;
	CHANNEL_TYPE*	cp; 
	size_t 		count;
	time_t 		T0;
	char 		FileName[1024];  
	int 		status, VERBOSE_LEVEL = 9; 
	
	mexPrintf("\nHello world! [nlhs=%i nrhs=%i]\n",nlhs,nrhs);
	mexPrintf("This is mexSLOAD, it is currently in an experimental state!\n");
	for (k=0; k<nrhs; k++)
	{	
		arg = prhs[k];
		if (mxIsEmpty(arg))
			mexPrintf("Empty\n");
		else if (mxIsCell(arg))
			mexPrintf("IsCell\n");
		else if (mxIsStruct(arg))
			mexPrintf("IsStruct\n");
		else if (mxIsNumeric(arg))
			mexPrintf("IsNumeric\n");
		else if (mxIsSingle(arg))
			mexPrintf("IsSingle\n");
		else if (mxIsChar(arg))
		{
			mxGetString(prhs[k], FileName, max(1022,mxGetN(prhs[k])));
			mexPrintf("IsChar[%i,%i]\n\t%s\n",mxGetM(prhs[k]),mxGetN(prhs[k]),FileName);

			hdr = sopen(FileName, "r", NULL);
			if ((status=serror())) exit(status); 
	
			if (hdr==NULL) exit(-1);
			if (VERBOSE_LEVEL>8) fprintf(stdout,"[112] SOPEN-R finished\n");

			hdr2ascii(hdr,stdout,1);	


			if (nlhs>1) {
if (VERBOSE_LEVEL>8) mexPrintf("[200]\n");
				uint16_t numfields;
				mxArray *HDR, *tmp;
				void* ptr;
				const char *fnames[] = {"TYPE","NS","SPR","NRec","SampleRate","FileName","FILE","Patient",NULL};
				for (numfields=0; fnames[numfields++] != 0; );
				plhs[1] = mxCreateStructMatrix(1, 1, --numfields, fnames);
				HDR = plhs[1];
				tmp = mxCreateNumericMatrix(1,1,mxUINT16_CLASS,mxREAL);
				memcpy(mxGetData(tmp),&(hdr->NS),sizeof(hdr->NS));
				mxSetField(HDR,1,"NS",tmp);

				tmp = mxCreateNumericMatrix(1,1,mxUINT32_CLASS,mxREAL);
				memcpy(mxGetData(tmp),&(hdr->SPR),sizeof(hdr->SPR));
				mxSetField(HDR,1,"SPR",tmp);

				tmp = mxCreateNumericMatrix(1,1,mxUINT64_CLASS,mxREAL);
				memcpy(mxGetData(tmp),&(hdr->NRec),sizeof(hdr->NRec));
				mxSetField(HDR,1,"NRec",tmp);

if (VERBOSE_LEVEL>8) mexPrintf("[205]\n");
/*
				tmp = mxCreateNumericMatrix(1,1,mxUINT32_CLASS,mxREAL);
				memcpy(mxGetData(tmp),hdr->SPR);
				mxSetField(HDR,1,"SPR",tmp);
				tmp = mxCreateNumericMatrix(1,1,mxUINT64_CLASS,mxREAL);
				*(uint64_t*)mxGetData(tmp) = hdr->NRec;
				mxSetField(HDR,1,"NRec",tmp);
*/
			}	

			plhs[0] = mxCreateDoubleMatrix(hdr->SPR * hdr->NRec, hdr->NS, mxREAL);
//			hdr->data.block = mxGetPr(plhs[0]);

			if (VERBOSE_LEVEL>8) fprintf(stdout,"[112] SOPEN-R finished\n");

			hdr->FLAG.OVERFLOWDETECTION = 0;
			hdr->FLAG.UCAL = 1;
	
			if (VERBOSE_LEVEL>8) fprintf(stdout,"[121]\n");

			count = sread(mxGetPr(plhs[0]), 0, hdr->NRec, hdr);
			if ((status=serror())) exit(status); 

			if (VERBOSE_LEVEL>8) 
				fprintf(stdout,"\n[129] SREAD on %s successful [%i,%i].\n",hdr->FileName,hdr->data.size[0],hdr->data.size[1]);

			if (VERBOSE_LEVEL>8) fprintf(stdout,"[131] going for SCLOSE\n");
			sclose(hdr);
			hdr = NULL; 
			if (VERBOSE_LEVEL>8) fprintf(stdout,"[137] SCLOSE finished\n");
		}
	}
/*		
	nlhs = 1; 	
	plhs = (mxArray*)mxCalloc(sizeof(mxArray*), nlhs);
	for (k=0; k<nrhs; k++)
	{
		plhs[k] = mxCreateNumericMatrix(k+1, k+2, mxDOUBLE_CLASS, mxREAL);
	}	
	
	mxAddField(pm, fieldname)
	mxRemoveField, 
	mxSetFieldByNumber
	mxSetPr(plhs[0], hdr->data.block);
*/
};

