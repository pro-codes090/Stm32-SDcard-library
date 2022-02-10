#include "stm32_SDcard.h"
#include "fsfat32.h"


static void extractFat32Params(fsfat32_t *pfsfat32) {

	// Bytes per sector
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_BytsPerSec); i++) {
		pfsfat32->BPB_BytsPerSec[sizeof(pfsfat32->BPB_BytsPerSec) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_BYTSPERSEC +i] ; // little endain conversion
		}
	// sector per clustor
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_SecPerClus); i++) {
			pfsfat32->BPB_SecPerClus[sizeof(pfsfat32->BPB_SecPerClus) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_SECPERCLUS + i] ; // little endain conversion
		}
	// reserved sectors
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_RsvdSecCnt); i++) {
			pfsfat32->BPB_RsvdSecCnt[sizeof(pfsfat32->BPB_RsvdSecCnt) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_RSVDSECCNT + i] ; // little endain conversion
		}
	// Number of fats
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_NumFATs); i++) {
			pfsfat32->BPB_NumFATs[sizeof(pfsfat32->BPB_NumFATs) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_NUMFATS +i] ; // little endain conversion
		}
	// size of each of each fat fats
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_FATSz32); i++) {
			pfsfat32->BPB_FATSz32[sizeof(pfsfat32->BPB_FATSz32) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_FATSz32 + i] ; // little endain conversion
		}
	// hidden sectors
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_HiddSec); i++) {
			pfsfat32->BPB_HiddSec[sizeof(pfsfat32->BPB_HiddSec) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_HIDDSEC +i] ; // little endain conversion
		}
	// location of root clustor
	for (uint8_t i = 0; i < sizeof(pfsfat32->BPB_RootClus); i++) {
			pfsfat32->BPB_RootClus[sizeof(pfsfat32->BPB_RootClus) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BPB_ROOTCLUS +i] ; // little endain conversion
		}
	// Boot signature
	for (uint8_t i = 0; i < sizeof(pfsfat32->BS_BootSig); i++) {
			pfsfat32->BS_BootSig[sizeof(pfsfat32->BS_BootSig) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BS_BOOTSIG + i] ; // little endain conversion
		}
	// Volume Label
	for (uint8_t i = 0; i < sizeof(pfsfat32->BS_VolLab); i++) {
			pfsfat32->BS_VolLab[sizeof(pfsfat32->BS_VolLab) -(i+1)] = pfsfat32->rcvBuffAddr[OFFSET_BS_VOLLAB + i] ; // little endain conversion
		}


}

void readBpbBlock(fsfat32_t *pfsfat32){

	readBlockSingle(0x00000000, pfsfat32->rcvBuffAddr) ;

	extractFat32Params(pfsfat32) ;

	getDataRegion(pfsfat32) ;

}

void getDataRegion (fsfat32_t *pfsfat32 ){
//	uint64_t temp ;
// formula from fat docs
//	FirstDataSector = BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors;

	// extract the parametrs first
	memset(&(pfsfat32->diskParam) , 0 , sizeof(pfsfat32->diskParam)) ;

	// BPB_BytsPerSec
	pfsfat32->diskParam.BPB_BytsPerSec |=  (pfsfat32->BPB_BytsPerSec[0] << 8) ;
	pfsfat32->diskParam.BPB_BytsPerSec |=  (pfsfat32->BPB_BytsPerSec[1] << 0) ;
	printf("BPB_BytsPerSec %d \n  " , pfsfat32->diskParam.BPB_BytsPerSec) ;

	// BPB_SecPerClus
	pfsfat32->diskParam.BPB_SecPerClus |=  (pfsfat32->BPB_SecPerClus[0] << 0) ;
	printf("BPB_SecPerClus %d \n  " , pfsfat32->diskParam.BPB_SecPerClus ) ;

	// BPB_RsvdSecCnt
	pfsfat32->diskParam.BPB_RsvdSecCnt |=  (pfsfat32->BPB_RsvdSecCnt[0] << 8) ;
	pfsfat32->diskParam.BPB_RsvdSecCnt |=  (pfsfat32->BPB_RsvdSecCnt[1] << 0) ;
	printf("BPB_RsvdSecCnt %d \n  " , pfsfat32->diskParam.BPB_RsvdSecCnt ) ;

	// BPB_NumFATs
	pfsfat32->diskParam.BPB_NumFATs |=  (pfsfat32->BPB_NumFATs[0] << 0) ;
	printf("BPB_NumFATs %d \n  " , pfsfat32->diskParam.BPB_NumFATs) ;

	// BPB_FATSz32
	pfsfat32->diskParam.BPB_FATSz32 |=  (pfsfat32->BPB_FATSz32 [0] << 24) ;
	pfsfat32->diskParam.BPB_FATSz32 |=  (pfsfat32->BPB_FATSz32 [1] << 16) ;
	pfsfat32->diskParam.BPB_FATSz32 |=  (pfsfat32->BPB_FATSz32 [2] << 8) ;
	pfsfat32->diskParam.BPB_FATSz32 |=  (pfsfat32->BPB_FATSz32 [3] << 0) ;
	printf("BPB_FATSz32 %d \n  " , pfsfat32->diskParam.BPB_FATSz32  ) ;

	// BPB_HiddSec
	pfsfat32->diskParam.BPB_HiddSec |=  (pfsfat32->BPB_HiddSec[0] << 24) ;
	pfsfat32->diskParam.BPB_HiddSec |=  (pfsfat32->BPB_HiddSec[1] << 16) ;
	pfsfat32->diskParam.BPB_HiddSec |=  (pfsfat32->BPB_HiddSec[2] << 8) ;
	pfsfat32->diskParam.BPB_HiddSec |=  (pfsfat32->BPB_HiddSec[3] << 0) ;
	printf("BPB_HiddSec %d \n  " , pfsfat32->diskParam.BPB_HiddSec) ;

	// BPB_RootClus
	pfsfat32->diskParam.BPB_RootClus |=  (pfsfat32->BPB_RootClus[0] << 24) ;
	pfsfat32->diskParam.BPB_RootClus |=  (pfsfat32->BPB_RootClus[1] << 16) ;
	pfsfat32->diskParam.BPB_RootClus |=  (pfsfat32->BPB_RootClus[2] << 8) ;
	pfsfat32->diskParam.BPB_RootClus |=  (pfsfat32->BPB_RootClus[3] << 0) ;
	printf("BPB_RootClus %d \n  " , pfsfat32->diskParam.BPB_RootClus) ;

	uint32_t FirstDataSector ;
	FirstDataSector = ( pfsfat32->diskParam.BPB_RsvdSecCnt + (pfsfat32->diskParam.BPB_NumFATs * pfsfat32->diskParam.BPB_FATSz32) + 0);
	printf("first data sector %d \n " , FirstDataSector) ;

	readBlockSingle(FirstDataSector, pfsfat32->rcvBuffAddr) ;




}



