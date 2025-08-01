#ifndef HEADER_CURL_TOOL_SETOPT_H
#define HEADER_CURL_TOOL_SETOPT_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include "tool_setup.h"

#include "tool_formparse.h"

/*
 * Macros used in operate()
 */

#ifndef CURL_DISABLE_LIBCURL_OPTION

/* Associate symbolic names with option values */
struct NameValue {
  const char *name;
  long value;
};

struct NameValueUnsigned {
  const char *name;
  unsigned long value;
};

extern const struct NameValue setopt_nv_CURLPROXY[];
extern const struct NameValue setopt_nv_CURL_SOCKS_PROXY[];
extern const struct NameValue setopt_nv_CURL_HTTP_VERSION[];
extern const struct NameValue setopt_nv_CURL_SSLVERSION[];
extern const struct NameValue setopt_nv_CURL_SSLVERSION_MAX[];
extern const struct NameValue setopt_nv_CURL_TIMECOND[];
extern const struct NameValue setopt_nv_CURLFTPSSL_CCC[];
extern const struct NameValue setopt_nv_CURLUSESSL[];
extern const struct NameValueUnsigned setopt_nv_CURLSSLOPT[];
extern const struct NameValue setopt_nv_CURL_NETRC[];
extern const struct NameValueUnsigned setopt_nv_CURLAUTH[];
extern const struct NameValueUnsigned setopt_nv_CURLHSTS[];

/* Map options to NameValue sets */
#define setopt_nv_CURLOPT_HSTS_CTRL setopt_nv_CURLHSTS
#define setopt_nv_CURLOPT_HTTP_VERSION setopt_nv_CURL_HTTP_VERSION
#define setopt_nv_CURLOPT_HTTPAUTH setopt_nv_CURLAUTH
#define setopt_nv_CURLOPT_SSLVERSION setopt_nv_CURL_SSLVERSION
#define setopt_nv_CURLOPT_PROXY_SSLVERSION setopt_nv_CURL_SSLVERSION
#define setopt_nv_CURLOPT_TIMECONDITION setopt_nv_CURL_TIMECOND
#define setopt_nv_CURLOPT_FTP_SSL_CCC setopt_nv_CURLFTPSSL_CCC
#define setopt_nv_CURLOPT_USE_SSL setopt_nv_CURLUSESSL
#define setopt_nv_CURLOPT_SSL_OPTIONS setopt_nv_CURLSSLOPT
#define setopt_nv_CURLOPT_PROXY_SSL_OPTIONS setopt_nv_CURLSSLOPT
#define setopt_nv_CURLOPT_NETRC setopt_nv_CURL_NETRC
#define setopt_nv_CURLOPT_PROXYTYPE setopt_nv_CURLPROXY
#define setopt_nv_CURLOPT_PROXYAUTH setopt_nv_CURLAUTH
#define setopt_nv_CURLOPT_SOCKS5_AUTH setopt_nv_CURLAUTH

/* Intercept setopt calls for --libcurl */

CURLcode tool_setopt_enum(CURL *curl, struct OperationConfig *config,
                          const char *name, CURLoption tag,
                          const struct NameValue *nv, long lval);
CURLcode tool_setopt_SSLVERSION(CURL *curl, struct OperationConfig *config,
                                const char *name, CURLoption tag,
                                long lval);
CURLcode tool_setopt_flags(CURL *curl, struct OperationConfig *config,
                           const char *name, CURLoption tag,
                           const struct NameValue *nv, long lval);
CURLcode tool_setopt_bitmask(CURL *curl, struct OperationConfig *config,
                             const char *name, CURLoption tag,
                             const struct NameValueUnsigned *nv, long lval);
CURLcode tool_setopt_mimepost(CURL *curl, struct OperationConfig *config,
                              const char *name, CURLoption tag,
                              curl_mime *mimepost);
CURLcode tool_setopt_slist(CURL *curl, struct OperationConfig *config,
                           const char *name, CURLoption tag,
                           struct curl_slist *list);
CURLcode tool_setopt_long(CURL *curl, struct OperationConfig *config,
                          const char *name, CURLoption tag,
                          long lval);
CURLcode tool_setopt_offt(CURL *curl, struct OperationConfig *config,
                          const char *name, CURLoption tag,
                          curl_off_t lval);
CURLcode tool_setopt(CURL *curl, bool str,
                     struct OperationConfig *config,
                     const char *name, CURLoption tag, ...);

#define my_setopt(x,y,z) \
  tool_setopt(x, FALSE, config, #y, y, z)

#define my_setopt_long(x,y,z) \
  tool_setopt_long(x, config, #y, y, z)

#define my_setopt_offt(x,y,z) \
  tool_setopt_offt(x, config, #y, y, z)

#define my_setopt_str(x,y,z) \
  tool_setopt(x, TRUE, config, #y, y, z)

#define my_setopt_enum(x,y,z) \
  tool_setopt_enum(x, config, #y, y, setopt_nv_ ## y, z)

#define my_setopt_SSLVERSION(x,y,z) \
  tool_setopt_SSLVERSION(x, config, #y, y, z)

#define my_setopt_bitmask(x,y,z) \
  tool_setopt_bitmask(x, config, #y, y, setopt_nv_ ## y, z)

#define my_setopt_mimepost(x,y,z) \
  tool_setopt_mimepost(x, config, #y, y, z)

#define my_setopt_slist(x,y,z) \
  tool_setopt_slist(x, config, #y, y, z)

#else /* CURL_DISABLE_LIBCURL_OPTION */

/* No --libcurl, so pass options directly to library */

#define my_setopt(x,y,z) \
  curl_easy_setopt(x, y, z)

#define my_setopt_long(x,y,z) \
  curl_easy_setopt(x, y, (long)(z))

#define my_setopt_offt(x,y,z) \
  curl_easy_setopt(x, y, (curl_off_t)(z))

#define my_setopt_str(x,y,z)                    \
  curl_easy_setopt(x, y, z)

#define my_setopt_enum(x,y,z) \
  curl_easy_setopt(x, y, z)

#define my_setopt_SSLVERSION(x,y,z) \
  curl_easy_setopt(x, y, z)

#define my_setopt_bitmask(x,y,z) \
  curl_easy_setopt(x, y, (long)z)

#define my_setopt_mimepost(x,y,z) \
  curl_easy_setopt(x, y, z)

#define my_setopt_slist(x,y,z) \
  curl_easy_setopt(x, y, z)

#endif /* CURL_DISABLE_LIBCURL_OPTION */

#endif /* HEADER_CURL_TOOL_SETOPT_H */
