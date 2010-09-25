#include "exifwriter.h"

#include "jhead.h"
#define LOG_TAG "ExifWriter"

#include <utils/Log.h>

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define TAG_ORIENTATION            0x0112
#define TAG_MAKE                   0x010F
#define TAG_MODEL                  0x0110

     static void dump_to_file(const char *fname,
                              uint8_t *buf, uint32_t size)
     {
         int nw, cnt = 0;
         uint32_t written = 0;

         LOGD("opening file [%s]\n", fname);
         int fd = open(fname, O_RDWR | O_CREAT);
         if (fd < 0) {
             LOGE("failed to create file [%s]: %s", fname, strerror(errno));
             return;
         }

         LOGD("writing %d bytes to file [%s]\n", size, fname);
         while (written < size) {
             nw = write(fd,
                          buf + written,
                          size - written);
             if (nw < 0) {
                 LOGE("failed to write to file [%s]: %s",
                      fname, strerror(errno));
                 break;
             }
             written += nw;
             cnt++;
         }
         LOGD("done writing %d bytes to file [%s] in %d passes\n",
              size, fname, cnt);
         close(fd);
     }

void writeExif( void *origData, void *destData , int origSize , uint32_t *resultSize, int orientation,camera_position_type  *pt ) {
  const char *filename = "/data/temp.jpg" ;
  
    dump_to_file( filename, (uint8_t *)origData, origSize ) ;
    chmod( filename, S_IRWXU ) ;
    ResetJpgfile() ;
    

    memset(&ImageInfo, 0, sizeof(ImageInfo));
    ImageInfo.FlashUsed = -1;
    ImageInfo.MeteringMode = -1;
    ImageInfo.Whitebalance = -1;

    int gpsTag = 0 ; 
   /* if( pt != NULL ) {
            gpsTag = 3 ;
    }*/
    
    
    ExifElement_t *t = (ExifElement_t *)malloc( sizeof(ExifElement_t)*(3+gpsTag) ) ;
    
    ExifElement_t *it = t ;
  // Store file date/time.
  (*it).Tag = TAG_ORIENTATION ;
  (*it).Format = FMT_USHORT ;
  (*it).DataLength = 1 ;
  unsigned short v ;
  if( orientation == 90 ) {
    (*it).Value = "6" ;
  } else if( orientation == 180 ) {
    (*it).Value = "3" ;
  } else {
    (*it).Value = "1" ;
  }
  (*it).GpsTag = FALSE ; 
  
  it++;

  (*it).Tag = TAG_MAKE ;
  (*it).Format = FMT_STRING ;
  (*it).Value = "Samsung" ;
  (*it).DataLength = 8 ;
  (*it).GpsTag = FALSE ;
  
  it++ ;
  
  (*it).Tag = TAG_MODEL ;
  (*it).Format = FMT_STRING ;
  (*it).Value = "Galaxy with GAOSP" ;
  (*it).DataLength = 18 ;
  (*it).GpsTag = FALSE ;
  
  
/*    if( pt != NULL ) {
    it++ ;
  
    char *mylat = (char *)malloc( 255 * sizeof(char) ) ;
    snprintf( mylat, 255,"%lf", pt->latitude ) ;
    
    (*it).Tag = 0x02 ;
    (*it).Format = FMT_URATIONAL ;
    (*it).Value = mylat ;
    (*it).DataLength = 1 ;
    (*it).GpsTag = TRUE ;
    
    it++ ;
     char *mylong = (char *)malloc( 255 * sizeof(char) ) ;
    snprintf( mylong, 255,"%lf", (*pt).longitude ) ;
    
    (*it).Tag = 0x04 ;
    (*it).Format = FMT_URATIONAL ;
    (*it).Value = mylong ;
    (*it).DataLength = 1 ;
    (*it).GpsTag = TRUE ; 

    it++ ;
     char *myalt = (char *)malloc( 255 * sizeof(char) ) ;
    snprintf( myalt, 255,"%d", (*pt).altitude ) ;
    
    (*it).Tag = 0x06 ;
    (*it).Format = FMT_SRATIONAL ;
    (*it).Value = myalt ;
    (*it).DataLength = 1 ;
    (*it).GpsTag = TRUE ;     
    }
  */
   {
        struct stat st;
        if (stat(filename, &st) >= 0) {
            ImageInfo.FileDateTime = st.st_mtime;
            ImageInfo.FileSize = st.st_size;
        }
    }
    strncpy(ImageInfo.FileName, filename, PATH_MAX);
    
    ReadMode_t ReadMode;
    ReadMode = READ_METADATA;
    ReadMode |= READ_IMAGE;
    int res = ReadJpegFile(filename, (ReadMode_t)ReadMode );

    create_EXIF( t, 3, gpsTag);
    
        WriteJpegFile(filename);
	chmod( filename, S_IRWXU ) ;
        DiscardData();    
    
	FILE *src ;
	src = fopen( filename, "r") ;

	fseek( src, 0L, SEEK_END ) ;
	(*resultSize) = ftell(src) ;
	fseek( src, 0L, SEEK_SET ) ;

	int read = fread( destData, 1, (*resultSize), src ) ;
   
     unlink( filename );
}
