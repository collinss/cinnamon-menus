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

/**
 * SECTION:gmenutreedirectory
 * @Short_description: A hierarchical representation of a category or subcategory
 * @Title: GMenuTreeDirectory
 *
 * The #GMenuTreeDirectory class gives access to information about the associated
 * category, including name and icon. It also holds a reference to all of the
 * category's direct children, including subdirectories and desktop entries.
 */

#include "gmenu-tree-directory.h"
#include "gmenu-tree-directory-private.h"
#include <stdio.h>

struct _GMenuTreeDirectory
{
    GMenuTreeItem   *parent;

    DesktopEntry    *directory_entry;
    char            *name;

    GSList  *entries;
    GSList  *subdirs;
    GSList  *contents;

    guint   only_unallocated : 1;
    guint   is_nodisplay : 1;
    guint   preprocessed : 1;
};

GMenuTreeItemType
directory_get_item_type (GMenuTreeItem *item)
{
    return GMENU_TREE_ITEM_DIRECTORY;
}

GMenuTreeItem *
directory_get_parent (GMenuTreeItem *item)
{
    GMenuTreeDirectory *directory = GMENU_TREE_DIRECTORY (item);

    return directory->parent;
}

static void
gmenu_tree_item_init (GMenuTreeItemInterface *iface)
{
    iface->get_item_type = directory_get_item_type;
    iface->get_parent = directory_get_parent;
}

G_DEFINE_TYPE_WITH_CODE (GMenuTreeDirectory, gmenu_tree_directory, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GMENU_TYPE_TREE_ITEM,
                                                gmenu_tree_item_init))

const char *
gmenu_tree_directory_get_name (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  if (!directory->directory_entry)
    return directory->name;

  return desktop_entry_get_name (directory->directory_entry);
}

const char *
gmenu_tree_directory_get_generic_name (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  if (!directory->directory_entry)
    return NULL;

  return desktop_entry_get_generic_name (directory->directory_entry);
}

const char *
gmenu_tree_directory_get_comment (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  if (!directory->directory_entry)
    return NULL;

  return desktop_entry_get_comment (directory->directory_entry);
}

/**
 * gmenu_tree_directory_get_icon:
 * @directory: a #GMenuTreeDirectory
 *
 * Gets the icon for the directory.
 *
 * Returns: (transfer none): The #GIcon for this directory
 */
GIcon *
gmenu_tree_directory_get_icon (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  if (!directory->directory_entry)
    return NULL;

  return desktop_entry_get_icon (directory->directory_entry);
}

const char *
gmenu_tree_directory_get_desktop_file_path (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  if (!directory->directory_entry)
    return NULL;

  return desktop_entry_get_path (directory->directory_entry);
}

const char *
gmenu_tree_directory_get_menu_id (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, NULL);

  return directory->name;
}

gboolean
gmenu_tree_directory_get_is_nodisplay (GMenuTreeDirectory *directory)
{
  g_return_val_if_fail (directory != NULL, FALSE);

  return directory->is_nodisplay;
}

void
gmenu_tree_directory_set_is_nodisplay (GMenuTreeDirectory *directory,
                                       gboolean            nodisplay)
{
    directory->is_nodisplay = nodisplay;
}

static void
append_directory_path (GMenuTreeDirectory *directory,
               GString            *path)
{
    if (!gmenu_tree_item_get_parent (GMENU_TREE_ITEM (directory)))
    {
        g_string_append_c (path, G_DIR_SEPARATOR);
        return;
    }

    append_directory_path (GMENU_TREE_DIRECTORY (gmenu_tree_item_get_parent (GMENU_TREE_ITEM (directory))), path);

    g_string_append (path, directory->name);
    g_string_append_c (path, G_DIR_SEPARATOR);
}

static void
gmenu_tree_directory_init (GMenuTreeDirectory *directory)
{
    directory->directory_entry     = NULL;
    directory->entries             = NULL;
    directory->subdirs             = NULL;
    directory->contents            = NULL;
    directory->only_unallocated    = FALSE;
    directory->is_nodisplay        = FALSE;
    directory->preprocessed        = FALSE;
}

static void
gmenu_tree_directory_class_init (GMenuTreeDirectoryClass *klass)
{
    GObjectClass *gobject_class = (GObjectClass *)klass;
}

GMenuTreeDirectory *
gmenu_tree_directory_new (GMenuTreeDirectory *parent,
                          const char         *name)
{
    GMenuTreeDirectory *retval;

    retval = g_object_new (GMENU_TYPE_TREE_DIRECTORY, NULL);

    if (parent != NULL)
        retval->parent = GMENU_TREE_ITEM (parent);

    retval->name = g_strdup (name);

    return retval;
}

static void
gmenu_tree_directory_finalize (GMenuTreeDirectory *directory)
{
    g_slist_free (directory->contents);
    directory->contents = NULL;

    // g_slist_foreach (directory->subdirs,
    //        (GFunc) gmenu_tree_item_unref_and_unset_parent,
    //        NULL);
    g_slist_free (directory->subdirs);
    directory->subdirs = NULL;

    // g_slist_foreach (directory->entries,
    //        (GFunc) gmenu_tree_item_unref_and_unset_parent,
    //        NULL);
    g_slist_free (directory->entries);
    directory->entries = NULL;

    if (directory->directory_entry)
    desktop_entry_unref (directory->directory_entry);
    directory->directory_entry = NULL;

    g_free (directory->name);
    directory->name = NULL;
}

GSList *
gmenu_tree_directory_get_contents (GMenuTreeDirectory *directory)
{
    return g_slist_copy (directory->contents);
}

void
gmenu_tree_directory_set_contents (GMenuTreeDirectory *directory,
                                   GSList             *contents)
{
    directory->contents = contents;
}

void
gmenu_tree_directory_contents_append (GMenuTreeDirectory *directory,
                                      GMenuTreeItem      *item)
{
    directory->contents = g_slist_append (directory->contents, item);
}

GSList *
gmenu_tree_directory_get_entries (GMenuTreeDirectory *directory)
{
    return g_slist_copy (directory->entries);
}

void
gmenu_tree_directory_set_entries (GMenuTreeDirectory *directory,
                                  GSList             *entries)
{
    directory->entries = entries;
}

void
gmenu_tree_directory_entries_append (GMenuTreeDirectory *directory,
                                     GMenuTreeItem      *item)
{
    directory->entries = g_slist_append (directory->entries, item);
}

GSList *
gmenu_tree_directory_get_subdirs (GMenuTreeDirectory *directory)
{
    return g_slist_copy (directory->subdirs);
}

void
gmenu_tree_directory_set_subdirs (GMenuTreeDirectory *directory,
                                  GSList             *subdirs)
{
    directory->subdirs = subdirs;
}

void
gmenu_tree_directory_subdirs_append (GMenuTreeDirectory *directory,
                                     GMenuTreeDirectory *subdir)
{
    directory->subdirs = g_slist_append (directory->subdirs, subdir);
}

DesktopEntry *
gmenu_tree_directory_get_directory_entry (GMenuTreeDirectory *directory)
{
    return directory->directory_entry;
}

void
gmenu_tree_directory_set_directory_entry (GMenuTreeDirectory *directory,
                                              DesktopEntry       *entry)
{
    if (directory->directory_entry)
        desktop_entry_unref (directory->directory_entry);
    directory->directory_entry = entry;
}
