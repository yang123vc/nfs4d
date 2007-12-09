/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include "nfs4_prot.h"
#include "server.h"

int debugging = 1;

bool_t nfsproc4_null_4_svc(void *argp, void *result, struct svc_req *rqstp)
{
	return TRUE;
}

bool_t valid_utf8string(utf8string *str)
{
	if (!str || !str->utf8string_len || !str->utf8string_val)
		return FALSE;
	if (!g_utf8_validate(str->utf8string_val, str->utf8string_len, NULL))
		return FALSE;
	return TRUE;
}

char *copy_utf8string(utf8string *str)
{
	return strndup(str->utf8string_val, str->utf8string_len);
}

bool_t has_dots(utf8string *str)
{
	if (!str)
		return FALSE;
	if ((str->utf8string_len == 1) &&
	    (!memcmp(str->utf8string_val, ".", 1)))
		return TRUE;
	if ((str->utf8string_len == 2) &&
	    (!memcmp(str->utf8string_val, "..", 2)))
		return TRUE;
	return FALSE;
}

guint64 get_bitmap(const bitmap4 *map)
{
	guint64 v = 0;

	if (map->bitmap4_len > 0)
		v |= map->bitmap4_val[0];
	if (map->bitmap4_len > 1)
		v |= ((guint64)map->bitmap4_val[1]) << 32;
	return v;
}

int set_bitmap(guint64 map_in, bitmap4 *map_out)
{
	map_out->bitmap4_len = 2;
	map_out->bitmap4_val = calloc(2, sizeof(uint32_t));
	if (!map_out->bitmap4_val) {
		map_out->bitmap4_len = 0;
		return -1;
	}

	map_out->bitmap4_val[0] = map_in;
	map_out->bitmap4_val[1] = (map_in >> 32);

	return 0;
}

static struct nfs_cxn *cli_init(struct svc_req *rqstp)
{
	struct nfs_cxn *cxn = calloc(1, sizeof(struct nfs_cxn));

	return cxn;
}

static void cli_free(struct nfs_cxn *cxn)
{
	free(cxn);
}

bool_t push_resop(COMPOUND4res *res, const nfs_resop4 *resop, nfsstat4 stat)
{
	void *mem;
	u_int array_len = res->resarray.resarray_len;

	mem = realloc(res->resarray.resarray_val,
		((array_len + 1) * sizeof(nfs_resop4)));
	if (!mem)
		return FALSE;

	res->resarray.resarray_len++;
	res->resarray.resarray_val = mem;
	memcpy(&res->resarray.resarray_val[array_len], resop,
	       sizeof(struct nfs_resop4));
	res->status = stat;

	return stat == NFS4_OK ? TRUE : FALSE;
}

static bool_t nfs_op_readlink(struct nfs_cxn *cxn, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	READLINK4res *res;
	READLINK4resok *resok;
	nfsstat4 status = NFS4_OK;
	struct nfs_inode *ino;
	gchar *linktext;

	if (debugging)
		syslog(LOG_INFO, "op READLINK");

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_READLINK;
	res = &resop.nfs_resop4_u.opreadlink;
	resok = &res->READLINK4res_u.resok4;

	ino = inode_get(cxn->current_fh);
	if (!ino) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}
	if (ino->type != NF4LNK) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	linktext = ino->u.linktext;
	g_assert(linktext != NULL);

	resok->link.utf8string_len = strlen(linktext);
	resok->link.utf8string_val = linktext;

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_notsupp(struct nfs_cxn *cxn, COMPOUND4res *cres,
			     nfs_opnum4 argop)
{
	struct nfs_resop4 resop;
	OPENATTR4res *res;
	nfsstat4 status = NFS4ERR_NOTSUPP;

	memset(&resop, 0, sizeof(resop));
	resop.resop = argop;
	res = &resop.nfs_resop4_u.opopenattr;
	res->status = status;
	return push_resop(cres, &resop, status);
}

static const char *arg_str[] = {
	"<n/a>",
	"<n/a>",
	"<n/a>",
	"ACCESS",
	"CLOSE",
	"COMMIT",
	"CREATE",
	"DELEGPURGE",
	"DELEGRETURN",
	"GETATTR",
	"GETFH",
	"LINK",
	"LOCK",
	"LOCKT",
	"LOCKU",
	"LOOKUP",
	"LOOKUPP",
	"NVERIFY",
	"OPEN",
	"OPENATTR",
	"OPEN_CONFIRM",
	"OPEN_DOWNGRADE",
	"PUTFH",
	"PUTPUBFH",
	"PUTROOTFH",
	"READ",
	"READDIR",
	"READLINK",
	"REMOVE",
	"RENAME",
	"RENEW",
	"RESTOREFH",
	"SAVEFH",
	"SECINFO",
	"SETATTR",
	"SETCLIENTID",
	"SETCLIENTID_CONFIRM",
	"VERIFY",
	"WRITE",
	"RELEASE_LOCKOWNER",
};

