/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#define TB_SLIST_GROW_SIZE 			(256)

/* ///////////////////////////////////////////////////////////////////////
 * details
 */

static tb_size_t tb_slist_insert_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	// insert one first
	tb_size_t itor = tb_slist_insert_head(slist, 0xd);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 10000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_insert(slist, itor, 0xd);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_insert(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n + 1);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_insert_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_insert_head(slist, 0xd);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_insert_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);
	
	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_insert_tail_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_insert_tail(slist, 0xd);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_insert_tail(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_ninsert_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	// insert one first
	tb_size_t itor = tb_slist_insert_head(slist, 0xd);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_slist_ninsert(slist, itor, 0xd, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_ninsert(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n + 1);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_ninsert_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_slist_ninsert_head(slist, 0xd, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_ninsert_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_ninsert_tail_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_slist_ninsert_tail(slist, 0xd, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_ninsert_tail(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xd);
	tb_assert(tb_slist_const_at_last(slist) == 0xd);

	// clear it
	tb_slist_clear(slist);
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_remove_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) itor = tb_slist_remove(slist, itor);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_remove(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_remove_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_remove_head(slist);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_remove_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);
}
static tb_size_t tb_slist_remove_last_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 10000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_remove_last(slist);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_remove_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nremove_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nremove(slist, tb_slist_itor_head(slist), n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nremove(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nremove_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nremove_head(slist, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nremove_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nremove_last_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nremove_last(slist, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nremove_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(!tb_slist_size(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_replace_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_slist_ninsert_head(slist, 0xd, n);
	tb_size_t itor = tb_slist_itor_head(slist);
	tb_size_t tail = tb_slist_itor_tail(slist);
	tb_int64_t t = tb_mclock();
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor)) tb_slist_replace(slist, itor, 0xe);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_replace(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xe);
	tb_assert(tb_slist_const_at_last(slist) == 0xe);

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_replace_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_replace_head(slist, 0xe);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_replace_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xe);

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_replace_last_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_slist_replace_last(slist, 0xe);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_replace_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_last(slist) == 0xe);


	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nreplace_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nreplace(slist, tb_slist_itor_head(slist), 0xe, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nreplace(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xe);
	tb_assert(tb_slist_const_at_last(slist) == 0xe);

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nreplace_head_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nreplace_head(slist, 0xe, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nreplace_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xe);
	tb_assert(tb_slist_const_at_last(slist) == 0xe);

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_nreplace_last_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_slist_ninsert_head(slist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_slist_nreplace_last(slist, 0xe, n);
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_nreplace_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// check
	tb_assert(tb_slist_size(slist) == n);
	tb_assert(tb_slist_const_at_head(slist) == 0xe);
	tb_assert(tb_slist_const_at_last(slist) == 0xe);


	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}

static tb_size_t tb_slist_iterator_next_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 1000000;
	tb_slist_ninsert_head(slist, 0xd, n);
	__tb_volatile__ tb_size_t itor = tb_slist_itor_head(slist);
	__tb_volatile__ tb_size_t tail = tb_slist_itor_tail(slist);
	tb_int64_t t = tb_mclock();
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor))
	{
		__tb_volatile__ tb_byte_t const* item = tb_slist_itor_const_at(slist, itor);
	}
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_iterator_next(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_size_t tb_slist_iterator_prev_test()
{
	// init
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(slist, 0);

	tb_size_t n = 10000;
	tb_slist_ninsert_head(slist, 0xd, n);
	__tb_volatile__ tb_size_t itor = tb_slist_itor_last(slist);
	__tb_volatile__ tb_size_t head = tb_slist_itor_head(slist);
	tb_int64_t t = tb_mclock();
	while (1)
	{
		__tb_volatile__ tb_byte_t const* item = tb_slist_itor_const_at(slist, itor);

		if (itor == head) break;
		itor = tb_slist_itor_prev(slist, itor);
	}
	t = tb_mclock() - t;

	// time
	tb_print("tb_slist_iterator_prev(%d): %lld ms, size: %d, maxn: %d", n, t, tb_slist_size(slist), tb_slist_maxn(slist));

	// exit
	tb_slist_exit(slist);

	return n / ((tb_uint32_t)(t) + 1);
}
static tb_void_t tb_slist_int_dump(tb_slist_t const* slist)
{
	tb_print("int size: %d, maxn: %d", tb_slist_size(slist), tb_slist_maxn(slist));
	tb_size_t itor = tb_slist_itor_head(slist);
	tb_size_t tail = tb_slist_itor_tail(slist);
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor))
	{
		tb_char_t const* item = tb_slist_itor_const_at(slist, itor);
		tb_print("int at[%d]: %x", itor, item);
	}
}
static tb_void_t tb_slist_int_test()
{
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return(slist);

	tb_size_t 			i = 0;
	tb_size_t 			j = 0;

	tb_print("=============================================================");
	tb_print("insert:");
	tb_slist_ninsert_head(slist, 0xa, 10);
	i = tb_slist_ninsert_tail(slist, 0xf, 10);
	j = tb_slist_insert(slist, i, 0);
	tb_slist_insert(slist, i, 1);
	tb_slist_insert(slist, i, 2);
	tb_slist_insert(slist, i, 3);
	tb_slist_insert(slist, i, 4);
	tb_slist_insert(slist, i, 5);
	tb_slist_insert(slist, i, 6);
	tb_slist_insert(slist, i, 7);
	tb_slist_insert(slist, i, 8);
	tb_slist_insert(slist, i, 9);
	tb_slist_insert_head(slist, 4);
	tb_slist_insert_head(slist, 3);
	tb_slist_insert_head(slist, 2);
	tb_slist_insert_head(slist, 1);
	tb_slist_insert_head(slist, 0);
	tb_slist_insert_tail(slist, 5);
	tb_slist_insert_tail(slist, 6);
	tb_slist_insert_tail(slist, 7);
	tb_slist_insert_tail(slist, 8);
	tb_slist_insert_tail(slist, 9);
	tb_slist_int_dump(slist);

	tb_print("=============================================================");
	tb_print("remove:");
	tb_slist_nremove_head(slist, 5);
	tb_slist_nremove_last(slist, 5);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);	
	tb_slist_int_dump(slist);

	tb_print("=============================================================");
	tb_print("replace:");
	tb_slist_nreplace_head(slist, 0xf, 10);
	tb_slist_nreplace_last(slist, 0xa, 10);
	tb_slist_replace_head(slist, 0);
	tb_slist_replace_last(slist, 0);
	tb_slist_int_dump(slist);

	tb_print("=============================================================");
	tb_print("clear:");
	tb_slist_clear(slist);
	tb_slist_int_dump(slist);

	tb_slist_exit(slist);
}
static tb_void_t tb_slist_str_dump(tb_slist_t const* slist)
{
	tb_print("str size: %d, maxn: %d", tb_slist_size(slist), tb_slist_maxn(slist));
	tb_size_t itor = tb_slist_itor_head(slist);
	tb_size_t tail = tb_slist_itor_tail(slist);
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor))
	{
		tb_char_t const* item = tb_slist_itor_const_at(slist, itor);
		tb_print("str at[%d]: %s", itor, item);
	}
}
static tb_void_t tb_slist_str_test()
{
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_str(TB_TRUE, tb_spool_init(TB_SPOOL_SIZE_SMALL)));
	tb_assert_and_check_return(slist);

	tb_size_t 			i = 0;
	tb_size_t 			j = 0;

	tb_print("=============================================================");
	tb_print("insert:");
	tb_slist_ninsert_head(slist, "HHHHHHHHHH", 10);
	i = tb_slist_ninsert_tail(slist, "TTTTTTTTTT", 10);
	j = tb_slist_insert(slist, i, "0000000000");
	tb_slist_insert(slist, i, "1111111111");
	tb_slist_insert(slist, i, "2222222222");
	tb_slist_insert(slist, i, "3333333333");
	tb_slist_insert(slist, i, "4444444444");
	tb_slist_insert(slist, i, "5555555555");
	tb_slist_insert(slist, i, "6666666666");
	tb_slist_insert(slist, i, "7777777777");
	tb_slist_insert(slist, i, "8888888888");
	tb_slist_insert(slist, i, "9999999999");
	tb_slist_insert_head(slist, "4444444444");
	tb_slist_insert_head(slist, "3333333333");
	tb_slist_insert_head(slist, "2222222222");
	tb_slist_insert_head(slist, "1111111111");
	tb_slist_insert_head(slist, "0000000000");
	tb_slist_insert_tail(slist, "5555555555");
	tb_slist_insert_tail(slist, "6666666666");
	tb_slist_insert_tail(slist, "7777777777");
	tb_slist_insert_tail(slist, "8888888888");
	tb_slist_insert_tail(slist, "9999999999");
	tb_slist_str_dump(slist);

	tb_print("=============================================================");
	tb_print("remove:");
	tb_slist_nremove_head(slist, 5);
	tb_slist_nremove_last(slist, 5);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);	
	tb_slist_str_dump(slist);

	tb_print("=============================================================");
	tb_print("replace:");
	tb_slist_nreplace_head(slist, "TTTTTTTTTT", 10);
	tb_slist_nreplace_last(slist, "HHHHHHHHHH", 10);
	tb_slist_replace_head(slist, "OOOOOOOOOO");
	tb_slist_replace_last(slist, "OOOOOOOOOO");
	tb_slist_str_dump(slist);

	tb_print("=============================================================");
	tb_print("clear:");
	tb_slist_clear(slist);
	tb_slist_str_dump(slist);

	tb_slist_exit(slist);
}
static tb_void_t tb_slist_efm_dump(tb_slist_t const* slist)
{
	tb_print("efm size: %d, maxn: %d", tb_slist_size(slist), tb_slist_maxn(slist));
	tb_size_t itor = tb_slist_itor_head(slist);
	tb_size_t tail = tb_slist_itor_tail(slist);
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor))
	{
		tb_char_t const* item = tb_slist_itor_const_at(slist, itor);
		tb_print("efm at[%d]: %s", itor, item);
	}
}
static tb_void_t tb_slist_efm_test()
{
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_efm(11, tb_fpool_init(256, 256, tb_item_func_ifm(11, TB_NULL, TB_NULL))));
	tb_assert_and_check_return(slist);

	tb_size_t 			i = 0;
	tb_size_t 			j = 0;

	tb_print("=============================================================");
	tb_print("insert:");
	tb_slist_ninsert_head(slist, "HHHHHHHHHH", 10);
	i = tb_slist_ninsert_tail(slist, "TTTTTTTTTT", 10);
	j = tb_slist_insert(slist, i, "0000000000");
	tb_slist_insert(slist, i, "1111111111");
	tb_slist_insert(slist, i, "2222222222");
	tb_slist_insert(slist, i, "3333333333");
	tb_slist_insert(slist, i, "4444444444");
	tb_slist_insert(slist, i, "5555555555");
	tb_slist_insert(slist, i, "6666666666");
	tb_slist_insert(slist, i, "7777777777");
	tb_slist_insert(slist, i, "8888888888");
	tb_slist_insert(slist, i, "9999999999");
	tb_slist_insert_head(slist, "4444444444");
	tb_slist_insert_head(slist, "3333333333");
	tb_slist_insert_head(slist, "2222222222");
	tb_slist_insert_head(slist, "1111111111");
	tb_slist_insert_head(slist, "0000000000");
	tb_slist_insert_tail(slist, "5555555555");
	tb_slist_insert_tail(slist, "6666666666");
	tb_slist_insert_tail(slist, "7777777777");
	tb_slist_insert_tail(slist, "8888888888");
	tb_slist_insert_tail(slist, "9999999999");
	tb_slist_efm_dump(slist);

	tb_print("=============================================================");
	tb_print("remove:");
	tb_slist_nremove_head(slist, 5);
	tb_slist_nremove_last(slist, 5);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);	
	tb_slist_efm_dump(slist);

	tb_print("=============================================================");
	tb_print("replace:");
	tb_slist_nreplace_head(slist, "TTTTTTTTTT", 10);
	tb_slist_nreplace_last(slist, "HHHHHHHHHH", 10);
	tb_slist_replace_head(slist, "OOOOOOOOOO");
	tb_slist_replace_last(slist, "OOOOOOOOOO");
	tb_slist_efm_dump(slist);

	tb_print("=============================================================");
	tb_print("clear:");
	tb_slist_clear(slist);
	tb_slist_efm_dump(slist);

	tb_slist_exit(slist);
}
static tb_void_t tb_slist_ifm_free(tb_item_func_t* func, tb_pointer_t item)
{
	tb_print("ifm free: %s, priv: %s", item, func->priv);
}
static tb_void_t tb_slist_ifm_dump(tb_slist_t const* slist)
{
	tb_print("ifm size: %d, maxn: %d", tb_slist_size(slist), tb_slist_maxn(slist));
	tb_size_t itor = tb_slist_itor_head(slist);
	tb_size_t tail = tb_slist_itor_tail(slist);
	for (; itor != tail; itor = tb_slist_itor_next(slist, itor))
	{
		tb_char_t const* item = tb_slist_itor_const_at(slist, itor);
		tb_print("ifm at[%d]: %s", itor, item);
	}
}
static tb_void_t tb_slist_ifm_test()
{
	tb_slist_t* slist = tb_slist_init(TB_SLIST_GROW_SIZE, tb_item_func_ifm(11, tb_slist_ifm_free, "ifm"));
	tb_assert_and_check_return(slist);

	tb_size_t 			i = 0;
	tb_size_t 			j = 0;

	tb_print("=============================================================");
	tb_print("insert:");
	tb_slist_ninsert_head(slist, "HHHHHHHHHH", 10);
	i = tb_slist_ninsert_tail(slist, "TTTTTTTTTT", 10);
	j = tb_slist_insert(slist, i, "0000000000");
	tb_slist_insert(slist, i, "1111111111");
	tb_slist_insert(slist, i, "2222222222");
	tb_slist_insert(slist, i, "3333333333");
	tb_slist_insert(slist, i, "4444444444");
	tb_slist_insert(slist, i, "5555555555");
	tb_slist_insert(slist, i, "6666666666");
	tb_slist_insert(slist, i, "7777777777");
	tb_slist_insert(slist, i, "8888888888");
	tb_slist_insert(slist, i, "9999999999");
	tb_slist_insert_head(slist, "4444444444");
	tb_slist_insert_head(slist, "3333333333");
	tb_slist_insert_head(slist, "2222222222");
	tb_slist_insert_head(slist, "1111111111");
	tb_slist_insert_head(slist, "0000000000");
	tb_slist_insert_tail(slist, "5555555555");
	tb_slist_insert_tail(slist, "6666666666");
	tb_slist_insert_tail(slist, "7777777777");
	tb_slist_insert_tail(slist, "8888888888");
	tb_slist_insert_tail(slist, "9999999999");
	tb_slist_ifm_dump(slist);

	tb_print("=============================================================");
	tb_print("remove:");
	tb_slist_nremove_head(slist, 5);
	tb_slist_nremove_last(slist, 5);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);
	j = tb_slist_remove(slist, j);	
	tb_slist_ifm_dump(slist);

	tb_print("=============================================================");
	tb_print("replace:");
	tb_slist_nreplace_head(slist, "TTTTTTTTTT", 10);
	tb_slist_nreplace_last(slist, "HHHHHHHHHH", 10);
	tb_slist_replace_head(slist, "OOOOOOOOOO");
	tb_slist_replace_last(slist, "OOOOOOOOOO");
	tb_slist_ifm_dump(slist);

	tb_print("=============================================================");
	tb_print("clear:");
	tb_slist_clear(slist);
	tb_slist_ifm_dump(slist);

	tb_slist_exit(slist);
}
static tb_void_t tb_slist_perf_test()
{
	tb_size_t score = 0;
	tb_print("=============================================================");
	tb_print("insert performance:");
	score += tb_slist_insert_test();
	score += tb_slist_insert_head_test();
	score += tb_slist_insert_tail_test();
	score += tb_slist_ninsert_test();
	score += tb_slist_ninsert_head_test();
	score += tb_slist_ninsert_tail_test();

	tb_print("=============================================================");
	tb_print("remove performance:");
	score += tb_slist_remove_test();
	score += tb_slist_remove_head_test();
	score += tb_slist_remove_last_test();
	score += tb_slist_nremove_test();
	score += tb_slist_nremove_head_test();
	score += tb_slist_nremove_last_test();

	tb_print("=============================================================");
	tb_print("replace performance:");
	score += tb_slist_replace_test();
	score += tb_slist_replace_head_test();
	score += tb_slist_replace_last_test();
	score += tb_slist_nreplace_test();
	score += tb_slist_nreplace_head_test();
	score += tb_slist_nreplace_last_test();

	tb_print("=============================================================");
	tb_print("iterator performance:");
	score += tb_slist_iterator_next_test();
	score += tb_slist_iterator_prev_test();

	tb_print("=============================================================");
	tb_print("score: %d", score / 100);

}
/* ///////////////////////////////////////////////////////////////////////
 * main
 */
int main(int argc, char** argv)
{
	if (!tb_init(malloc(30 * 1024 * 1024), 30 * 1024 * 1024)) return 0;

	tb_slist_int_test();
	tb_slist_str_test();
	tb_slist_efm_test();
	tb_slist_ifm_test();

	tb_slist_perf_test();

	return 0;
}
