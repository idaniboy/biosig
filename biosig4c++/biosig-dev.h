/*
%
% $Id: biosig-dev.h,v 1.1 2008-03-14 08:32:04 schloegl Exp $
% Copyright (C) 2005,2006,2007 Alois Schloegl <a.schloegl@ieee.org>
% This file is part of the "BioSig for C/C++" repository 
% (biosig4c++) at http://biosig.sf.net/ 


    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.


 */

/* 

/* 
	Internal definitions (external API is defined in biosig.h) 
*/

/****************************************************************************/
/**                                                                        **/
/**                CONSTANTS and Global variables                          **/
/**                                                                        **/
/****************************************************************************/



/****************************************************************************/
/**                                                                        **/
/**                 DEFINITIONS, TYPEDEFS AND MACROS                       **/
/**                                                                        **/
/****************************************************************************/
#ifndef __BIOSIG_INTERNAL_H__
#define __BIOSIG_INTERNAL_H__

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "biosig.h"


#if  	__APPLE__
#define __BIG_ENDIAN  	 4321
#define __LITTLE_ENDIAN  1234
#if	__LITTLE_ENDIAN__
#define __BYTE_ORDER 	__LITTLE_ENDIAN
#else
#define __BYTE_ORDER 	__BIG_ENDIAN
#endif
#endif

#if	__sparc__
#define __BIG_ENDIAN  	 4321
#define __LITTLE_ENDIAN  1234
#define __BYTE_ORDER 	__BIG_ENDIAN
#endif 

#ifdef __linux__
/* use byteswap macros from the host system, hopefully optimized ones ;-) */
#include <byteswap.h>
#endif 


#ifndef _BYTESWAP_H
/* define our own version - needed for Max OS X*/
#define bswap_16(x)   \
	((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))

#define bswap_32(x)   \
	 ((((x) & 0xff000000) >> 24) \
        | (((x) & 0x00ff0000) >> 8)  \
	| (((x) & 0x0000ff00) << 8)  \
	| (((x) & 0x000000ff) << 24))

#define bswap_64(x) \
      	 ((((x) & 0xff00000000000000ull) >> 56)	\
      	| (((x) & 0x00ff000000000000ull) >> 40)	\
      	| (((x) & 0x0000ff0000000000ull) >> 24)	\
      	| (((x) & 0x000000ff00000000ull) >> 8)	\
      	| (((x) & 0x00000000ff000000ull) << 8)	\
      	| (((x) & 0x0000000000ff0000ull) << 24)	\
      	| (((x) & 0x000000000000ff00ull) << 40)	\
      	| (((x) & 0x00000000000000ffull) << 56))
#endif  /* _BYTESWAP_H */


#if __BYTE_ORDER == __BIG_ENDIAN
#define l_endian_u16(x) ((uint16_t)bswap_16((uint16_t)(x)))
#define l_endian_u32(x) ((uint32_t)bswap_32((uint32_t)(x)))
#define l_endian_u64(x) ((uint64_t)bswap_64((uint64_t)(x)))
#define l_endian_i16(x) ((int16_t)bswap_16((int16_t)(x)))
#define l_endian_i32(x) ((int32_t)bswap_32((int32_t)(x)))
#define l_endian_i64(x) ((int64_t)bswap_64((int64_t)(x)))
float   l_endian_f32(float x); 
double  l_endian_f64(double x); 

#define b_endian_u16(x) ((uint16_t)(x))
#define b_endian_u32(x) ((uint32_t)(x))
#define b_endian_u64(x) ((uint64_t)(x))
#define b_endian_i16(x) ((int16_t)(x))
#define b_endian_i32(x) ((int32_t)(x))
#define b_endian_i64(x) ((int64_t)(x))
#define b_endian_f32(x) ((float)(x))
#define b_endian_f64(x) ((double)(x))

#elif __BYTE_ORDER==__LITTLE_ENDIAN
#define l_endian_u16(x) ((uint16_t)(x))
#define l_endian_u32(x) ((uint32_t)(x))
#define l_endian_u64(x) ((uint64_t)(x))
#define l_endian_i16(x) ((int16_t)(x))
#define l_endian_i32(x) ((int32_t)(x))
#define l_endian_i64(x) ((int64_t)(x))
#define l_endian_f32(x) ((float)(x))
#define l_endian_f64(x) ((double)(x))

#define b_endian_u16(x) ((uint16_t)bswap_16((uint16_t)(x)))
#define b_endian_u32(x) ((uint32_t)bswap_32((uint32_t)(x)))
#define b_endian_u64(x) ((uint64_t)bswap_64((uint64_t)(x)))
#define b_endian_i16(x) ((int16_t)bswap_16((int16_t)(x)))
#define b_endian_i32(x) ((int32_t)bswap_32((int32_t)(x)))
#define b_endian_i64(x) ((int64_t)bswap_64((int64_t)(x)))
float   b_endian_f32(float x); 
double  b_endian_f64(double x); 

#endif /* __BYTE_ORDER */


