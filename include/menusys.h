#ifndef __MENUSYS_H
#define __MENUSYS_H

#include "include/texcache.h"

/// a single submenu item
typedef struct submenu_item {
	/// Icon used for rendering of this item
	int icon_id;
	
	/// item description
	char *text;
	
	/// item description in localized form (used if value is not negative)
	int text_id;
	
	/// item id
	int id;
	
	int cache_id[3];
	int cache_uid[3];
} submenu_item_t;

typedef struct submenu_list {
	struct submenu_item item;
	
	struct submenu_list *prev, *next;
} submenu_list_t;

typedef struct menu_hint_item {
	int icon_id;
	int text_id;
	
	struct menu_hint_item *next;
} menu_hint_item_t;

/// a single menu item. Linked list impl (for the ease of rendering)
typedef struct menu_item {
	/// Icon used for rendering of this item
	int icon_id;
	
	/// item description
	char *text;
	
	/// item description in localised form (used if value is not negative)
	int text_id;
	
	void *userdata;
	
	/// submenu, selection and page start (only used in static mode)
	struct submenu_list *submenu, *current, *pagestart;
	
	void (*refresh)(struct menu_item *self);

	void (*execCross)(struct menu_item *self, int id);
	
	void (*execTriangle)(struct menu_item *self, int id);

	void (*execCircle)(struct menu_item *self, int id);
	
	void (*execSquare)(struct menu_item *self, int id);
	
	/// hint list
	struct menu_hint_item *hints;
} menu_item_t;

typedef struct menu_list {
	struct menu_item *item;
	
	struct menu_list *prev, *next;
} menu_list_t;

void menuInit();
void menuEnd();

void menuAppendItem(menu_item_t* item);

submenu_list_t* submenuAppendItem(submenu_list_t** submenu, int icon_id, char *text, int id, int text_id);
void submenuRemoveItem(submenu_list_t** submenu, int id);
void submenuDestroy(submenu_list_t** submenu);
void submenuSort(submenu_list_t** submenu);

/// Get the text of the item (considers localised version of the string)
char *submenuItemGetText(submenu_item_t* it);

void menuDrawStatic();

void menuNextH();
void menuPrevH();
void menuNextV();
void menuPrevV();
void menuNextPage();
void menuPrevPage();
void menuFirstPage();
void menuLastPage();
menu_item_t* menuGetCurrent();
GSTEXTURE* menuGetCurrentArt();
void menuItemExecButton(void (*execActionButton)(menu_item_t *self, int id));

// Sets the selected item if it is found in the menu list
void menuSetSelectedItem(menu_item_t *item);

void menuAddHint(menu_item_t *menu, int text_id, int icon_id);
void menuRemoveHints(menu_item_t *menu);
void menuInitHints(menu_item_t *menu);

#endif
