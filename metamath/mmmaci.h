#ifndef MMMACHI_H_
#define MMMACHI_H_

/*****************************************************************************/
/*        Copyright (C) 2005  NORMAN MEGILL  nm at alum.mit.edu              */
/*            License terms:  GNU General Public License                     */
/*****************************************************************************/
/*34567890123456 (79-character line to adjust editor window) 2345678901234567*/

/***********************************/
/*  Macintosh interface functions  */
/***********************************/

void ToolBoxInit(void);
void WindowInit(void);
void DrawMyPicture(void);

#ifdef THINK_C
void CenterPict(PicHandle picture, Rect *destRectPtr);
#endif

#endif /*MMMACHI_H_*/