#ifndef __sparc__
// if misaligned data words can be handled 
#define leu16p(i) l_endian_u16(*(uint16_t*)(i))
#define lei16p(i) l_endian_i16(*( int16_t*)(i))
#define leu32p(i) l_endian_u32(*(uint32_t*)(i))
#define lei32p(i) l_endian_i32(*( int32_t*)(i))
#define leu64p(i) l_endian_u64(*(uint64_t*)(i))
#define lei64p(i) l_endian_i64(*( int64_t*)(i))
#define lef32p(i) l_endian_f32(*(float*)(i))
#define lef64p(i) l_endian_f64(*(double*)(i))

#define beu16p(i) b_endian_u16(*(uint16_t*)(i))
#define bei16p(i) b_endian_i16(*( int16_t*)(i))
#define beu32p(i) b_endian_u32(*(uint32_t*)(i))
#define bei32p(i) b_endian_i32(*( int32_t*)(i))
#define beu64p(i) b_endian_u64(*(uint64_t*)(i))
#define bei64p(i) b_endian_i64(*( int64_t*)(i))
#define bef32p(i) b_endian_f32(*(float*)(i))
#define bef64p(i) b_endian_f64(*(double*)(i))

#define leu16a(i,r) (*(uint16_t*)r = l_endian_u16(i))
#define lei16a(i,r) (*( int16_t*)r = l_endian_i16(i))
#define leu32a(i,r) (*(uint32_t*)r = l_endian_u32(i))
#define lei32a(i,r) (*( int32_t*)r = l_endian_i32(i))
#define leu64a(i,r) (*(uint64_t*)r = l_endian_u64(i))
#define lei64a(i,r) (*( int64_t*)r = l_endian_i64(i))
#define lef32a(i,r) (*(uint32_t*)r = l_endian_f32(i))
#define lef64a(i,r) (*(uint64_t*)r = l_endian_f64(i))

#define beu16a(i,r) (*(uint16_t*)r = b_endian_u16(i))
#define bei16a(i,r) (*( int16_t*)r = b_endian_i16(i))
#define beu32a(i,r) (*(uint32_t*)r = b_endian_u32(i))
#define bei32a(i,r) (*( int32_t*)r = b_endian_i32(i))
#define beu64a(i,r) (*(uint64_t*)r = b_endian_u64(i))
#define bei64a(i,r) (*( int64_t*)r = b_endian_i64(i))
#define bef32a(i,r) (*(uint32_t*)r = b_endian_f32(i))
#define bef64a(i,r) (*(uint64_t*)r = b_endian_f64(i))

#else
/*    SPARC: missing alignment must be explicitly handled     */ 
uint16_t leu16p(uint8_t* i);
int16_t  lei16p(uint8_t* i);
uint32_t leu32p(uint8_t* i);
int32_t  lei32p(uint8_t* i);
uint64_t leu64p(uint8_t* i);
int64_t  lei64p(uint8_t* i);
float    lef32p(uint8_t* i);
double   lef64p(uint8_t* i);

uint16_t beu16p(uint8_t* i);
int16_t  bei16p(uint8_t* i);
uint32_t beu32p(uint8_t* i);
int32_t  bei32p(uint8_t* i);
uint64_t beu64p(uint8_t* i);
int64_t  bei64p(uint8_t* i);
float    bef32p(uint8_t* i);
double   bef64p(uint8_t* i);

void leu16a(uint16_t i, uint8_t* r);
void lei16a( int16_t i, uint8_t* r);
void leu32a(uint32_t i, uint8_t* r);
void lei32a( int32_t i, uint8_t* r);
void leu64a(uint64_t i, uint8_t* r);
void lei64a( int64_t i, uint8_t* r);
void lef32a(   float i, uint8_t* r);
void lef64a(  double i, uint8_t* r);

void beu16a(uint16_t i, uint8_t* r);
void bei16a( int16_t i, uint8_t* r);
void beu32a(uint32_t i, uint8_t* r);
void bei32a( int32_t i, uint8_t* r);
void beu64a(uint64_t i, uint8_t* r);
void bei64a( int64_t i, uint8_t* r);
void bef32a(   float i, uint8_t* r);
void bef64a(  double i, uint8_t* r);

#endif


#define NaN (0.0/0.0)	/* used for encoding of missing values */ 
#define INF (1.0/0.0)	/* positive infinity */

#define min(a,b)	(((a) < (b)) ? (a) : (b))
#define max(a,b)	(((a) > (b)) ? (a) : (b))



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	global constants and variables 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/****************************************************************************/
/**                                                                        **/
/**                     TYPEDEFS AND STRUCTURES                            **/
/**                                                                        **/
/****************************************************************************/


/*
	This structure defines the fields used for "Annotated ECG" 
 */
