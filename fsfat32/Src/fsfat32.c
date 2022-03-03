#include "Config.h"
#include "stm32_SDcard.h"
#include "fsfat32.h"
static void readBPB( fsfat32_t * fsfat32, uint8_t * SD_BUFFER){
	readBlockSingle(0x00000000 , SD_BUFFER) ;
	memcpy(&fsfat32->BPB , SD_BUFFER , sizeof(fsfat32->BPB)) ;
#if (FAT_DEV_MODE )
	printf(" bytes per sector  %d \n" , fsfat32->BPB.BPB_BytesPerSector) ;
	printf("sector per cluster %d \n" , fsfat32->BPB.BPB_SectorPerCluster) ;
	printf("reserved sec count %d \n" , fsfat32->BPB.BPB_ReservedSectorCount) ;
	printf("number of fats     %d \n" , fsfat32->BPB.BPB_NumberOfFats) ;
	printf("Rootentcnt         %d \n" , fsfat32->BPB.BPB_RootEntCnt) ;
	printf("Root cluster       %u \n" , fsfat32->BPB.BPB_RootClus) ;
	printf("BPB To Sec 32      %u \n" , fsfat32->BPB.BPB_ToSec32) ;
	printf("size of each fat   %u \n" , fsfat32->BPB.BPB_FATSz32) ;
#endif
}

static void getRootDirectory(fsfat32_t *fsfat32){
	fsfat32->RootDirSectors = ((fsfat32->BPB.BPB_RootEntCnt * 32) + (fsfat32->BPB.BPB_BytesPerSector - 1 )) / fsfat32->BPB.BPB_BytesPerSector ;
#if (FAT_DEV_MODE )
     printf(" root dir count %u \n" , fsfat32->RootDirSectors) ;
#endif
}

static void getFatType(fsfat32_t *fsfat32){
	uint32_t FATSz ;
	if(fsfat32->BPB.BPB_FTASz16 != 0){
	    FATSz = fsfat32->BPB.BPB_FTASz16  ;
	}else{
	FATSz = fsfat32->BPB.BPB_FATSz32 ;
	}
	fsfat32->firstDatasector = ( fsfat32->BPB.BPB_ReservedSectorCount + (fsfat32->BPB.BPB_NumberOfFats* FATSz) + fsfat32->RootDirSectors ) ;

#if (FAT_DEV_MODE )
	printf(" first data sector %u \n" , fsfat32->firstDatasector ) ;
#endif
	// determine the fat type
	uint32_t totsec = 0 ;
	if (fsfat32->BPB.BPB_ToSec16!= 0) {
		totsec = fsfat32->BPB.BPB_ToSec16 ;
	}else{
		totsec = fsfat32->BPB.BPB_ToSec32 ;
	}

	 uint32_t CountofClusters = ( (totsec - ( fsfat32->BPB.BPB_ReservedSectorCount + (fsfat32->BPB.BPB_NumberOfFats* FATSz) )
			 	 	 	 	 	 + fsfat32->RootDirSectors) / (fsfat32->BPB.BPB_SectorPerCluster) );

	 if(CountofClusters < 4085) {
	 /* Volume is FAT12 */
		 fsfat32->fatType = FAT_TYPE_12 ;

#if (FAT_DEV_MODE )
		 printf("volume is fat 12 %u \n" , CountofClusters) ;
#endif
	 } else if(CountofClusters < 65525) {
	     /* Volume is FAT16 */
		 fsfat32->fatType  = FAT_TYPE_16 ;

#if (FAT_DEV_MODE )
		 printf("volume is fat 16 %u \n" , CountofClusters) ;
#endif
	 } else {
	     /* Volume is FAT32 */
		 fsfat32->fatType = FAT_TYPE_32 ;

#if (FAT_DEV_MODE )
		 printf("volume is fat 32 %u \n" , CountofClusters) ;
#endif
	}
}


