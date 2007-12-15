/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <stdio.h>
#include <memory.h> /* for memset */
#include "nfs4_prot.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

void *
nfsproc4_null_4(void *argp, CLIENT *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, NFSPROC4_NULL,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

COMPOUND4res *
nfsproc4_compound_4(COMPOUND4args *argp, CLIENT *clnt)
{
	static COMPOUND4res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, NFSPROC4_COMPOUND,
		(xdrproc_t) xdr_COMPOUND4args, (caddr_t) argp,
		(xdrproc_t) xdr_COMPOUND4res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

void *
cb_null_1(void *argp, CLIENT *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, CB_NULL,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

CB_COMPOUND4res *
cb_compound_1(CB_COMPOUND4args *argp, CLIENT *clnt)
{
	static CB_COMPOUND4res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, CB_COMPOUND,
		(xdrproc_t) xdr_CB_COMPOUND4args, (caddr_t) argp,
		(xdrproc_t) xdr_CB_COMPOUND4res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
