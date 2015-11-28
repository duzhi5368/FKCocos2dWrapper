//-------------------------------------------------------------------------
#include "../Include/FKCW_Base_DecodeHtmlEntitiesUTF8.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
//-------------------------------------------------------------------------
#define UNICODE_MAX 0x10FFFFul
//-------------------------------------------------------------------------
static const char *const NAMED_ENTITIES[][2] = {
	{ "AElig;", "?" },
	{ "Aacute;", "?" },
	{ "Acirc;", "?" },
	{ "Agrave;", "?" },
	{ "Alpha;", "��" },
	{ "Aring;", "?" },
	{ "Atilde;", "?" },
	{ "Auml;", "?" },
	{ "Beta;", "��" },
	{ "Ccedil;", "?" },
	{ "Chi;", "��" },
	{ "Dagger;", "?" },
	{ "Delta;", "��" },
	{ "ETH;", "?" },
	{ "Eacute;", "?" },
	{ "Ecirc;", "?" },
	{ "Egrave;", "?" },
	{ "Epsilon;", "��" },
	{ "Eta;", "��" },
	{ "Euml;", "?" },
	{ "Gamma;", "��" },
	{ "Iacute;", "?" },
	{ "Icirc;", "?" },
	{ "Igrave;", "?" },
	{ "Iota;", "��" },
	{ "Iuml;", "?" },
	{ "Kappa;", "��" },
	{ "Lambda;", "��" },
	{ "Mu;", "��" },
	{ "Ntilde;", "?" },
	{ "Nu;", "��" },
	{ "OElig;", "?" },
	{ "Oacute;", "?" },
	{ "Ocirc;", "?" },
	{ "Ograve;", "?" },
	{ "Omega;", "��" },
	{ "Omicron;", "��" },
	{ "Oslash;", "?" },
	{ "Otilde;", "?" },
	{ "Ouml;", "?" },
	{ "Phi;", "��" },
	{ "Pi;", "��" },
	{ "Prime;", "��" },
	{ "Psi;", "��" },
	{ "Rho;", "��" },
	{ "Scaron;", "?" },
	{ "Sigma;", "��" },
	{ "THORN;", "?" },
	{ "Tau;", "��" },
	{ "Theta;", "��" },
	{ "Uacute;", "?" },
	{ "Ucirc;", "?" },
	{ "Ugrave;", "?" },
	{ "Upsilon;", "��" },
	{ "Uuml;", "?" },
	{ "Xi;", "��" },
	{ "Yacute;", "?" },
	{ "Yuml;", "?" },
	{ "Zeta;", "��" },
	{ "aacute;", "��" },
	{ "acirc;", "?" },
	{ "acute;", "?" },
	{ "aelig;", "?" },
	{ "agrave;", "��" },
	{ "alefsym;", "?" },
	{ "alpha;", "��" },
	{ "amp;", "&" },
	{ "and;", "��" },
	{ "ang;", "��" },
	{ "apos;", "'" },
	{ "aring;", "?" },
	{ "asymp;", "��" },
	{ "atilde;", "?" },
	{ "auml;", "?" },
	{ "bdquo;", "?" },
	{ "beta;", "��" },
	{ "brvbar;", "?" },
	{ "bull;", "?" },
	{ "cap;", "��" },
	{ "ccedil;", "?" },
	{ "cedil;", "?" },
	{ "cent;", "?" },
	{ "chi;", "��" },
	{ "circ;", "?" },
	{ "clubs;", "?" },
	{ "cong;", "?" },
	{ "copy;", "?" },
	{ "crarr;", "?" },
	{ "cup;", "��" },
	{ "curren;", "��" },
	{ "dArr;", "?" },
	{ "dagger;", "?" },
	{ "darr;", "��" },
	{ "deg;", "��" },
	{ "delta;", "��" },
	{ "diams;", "?" },
	{ "divide;", "��" },
	{ "eacute;", "��" },
	{ "ecirc;", "��" },
	{ "egrave;", "��" },
	{ "empty;", "?" },
	{ "emsp;", "?" },
	{ "ensp;", "?" },
	{ "epsilon;", "��" },
	{ "equiv;", "��" },
	{ "eta;", "��" },
	{ "eth;", "?" },
	{ "euml;", "?" },
	{ "euro;", "�" },
	{ "exist;", "?" },
	{ "fnof;", "?" },
	{ "forall;", "?" },
	{ "frac12;", "?" },
	{ "frac14;", "?" },
	{ "frac34;", "?" },
	{ "frasl;", "?" },
	{ "gamma;", "��" },
	{ "ge;", "��" },
	{ "gt;", ">" },
	{ "hArr;", "?" },
	{ "harr;", "?" },
	{ "hearts;", "?" },
	{ "hellip;", "��" },
	{ "iacute;", "��" },
	{ "icirc;", "?" },
	{ "iexcl;", "?" },
	{ "igrave;", "��" },
	{ "image;", "?" },
	{ "infin;", "��" },
	{ "int;", "��" },
	{ "iota;", "��" },
	{ "iquest;", "?" },
	{ "isin;", "��" },
	{ "iuml;", "?" },
	{ "kappa;", "��" },
	{ "lArr;", "?" },
	{ "lambda;", "��" },
	{ "lang;", "��" },
	{ "laquo;", "?" },
	{ "larr;", "��" },
	{ "lceil;", "?" },
	{ "ldquo;", "��" },
	{ "le;", "��" },
	{ "lfloor;", "?" },
	{ "lowast;", "?" },
	{ "loz;", "?" },
	{ "lrm;", "\xE2\x80\x8E" },
	{ "lsaquo;", "?" },
	{ "lsquo;", "��" },
	{ "lt;", "<" },
	{ "macr;", "?" },
	{ "mdash;", "��" },
	{ "micro;", "?" },
	{ "middot;", "��" },
	{ "minus;", "?" },
	{ "mu;", "��" },
	{ "nabla;", "?" },
	{ "nbsp;", "?" },
	{ "ndash;", "�C" },
	{ "ne;", "��" },
	{ "ni;", "?" },
	{ "not;", "?" },
	{ "notin;", "?" },
	{ "nsub;", "?" },
	{ "ntilde;", "?" },
	{ "nu;", "��" },
	{ "oacute;", "��" },
	{ "ocirc;", "?" },
	{ "oelig;", "?" },
	{ "ograve;", "��" },
	{ "oline;", "?" },
	{ "omega;", "��" },
	{ "omicron;", "��" },
	{ "oplus;", "��" },
	{ "or;", "��" },
	{ "ordf;", "?" },
	{ "ordm;", "?" },
	{ "oslash;", "?" },
	{ "otilde;", "?" },
	{ "otimes;", "?" },
	{ "ouml;", "?" },
	{ "para;", "?" },
	{ "part;", "?" },
	{ "permil;", "��" },
	{ "perp;", "��" },
	{ "phi;", "��" },
	{ "pi;", "��" },
	{ "piv;", "?" },
	{ "plusmn;", "��" },
	{ "pound;", "?" },
	{ "prime;", "��" },
	{ "prod;", "��" },
	{ "prop;", "��" },
	{ "psi;", "��" },
	{ "quot;", "\"" },
	{ "rArr;", "?" },
	{ "radic;", "��" },
	{ "rang;", "��" },
	{ "raquo;", "?" },
	{ "rarr;", "��" },
	{ "rceil;", "?" },
	{ "rdquo;", "��" },
	{ "real;", "?" },
	{ "reg;", "?" },
	{ "rfloor;", "?" },
	{ "rho;", "��" },
	{ "rlm;", "\xE2\x80\x8F" },
	{ "rsaquo;", "?" },
	{ "rsquo;", "��" },
	{ "sbquo;", "?" },
	{ "scaron;", "?" },
	{ "sdot;", "?" },
	{ "sect;", "��" },
	{ "shy;", "\xC2\xAD" },
	{ "sigma;", "��" },
	{ "sigmaf;", "?" },
	{ "sim;", "?" },
	{ "spades;", "?" },
	{ "sub;", "?" },
	{ "sube;", "?" },
	{ "sum;", "��" },
	{ "sup;", "?" },
	{ "sup1;", "?" },
	{ "sup2;", "?" },
	{ "sup3;", "?" },
	{ "supe;", "?" },
	{ "szlig;", "?" },
	{ "tau;", "��" },
	{ "there4;", "��" },
	{ "theta;", "��" },
	{ "thetasym;", "?" },
	{ "thinsp;", "?" },
	{ "thorn;", "?" },
	{ "tilde;", "?" },
	{ "times;", "��" },
	{ "trade;", "?" },
	{ "uArr;", "?" },
	{ "uacute;", "��" },
	{ "uarr;", "��" },
	{ "ucirc;", "?" },
	{ "ugrave;", "��" },
	{ "uml;", "��" },
	{ "upsih;", "?" },
	{ "upsilon;", "��" },
	{ "uuml;", "��" },
	{ "weierp;", "?" },
	{ "xi;", "��" },
	{ "yacute;", "?" },
	{ "yen;", "?" },
	{ "yuml;", "?" },
	{ "zeta;", "��" },
	{ "zwj;", "\xE2\x80\x8D" },
	{ "zwnj;", "\xE2\x80\x8C" }
};

