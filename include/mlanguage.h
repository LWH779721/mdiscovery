/*  
 *  @discription: define some new syntax for c language 
 *  @author:  lwh
 *  @date:  2017/07/12
 */
#ifndef __M_LANGUAGE_H__
#define __M_LANGUAGE_H__

#ifdef __Cplusplus
extern "C"{
#endif

#ifndef elif
#define elif    else if 
#endif

#define uint8   unsigned char
#define int8    char
#define uint16  unsigned short
#define int16   short
#define uint32  unsigned int
#define int32   int

#ifdef __Cplusplus
}
#endif

#endif