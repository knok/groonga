/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2013 Brazil

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License version 2.1 as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GRN_EXPR_H
#define GRN_EXPR_H

#include "db.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCAN_ACCESSOR                  (0x01)
#define SCAN_PUSH                      (0x02)
#define SCAN_POP                       (0x04)
#define SCAN_PRE_CONST                 (0x08)

typedef enum {
  SCAN_START = 0,
  SCAN_VAR,
  SCAN_COL1,
  SCAN_COL2,
  SCAN_CONST
} scan_stat;

typedef struct _grn_scan_info scan_info;
typedef grn_bool (*grn_scan_info_each_arg_callback)(grn_ctx *ctx, grn_obj *obj, void *user_data);

scan_info *grn_scan_info_open(grn_ctx *ctx, int start);
void grn_scan_info_close(grn_ctx *ctx, scan_info *si);
void grn_scan_info_put_index(grn_ctx *ctx, scan_info *si, grn_obj *index,
                             uint32_t sid, int32_t weight);
scan_info **grn_scan_info_put_logical_op(grn_ctx *ctx, scan_info **sis, int *ip,
                                         grn_operator op, int start);
int grn_scan_info_get_flags(scan_info *si);
void grn_scan_info_set_flags(scan_info *si, int flags);
grn_operator grn_scan_info_get_logical_op(scan_info *si);
void grn_scan_info_set_logical_op(scan_info *si, grn_operator logical_op);
grn_operator grn_scan_info_get_op(scan_info *si);
void grn_scan_info_set_op(scan_info *si, grn_operator op);
void grn_scan_info_set_end(scan_info *si, uint32_t end);
void grn_scan_info_set_query(scan_info *si, grn_obj *query);
int grn_scan_info_get_max_interval(scan_info *si);
void grn_scan_info_set_max_interval(scan_info *si, int max_interval);
grn_bool grn_scan_info_push_arg(scan_info *si, grn_obj *arg);
grn_obj *grn_scan_info_get_arg(grn_ctx *ctx, scan_info *si, int i);

int32_t grn_expr_code_get_weight(grn_ctx *ctx, grn_expr_code *ec);
grn_rc grn_expr_get_keywords(grn_ctx *ctx, grn_obj *expr, grn_obj *keywords);

#ifdef __cplusplus
}
#endif

#endif /* GRN_EXPR_H */