typedef struct {
	char*		test;		/* test field for annotated ECG */
	
	float		diastolicBloodPressure;				
	float		systolicBloodPressure;	
	char*		MedicationDrugs;
	char*		ReferringPhysician;
	char*		LatestConfirmingPhysician;
	char*		Diagnosis;
	uint8_t		EmergencyLevel; /* 0: routine 1-10: increased emergency level */

	float		HeartRate;	
	float		P_wave[2]; 	/* start and end  */
	float		QRS_wave[2]; 	/* start and end  */
	float		T_wave[2]; 	/* start and end  */
	float		P_QRS_T_axes[3];

	/***** SCP only fields *****/
	struct {	
		uint8_t	HUFFMAN;
		uint8_t	REF_BEAT;
		uint8_t	DIFF;
		uint8_t	BIMODAL;
	} FLAG;
        struct {
		//uint8_t tag14[41],tag15[41];
	        struct {
			uint16_t INST_NUMBER;		/* tag 14, byte 1-2  */
			uint16_t DEPT_NUMBER;		/* tag 14, byte 3-4  */
			uint16_t DEVICE_ID;		/* tag 14, byte 5-6  */
			uint8_t  DEVICE_TYPE;		/* tag 14, byte 7: 0: Cart, 1: System (or Host)  */
			uint8_t MANUF_CODE;		/* tag 14, byte 8 (MANUF_CODE has to be 255) */
			char*   MOD_DESC;		/* tag 14, byte 9 (MOD_DESC has to be "Cart1") */
			uint8_t VERSION;		/* tag 14, byte 15 (VERSION has to be 20) */
			uint8_t PROT_COMP_LEVEL;	/* tag 14, byte 16 (PROT_COMP_LEVEL has to be 0xA0 => level II) */
			uint8_t LANG_SUPP_CODE;		/* tag 14, byte 17 (LANG_SUPP_CODE has to be 0x00 => Ascii only, latin and 1-byte code) */
			uint8_t ECG_CAP_DEV;		/* tag 14, byte 18 (ECG_CAP_DEV has to be 0xD0 => Acquire, (No Analysis), Print and Store) */
			uint8_t MAINS_FREQ;		/* tag 14, byte 19 (MAINS_FREQ has to be 0: unspecified, 1: 50 Hz, 2: 60Hz) */
			char 	reserved[22]; 		/* char[35-19] reserved; */			
			char* 	ANAL_PROG_REV_NUM;
			char* 	SERIAL_NUMBER_ACQ_DEV;
			char* 	ACQ_DEV_SYS_SW_ID;
			char* 	ACQ_DEV_SCP_SW; 	/* tag 14, byte 38 (SCP_IMPL_SW has to be "OpenECG XML-SCP 1.00") */
			char* 	ACQ_DEV_MANUF;		/* tag 14, byte 38 (ACQ_DEV_MANUF has to be "Manufacturer") */
        	} Tag14, Tag15; 
        } Section1;
        struct {
        	size_t   StartPtr;
        	size_t	 Length;
        } Section5;
        struct {
        	size_t   StartPtr;
        	size_t	 Length;
        } Section6;
} aECG_TYPE;

/****************************************************************************/
/**                                                                        **/
/**                     INTERNAL FUNCTIONS                                 **/
/**                                                                        **/
/****************************************************************************/

/*
        file access wrapper: use ZLIB (if available) or STDIO
 */ 	 

HDRTYPE* 	ifopen(HDRTYPE* hdr, const char* mode );
int 		ifclose(HDRTYPE* hdr);
int 		ifflush(HDRTYPE* hdr);
size_t 		ifread(void* buf, size_t size, size_t nmemb, HDRTYPE* hdr);
size_t 		ifwrite(void* buf, size_t size, size_t nmemb, HDRTYPE* hdr);
int             ifprintf(HDRTYPE* hdr, const char *format, ...);
int             ifputc(int c, HDRTYPE* hdr);
int 		ifgetc(HDRTYPE* hdr);
char*           ifgets(char *str, int n, HDRTYPE* hdr);
int             ifseek(HDRTYPE* hdr, long offset, int whence );
long            iftell(HDRTYPE* hdr);
int 		ifgetpos(HDRTYPE* hdr, fpos_t *pos);
int             iferror(HDRTYPE* hdr);

/*
	These functions are for the converter between SCP to HL7aECG
 */

int sopen_SCP_read     (HDRTYPE* hdr);
int sopen_SCP_write    (HDRTYPE* hdr);
int sopen_HL7aECG_read (HDRTYPE* hdr);
int sopen_HL7aECG_write(HDRTYPE* hdr);
int sclose_HL7aECG_write(HDRTYPE* hdr);

uint32_t gcd(uint32_t A, uint32_t B);
uint32_t lcm(uint32_t A, uint32_t B);

extern const int16_t GDFTYP_BYTE[];
extern const char *LEAD_ID_TABLE[];

char* PhysDim(uint16_t PhysDimCode, char *PhysDim);
uint16_t PhysDimCode(char* PhysDim0);
double PhysDimScale(uint16_t PhysDimCode);

uint16_t CRCEvaluate(uint8_t* datablock, uint32_t datalength);
int16_t CRCCheck(uint8_t* datablock, uint32_t datalength);

/****************************************************************************/
/**                                                                        **/
/**                               EOF                                      **/
/**                                                                        **/
/****************************************************************************/

#endif	/* BIOSIG_INTERNAL_H */