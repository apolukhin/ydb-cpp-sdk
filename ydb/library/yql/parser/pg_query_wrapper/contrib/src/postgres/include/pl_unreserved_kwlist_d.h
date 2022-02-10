/*------------------------------------------------------------------------- 
 * 
 * pl_unreserved_kwlist_d.h 
 *    List of keywords represented as a ScanKeywordList. 
 * 
 * Portions Copyright (c) 1996-2020, PostgreSQL Global Development Group 
 * Portions Copyright (c) 1994, Regents of the University of California 
 * 
 * NOTES 
 *  ****************************** 
 *  *** DO NOT EDIT THIS FILE! *** 
 *  ****************************** 
 * 
 *  It has been GENERATED by src/tools/gen_keywordlist.pl 
 * 
 *------------------------------------------------------------------------- 
 */ 
 
#ifndef PL_UNRESERVED_KWLIST_D_H 
#define PL_UNRESERVED_KWLIST_D_H 
 
#include "common/kwlookup.h" 
 
static const char UnreservedPLKeywords_kw_string[] = 
	"absolute\0" 
	"alias\0" 
	"and\0" 
	"array\0" 
	"assert\0" 
	"backward\0" 
	"call\0" 
	"chain\0" 
	"close\0" 
	"collate\0" 
	"column\0" 
	"column_name\0" 
	"commit\0" 
	"constant\0" 
	"constraint\0" 
	"constraint_name\0" 
	"continue\0" 
	"current\0" 
	"cursor\0" 
	"datatype\0" 
	"debug\0" 
	"default\0" 
	"detail\0" 
	"diagnostics\0" 
	"do\0" 
	"dump\0" 
	"elseif\0" 
	"elsif\0" 
	"errcode\0" 
	"error\0" 
	"exception\0" 
	"exit\0" 
	"fetch\0" 
	"first\0" 
	"forward\0" 
	"get\0" 
	"hint\0" 
	"import\0" 
	"info\0" 
	"insert\0" 
	"is\0" 
	"last\0" 
	"log\0" 
	"message\0" 
	"message_text\0" 
	"move\0" 
	"next\0" 
	"no\0" 
	"notice\0" 
	"open\0" 
	"option\0" 
	"perform\0" 
	"pg_context\0" 
	"pg_datatype_name\0" 
	"pg_exception_context\0" 
	"pg_exception_detail\0" 
	"pg_exception_hint\0" 
	"print_strict_params\0" 
	"prior\0" 
	"query\0" 
	"raise\0" 
	"relative\0" 
	"reset\0" 
	"return\0" 
	"returned_sqlstate\0" 
	"reverse\0" 
	"rollback\0" 
	"row_count\0" 
	"rowtype\0" 
	"schema\0" 
	"schema_name\0" 
	"scroll\0" 
	"set\0" 
	"slice\0" 
	"sqlstate\0" 
	"stacked\0" 
	"table\0" 
	"table_name\0" 
	"type\0" 
	"use_column\0" 
	"use_variable\0" 
	"variable_conflict\0" 
	"warning"; 
 
static const uint16 UnreservedPLKeywords_kw_offsets[] = { 
	0, 
	9, 
	15, 
	19, 
	25, 
	32, 
	41, 
	46, 
	52, 
	58, 
	66, 
	73, 
	85, 
	92, 
	101, 
	112, 
	128, 
	137, 
	145, 
	152, 
	161, 
	167, 
	175, 
	182, 
	194, 
	197, 
	202, 
	209, 
	215, 
	223, 
	229, 
	239, 
	244, 
	250, 
	256, 
	264, 
	268, 
	273, 
	280, 
	285, 
	292, 
	295, 
	300, 
	304, 
	312, 
	325, 
	330, 
	335, 
	338, 
	345, 
	350, 
	357, 
	365, 
	376, 
	393, 
	414, 
	434, 
	452, 
	472, 
	478, 
	484, 
	490, 
	499, 
	505, 
	512, 
	530, 
	538, 
	547, 
	557, 
	565, 
	572, 
	584, 
	591, 
	595, 
	601, 
	610, 
	618, 
	624, 
	635, 
	640, 
	651, 
	664, 
	682, 
}; 
 
#define UNRESERVEDPLKEYWORDS_NUM_KEYWORDS 83 
 
static int 
UnreservedPLKeywords_hash_func(const void *key, size_t keylen) 
{ 
	static const int16 h[167] = { 
		    10,  32767,  32767,     57,  32767,     62,     21,  32767, 
		    54,     18,  32767,     58,     59,    -54,     47,      0, 
		   -22,    -64,  32767,    -22,     33,     44,     -5,  32767, 
		 32767,     43,     57,    102,  32767,    -65,      7,  32767, 
		    13,  32767,    -28,     14,  32767,  32767,     82,  32767, 
		     0,      0,  32767,      8,    -43,      0,     19,      8, 
		    75,    -58,  32767,  32767,      0,     22,     29,  32767, 
		   -50,      6,  32767,      0,     30,  32767,  32767,     29, 
		     0,    104,  32767,  32767,     26,      0,  32767,  32767, 
		    -9,      2,  32767,     50,     39,     38,     39,     80, 
		 32767,  32767,  32767,  32767,    -67,     89,  32767,    -40, 
		    64,  32767,  32767,     26,     10,     27,  32767,     19, 
		    51,    -13,     26,  32767,  32767,  32767,     84,     23, 
		     0,     66,     12,     -5,  32767,  32767,      0,     50, 
		   141,     72,     45,  32767,  32767,      0,    -22,      0, 
		 32767,  32767,    -34,      0,     19,     -5,  32767,  32767, 
		 32767,      0,     37,     13,  32767,  32767,  32767,  32767, 
		   -68,     -4,  32767,  32767,     78,  32767,  32767,      0, 
		    85,  32767,  32767,  32767,    -93,  32767,      0,      0, 
		 32767,     74,      5,  32767,  32767,     71,      0,  32767, 
		 32767,      0,  32767,  32767,  32767,     46,     70, 
	}; 
 
	const unsigned char *k = (const unsigned char *) key; 
	uint32		a = 0; 
	uint32		b = 1; 
 
	while (keylen--) 
	{ 
		unsigned char c = *k++ | 0x20; 
 
		a = a * 31 + c; 
		b = b * 127 + c; 
	} 
	return h[a % 167] + h[b % 167]; 
} 
 
static const ScanKeywordList UnreservedPLKeywords = { 
	UnreservedPLKeywords_kw_string, 
	UnreservedPLKeywords_kw_offsets, 
	UnreservedPLKeywords_hash_func, 
	UNRESERVEDPLKEYWORDS_NUM_KEYWORDS, 
	20 
}; 
 
#endif							/* PL_UNRESERVED_KWLIST_D_H */ 
