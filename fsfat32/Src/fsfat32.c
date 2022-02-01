#include "stm32_SDcard.h"
#include "fsfat32.h"


static void extractFat32Params(fsfat32_t *pfsfat32) {

	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_BytsPerSec); i++) {
		pfsfat32->BPB_BytsPerSec[sizeof(pfsfat32->BPB_BytsPerSec) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_BYTSPERSEC +i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_SecPerClus); i++) {
			pfsfat32->BPB_SecPerClus[sizeof(pfsfat32->BPB_SecPerClus) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_SECPERCLUS + i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_RsvdSecCnt); i++) {
			pfsfat32->BPB_RsvdSecCnt[sizeof(pfsfat32->BPB_RsvdSecCnt) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_RSVDSECCNT + i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_NumFATs); i++) {
			pfsfat32->BPB_NumFATs[sizeof(pfsfat32->BPB_NumFATs) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_NUMFATS +i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_HiddSec); i++) {
			pfsfat32->BPB_HiddSec[sizeof(pfsfat32->BPB_HiddSec) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_HIDDSEC +i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_RootClus); i++) {
			pfsfat32->BPB_RootClus[sizeof(pfsfat32->BPB_RootClus) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_ROOTCLUS +i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BS_BootSig); i++) {
			pfsfat32->BS_BootSig[sizeof(pfsfat32->BS_BootSig) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BS_BOOTSIG + i] ; // little endain conversion
		}
	for (uint8_t i = 0; i < sizeof(pfsfat32->BS_VolLab); i++) {
			pfsfat32->BS_VolLab[sizeof(pfsfat32->BS_VolLab) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BS_VOLLAB + i] ; // little endain conversion
		}


}

void readBpbBlock(fsfat32_t *pfsfat32){

	readBlockSingle(0x00000000, pfsfat32->rcvBuffAddr) ;

	extractFat32Params(pfsfat32) ;

}



