/*
 *  ifmetabase.h
 *  ZoomCocoa
 *
 *  Created by Andrew Hunter on 14/03/2005
 *  Copyright 2005 Andrew Hunter. All rights reserved.
 */

#ifndef __IFMETABASE_H
#define __IFMETABASE_H

/*
 * The metabase is a set of functions designed for creating and manipulating metadata in the
 * 'iFiction' format. It deals with the metadata in an abstract sense: this library does not
 * define the external format of the data.
 */

/* Data structures */

typedef unsigned short IFChar;						/* A UTF-16 character */

typedef struct IFMetabase* IFMetabase;				/* A metabase */
typedef struct IFID* IFID;							/* A story identifier */
typedef struct IFStory* IFStory;					/* A story entry in the metabase */

typedef struct IFStoryIterator* IFStoryIterator;	/* An iterator that covers all stories */
typedef struct IFValueIterator* IFValueIterator;	/* An iterator that covers the values set for a story */

/* Functions - general metabase manipulation */

/* Constructs a new, empty metabase */
extern IFMetabase IFMB_Create();

/* Frees up all the memory associated with a metabase */
extern void IFMB_Free(IFMetabase meta);

/* Functions - IFIDs */

/* Takes an ID string and produces a corresponding IFID structure, or NULL if the string is invalid */
extern IFID IFMB_IdFromString(const char* idString);

/* Returns an IFID based on the 16-byte UUID passed as an argument */
extern IFID IFMB_UUID(const char* uuid);

/* Returns an IFID based on a Z-Code legacy identifier */
extern IFID IFMB_ZcodeId(int release, const char* serial, int checksum);

/* Merges a set of IFIDs into a single ID */
extern IFID IFMB_CompoundId(int count, IFID identifiers);

/* Compares two IDs */
extern int IFMB_CompareIds(IFID a, IFID b);

/* Frees an ID */
extern void IFMB_FreeId(IFID ident);

/* Copies an ID */
extern IFID IFMB_CopyId(IFID ident);

/* Functions - stories */

/* Retrieves the story in the metabase with the given ID */
extern IFStory IFMB_GetStoryWithId(IFMetabase meta, IFID ident);

/* Retrieves the ID associated with a given story object */
extern IFID IFMB_IdForStory(IFStory story);

/* Removes a story with the given ID from the metabase */
extern IFID IFMB_RemoveStoryWithId(IFID ident);

/* Returns non-zero if the metabase contains a story with a given ID */
extern int IFMB_ContainsStoryWithId(IFID ident);

/* Returns a UTF-16 string for a given parameter in a story, or NULL if none was found */
/* Copy this value away if you intend to retain it: it may be destroyed on the next IFMB_ call */
extern IFChar* IFMB_GetValue(IFStory story, const char* valueKey);

/* Sets the UTF-16 string for a given parameter in the story (NULL to unset the parameter) */
extern void IFMB_SetValue(IFStory story, const char* valueKey, IFChar* utf16value);

/* Functions - iterating */

/* Gets an iterator covering all the stories in the given metabase */
extern IFStoryIterator IFMB_GetStoryIterator(IFMetabase meta);

/* Gets an iterator covering all the values set in a story */
extern IFValueIterator IFMB_GetValueIterator(IFStory story);

/* Gets the next story defined in the metabase */
extern IFStory IFMB_NextStory(IFStoryIterator iter);

/* Gets the next value set in a story */
extern char* IFMB_NextValue(IFValueIterator iter);

/* Functions - basic UTF-16 string manipulation */

extern int IFMB_StrCmp(const IFChar* a, const IFChar* b);
extern void IFMB_StrCpy(IFChar* a, const IFChar* b);

#endif
