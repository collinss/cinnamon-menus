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

#ifndef __GMENU_TREE_DIRECTORY_PRIV_H__
#define __GMENU_TREE_DIRECTORY_PRIV_H__

#include "gmenu-tree-directory.h"
#include "desktop-entries.h"
#include "menu-layout.h"

GSList*         gmenu_tree_directory_get_contents             (GMenuTreeDirectory *directory);
void            gmenu_tree_directory_set_contents             (GMenuTreeDirectory *directory,
                                                               GSList             *contents);
void            gmenu_tree_directory_contents_append          (GMenuTreeDirectory *directory,
                                                               GMenuTreeItem      *item);

GSList*         gmenu_tree_directory_get_entries              (GMenuTreeDirectory *directory);
void            gmenu_tree_directory_set_entries              (GMenuTreeDirectory *directory,
                                                               GSList             *entries);
void            gmenu_tree_directory_entries_append           (GMenuTreeDirectory *directory,
                                                               GMenuTreeItem      *item);

GSList*         gmenu_tree_directory_get_subdirs              (GMenuTreeDirectory *directory);
void            gmenu_tree_directory_set_subdirs              (GMenuTreeDirectory *directory,
                                                               GSList             *subdirs);
void            gmenu_tree_directory_subdirs_append           (GMenuTreeDirectory *directory,
                                                               GMenuTreeDirectory *subdir);

DesktopEntry *  gmenu_tree_directory_get_directory_entry      (GMenuTreeDirectory *directory);
void            gmenu_tree_directory_set_directory_entry      (GMenuTreeDirectory *directory,
                                                               DesktopEntry       *entry);

void            gmenu_tree_directory_set_is_nodisplay         (GMenuTreeDirectory *directory,
                                                               gboolean            nodisplay);

GMenuTreeDirectory *gmenu_tree_directory_new                  (GMenuTreeDirectory *parent,
                                                               const char         *name);

#endif /* __GMENU_TREE_DIRECTORY_PRIV_H__ */
