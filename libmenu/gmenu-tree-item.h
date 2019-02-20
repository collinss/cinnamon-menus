/*
 * Copyright (C) 2004, 2011 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GMENU_TREE_ITEM_H__
#define __GMENU_TREE_ITEM_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum
{
    GMENU_TREE_ITEM_INVALID = 0,
    GMENU_TREE_ITEM_DIRECTORY,
    GMENU_TREE_ITEM_ENTRY,

    // the following are kept for backwards compatibility, but are no longer used
    GMENU_TREE_ITEM_SEPARATOR,
    GMENU_TREE_ITEM_HEADER,
    GMENU_TREE_ITEM_ALIAS
} GMenuTreeItemType;

G_DECLARE_INTERFACE(GMenuTreeItem, gmenu_tree_item, GMENU, TREE_ITEM, GObject)

#define GMENU_TYPE_TREE_ITEM (gmenu_tree_item_get_type ())

struct _GMenuTreeItemInterface
{
    GTypeInterface parent;

    GMenuTreeItemType   (*get_item_type)    (GMenuTreeItem *item);
    GMenuTreeItem *     (*get_parent)       (GMenuTreeItem *item);
};

GMenuTreeItemType   gmenu_tree_item_get_item_type   (GMenuTreeItem *item);
GMenuTreeItem *     gmenu_tree_item_get_parent      (GMenuTreeItem *item);

G_END_DECLS

#endif /* __GMENU_TREE_ITEM_H__ */
