/* dynload.5
 *	Copyright (C) 1998 Free Software Foundation, Inc.
 *
 * This file is part of GNUPG.
 *
 * GNUPG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifndef G10_CIPHER_DYNLOAD_H
#define G10_CIPHER_DYNLOAD_H

int
enum_gnupgext_digests( void **enum_context,
	    int *algo,
	    const char *(**r_get_info)( int, size_t*,byte**, int*, int*,
				       void (**)(void*),
				       void (**)(void*,byte*,size_t),
				       void (**)(void*),byte *(**)(void*)) );

const char *
enum_gnupgext_ciphers( void **enum_context, int *algo,
		       size_t *keylen, size_t *blocksize, size_t *contextsize,
		       void (**setkey)( void *c, byte *key, unsigned keylen ),
		       void (**encrypt)( void *c, byte *outbuf, byte *inbuf ),
		       void (**decrypt)( void *c, byte *outbuf, byte *inbuf )
		     );


const char *
enum_gnupgext_pubkeys( void **enum_context, int *algo,
    int *npkey, int *nskey, int *nenc, int *nsig, int *usage,
    int (**generate)( int algo, unsigned nbits, MPI *skey, MPI **retfactors ),
    int (**check_secret_key)( int algo, MPI *skey ),
    int (**encrypt)( int algo, MPI *resarr, MPI data, MPI *pkey ),
    int (**decrypt)( int algo, MPI *result, MPI *data, MPI *skey ),
    int (**sign)( int algo, MPI *resarr, MPI data, MPI *skey ),
    int (**verify)( int algo, MPI hash, MPI *data, MPI *pkey,
		    int (*cmp)(void *, MPI), void *opaquev ),
    unsigned (**get_nbits)( int algo, MPI *pkey ) );

#endif /*G10_CIPHER_DYNLOAD_H*/