#include "stm32_SDcard.h"
#include "fsfat32.h"

#define FAT_TYPE_32		32
#define FAT_TYPE_16		16
#define FAT_TYPE_12		12

	BPB_structure_t * BPB ;

void readBPBandcompute( uint8_t * SD_BUFFER){

	BPB = SD_BUFFER;

	readBlockSingle(0x00000000 , SD_BUFFER) ;

	printf(" bytes per sector %d \n" , BPB->BPB_BytesPerSector) ;
	printf("sector per cluster %d \n" , BPB->BPB_SectorPerCluster) ;
	printf("reserved sector count %d \n" , BPB->BPB_ReservedSectorCount) ;
	printf("number of fats %d \n" , BPB->BPB_NumberOfFats) ;
	printf("Rootentcnt %d \n" , BPB->BPB_RootEntCnt) ;
	printf("Root cluster %u \n" , BPB->BPB_RootClus) ;
	printf("BPB To Sec 32 %u \n" , BPB->BPB_ToSec32) ;
	printf("size of each fat %u \n" , BPB->BPB_FATSz32) ;

	uint8_t RootDirSectors = ((BPB->BPB_RootEntCnt * 32) + (BPB->BPB_BytesPerSector - 1 )) / BPB->BPB_BytesPerSector ;
	printf(" root dir count %u \n" , RootDirSectors) ;

	    uint32_t FATSz ;
	if(BPB->BPB_FTASz16!= 0){
	    FATSz = BPB->BPB_FTASz16 ;
	}else{
	FATSz = BPB->BPB_FATSz32 ;
	}

	uint32_t FirstDataSector = BPB->BPB_ReservedSectorCount + (BPB->BPB_NumberOfFats* FATSz) + RootDirSectors;
	printf(" first data sector %u \n" , FirstDataSector) ;

	// determine the fat type
	uint32_t totsec = 0 ;
	if (BPB->BPB_ToSec16 != 0) {
		totsec = BPB->BPB_ToSec16 ;
	}else{
		totsec = BPB->BPB_ToSec32 ;
	}

	uint32_t DataSec = 0 ;
	 DataSec = totsec - ( BPB->BPB_ReservedSectorCount + (BPB->BPB_NumberOfFats* FATSz) ) + RootDirSectors;

	 uint32_t CountofClusters = DataSec / BPB->BPB_SectorPerCluster ;

	 uint8_t fatType = 0 ;

	 if(CountofClusters < 4085) {
	 /* Volume is FAT12 */
		 fatType = FAT_TYPE_12 ;
		 printf("volume is fat 12 %u \n" , CountofClusters) ;
	 } else if(CountofClusters < 65525) {
	     /* Volume is FAT16 */
		 fatType = FAT_TYPE_16 ;
		 printf("volume is fat 16 %u \n" , CountofClusters) ;
	 } else {
	     /* Volume is FAT32 */
		 fatType = FAT_TYPE_32 ;
		 printf("volume is fat 32 %u \n" , CountofClusters) ;

	 }

	 // Cluster to FAT maping

	 // we do not do for fat 12 as of now

	 If(fatType == FAT_TYPE_16)
	     FATOffset = N * 2;
	 Else if (FATType == FAT32)
	     FATOffset = N * 4;

	 ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset / BPB_BytsPerSec);
	 ThisFATEntOffset = REM(FATOffset / BPB_BytsPerSec);


}



