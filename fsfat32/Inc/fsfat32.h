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
uint8_t BS_jumpBoot [3];
uint8_t BS_OEMName [8] ;
uint16_t BPB_BytesPerSector;
uint8_t BPB_SectorPerCluster;
uint16_t BPB_ReservedSectorCount;
uint8_t BPB_NumberOfFats;
uint16_t BPB_RootEntCnt;
uint16_t BPB_ToSec16;
uint8_t BPB_Media;
uint16_t BPB_FTASz16;
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

}__attribute__((__packed__))BPB_structure_t;

void readBPBandcompute( uint8_t * SD_BUFFER);

#endif /* INC_FSFAT32_H_ */