static bool_t nfs_arg(struct nfs_cxn *cxn, nfs_argop4 *arg, COMPOUND4res *res)
{
	switch (arg->argop) {
	case OP_ACCESS:
		return nfs_op_access(cxn, &arg->nfs_argop4_u.opaccess, res);
	case OP_CLOSE:
		return nfs_op_close(cxn, &arg->nfs_argop4_u.opclose, res);
	case OP_CREATE:
		return nfs_op_create(cxn, &arg->nfs_argop4_u.opcreate, res);
	case OP_GETATTR:
		return nfs_op_getattr(cxn, &arg->nfs_argop4_u.opgetattr, res);
	case OP_GETFH:
		return nfs_op_getfh(cxn, res);
	case OP_LINK:
		return nfs_op_link(cxn, &arg->nfs_argop4_u.oplink, res);
	case OP_LOOKUP:
		return nfs_op_lookup(cxn, &arg->nfs_argop4_u.oplookup, res);
	case OP_LOOKUPP:
		return nfs_op_lookupp(cxn, res);
	case OP_NVERIFY:
		return nfs_op_verify(cxn,
				(VERIFY4args *) &arg->nfs_argop4_u.opnverify,
				res, 1);
	case OP_OPEN:
		return nfs_op_open(cxn, &arg->nfs_argop4_u.opopen, res);
	case OP_PUTFH:
		return nfs_op_putfh(cxn, &arg->nfs_argop4_u.opputfh, res);
	case OP_PUTPUBFH:
		return nfs_op_putpubfh(cxn, res);
	case OP_PUTROOTFH:
		return nfs_op_putrootfh(cxn, res);
	case OP_READDIR:
		return nfs_op_readdir(cxn, &arg->nfs_argop4_u.opreaddir, res);
	case OP_READLINK:
		return nfs_op_readlink(cxn, res);
	case OP_REMOVE:
		return nfs_op_remove(cxn, &arg->nfs_argop4_u.opremove, res);
	case OP_RENAME:
		return nfs_op_rename(cxn, &arg->nfs_argop4_u.oprename, res);
	case OP_RESTOREFH:
		return nfs_op_restorefh(cxn, res);
	case OP_SAVEFH:
		return nfs_op_savefh(cxn, res);
	case OP_SETCLIENTID:
		return nfs_op_setclientid(cxn,
					&arg->nfs_argop4_u.opsetclientid, res);
	case OP_SETCLIENTID_CONFIRM:
		return nfs_op_setclientid_confirm(cxn,
				&arg->nfs_argop4_u.opsetclientid_confirm, res);
	case OP_WRITE:
		return nfs_op_write(cxn, &arg->nfs_argop4_u.opwrite, res);
	case OP_VERIFY:
		return nfs_op_verify(cxn, &arg->nfs_argop4_u.opverify, res, 0);

	case OP_COMMIT:
	case OP_DELEGPURGE:
	case OP_DELEGRETURN:
	case OP_LOCK:
	case OP_LOCKT:
	case OP_LOCKU:
	case OP_OPEN_CONFIRM:
	case OP_OPEN_DOWNGRADE:
	case OP_READ:
	case OP_RENEW:
	case OP_SECINFO:
	case OP_SETATTR:
	case OP_RELEASE_LOCKOWNER:
	case OP_OPENATTR:
		if (debugging)
			syslog(LOG_INFO, "compound op %s",
			       (arg->argop > 39) ?  "<n/a>" :
			       	arg_str[arg->argop]);

		return nfs_op_notsupp(cxn, res, arg->argop);
	default:
		return FALSE;
	}

	return FALSE;	/* never reached */
}

bool_t nfsproc4_compound_4_svc(COMPOUND4args *arg, COMPOUND4res *res,
			       struct svc_req *rqstp)
{
	struct nfs_cxn *cxn;
	unsigned int i;

	memset(res, 0, sizeof(*res));
	res->status = NFS4_OK;
	memcpy(&res->tag, &arg->tag, sizeof(utf8str_cs));

	if (arg->minorversion != 0) {
		res->status = NFS4ERR_MINOR_VERS_MISMATCH;
		goto out;
	}

	cxn = cli_init(rqstp);
	if (!cxn) {
		res->status = NFS4ERR_RESOURCE;
		goto out;
	}

	for (i = 0; i < arg->argarray.argarray_len; i++)
		if (!nfs_arg(cxn, &arg->argarray.argarray_val[i], res)) {
			syslog(LOG_WARNING, "compound failed early");
			break;
		}

	if (debugging)
		syslog(LOG_INFO, "arg list end (%u of %u args)",
		       (i == arg->argarray.argarray_len) ? i : i + 1,
		       arg->argarray.argarray_len);

	cli_free(cxn);
out:
	return TRUE;
}

static void nfs_free(nfs_resop4 *res)
{
	switch(res->resop) {
	case OP_CREATE:
		free(res->nfs_resop4_u.opcreate.CREATE4res_u.resok4.attrset.bitmap4_val);
		break;
	case OP_GETATTR:
		nfs_getattr_free(&res->nfs_resop4_u.opgetattr);
		break;
	case OP_GETFH:
		nfs_getfh_free(&res->nfs_resop4_u.opgetfh);
		break;
	default:
		/* nothing to free */
		break;
	}
}

int nfs4_program_4_freeresult (SVCXPRT *transp, xdrproc_t xdr_result,
			       COMPOUND4res *res)
{
	unsigned int i;

	for (i = 0; i < res->resarray.resarray_len; i++)
		nfs_free(&res->resarray.resarray_val[i]);

	free(res->resarray.resarray_val);

	return TRUE;
}

