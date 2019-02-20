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

#ifndef __GMENU_TREE_H__
#define __GMENU_TREE_H__

#ifndef GMENU_I_KNOW_THIS_IS_UNSTABLE
#error "libgnome-menu should only be used if you understand that it's subject to frequent change, and is not supported as a fixed API/ABI or as part of the platform"
#endif

#include <gio/gdesktopappinfo.h>

#include "gmenu-tree-item.h"
#include "gmenu-tree-directory.h"
#include "gmenu-tree-entry.h"

G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE (GMenuTree, gmenu_tree, GMENU, TREE, GObject)

#define GMENU_TYPE_TREE         (gmenu_tree_get_type ())

typedef struct GMenuTreeIter      GMenuTreeIter;

GType gmenu_tree_iter_get_type (void);

typedef enum
{
  GMENU_TREE_FLAGS_NONE                = 0,
  GMENU_TREE_FLAGS_INCLUDE_EXCLUDED    = 1 << 0,
  GMENU_TREE_FLAGS_INCLUDE_NODISPLAY   = 1 << 1,
  GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED = 1 << 2,
  /* leave some space for more include flags */
  GMENU_TREE_FLAGS_SHOW_EMPTY          = 1 << 8,
  GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS = 1 << 9,
  /* leave some space for more show flags */
  GMENU_TREE_FLAGS_SORT_DISPLAY_NAME   = 1 << 16
} GMenuTreeFlags;

GType gmenu_tree_flags_get_type (void);
#define GMENU_TYPE_TREE_FLAGS (gmenu_tree_flags_get_type ())

GMenuTree *gmenu_tree_new (const char     *menu_basename,
                           GMenuTreeFlags  flags);

GMenuTree *gmenu_tree_new_for_path (const char     *menu_path,
                                    GMenuTreeFlags  flags);

gboolean   gmenu_tree_load_sync (GMenuTree  *tree,
                                 GError    **error);

const char         *gmenu_tree_get_canonical_menu_path (GMenuTree  *tree);
GMenuTreeDirectory *gmenu_tree_get_root_directory      (GMenuTree  *tree);
GMenuTreeDirectory *gmenu_tree_get_directory_from_path (GMenuTree  *tree,
							const char *path);
GMenuTreeEntry     *gmenu_tree_get_entry_by_id         (GMenuTree  *tree,
							const char *id);

GMenuTreeIter      *gmenu_tree_iter_ref                  (GMenuTreeIter *iter);
void                gmenu_tree_iter_unref                (GMenuTreeIter *iter);

GMenuTreeItemType   gmenu_tree_iter_next                 (GMenuTreeIter *iter);
GMenuTreeDirectory *gmenu_tree_iter_get_directory        (GMenuTreeIter *iter);
GMenuTreeEntry     *gmenu_tree_iter_get_entry            (GMenuTreeIter *iter);
// GMenuTreeHeader    *gmenu_tree_iter_get_header           (GMenuTreeIter *iter);
// GMenuTreeAlias     *gmenu_tree_iter_get_alias            (GMenuTreeIter *iter);
// GMenuTreeSeparator *gmenu_tree_iter_get_separator        (GMenuTreeIter *iter);

G_END_DECLS

#endif /* __GMENU_TREE_H__ */