static int cmp(const void *key, const void *value)
{
	return strncmp((const char *)key, *(const char **)value,
		strlen(*(const char **)value));
}

static const char *get_named_entity(const char *name)
{
	const char *const *entity = (const char *const *)bsearch(name,
		NAMED_ENTITIES, sizeof NAMED_ENTITIES / sizeof *NAMED_ENTITIES,
		sizeof *NAMED_ENTITIES, cmp);

	return entity ? entity[1] : NULL;
}

static size_t putc_utf8(unsigned long cp, char *buffer)
{
	unsigned char *bytes = (unsigned char *)buffer;

	if(cp <= 0x007Ful)
	{
		bytes[0] = (unsigned char)cp;
		return 1;
	}

	if(cp <= 0x07FFul)
	{
		bytes[1] = (unsigned char)((2 << 6) | (cp & 0x3F));
		bytes[0] = (unsigned char)((6 << 5) | (cp >> 6));
		return 2;
	}

	if(cp <= 0xFFFFul)
	{
		bytes[2] = (unsigned char)(( 2 << 6) | ( cp       & 0x3F));
		bytes[1] = (unsigned char)(( 2 << 6) | ((cp >> 6) & 0x3F));
		bytes[0] = (unsigned char)((14 << 4) |  (cp >> 12));
		return 3;
	}

	if(cp <= 0x10FFFFul)
	{
		bytes[3] = (unsigned char)(( 2 << 6) | ( cp        & 0x3F));
		bytes[2] = (unsigned char)(( 2 << 6) | ((cp >>  6) & 0x3F));
		bytes[1] = (unsigned char)(( 2 << 6) | ((cp >> 12) & 0x3F));
		bytes[0] = (unsigned char)((30 << 3) |  (cp >> 18));
		return 4;
	}

	return 0;
}

