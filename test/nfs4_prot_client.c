/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "nfs4_prot.h"


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

static const char *name_nfs4status[] = {
	[NFS4_OK] = "NFS4_OK",
	[NFS4ERR_PERM] = "NFS4ERR_PERM",
	[NFS4ERR_NOENT] = "NFS4ERR_NOENT",
	[NFS4ERR_IO] = "NFS4ERR_IO",
	[NFS4ERR_NXIO] = "NFS4ERR_NXIO",
	[NFS4ERR_ACCESS] = "NFS4ERR_ACCESS",
	[NFS4ERR_EXIST] = "NFS4ERR_EXIST",
	[NFS4ERR_XDEV] = "NFS4ERR_XDEV",
	[NFS4ERR_NOTDIR] = "NFS4ERR_NOTDIR",
	[NFS4ERR_ISDIR] = "NFS4ERR_ISDIR",
	[NFS4ERR_INVAL] = "NFS4ERR_INVAL",
	[NFS4ERR_FBIG] = "NFS4ERR_FBIG",
	[NFS4ERR_NOSPC] = "NFS4ERR_NOSPC",
	[NFS4ERR_ROFS] = "NFS4ERR_ROFS",
	[NFS4ERR_MLINK] = "NFS4ERR_MLINK",
	[NFS4ERR_NAMETOOLONG] = "NFS4ERR_NAMETOOLONG",
	[NFS4ERR_NOTEMPTY] = "NFS4ERR_NOTEMPTY",
	[NFS4ERR_DQUOT] = "NFS4ERR_DQUOT",
	[NFS4ERR_STALE] = "NFS4ERR_STALE",
	[NFS4ERR_BADHANDLE] = "NFS4ERR_BADHANDLE",
	[NFS4ERR_BAD_COOKIE] = "NFS4ERR_BAD_COOKIE",
	[NFS4ERR_NOTSUPP] = "NFS4ERR_NOTSUPP",
	[NFS4ERR_TOOSMALL] = "NFS4ERR_TOOSMALL",
	[NFS4ERR_SERVERFAULT] = "NFS4ERR_SERVERFAULT",
	[NFS4ERR_BADTYPE] = "NFS4ERR_BADTYPE",
	[NFS4ERR_DELAY] = "NFS4ERR_DELAY",
	[NFS4ERR_SAME] = "NFS4ERR_SAME",
	[NFS4ERR_DENIED] = "NFS4ERR_DENIED",
	[NFS4ERR_EXPIRED] = "NFS4ERR_EXPIRED",
	[NFS4ERR_LOCKED] = "NFS4ERR_LOCKED",
	[NFS4ERR_GRACE] = "NFS4ERR_GRACE",
	[NFS4ERR_FHEXPIRED] = "NFS4ERR_FHEXPIRED",
	[NFS4ERR_SHARE_DENIED] = "NFS4ERR_SHARE_DENIED",
	[NFS4ERR_WRONGSEC] = "NFS4ERR_WRONGSEC",
	[NFS4ERR_CLID_INUSE] = "NFS4ERR_CLID_INUSE",
	[NFS4ERR_RESOURCE] = "NFS4ERR_RESOURCE",
	[NFS4ERR_MOVED] = "NFS4ERR_MOVED",
	[NFS4ERR_NOFILEHANDLE] = "NFS4ERR_NOFILEHANDLE",
	[NFS4ERR_MINOR_VERS_MISMATCH] = "NFS4ERR_MINOR_VERS_MISMATCH",
	[NFS4ERR_STALE_CLIENTID] = "NFS4ERR_STALE_CLIENTID",
	[NFS4ERR_STALE_STATEID] = "NFS4ERR_STALE_STATEID",
	[NFS4ERR_OLD_STATEID] = "NFS4ERR_OLD_STATEID",
	[NFS4ERR_BAD_STATEID] = "NFS4ERR_BAD_STATEID",
	[NFS4ERR_BAD_SEQID] = "NFS4ERR_BAD_SEQID",
	[NFS4ERR_NOT_SAME] = "NFS4ERR_NOT_SAME",
	[NFS4ERR_LOCK_RANGE] = "NFS4ERR_LOCK_RANGE",
	[NFS4ERR_SYMLINK] = "NFS4ERR_SYMLINK",
	[NFS4ERR_RESTOREFH] = "NFS4ERR_RESTOREFH",
	[NFS4ERR_LEASE_MOVED] = "NFS4ERR_LEASE_MOVED",
	[NFS4ERR_ATTRNOTSUPP] = "NFS4ERR_ATTRNOTSUPP",
	[NFS4ERR_NO_GRACE] = "NFS4ERR_NO_GRACE",
	[NFS4ERR_RECLAIM_BAD] = "NFS4ERR_RECLAIM_BAD",
	[NFS4ERR_RECLAIM_CONFLICT] = "NFS4ERR_RECLAIM_CONFLICT",
	[NFS4ERR_BADXDR] = "NFS4ERR_BADXDR",
	[NFS4ERR_LOCKS_HELD] = "NFS4ERR_LOCKS_HELD",
	[NFS4ERR_OPENMODE] = "NFS4ERR_OPENMODE",
	[NFS4ERR_BADOWNER] = "NFS4ERR_BADOWNER",
	[NFS4ERR_BADCHAR] = "NFS4ERR_BADCHAR",
	[NFS4ERR_BADNAME] = "NFS4ERR_BADNAME",
	[NFS4ERR_BAD_RANGE] = "NFS4ERR_BAD_RANGE",
	[NFS4ERR_LOCK_NOTSUPP] = "NFS4ERR_LOCK_NOTSUPP",
	[NFS4ERR_OP_ILLEGAL] = "NFS4ERR_OP_ILLEGAL",
	[NFS4ERR_DEADLOCK] = "NFS4ERR_DEADLOCK",
	[NFS4ERR_FILE_OPEN] = "NFS4ERR_FILE_OPEN",
	[NFS4ERR_ADMIN_REVOKED] = "NFS4ERR_ADMIN_REVOKED",
	[NFS4ERR_CB_PATH_DOWN] = "NFS4ERR_CB_PATH_DOWN",
};

