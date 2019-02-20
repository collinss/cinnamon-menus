/* -*- mode:c; c-file-style: "gnu"; indent-tabs-mode: nil -*-
 * Copyright (C) 2003, 2004, 2011 Red Hat, Inc.
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

#include <config.h>

#include "gmenu-tree-item.h"

G_DEFINE_INTERFACE (GMenuTreeItem, gmenu_tree_item, G_TYPE_OBJECT);

GMenuTreeItemType
gmenu_tree_item_get_item_type (GMenuTreeItem *item)
{
    GMenuTreeItemInterface *iface = GMENU_TREE_ITEM_GET_IFACE (item);
    return iface->get_item_type (item);
}

/**
 * gmenu_tree_item_get_parent:
 * @item: a #GMenuTreeItem
 *
 * Gets the parent directory.
 *
 * Returns: (transfer full): The #GMenuTreeItem parent for this item
 */
GMenuTreeItem *
gmenu_tree_item_get_parent (GMenuTreeItem *item)
{
    GMenuTreeItemInterface *iface = GMENU_TREE_ITEM_GET_IFACE (item);
    return g_object_ref (iface->get_parent (item));
}

static void
gmenu_tree_item_default_init (GMenuTreeItemInterface *iface)
{
}
