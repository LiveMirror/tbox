/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		charset.c
 * @ingroup 	charset
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "charset.h"
#include "../algorithm/algorithm.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the charset type
typedef struct __tb_charset_t
{
	// the charset type
	tb_size_t 			type;

	// the charset name
	tb_char_t const* 	name;

	/* get ucs4 character
	 *
	 * return: -1, 0 or 1
	 *
	 * -1: 	failed, break it
	 * 0: 	no character, skip and continue it
	 * 1: 	ok, continue it
	 */
	tb_long_t 			(*get)(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);

	/* set ucs4 character
	 *
	 * return: -1, 0 or 1
	 *
	 * -1: 	failed, break it
	 * 0: 	no character, skip and continue it
	 * 1: 	ok, continue it
	 */
	tb_long_t 			(*set)(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

}tb_charset_t;

/* ///////////////////////////////////////////////////////////////////////
 * declaration
 */

// ascii
tb_long_t tb_charset_ascii_get(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);
tb_long_t tb_charset_ascii_set(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

// utf8
tb_long_t tb_charset_utf8_get(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);
tb_long_t tb_charset_utf8_set(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

// utf16
tb_long_t tb_charset_utf16_get(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);
tb_long_t tb_charset_utf16_set(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

// ucs4
tb_long_t tb_charset_ucs4_get(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);
tb_long_t tb_charset_ucs4_set(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

// gb2312
tb_long_t tb_charset_gb2312_get(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t* ch);
tb_long_t tb_charset_gb2312_set(tb_bstream_t* bst, tb_bool_t be, tb_uint32_t ch);

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// the charsets, @note: type & name is sorted
static tb_charset_t g_charsets[] =
{
	{TB_CHARSET_TYPE_ASCII, 	"ascii", 	tb_charset_ascii_get, 	tb_charset_ascii_set 	}
,	{TB_CHARSET_TYPE_GB2312, 	"gb2312", 	tb_charset_gb2312_get, 	tb_charset_gb2312_set 	}
,	{TB_CHARSET_TYPE_GBK, 		"gbk", 		tb_charset_gb2312_get, 	tb_charset_gb2312_set 	}
,	{TB_CHARSET_TYPE_UCS4, 		"ucs4", 	tb_charset_ucs4_get, 	tb_charset_ucs4_set 	}
,	{TB_CHARSET_TYPE_UTF16, 	"utf16", 	tb_charset_utf16_get, 	tb_charset_utf16_get 	}
,	{TB_CHARSET_TYPE_UTF8, 		"utf8", 	tb_charset_utf8_get, 	tb_charset_utf8_get 	}
};

/* ///////////////////////////////////////////////////////////////////////
 * finder
 */
static tb_long_t tb_charset_comp_by_name(tb_iterator_t* iterator, tb_cpointer_t item, tb_cpointer_t name)
{
	// check
	tb_assert_return_val(item, 0);

	// comp
	return tb_stricmp(((tb_charset_t const*)item)->name, name);
}
static tb_long_t tb_charset_comp_by_type(tb_iterator_t* iterator, tb_cpointer_t item, tb_cpointer_t type)
{
	// check
	tb_assert_return_val(item && type, 0);

	// comp
	return (tb_long_t)((tb_charset_t const*)item)->type - (tb_long_t)type;
}
static tb_charset_t const* tb_charset_find_by_name(tb_char_t const* name)
{
	// init iterator
	tb_iterator_t 	iterator = tb_iterator_mem(g_charsets, tb_arrayn(g_charsets), sizeof(tb_charset_t));
	iterator.comp = tb_charset_comp_by_name;

	// find it by the binary search
	tb_size_t 		itor = tb_binary_find_all(&iterator, name);

	// ok?
	if (itor != tb_iterator_tail(&iterator))
		return (tb_charset_t const*)tb_iterator_item(&iterator, itor);
	else return tb_null;
}
static tb_charset_t const* tb_charset_find_by_type(tb_size_t type)
{
	// init iterator
	tb_iterator_t 	iterator = tb_iterator_mem(g_charsets, tb_arrayn(g_charsets), sizeof(tb_charset_t));
	iterator.comp = tb_charset_comp_by_type;

	// find it by the binary search
	tb_size_t 		itor = tb_binary_find_all(&iterator, (tb_cpointer_t)TB_CHARSET_TYPE(type));

	// ok?
	if (itor != tb_iterator_tail(&iterator))
		return (tb_charset_t const*)tb_iterator_item(&iterator, itor);
	else return tb_null;
}
/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_char_t const* tb_charset_name(tb_size_t type)
{
	// find
	tb_charset_t const* charset = tb_charset_find_by_type(type);
	tb_assert_and_check_return_val(charset, tb_null);

	// type
	return charset->name;
}
tb_size_t tb_charset_type(tb_char_t const* name)
{
	// find
	tb_charset_t const* charset = tb_charset_find_by_name(name);
	tb_assert_and_check_return_val(charset, TB_CHARSET_TYPE_NONE);

	// type
	return charset->type;
}
tb_long_t tb_charset_conv_bst(tb_size_t ftype, tb_size_t ttype, tb_bstream_t* fst, tb_bstream_t* tst)
{
	// check
	tb_assert_and_check_return_val(TB_CHARSET_TYPE_OK(ftype) && TB_CHARSET_TYPE_OK(ttype) && fst && tst, -1);
	tb_assert_and_check_return_val(tb_bstream_valid(fst) && tb_bstream_valid(tst), -1);

	// init the charset
	tb_charset_t const* fr = tb_charset_find_by_type(ftype);
	tb_charset_t const* to = tb_charset_find_by_type(ttype);
	tb_assert_and_check_return_val(fr && to && fr->get && fr->set, -1);

	// big endian?
	tb_bool_t fbe = !(ftype & TB_CHARSET_TYPE_LE)? tb_true : tb_false;
	tb_bool_t tbe = !(ttype & TB_CHARSET_TYPE_LE)? tb_true : tb_false;

	// walk
	tb_uint32_t 		ch;
	tb_long_t 			cn = 0;
	tb_byte_t const* 	tp = tb_bstream_pos(tst);
	while (tb_bstream_left(fst) && tb_bstream_left(tst))
	{
		// get ucs4 character
		tb_long_t ok = 0;
		if ((ok = fr->get(fst, fbe, &ch)) > 0)
		{
			// set ucs4 character
			if (to->set(tst, tbe, ch) < 0) break;
		}
		else if (ok < 0) break;
	}

	// ok?
	return tb_bstream_pos(tst) - tp;
}
tb_long_t tb_charset_conv_cstr(tb_size_t ftype, tb_size_t ttype, tb_char_t const* cstr, tb_byte_t* data, tb_size_t size)
{
	// check
	tb_assert_and_check_return_val(TB_CHARSET_TYPE_OK(ftype) && TB_CHARSET_TYPE_OK(ttype) && cstr && data && size, -1);

	// conv
	return tb_charset_conv_data(ftype, ttype, (tb_byte_t const*)cstr, tb_strlen(cstr), data, size);
}
tb_long_t tb_charset_conv_data(tb_size_t ftype, tb_size_t ttype, tb_byte_t const* idata, tb_size_t isize, tb_byte_t* odata, tb_size_t osize)
{
	// check
	tb_assert_and_check_return_val(TB_CHARSET_TYPE_OK(ftype) && TB_CHARSET_TYPE_OK(ttype) && idata && isize && odata && osize, -1);

	// init bstream
	tb_bstream_t ist;
	tb_bstream_t ost;
	tb_bstream_attach(&ist, idata, isize);
	tb_bstream_attach(&ost, odata, osize);

	// conv
	return tb_charset_conv_bst(ftype, ttype, &ist, &ost);
}
