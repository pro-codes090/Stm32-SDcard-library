#include "stm32_SDcard.h"
#include "fsfat32.h"

void fsfat32_Init(fsfat32_t *fsfat32, uint8_t * SD_BUFFER){

	readBPB(fsfat32,SD_BUFFER) ;

	getRootDirectory(fsfat32) ;

	getFatType(fsfat32) ;

}

void readBPB( fsfat32_t * fsfat32, uint8_t * SD_BUFFER){

	readBlockSingle(0x00000000 , SD_BUFFER) ;

	memcpy(&fsfat32->BPB , SD_BUFFER , sizeof(fsfat32->BPB)) ;
	printf(" bytes per sector  %d \n" , fsfat32->BPB.BPB_BytesPerSector) ;
	printf("sector per cluster %d \n" , fsfat32->BPB.BPB_SectorPerCluster) ;
	printf("reserved sec count %d \n" , fsfat32->BPB.BPB_ReservedSectorCount) ;
	printf("number of fats     %d \n" , fsfat32->BPB.BPB_NumberOfFats) ;
	printf("Rootentcnt         %d \n" , fsfat32->BPB.BPB_RootEntCnt) ;
	printf("Root cluster       %u \n" , fsfat32->BPB.BPB_RootClus) ;
	printf("BPB To Sec 32      %u \n" , fsfat32->BPB.BPB_ToSec32) ;
	printf("size of each fat   %u \n" , fsfat32->BPB.BPB_FATSz32) ;

}

void getRootDirectory(fsfat32_t *fsfat32){

	fsfat32->RootDirSectors = ((fsfat32->BPB.BPB_RootEntCnt * 32) + (fsfat32->BPB.BPB_BytesPerSector - 1 )) / fsfat32->BPB.BPB_BytesPerSector ;
     printf(" root dir count %u \n" , fsfat32->RootDirSectors) ;

}


void getFatType(fsfat32_t *fsfat32){
	uint32_t FATSz ;
	if(fsfat32->BPB.BPB_FTASz16 != 0){
	    FATSz = fsfat32->BPB.BPB_FTASz16  ;
	}else{
	FATSz = fsfat32->BPB.BPB_FATSz32 ;
	}

	fsfat32->firstDatasector = ( fsfat32->BPB.BPB_ReservedSectorCount + (fsfat32->BPB.BPB_NumberOfFats* FATSz) + fsfat32->RootDirSectors ) ;
	printf(" first data sector %u \n" , fsfat32->firstDatasector ) ;

	// determine the fat type
	uint32_t totsec = 0 ;
	if (fsfat32->BPB.BPB_ToSec16!= 0) {
		totsec = fsfat32->BPB.BPB_ToSec16 ;
	}else{
		totsec = fsfat32->BPB.BPB_ToSec32 ;
	}

	 uint32_t CountofClusters = ( (totsec - ( fsfat32->BPB.BPB_ReservedSectorCount + (fsfat32->BPB.BPB_NumberOfFats* FATSz) ) + fsfat32->RootDirSectors) / (fsfat32->BPB.BPB_SectorPerCluster) );

	 if(CountofClusters < 4085) {
	 /* Volume is FAT12 */
		 fsfat32->fatType = FAT_TYPE_12 ;
		 printf("volume is fat 12 %u \n" , CountofClusters) ;
	 } else if(CountofClusters < 65525) {
	     /* Volume is FAT16 */
		 fsfat32->fatType  = FAT_TYPE_16 ;
		 printf("volume is fat 16 %u \n" , CountofClusters) ;
	 } else {
	     /* Volume is FAT32 */
		 fsfat32->fatType = FAT_TYPE_32 ;
		 printf("volume is fat 32 %u \n" , CountofClusters) ;

	 }
}


void mapClusterToFat(fsfat32_t *fsfat32 , uint32_t clusterNumber ,uint8_t * SD_BUFFER){
uint32_t FATOffset = 0 ;

	if(fsfat32->fatType == FAT_TYPE_16){
	    FATOffset = clusterNumber * 2;
	}
	else if (fsfat32->fatType == FAT_TYPE_32){
	    FATOffset = clusterNumber * 4;
	}

	fsfat32->ThisFatSecNum = fsfat32->BPB.BPB_ReservedSectorCount + (FATOffset / fsfat32->BPB.BPB_BytesPerSector);



}

//fatToclusterMap(uint32_t ClusterNumber ){
//	 uint32_t  FATOffset = 0  ;
//
//	 if(BPB->fatcal == FAT_TYPE_16){
//	     FATOffset = N * 2;
//	 }
//	 else if (BPB->fatcal== FAT_TYPE_32){
//	     FATOffset = N * 4;
//	}
//	 ThisFATSecNum = BPB_ResvdSecCnt + (FATOffset / BPB_BytsPerSec);
//	 ThisFATEntOffset = REM(FATOffset / BPB_BytsPerSec);
//
//	 return
//}



//uint8_t RootDirSectors = ((BPB->BPB_RootEntCnt * 32) + (BPB->BPB_BytesPerSector - 1 )) / BPB->BPB_BytesPerSector ;
//printf(" root dir count %u \n" , RootDirSectors) ;
//
//    uint32_t FATSz ;
//if(BPB->BPB_FTASz16!= 0){
//    FATSz = BPB->BPB_FTASz16 ;
//}else{
//FATSz = BPB->BPB_FATSz32 ;
//}
//
//uint32_t FirstDataSector = BPB->BPB_ReservedSectorCount + (BPB->BPB_NumberOfFats* FATSz) + RootDirSectors;
//printf(" first data sector %u \n" , FirstDataSector) ;
//
//// determine the fat type
//uint32_t totsec = 0 ;
//if (BPB->BPB_ToSec16 != 0) {
//	totsec = BPB->BPB_ToSec16 ;
//}else{
//	totsec = BPB->BPB_ToSec32 ;
//}
//
//uint32_t DataSec = 0 ;
// DataSec = totsec - ( BPB->BPB_ReservedSectorCount + (BPB->BPB_NumberOfFats* FATSz) ) + RootDirSectors;
//
// uint32_t CountofClusters = DataSec / BPB->BPB_SectorPerCluster ;
//
// uint8_t fatType = 0 ;
//
// if(CountofClusters < 4085) {
// /* Volume is FAT12 */
//	 BPB->fatcal.fatType = FAT_TYPE_12 ;
//	 printf("volume is fat 12 %u \n" , CountofClusters) ;
// } else if(CountofClusters < 65525) {
//     /* Volume is FAT16 */
//	 BPB->fatcal.fatType= FAT_TYPE_16 ;
//	 printf("volume is fat 16 %u \n" , CountofClusters) ;
// } else {
//     /* Volume is FAT32 */
//	 BPB->fatcal.fatType = FAT_TYPE_32 ;
//	 printf("volume is fat 32 %u \n" , CountofClusters) ;
//
// }

