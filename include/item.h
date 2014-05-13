/* item.h */

#ifndef __ITEM_H__
#define __ITEM_H__

//! The ItemType enum
/*!
	A list of types an Item object may have.
*/
typedef enum{
	ItemTypeFood,
	ItemTypeClothing,
	ItemTypeData
} ItemType;

//! The Item structure
/*!
	An Item object which represents an interactive, non-character.
*/
typedef struct _Item {
	char name[256];
	char description[1024];
	ItemType type;
} Item;

#endif
