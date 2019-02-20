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

#include "gmenu-tree-entry.h"
#include "gmenu-tree-entry-private.h"

struct _GMenuTreeEntry
{
    GMenuTreeItem   *parent;

    DesktopEntry    *desktop_entry;
    char            *desktop_file_id;

    guint            is_excluded : 1;
    guint            is_unallocated : 1;
};

GMenuTreeItemType
entry_get_item_type (GMenuTreeItem *item)
{
    return GMENU_TREE_ITEM_ENTRY;
}

GMenuTreeItem *
entry_get_parent (GMenuTreeItem *item)
{
    GMenuTreeEntry *entry = GMENU_TREE_ENTRY (item);

    return entry->parent;
}

static void
gmenu_tree_item_init (GMenuTreeItemInterface *iface)
{
    iface->get_item_type = entry_get_item_type;
    iface->get_parent = entry_get_parent;
}

G_DEFINE_TYPE_WITH_CODE (GMenuTreeEntry, gmenu_tree_entry, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GMENU_TYPE_TREE_ITEM,
                                                gmenu_tree_item_init))

/**
 * gmenu_tree_entry_get_app_info:
 * @entry: a #GMenuTreeEntry
 *
 * Returns: (transfer none): The #GDesktopAppInfo for this entry
 */
GDesktopAppInfo *
gmenu_tree_entry_get_app_info (GMenuTreeEntry *entry)
{
    g_return_val_if_fail (entry != NULL, NULL);

    return desktop_entry_get_app_info (entry->desktop_entry);
}

const char *
gmenu_tree_entry_get_desktop_file_path (GMenuTreeEntry *entry)
{
    g_return_val_if_fail (entry != NULL, NULL);

    return desktop_entry_get_path (entry->desktop_entry);
}

const char *
gmenu_tree_entry_get_desktop_file_id (GMenuTreeEntry *entry)
{
    g_return_val_if_fail (entry != NULL, NULL);

    return entry->desktop_file_id;
}

gboolean
gmenu_tree_entry_get_is_nodisplay_recurse (GMenuTreeEntry *entry)
{
    GMenuTreeDirectory *directory;
    GDesktopAppInfo *app_info;

    g_return_val_if_fail (entry != NULL, FALSE);

    app_info = gmenu_tree_entry_get_app_info (entry);

    if (g_desktop_app_info_get_nodisplay (app_info))
        return TRUE;

    directory = GMENU_TREE_DIRECTORY (gmenu_tree_item_get_parent (GMENU_TREE_ITEM (entry)));

    while (directory != NULL)
    {
        if (gmenu_tree_directory_get_is_nodisplay (directory))
            return TRUE;

        directory = GMENU_TREE_DIRECTORY (gmenu_tree_item_get_parent (GMENU_TREE_ITEM (directory)));
    }

    return FALSE;
}

gboolean
gmenu_tree_entry_get_is_excluded (GMenuTreeEntry *entry)
{
    g_return_val_if_fail (entry != NULL, FALSE);

    return entry->is_excluded;
}

gboolean
gmenu_tree_entry_get_is_unallocated (GMenuTreeEntry *entry)
{
    g_return_val_if_fail (entry != NULL, FALSE);

    return entry->is_unallocated;
}

static void
gmenu_tree_entry_finalize (GMenuTreeEntry *entry)
{
    g_free (entry->desktop_file_id);
    entry->desktop_file_id = NULL;

    if (entry->desktop_entry)
        desktop_entry_unref (entry->desktop_entry);
    entry->desktop_entry = NULL;
}

int
gmenu_tree_entry_compare_by_id (GMenuTreeItem *a,
                                GMenuTreeItem *b)
{
    return strcmp (GMENU_TREE_ENTRY (a)->desktop_file_id,
                   GMENU_TREE_ENTRY (b)->desktop_file_id);
}

static void
gmenu_tree_entry_init (GMenuTreeEntry *entry)
{
}

static void
gmenu_tree_entry_class_init (GMenuTreeEntryClass *klass)
{
    GObjectClass *gobject_class = (GObjectClass *)klass;
}

GMenuTreeEntry *
gmenu_tree_entry_new (GMenuTreeDirectory *parent,
                      DesktopEntry       *desktop_entry,
                      const char         *desktop_file_id,
                      gboolean            is_excluded,
                      gboolean            is_unallocated)
{
    GMenuTreeEntry *retval;

    retval = g_object_new (GMENU_TYPE_TREE_ENTRY, NULL);

    retval->parent = GMENU_TREE_ITEM (parent);
    retval->desktop_entry   = desktop_entry_ref (desktop_entry);
    retval->desktop_file_id = g_strdup (desktop_file_id);
    retval->is_excluded     = is_excluded != FALSE;
    retval->is_unallocated  = is_unallocated != FALSE;

    return retval;
}

DesktopEntry *
gmenu_tree_entry_get_desktop_entry (GMenuTreeEntry *entry)
{
    return entry->desktop_entry;
}
