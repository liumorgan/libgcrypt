/* cipher.h
 *	Copyright (C) 1998, 2002, 2003 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser general Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifndef G10_CIPHER_H
#define G10_CIPHER_H


#define DBG_CIPHER _gcry_get_debug_flag( 1 )

#include "../cipher/random.h"

#define PUBKEY_FLAG_NO_BLINDING 0x00000001

#define is_RSA(a)     ((a)==GCRY_PK_RSA || (a)==GCRY_PK_RSA_E \
		       || (a)==GCRY_PK_RSA_S )
#define is_ELGAMAL(a) ((a)==GCRY_PK_ELG || (a)==GCRY_PK_ELG_E)


/*-- rmd160.c --*/
void _gcry_rmd160_hash_buffer( char *outbuf, const char *buffer, size_t length );


/*-- smallprime.c --*/
extern ushort small_prime_numbers[];

/*-- dsa.c --*/
void _gcry_register_pk_dsa_progress (void (*cb)(void *,const char *,
                                                int,int,int),
                                     void *cb_data );
/*-- elgamal.c --*/
void _gcry_register_pk_elg_progress (void (*cb)(void *,const char *,
                                                int,int,int),
                                     void *cb_data );
/*-- primegen.c --*/
void _gcry_register_primegen_progress (void (*cb)(void *,const char *,
                                                int,int,int),
                                       void *cb_data );

typedef struct gcry_pubkey_spec
{
  const char *name;
  int id;
  int npkey;
  int nskey;
  int nenc;
  int nsig;
  int use;
  int (*generate) (int algo, unsigned int nbits, unsigned long use_e,
		   GcryMPI *skey, GcryMPI **retfactors);
  int (*check_secret_key) (int algo, GcryMPI *skey);
  int (*encrypt) (int algo, GcryMPI *resarr, GcryMPI data, GcryMPI *pkey, int flags);
  int (*decrypt) (int algo, GcryMPI *result, GcryMPI *data, GcryMPI *skey, int flags);
  int (*sign) (int algo, GcryMPI *resarr, GcryMPI data, GcryMPI *skey);
  int (*verify) (int algo, GcryMPI hash, GcryMPI *data, GcryMPI *pkey,
		 int (*cmp)(void *, GcryMPI), void *opaquev);
  unsigned (*get_nbits) (int algo, GcryMPI *pkey);
} GcryPubkeySpec;

typedef struct gcry_digest_spec
{
  const char *name;
  int id;
  unsigned char *asnoid;
  int asnlen;
  int mdlen;
  void (*init) (void *c);
  void (*write) (void *c, unsigned char *buf, size_t nbytes);
  void (*final) (void *c);
  unsigned char *(*read) (void *c);
  size_t contextsize; /* allocate this amount of context */
} GcryDigestSpec;

typedef struct gcry_cipher_spec
{
  const char *name;
  int id;
  size_t blocksize;
  size_t keylen;
  size_t contextsize;
  int  (*setkey) (void *c, const unsigned char *key, unsigned keylen);
  void (*encrypt) (void *c, unsigned char *outbuf, const unsigned char *inbuf);
  void (*decrypt) (void *c, unsigned char *outbuf, const unsigned char *inbuf);
  void (*stencrypt) (void *c, unsigned char *outbuf, const unsigned char *inbuf,
		     unsigned int n);
  void (*stdecrypt) (void *c, unsigned char *outbuf, const unsigned char *inbuf,
		     unsigned int n);
} GcryCipherSpec;

/* Declarations for the cipher specifications.  */
extern GcryCipherSpec cipher_spec_blowfish;
extern GcryCipherSpec cipher_spec_des;
extern GcryCipherSpec cipher_spec_tripledes;
extern GcryCipherSpec cipher_spec_arcfour;
extern GcryCipherSpec cipher_spec_cast5;
extern GcryCipherSpec cipher_spec_aes;
extern GcryCipherSpec cipher_spec_aes192;
extern GcryCipherSpec cipher_spec_aes256;
extern GcryCipherSpec cipher_spec_twofish;
extern GcryCipherSpec cipher_spec_twofish128;

/* Declarations for the digest specifications.  */
extern GcryDigestSpec digest_spec_crc32;
extern GcryDigestSpec digest_spec_crc32_rfc1510;
extern GcryDigestSpec digest_spec_crc24_rfc2440;
extern GcryDigestSpec digest_spec_md4;
extern GcryDigestSpec digest_spec_md5;
extern GcryDigestSpec digest_spec_rmd160;
extern GcryDigestSpec digest_spec_sha1;
extern GcryDigestSpec digest_spec_sha256;
extern GcryDigestSpec digest_spec_sha512;
extern GcryDigestSpec digest_spec_sha384;
extern GcryDigestSpec digest_spec_tiger;

/* Declarations for the pubkey cipher specifications.  */
extern GcryPubkeySpec pubkey_spec_rsa;
extern GcryPubkeySpec pubkey_spec_elg;
extern GcryPubkeySpec pubkey_spec_dsa;


#endif /*G10_CIPHER_H*/

