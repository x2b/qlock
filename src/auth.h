#ifndef AUTH_H
#define AUTH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define SALTLEN 20
#define HASHLEN 20

/**
 * Compute hash function
 * \param str  a zero terminated string containig the passkey
 * \param hash an array that will be filled with the result
 * \param salt the salt to be added to the hash function
 * \return 1 on success, 0 on failure
 */
int compute_hash(const char* str,
  char hash[HASHLEN],
  char salt[SALTLEN]);

/**
 * Convert a string to binary data
 * \param str the zero terminated string containing an even number of
 *  hex digits
 * \param dst the destination of the operation, it should have at
 *  least strlen(str)/2 bytes available
 * \return 1 on success, 0 on failure
 */
int str2hex(const char* str,
  char* dst);

/**
 * Convert binary data to a hexadecimal representation
 * \param hex the pointer to the binary data
 * \param dst the destination of the operation, it should have
 *  at least 2*n+1 bytes available
 * \param n   the length of the binary data
 */
void hex2str(const char* hex,
  char* dst,
  int n);

/**
 * A structure holding a particular hash/salt, stored in a file
 */
typedef struct {
  FILE *file;          /** the file containing hash/salt*/
  char  hash[HASHLEN]; /** the hash*/
  char  salt[SALTLEN]; /** the salt*/
} auth;

/**
 * A function to read the contents of a file into an auth structure
 * \param ptr   a pointer to an auth structure, *ptr will be allocated
 *  and initialized
 * \param fname the name of the file to be opened
 * \return 1 on success, 0 on failure
 */
int read_auth(auth** ptr,
  const char *fname);

/**
 * A function to create a new file and associated auth structure
 * \param ptr   a pointer to an auth structure, *ptr will be allocated
 *  and initialized
 * \param fname the name of the file to be opened
 * \param str   the password to be stored as a zero terminated string
 * \return 1 on success, 0 on failure
 */
int create_auth(auth** ptr,
  const char *fname,
  const char *str);

/**
 * A function to release an auth structure
 * \param ptr   a pointer to an auth structure, the structure will be
 *  freed, *ptr set to NULL
 */
void free_auth(auth** ptr);

/**
 * A function to verify a passkey against an auth structure
 * \param a   the auth structure to be used
 * \param key the key to be verified
 * \return  1 if the key matches the one stored in the structure,
 *  0 otherwise
 */
int verify(auth* a, const char* key);

#ifdef __cplusplus
}
#endif

#endif