static void print_resop(nfs_resop4 *res)
{
	printf("  resop: %s\n", arg_str[res->resop]);

	switch(res->resop) {
	case OP_PUTROOTFH:
		printf("    status: %s\n",
			name_nfs4status[res->nfs_resop4_u.opputrootfh.status]);
		break;
	case OP_LOOKUP:
		printf("    status: %s\n",
			name_nfs4status[res->nfs_resop4_u.oplookup.status]);
		break;
	default:
		printf("    unknown operation\n");
		break;
	}
}

void
nfs4_program_4(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *nfsproc4_null_4_arg;
	COMPOUND4res  *res;
	COMPOUND4args  arg;
	nfs_argop4 args[2];
	int i;

#ifndef	DEBUG
	clnt = clnt_create (host, NFS4_PROGRAM, NFS_V4, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	clnt->cl_auth = authunix_create_default();

	result_1 = nfsproc4_null_4((void*)&nfsproc4_null_4_arg, clnt);
	if (result_1 == (void *) NULL)
		exit(1);

	result_1 = nfsproc4_null_4((void*)&nfsproc4_null_4_arg, clnt);
	if (result_1 == (void *) NULL)
		exit(1);

	exit(0);

	memset(&arg, 0, sizeof(arg));
	arg.tag.utf8string_val = "blah";
	arg.tag.utf8string_len = strlen(arg.tag.utf8string_val);
	arg.minorversion = 0;
	arg.argarray.argarray_len = 2;
	arg.argarray.argarray_val = args;

	args[0].argop = OP_PUTROOTFH;

	args[1].argop = OP_LOOKUP;
	args[1].nfs_argop4_u.oplookup.objname.utf8string_val = "tmp";
	args[1].nfs_argop4_u.oplookup.objname.utf8string_len =
		strlen(args[1].nfs_argop4_u.oplookup.objname.utf8string_val);

	res = nfsproc4_compound_4(&arg, clnt);
	if (res == (COMPOUND4res *) NULL) {
		clnt_perror (clnt, "call failed");
		goto out;
	}

	printf(	"COMPOUND result:\n"
		"status %s\n"
		"tag %.*s\n"
		"numres %u\n",
		name_nfs4status[res->status],
		res->tag.utf8string_len,
		res->tag.utf8string_val,
		res->resarray.resarray_len);

	for (i = 0; i < res->resarray.resarray_len; i++)
		print_resop(&res->resarray.resarray_val[i]);

out:
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
nfs4_callback_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *cb_null_1_arg;
#if 0
	CB_COMPOUND4res  *result_2;
	CB_COMPOUND4args  cb_compound_1_arg;
#endif

#ifndef	DEBUG
	clnt = clnt_create (host, NFS4_CALLBACK, NFS_CB, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	clnt->cl_auth = authunix_create_default();

	result_1 = cb_null_1((void*)&cb_null_1_arg, clnt);
	if (result_1 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc != 1) {
		printf ("usage: %s\n", argv[0]);
		exit (1);
	}
	host = "localhost";
	nfs4_program_4 (host);
#if 0
	nfs4_callback_1 (host);
#endif
exit (0);
}