static bool parse_entity(
	const char *current, char **to, const char **from)
{
	const char *end = strchr(current, ';');
	if(!end) return 0;

	if(current[1] == '#')
	{
		char *tail = NULL;
		int errno_save = errno;
		bool hex = current[2] == 'x' || current[2] == 'X';

		errno = 0;
		unsigned long cp = strtoul(
			current + (hex ? 3 : 2), &tail, hex ? 16 : 10);

		bool fail = errno || tail != end || cp > UNICODE_MAX;
		errno = errno_save;
		if(fail) return 0;

		*to += putc_utf8(cp, *to);
		*from = end + 1;

		return 1;
	}
	else
	{
		const char *entity = get_named_entity(&current[1]);
		if(!entity) return 0;

		size_t len = strlen(entity);
		memcpy(*to, entity, len);

		*to += len;
		*from = end + 1;

		return 1;
	}
}

size_t decode_html_entities_utf8(char *dest, const char *src)
{
	if(!src) src = dest;

	char *to = dest;
	const char *from = src;
	const char *current = strchr(from, '&');
	while(current) {
		memmove(to, from, (size_t)(current - from));
		to += current - from;
		
		if(!parse_entity(current, &to, &from)) {
			from = current;
			*to++ = *from++;
		}
		
		current = strchr(from, '&');
	}

	size_t remaining = strlen(from);

	memmove(to, from, remaining);
	to += remaining;
	*to = 0;

	return (size_t)(to - dest);
}
//-------------------------------------------------------------------------