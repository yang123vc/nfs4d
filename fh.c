
/*
 * Copyright 2008-2009 Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "nfs4d-config.h"

#include <string.h>
#include <syslog.h>
#include <glib.h>
#include "nfs4_prot.h"
#include "server.h"

#define WRFH(fh)		wr_fh(writes, wr, (fh))

static void *wr_fh(struct list_head *writes, struct rpc_write **wr_io,
		   struct nfs_fh fh_in)
{
	struct nfs_buf nb;
	struct nfs_fh fh;

	fh.inum = inum_encode(fh_in.inum);

	nb.len = sizeof(fh);
	nb.val = (char *) &fh;

	return wr_buf(writes, wr_io, &nb);
}

static int nfs_fh_decode(DB_TXN *txn, const struct nfs_buf *fh_in,
			 struct nfs_fh *fh_out)
{
	uint64_t *p;
	struct nfs_fh fh;

	memset(&fh, 0, sizeof(fh));

	if (!fh_in)
		return 0;
	if (fh_in->len != sizeof(fh))
		return 0;
	if (!fh_in->val)
		return 0;
	p = (void *) fh_in->val;

	fh.inum = inum_decode(*p);
	p++;

	if (!inode_fhcheck(txn, fh))
		return -1;

	*fh_out = fh;
	return 1;
}

nfsstat4 nfs_op_getfh(struct nfs_cxn *cxn,
		      struct list_head *writes, struct rpc_write **wr)
{
	nfsstat4 status = NFS4_OK;
	bool printed = false;

	if (!inode_fhcheck(NULL, cxn->current_fh)) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	if (debugging) {
		applog(LOG_INFO, "op GETFH -> %016llX",
		       (unsigned long long) cxn->current_fh.inum);
		printed = true;
	}

out:
	if (!printed) {
		if (debugging)
			applog(LOG_INFO, "op GETFH");
	}

	WR32(status);
	if (status == NFS4_OK)
		WRFH(cxn->current_fh);
	return status;
}

nfsstat4 nfs_op_putfh(struct nfs_cxn *cxn, const PUTFH4args *args,
		      struct list_head *writes, struct rpc_write **wr)
{
	nfsstat4 status = NFS4_OK;
	struct nfs_fh fh;
	struct nfs_buf nb;
	int rc;

	memset(&fh, 0, sizeof(fh));

	nb.len = args->object.nfs_fh4_len;
	nb.val = args->object.nfs_fh4_val;

	rc = nfs_fh_decode(NULL, &nb, &fh);
	if (rc == 0)
		status = NFS4ERR_BADHANDLE;
	else if (rc < 0)
		status = NFS4ERR_STALE;
	else
		cxn->current_fh = fh;

	if (debugging)
		applog(LOG_INFO, "op PUTFH (%016llX)",
		       (unsigned long long) fh.inum);

	WR32(status);
	return status;
}

nfsstat4 nfs_op_putrootfh(struct nfs_cxn *cxn,
		      struct list_head *writes, struct rpc_write **wr)
{
	fh_set(&cxn->current_fh, INO_ROOT);

	if (debugging)
		applog(LOG_INFO, "op PUTROOTFH -> %016llX",
		       (unsigned long long) cxn->current_fh.inum);

	WR32(NFS4_OK);
	return NFS4_OK;
}

nfsstat4 nfs_op_putpubfh(struct nfs_cxn *cxn,
		      struct list_head *writes, struct rpc_write **wr)
{
	fh_set(&cxn->current_fh, INO_ROOT);

	if (debugging)
		applog(LOG_INFO, "op PUTPUBFH -> %016llX",
			(unsigned long long) cxn->current_fh.inum);

	WR32(NFS4_OK);
	return NFS4_OK;
}

nfsstat4 nfs_op_restorefh(struct nfs_cxn *cxn,
		      struct list_head *writes, struct rpc_write **wr)
{
	nfsstat4 status = NFS4_OK;
	bool printed = false;

	if (!inode_fhcheck(NULL, cxn->save_fh)) {
		status = NFS4ERR_RESTOREFH;
		goto out;
	}

	cxn->current_fh = cxn->save_fh;

	if (debugging) {
		applog(LOG_INFO, "op RESTOREFH -> %016llX",
			(unsigned long long) cxn->current_fh.inum);
		printed = true;
	}

out:
	if (!printed) {
		if (debugging)
			applog(LOG_INFO, "op RESTOREFH");
	}

	WR32(status);
	return status;
}

nfsstat4 nfs_op_savefh(struct nfs_cxn *cxn,
		       struct list_head *writes, struct rpc_write **wr)
{
	nfsstat4 status = NFS4_OK;
	bool printed = false;

	if (!inode_fhcheck(NULL, cxn->current_fh)) {
		status = NFS4ERR_NOFILEHANDLE;
		goto out;
	}

	cxn->save_fh = cxn->current_fh;

	if (debugging) {
		applog(LOG_INFO, "op SAVEFH (SAVE:%016llX)",
			(unsigned long long) cxn->save_fh.inum);
		printed = true;
	}

out:
	if (!printed) {
		if (debugging)
			applog(LOG_INFO, "op SAVEFH");
	}

	WR32(status);
	return status;
}

