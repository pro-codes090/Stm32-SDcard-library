/*
 * fsfat32.h
 *
 *  Created on: 31-Jan-2022
 *      Author: pro
 */

#ifndef INC_FSFAT32_H_
#define INC_FSFAT32_H_

#include <stdint.h>


typedef struct {
uint8_t fatType ;
}__attribute__((__packed__))fatCal_t;

// BPB parameters offsets

#define  OFFSET_BS_JUMPBOOT 			 0
#define  OFFSET_BS_OEMNAME         	     3
#define  OFFSET_BPB_BYTESPERSECTOR      11
#define  OFFSET_BPB_SECTORPERCLUSTER    13
#define  OFFSET_BPB_RESERVEDSECTORCOUNT 14
#define  OFFSET_BPB_NUMBEROFFATS        16
#define  OFFSET_BPB_ROOTENTCNT			17
#define  OFFSET_BPB_TOSEC16				19
#define  OFFSET_BPB_MEDIA               21
#define  OFFSET_BPB_FTASZ16             22
#define  OFFSET_BPB_SECPERTRK           24
#define  OFFSET_BPB_NUMHEADS            26
#define  OFFSET_BPB_HIDDENSECTOR 		28
#define  OFFSET_BPB_TOSEC32             32
#define  OFFSET_BPB_FATSZ32             36
#define  OFFSET_BPB_EXTFLAGS 			40
#define  OFFSET_BPB_FSVER               42
#define  OFFSET_BPB_ROOTCLUS 			44
#define  OFFSET_BPB_FSINFO              48
#define  OFFSET_BPB_BKBOOTSEC           50

#define FAT_TYPE_32		32
#define FAT_TYPE_16		16
#define FAT_TYPE_12		12

#define FirstSectorOfCluster(N , p_FSFAT32)  ( ((N - 2) * p_FSFAT32->BPB.BPB_SectorPerCluster) + p_FSFAT32->firstDatasector)

typedef struct {
uint8_t BS_jumpBoot [3];
uint8_t BS_OEMName [8] ;
uint16_t BPB_BytesPerSector;
uint8_t BPB_SectorPerCluster;
uint16_t BPB_ReservedSectorCount;
uint8_t BPB_NumberOfFats;
uint16_t BPB_RootEntCnt;
uint16_t BPB_ToSec16;
uint8_t BPB_Media;
uint16_t BPB_FTASz16;	// there is a little spelling mistake
uint16_t BPB_SecPerTrk ;
uint16_t BPB_NumHeads ;
uint32_t BPB_HiddenSector ;
uint32_t BPB_ToSec32;
uint32_t BPB_FATSz32 ;
uint16_t BPB_ExtFlags ;
uint16_t BPB_FSVer ;
uint32_t BPB_RootClus ;
uint16_t BPB_FSInfo;
uint16_t BPB_BkBootSec;
fatCal_t fatcal ;
}__attribute__((__packed__))BPB_structure_t;

typedef struct {
BPB_structure_t BPB;
uint8_t RootDirSectors ;
uint32_t firstDatasector ;
uint8_t fatType ;
clusfat_t clusfat ;
}__attribute__((__packed__))fsfat32_t;

typedef struct {
uint32_t ThisFatSecNum ;
uint32_t ThisFATEntOffset ;

}__attribute__((__packed__))clusfat_t;


void readBPB( fsfat32_t * fsfat32, uint8_t * SD_BUFFER);
void getRootDirectory(fsfat32_t *fsfat32);
void fsfat32_Init(fsfat32_t *fsfat32, uint8_t * SD_BUFFER);
void getFatType(fsfat32_t *fsfat32);

#endif /* INC_FSFAT32_H_ */