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

#ifndef __GMENU_TREE_DIRECTORY_H__
#define __GMENU_TREE_DIRECTORY_H__

#include <glib-object.h>
#include <gio/gdesktopappinfo.h>

#include "gmenu-tree-item.h"

G_BEGIN_DECLS

#define GMENU_TYPE_TREE_DIRECTORY         (gmenu_tree_directory_get_type ())

G_DECLARE_FINAL_TYPE (GMenuTreeDirectory, gmenu_tree_directory, GMENU, TREE_DIRECTORY, GObject)

const char*    gmenu_tree_directory_get_name              (GMenuTreeDirectory *directory);
const char*    gmenu_tree_directory_get_generic_name      (GMenuTreeDirectory *directory);
const char*    gmenu_tree_directory_get_comment           (GMenuTreeDirectory *directory);
GIcon*         gmenu_tree_directory_get_icon              (GMenuTreeDirectory *directory);
const char*    gmenu_tree_directory_get_desktop_file_path (GMenuTreeDirectory *directory);
const char*    gmenu_tree_directory_get_menu_id           (GMenuTreeDirectory *directory);

gboolean       gmenu_tree_directory_get_is_nodisplay      (GMenuTreeDirectory *directory);

G_END_DECLS

#endif /* __GMENU_TREE_DIRECTORY_H__ */
