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

#ifndef __GMENU_TREE_ENTRY_H__
#define __GMENU_TREE_ENTRY_H__

#include <glib-object.h>

#include "gmenu-tree-item.h"
#include "gmenu-tree-directory.h"
#include "desktop-entries.h"

G_BEGIN_DECLS

#define GMENU_TYPE_TREE_ENTRY         (gmenu_tree_entry_get_type ())

G_DECLARE_FINAL_TYPE (GMenuTreeEntry, gmenu_tree_entry, GMENU, TREE_ENTRY, GObject)

GDesktopAppInfo    *gmenu_tree_entry_get_app_info           (GMenuTreeEntry *entry);

const char     *gmenu_tree_entry_get_desktop_file_path      (GMenuTreeEntry *entry);
const char     *gmenu_tree_entry_get_desktop_file_id        (GMenuTreeEntry *entry);

gboolean        gmenu_tree_entry_get_is_nodisplay_recurse   (GMenuTreeEntry *entry);
gboolean        gmenu_tree_entry_get_is_excluded            (GMenuTreeEntry *entry);
gboolean        gmenu_tree_entry_get_is_unallocated         (GMenuTreeEntry *entry);

G_END_DECLS

#endif /* __GMENU_TREE_ENTRY_H__ */
