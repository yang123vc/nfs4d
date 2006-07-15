/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "nfs4_prot.h"
#include "server.h"

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

gchar *copy_utf8string(utf8string *str)
{
	return g_strndup(str->utf8string_val, str->utf8string_len);
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

static struct nfs_client *cli_init(struct svc_req *rqstp)
{
	struct nfs_client *cli = g_new0(struct nfs_client, 1);

	return cli;
}

static void cli_free(struct nfs_client *cli)
{
	free(cli);
}

static void nfs_fh_set(nfs_fh4 *fh, nfsino_t fh_int)
{
	nfsino_t *fh_val = g_new(nfsino_t, 1);
	*fh_val = GUINT32_TO_BE(fh_int);

	fh->nfs_fh4_len = sizeof(nfsino_t);
	fh->nfs_fh4_val = (char *)(void *) fh_val;
}

static void nfs_fh_free(nfs_fh4 *fh)
{
	if (fh) {
		free(fh->nfs_fh4_val);
		fh->nfs_fh4_val = NULL;
	}
}

static nfsino_t nfs_fh_decode(nfs_fh4 *fh_in)
{
	nfsino_t *fhp;
	nfsino_t fh;

	if (!fh_in)
		return 0;
	if (fh_in->nfs_fh4_len != sizeof(nfsino_t))
		return 0;
	if (!fh_in->nfs_fh4_val)
		return 0;
	fhp = (void *) fh_in->nfs_fh4_val;
	fh = GUINT32_FROM_BE(*fhp);

	if (!inode_get(fh))
		return 0;

	return fh;
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

	return TRUE;
}

static void nfs_getfh_free(GETFH4res *opgetfh)
{
	nfs_fh_free(&opgetfh->GETFH4res_u.resok4.object);
}

static bool_t nfs_op_getfh(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	GETFH4res *res;
	GETFH4resok *resok;
	nfsstat4 status = NFS4_OK;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_GETFH;
	res = &resop.nfs_resop4_u.opgetfh;
	resok = &res->GETFH4res_u.resok4;

	if (!inode_get(cli->current_fh)) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	nfs_fh_set(&resok->object, cli->current_fh);

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_putfh(struct nfs_client *cli, PUTFH4args *arg, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	PUTFH4res *res;
	nfsstat4 status = NFS4_OK;
	nfsino_t fh;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_PUTFH;
	res = &resop.nfs_resop4_u.opputfh;

	fh = nfs_fh_decode(&arg->object);
	if (!fh) {
		status = NFS4ERR_BADHANDLE;
		goto out;
	}

	cli->current_fh = fh;

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_putrootfh(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	PUTFH4res *res;
	nfsstat4 status = NFS4_OK;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_PUTROOTFH;
	res = &resop.nfs_resop4_u.opputfh;

	cli->current_fh = INO_ROOT;

	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_putpubfh(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	PUTFH4res *res;
	nfsstat4 status = NFS4_OK;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_PUTPUBFH;
	res = &resop.nfs_resop4_u.opputfh;

	cli->current_fh = INO_ROOT;

	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_restorefh(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	RESTOREFH4res *res;
	nfsstat4 status = NFS4_OK;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_RESTOREFH;
	res = &resop.nfs_resop4_u.oprestorefh;

	if (!inode_get(cli->save_fh)) {
		status = NFS4ERR_RESTOREFH;
		goto out;
	}

	cli->current_fh = cli->save_fh;

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_savefh(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	SAVEFH4res *res;
	nfsstat4 status = NFS4_OK;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_SAVEFH;
	res = &resop.nfs_resop4_u.opsavefh;

	if (!inode_get(cli->current_fh)) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	cli->save_fh = cli->current_fh;

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_op_readlink(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	READLINK4res *res;
	READLINK4resok *resok;
	nfsstat4 status = NFS4_OK;
	struct nfs_inode *ino;
	gchar *linktext;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_READLINK;
	res = &resop.nfs_resop4_u.opreadlink;
	resok = &res->READLINK4res_u.resok4;

	ino = inode_get(cli->current_fh);
	if (!ino) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}
	if (ino->type != IT_SYMLINK) {
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

static bool_t nfs_op_openattr(struct nfs_client *cli, COMPOUND4res *cres)
{
	struct nfs_resop4 resop;
	OPENATTR4res *res;
	nfsstat4 status = NFS4_OK;
	struct nfs_inode *ino;

	memset(&resop, 0, sizeof(resop));
	resop.resop = OP_OPENATTR;
	res = &resop.nfs_resop4_u.opopenattr;

	ino = inode_get(cli->current_fh);
	if (!ino) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	/* named attributes not supported */
	status = NFS4ERR_NOTSUPP;

out:
	res->status = status;
	return push_resop(cres, &resop, status);
}

static bool_t nfs_arg(struct nfs_client *cli, nfs_argop4 *arg, COMPOUND4res *res)
{
	switch (arg->argop) {
	case OP_GETFH:
		return nfs_op_getfh(cli, res);
	case OP_LINK:
		return nfs_op_link(cli, &arg->nfs_argop4_u.oplink, res);
	case OP_LOOKUP:
		return nfs_op_lookup(cli, &arg->nfs_argop4_u.oplookup, res);
	case OP_LOOKUPP:
		return nfs_op_lookupp(cli, res);
	case OP_OPENATTR:
		return nfs_op_openattr(cli, res);
	case OP_PUTFH:
		return nfs_op_putfh(cli, &arg->nfs_argop4_u.opputfh, res);
	case OP_PUTPUBFH:
		return nfs_op_putpubfh(cli, res);
	case OP_PUTROOTFH:
		return nfs_op_putrootfh(cli, res);
	case OP_READLINK:
		return nfs_op_readlink(cli, res);
	case OP_REMOVE:
		return nfs_op_remove(cli, &arg->nfs_argop4_u.opremove, res);
	case OP_RESTOREFH:
		return nfs_op_restorefh(cli, res);
	case OP_SAVEFH:
		return nfs_op_savefh(cli, res);

	case OP_ACCESS:
	case OP_CLOSE:
	case OP_COMMIT:
	case OP_CREATE:
	case OP_DELEGPURGE:
	case OP_DELEGRETURN:
	case OP_GETATTR:
	case OP_LOCK:
	case OP_LOCKT:
	case OP_LOCKU:
	case OP_NVERIFY:
	case OP_OPEN:
	case OP_OPEN_CONFIRM:
	case OP_OPEN_DOWNGRADE:
	case OP_READ:
	case OP_READDIR:
	case OP_RENAME:
	case OP_RENEW:
	case OP_SECINFO:
	case OP_SETATTR:
	case OP_SETCLIENTID:
	case OP_SETCLIENTID_CONFIRM:
	case OP_VERIFY:
	case OP_WRITE:
	case OP_RELEASE_LOCKOWNER:
	default:
		return FALSE;
	}

	return FALSE;	/* never reached */
}

bool_t nfsproc4_compound_4_svc(COMPOUND4args *arg, COMPOUND4res *res,
			       struct svc_req *rqstp)
{
	struct nfs_client *cli;
	unsigned int i;

	memset(res, 0, sizeof(*res));
	res->status = NFS4_OK;
	memcpy(&res->tag, &arg->tag, sizeof(utf8str_cs));

	if (arg->minorversion != 0) {
		res->status = NFS4ERR_MINOR_VERS_MISMATCH;
		goto out;
	}

	cli = cli_init(rqstp);
	if (!cli) {
		res->status = NFS4ERR_RESOURCE;
		goto out;
	}

	for (i = 0; i < arg->argarray.argarray_len; i++)
		if (!nfs_arg(cli, &arg->argarray.argarray_val[i], res))
			break;

	cli_free(cli);
out:
	return TRUE;
}

static void nfs_free(nfs_resop4 *res)
{
	switch(res->resop) {
	case OP_GETFH:
		nfs_getfh_free(&res->nfs_resop4_u.opgetfh);
		break;
	case OP_PUTFH:
	case OP_PUTPUBFH:
	case OP_PUTROOTFH:
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