static void mapClusterToFat(fsfat32_t *fsfat32 , uint32_t clusterNumber ,uint8_t * SD_BUFFER){
uint32_t FATOffset = 0 ;
uint32_t ThisFATEntOffset = 0 ;
uint32_t ThisFatSecNum = 0 ;
fsfat32->clusfat.FAT32ClusEntryVal = 0 ;
	if(fsfat32->fatType == FAT_TYPE_16){
	    FATOffset = clusterNumber * 2;
	}
	else if (fsfat32->fatType == FAT_TYPE_32){
	    FATOffset = clusterNumber * 4;
	}
\
	ThisFatSecNum = fsfat32->BPB.BPB_ReservedSectorCount + (FATOffset / fsfat32->BPB.BPB_BytesPerSector);
	ThisFATEntOffset = (FATOffset % fsfat32->BPB.BPB_BytesPerSector);

	readBlockSingle(ThisFatSecNum, SD_BUFFER) ;

#if (FAT_DEV_MODE )
	 printf("ThisFATEntOffset is : %d \n " , ThisFATEntOffset) ;
	 printf("ThisFatSecNum is : %d \n " , ThisFatSecNum) ;
#endif
	 fsfat32->clusfat.FAT32ClusEntryVal |= ( (SD_BUFFER[ThisFATEntOffset] << 0) );
	 fsfat32->clusfat.FAT32ClusEntryVal |= ( (SD_BUFFER[ThisFATEntOffset + 1] << 8) );
	 fsfat32->clusfat.FAT32ClusEntryVal |= ( (SD_BUFFER[ThisFATEntOffset + 2] << 16) );
	 fsfat32->clusfat.FAT32ClusEntryVal |= ( (SD_BUFFER[ThisFATEntOffset + 3] << 24) );

	 fsfat32->clusfat.FAT32ClusEntryVal &= 0x0FFFFFFF ;

#if (FAT_DEV_MODE )
	 printf("cluster number calculated from ThisFATEntOffset  is : %d \n " , fsfat32->clusfat.FAT32ClusEntryVal ) ;
#endif
}


void fsfat32_Init(fsfat32_t *fsfat32, uint8_t * SD_BUFFER){
	readBPB(fsfat32,SD_BUFFER) ;
	getRootDirectory(fsfat32) ;
	getFatType(fsfat32) ;
}


