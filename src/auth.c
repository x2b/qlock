#include <string.h>
#include <gcrypt.h>
#include <assert.h>

#include "auth.h"

#define BUFLEN 1024
#define ITNUM 100

#define MAX(A,B)	( (A) > (B) ? (A):(B)) 

int compute_hash(const char* str, char hash[HASHLEN], char salt[SALTLEN])
{
  char buf[BUFLEN];
  int  i;
  int  slen  = strlen(str);
  
  assert(gcry_md_get_algo_dlen( GCRY_MD_SHA1 ) == HASHLEN);
  memset(buf, 0, BUFLEN);
  memcpy(buf, salt, SALTLEN);
  strncpy(buf + SALTLEN, str, BUFLEN - SALTLEN);
  
  gcry_md_hash_buffer( GCRY_MD_SHA1, hash, buf, SALTLEN + slen );
  
  for(i = 0; i < ITNUM - 1; ++i)
  {
    memcpy(buf + SALTLEN, hash, HASHLEN);
    gcry_md_hash_buffer( GCRY_MD_SHA1, hash, buf, SALTLEN + HASHLEN );
  }
  return 1;
}

int str2hex(const char* src, char* dst)
{
  int n;
  unsigned int u;
  char *ptr;
  const char *end;
  
  n = strlen(src);
  if(n % 2 != 0)
    return 0;
    
  ptr = dst;
  end = src + n;
    
  while (src < end && sscanf(src, "%2x", &u) == 1)
  {
    *ptr++ = u;
    src += 2;
  }
    
  return 1;
}

void hex2str(const char* hex, char* dst, int n)
{
  char *ptr, *end;
  
  end = dst + 2*n;
  
  for(ptr = dst; ptr != end; ptr+=2)
  {
    sprintf(ptr, "%02x", (unsigned char) *hex++);
  }
  
  dst[2*n] = '\0';
  return;
}

int read_auth(auth** ptr, const char *fname)
{
  char line[100];
  char name[100];
  char storage[2*MAX(HASHLEN, SALTLEN)+1];
  char *tmp;
  auth* a;
  
  (*ptr) = (auth*) malloc(sizeof(auth));
  a = *ptr;
  a->file = NULL;
  
  if(!(a->file = fopen(fname, "r")))
    goto cleanup;
  
  while(NULL != fgets(line, sizeof(line), a->file))
  {
    tmp = strchr(line, ':');
    if(tmp == NULL)
      continue;
    strncpy(name, line, tmp - line);
    name[tmp - line] = '\0';
    
    if(!strcmp(name, "hash"))
    {
      assert(strlen(tmp) >= 2*HASHLEN + 1);
      strncpy(storage, tmp + 2, 2*HASHLEN);
      storage[2*HASHLEN] = '\0';
            
      if(!str2hex(storage, a->hash))
        goto cleanup;
    }
    else if(!strcmp(name, "salt"))
    {
      assert(strlen(tmp) >= 2*HASHLEN + 1);
      strncpy(storage, tmp + 2, 2*SALTLEN);
      storage[2*SALTLEN] = '\0';
      if(!str2hex(storage, a->salt))
        goto cleanup;
    }
    else
      goto cleanup;
  }
  
  return 1;
  
  cleanup:
  free_auth(ptr);
  return 0;
}

int create_auth(auth** ptr, const char *fname, const char *str)
{
  char storage[2*MAX(HASHLEN,SALTLEN) + 1];
  auth* a;
  
  (*ptr) = (auth*) malloc(sizeof(auth));
  a = *ptr;
  a->file = NULL;
  
  if(!(a->file = fopen(fname, "w")))
    goto cleanup;
    
  gcry_randomize(a->salt, SALTLEN, GCRY_STRONG_RANDOM);
  
  compute_hash(str, a->hash, a->salt);
  
  hex2str(a->hash, storage, HASHLEN);
  fprintf(a->file, "hash: %s\n", storage);
  
  hex2str(a->salt, storage, HASHLEN);
  fprintf(a->file, "salt: %s\n", storage);
    
  return 1;
    
  cleanup:
  free_auth(ptr);
  return 0;
}

void free_auth(auth** ptr)
{
  if(NULL == *ptr)
    return;
  
  if(NULL != (*ptr)->file)
    fclose((*ptr)->file);
    
  *ptr = NULL;
}

int verify(auth* a, const char* key)
{
  char hash[HASHLEN];
  
  if(a == NULL)
    return 0;
  
  compute_hash(key, hash, a->salt);
  return memcmp(hash, a->hash, HASHLEN) == 0;
}


#ifdef MAIN

int main(int argc, char** argv)
{
  auth* a;
  int i;
  
  create_auth(&a, ".testpass", "testpasswd");
  
  assert(verify(a, "testpasswd"));
  
  assert(!verify(a, "not quite right..."));
  
  free_auth(&a);
  
  return 0;
}


#endif
