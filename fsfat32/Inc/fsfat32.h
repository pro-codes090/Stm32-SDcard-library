/*
 * fsfat32.h
 *
 *  Created on: 31-Jan-2022
 *      Author: pro
 */

#ifndef INC_FSFAT32_H_
#define INC_FSFAT32_H_

#include <stdint.h>

#define OFFSET_BPB_BYTSPERSEC	11
#define OFFSET_BPB_SECPERCLUS	13
#define OFFSET_BPB_RSVDSECCNT	14
#define OFFSET_BPB_NUMFATS   	16
#define OFFSET_BPB_HIDDSEC   	28

#define OFFSET_BPB_ROOTCLUS  	44
#define OFFSET_BS_BOOTSIG    	66
#define OFFSET_BS_VOLLAB     	71


typedef struct {
uint8_t BPB_BytsPerSec[2] ;
uint8_t BPB_SecPerClus[1] ;
uint8_t BPB_RsvdSecCnt[2] ;
uint8_t BPB_NumFATs   [1] ;
uint8_t BPB_HiddSec   [4] ;
// From Offset 36
uint8_t BPB_RootClus  [4] ;
uint8_t BS_BootSig    [1] ;
uint8_t BS_VolLab     [11];
uint8_t *rcvBuffAddr   ;
uint8_t *txBuffAddr   ;

}fsfat32_t;


void readBpbBlock(fsfat32_t *pfsfat32) ;

#endif /* INC_FSFAT32_H_ */