void readFile(fsfat32_t *fsfat32 , uint8_t *SD_BUFFER ,char fileName[11] , uint8_t Next){

#if (FAT_DEV_MODE )
	printf("file to search : %s \n" , fileName );
#endif
	char Name [7] ="" ;
	memset(Name , 0x20 , 7) ;
	char Extension[3] ="" ;
	memset(Extension, 0x20 , 7) ;
	// make the actual string to compare
	char DOSName[12] = "xxxxxxxxxxx" ; // some dummy data
	memset(DOSName ,0x20 , 12) ;
	char str[11] = "";
	strcpy(str , fileName) ;
	   const char s[1] = ".";
	   char *token;
	   char *tempToken;
	   /* get the first token */
	   token = strtok(str, s);
	   /* walk through other tokens */
//       printf( " %s\n", token );
	   strcpy(Name ,token) ;
	   for (uint8_t i = 0; i < 7; i++) {
	   if (Name[i] == 0) {
		Name[i] = 0x20 ;
		}
	}
	  while(token != NULL){
	  tempToken = token ;
	  token = strtok(NULL, s);
	  if (token == 0) {
		memcpy(Extension ,tempToken, 3) ;
	  }
   }
	// form the final string which is DOS compatible
	      memcpy(DOSName , Name , 7) ;
	      memcpy(&DOSName[8], Extension, 3) ;
	      DOSName[11] = '\0' ;

#if (FAT_DEV_MODE )
	      printf("DOS NAME IS %s \n" , DOSName) ;
#endif
	Dir_Entry_t DirEntry ;
	char DIR_Name[12] = "FILENAME.TXT" ;	// dummy name
 for (uint8_t i = 0;  i < fsfat32->BPB.BPB_SectorPerCluster ; i++) {
	readBlockSingle(fsfat32->firstDatasector + i, SD_BUFFER) ;			// for every block in a sector (8 ideally)

	for (uint8_t i = 0; i < 16; i++) {			// for every directory entry i.e 16 in a block
		// map dir entry with sd buffer
		memcpy(&DirEntry , &SD_BUFFER[(i*32)] , sizeof(DirEntry)) ;
		memcpy(DIR_Name , DirEntry.DIR_Name , 12) ;
		DIR_Name[11] = '\0' ;

		// compare the names and exclude the deleted entries
		if (DirEntry.DIR_Name[0] != 0xE5) {
			if (strcmp(DIR_Name , DOSName)== 0) {

#if (FAT_DEV_MODE )
				printf("match found for: %s\n" , DOSName ) ;
#endif
				// save the file's data to clusfat
				fsfat32->clusfat.fileStartCluster = 0;

				fsfat32->clusfat.fileStartCluster |= DirEntry.DIR_FstClusLO << 0 ;
				fsfat32->clusfat.fileStartCluster |= DirEntry.DIR_FstClusHI << 16 ;
				fsfat32->clusfat.fileStartSector = 0 ;
				fsfat32->clusfat.fileStartSector = (((fsfat32->clusfat.fileStartCluster) - 2)
													* fsfat32->BPB.BPB_SectorPerCluster ) + fsfat32->firstDatasector;
				fsfat32->clusfat.fileSize = 0 ;
				fsfat32->clusfat.fileSize = DirEntry.DIR_FileSize ;

				return ;
			}
#if (FAT_DEV_MODE )
			printf("file name is : %s \n" , DIR_Name) ;
#endif
		}
	 }
  }

 /* once the dir entries of cluster 2 have been fetched we
  * get the values from the fat table and loop until we are
  * finished */

 // first get the value of next cluster from fat table after cluster 2
 mapClusterToFat(fsfat32, 2, SD_BUFFER) ;

 while (fsfat32->clusfat.FAT32ClusEntryVal != 0x0FFFFFFF){

	 // the value " FAT32ClusEntryVal " is the value of next cluster after the previous cluster is read
	 // get the first sector number of a cluster and fetch the data in that sector
	 fsfat32->clusfat.currentSector = ((fsfat32->clusfat.FAT32ClusEntryVal -2) * fsfat32->BPB.BPB_SectorPerCluster ) + fsfat32->firstDatasector;

	 for (uint8_t i = 0;  i < fsfat32->BPB.BPB_SectorPerCluster ; i++) {
		readBlockSingle(fsfat32->clusfat.currentSector + i, SD_BUFFER) ;			// for every block in a sector (8 ideally)

		for (uint8_t i = 0; i < 16; i++) {			// for every directory entry i.e 16 in a block
			// map dir entry with sd buffer
			memcpy(&DirEntry , &SD_BUFFER[(i*32)] , sizeof(DirEntry)) ;
			memcpy(DIR_Name , DirEntry.DIR_Name , 12) ;
			DIR_Name[11] = '\0' ;

			// compare the names and exclude the deleted entries
			if (DirEntry.DIR_Name[0] != 0xE5) {
				if (strcmp(DIR_Name , DOSName)== 0) {

				#if (FAT_DEV_MODE )
					printf("match found for: %s\n" , DOSName ) ;
				#endif
					fsfat32->clusfat.fileStartCluster |= DirEntry.DIR_FstClusLO << 0 ;
					fsfat32->clusfat.fileStartCluster |= DirEntry.DIR_FstClusLO << 16 ;

					fsfat32->clusfat.fileStartSector= (((fsfat32->clusfat.fileStartSector) - 2)
													* fsfat32->BPB.BPB_SectorPerCluster ) + fsfat32->firstDatasector;

					fsfat32->clusfat.fileSize = DirEntry.DIR_FileSize ;

					return ;
			 }

				#if (FAT_DEV_MODE )
			 printf("file name is : %s \n" , DIR_Name) ;
				#endif
		  }
		}
	  }
	 mapClusterToFat(fsfat32, fsfat32->clusfat.FAT32ClusEntryVal, SD_BUFFER) ;
   }
 }


void getFileData(fsfat32_t *fsfat32 ,uint8_t *SD_BUFFER , void (*dataProcessor)(uint8_t *SD_BUFFER) , uint32_t DataSize) {
	fsfat32->FileReadComplete = 0 ;
	uint32_t blocksizeRead = 0 ;
	while(!fsfat32->FileReadComplete){
		for (uint8_t i= 0; i < fsfat32->BPB.BPB_SectorPerCluster; i++) {
			memset(SD_BUFFER ,0, 512);
			readBlockSingle(((((fsfat32->clusfat.fileStartCluster - 2 )*fsfat32->BPB.BPB_SectorPerCluster ) + fsfat32->firstDatasector )+ i), SD_BUFFER) ;
			dataProcessor(SD_BUFFER) ;
			blocksizeRead += 512 ;
		}
		mapClusterToFat(fsfat32, fsfat32->clusfat.fileStartCluster, SD_BUFFER) ;
		fsfat32->clusfat.fileStartCluster = fsfat32->clusfat.FAT32ClusEntryVal ;
		if (fsfat32->clusfat.FAT32ClusEntryVal == 0x0FFFFFFF) {
			fsfat32->FileReadComplete = 1 ;

				#if (FAT_DEV_MODE)
			printf("fileSize reached : %u \n" , blocksizeRead) ;
				#endif
		}else if(blocksizeRead >= DataSize){
			fsfat32->FileReadComplete = 1 ;
				#if (FAT_DEV_MODE)
			printf("blockSize reached DataSize : %u \n" , blocksizeRead) ;
				#endif
		}
	}
}
