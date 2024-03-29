﻿//==============================================================================
// Consts.cpp
//==============================================================================
#include "stdafx.h"

#define AssignConst(name) frame.Assign(#name, new Value_Number(name))

Gurax_BeginModuleScope(curl)

void AssignConsts(Frame& frame)
{
	// CURLcode
	AssignConst(CURLE_OK);
	AssignConst(CURLE_UNSUPPORTED_PROTOCOL);
	AssignConst(CURLE_FAILED_INIT);
	AssignConst(CURLE_URL_MALFORMAT);
	AssignConst(CURLE_NOT_BUILT_IN);
	AssignConst(CURLE_COULDNT_RESOLVE_PROXY);
	AssignConst(CURLE_COULDNT_RESOLVE_HOST);
	AssignConst(CURLE_COULDNT_CONNECT);
	AssignConst(CURLE_WEIRD_SERVER_REPLY);
	AssignConst(CURLE_REMOTE_ACCESS_DENIED);
	AssignConst(CURLE_FTP_ACCEPT_FAILED);
	AssignConst(CURLE_FTP_WEIRD_PASS_REPLY);
	AssignConst(CURLE_FTP_ACCEPT_TIMEOUT);
	AssignConst(CURLE_FTP_WEIRD_PASV_REPLY);
	AssignConst(CURLE_FTP_WEIRD_227_FORMAT);
	AssignConst(CURLE_FTP_CANT_GET_HOST);
	AssignConst(CURLE_HTTP2);
	AssignConst(CURLE_FTP_COULDNT_SET_TYPE);
	AssignConst(CURLE_PARTIAL_FILE);
	AssignConst(CURLE_FTP_COULDNT_RETR_FILE);
	AssignConst(CURLE_OBSOLETE20);
	AssignConst(CURLE_QUOTE_ERROR);
	AssignConst(CURLE_HTTP_RETURNED_ERROR);
	AssignConst(CURLE_WRITE_ERROR);
	AssignConst(CURLE_OBSOLETE24);
	AssignConst(CURLE_UPLOAD_FAILED);
	AssignConst(CURLE_READ_ERROR);
	AssignConst(CURLE_OUT_OF_MEMORY);
	AssignConst(CURLE_OPERATION_TIMEDOUT);
	AssignConst(CURLE_OBSOLETE29);
	AssignConst(CURLE_FTP_PORT_FAILED);
	AssignConst(CURLE_FTP_COULDNT_USE_REST);
	AssignConst(CURLE_OBSOLETE32);
	AssignConst(CURLE_RANGE_ERROR);
	AssignConst(CURLE_HTTP_POST_ERROR);
	AssignConst(CURLE_SSL_CONNECT_ERROR);
	AssignConst(CURLE_BAD_DOWNLOAD_RESUME);
	AssignConst(CURLE_FILE_COULDNT_READ_FILE);
	AssignConst(CURLE_LDAP_CANNOT_BIND);
	AssignConst(CURLE_LDAP_SEARCH_FAILED);
	AssignConst(CURLE_OBSOLETE40);
	AssignConst(CURLE_FUNCTION_NOT_FOUND);
	AssignConst(CURLE_ABORTED_BY_CALLBACK);
	AssignConst(CURLE_BAD_FUNCTION_ARGUMENT);
	AssignConst(CURLE_OBSOLETE44);
	AssignConst(CURLE_INTERFACE_FAILED);
	AssignConst(CURLE_OBSOLETE46);
	AssignConst(CURLE_TOO_MANY_REDIRECTS);
	AssignConst(CURLE_UNKNOWN_OPTION);
	AssignConst(CURLE_TELNET_OPTION_SYNTAX);
	AssignConst(CURLE_OBSOLETE50);
	AssignConst(CURLE_OBSOLETE51);
	AssignConst(CURLE_GOT_NOTHING);
	AssignConst(CURLE_SSL_ENGINE_NOTFOUND);
	AssignConst(CURLE_SSL_ENGINE_SETFAILED);
	AssignConst(CURLE_SEND_ERROR);
	AssignConst(CURLE_RECV_ERROR);
	AssignConst(CURLE_OBSOLETE57);
	AssignConst(CURLE_SSL_CERTPROBLEM);
	AssignConst(CURLE_SSL_CIPHER);
	AssignConst(CURLE_PEER_FAILED_VERIFICATION);
	AssignConst(CURLE_BAD_CONTENT_ENCODING);
	AssignConst(CURLE_LDAP_INVALID_URL);
	AssignConst(CURLE_FILESIZE_EXCEEDED);
	AssignConst(CURLE_USE_SSL_FAILED);
	AssignConst(CURLE_SEND_FAIL_REWIND);
	AssignConst(CURLE_SSL_ENGINE_INITFAILED);
	AssignConst(CURLE_LOGIN_DENIED);
	AssignConst(CURLE_TFTP_NOTFOUND);
	AssignConst(CURLE_TFTP_PERM);
	AssignConst(CURLE_REMOTE_DISK_FULL);
	AssignConst(CURLE_TFTP_ILLEGAL);
	AssignConst(CURLE_TFTP_UNKNOWNID);
	AssignConst(CURLE_REMOTE_FILE_EXISTS);
	AssignConst(CURLE_TFTP_NOSUCHUSER);
	AssignConst(CURLE_CONV_FAILED);
	AssignConst(CURLE_CONV_REQD);
	AssignConst(CURLE_SSL_CACERT_BADFILE);
	AssignConst(CURLE_REMOTE_FILE_NOT_FOUND);
	AssignConst(CURLE_SSH);
	AssignConst(CURLE_SSL_SHUTDOWN_FAILED);
	AssignConst(CURLE_AGAIN);
	AssignConst(CURLE_SSL_CRL_BADFILE);
	AssignConst(CURLE_SSL_ISSUER_ERROR);
	AssignConst(CURLE_FTP_PRET_FAILED);
	AssignConst(CURLE_RTSP_CSEQ_ERROR);
	AssignConst(CURLE_RTSP_SESSION_ERROR);
	AssignConst(CURLE_FTP_BAD_FILE_LIST);
	AssignConst(CURLE_CHUNK_FAILED);
	AssignConst(CURLE_NO_CONNECTION_AVAILABLE);
	AssignConst(CURLE_SSL_PINNEDPUBKEYNOTMATCH);
	AssignConst(CURLE_SSL_INVALIDCERTSTATUS);
	AssignConst(CURLE_HTTP2_STREAM);
	AssignConst(CURLE_RECURSIVE_API_CALL);
	AssignConst(CURLE_AUTH_ERROR);
	AssignConst(CURLE_HTTP3);
	AssignConst(CURLE_QUIC_CONNECT_ERROR);
	AssignConst(CURLE_PROXY);
	AssignConst(CURL_LAST);
	AssignConst(CURLE_OBSOLETE16);
	AssignConst(CURLE_OBSOLETE10);
	AssignConst(CURLE_OBSOLETE12);
	AssignConst(CURLE_FTP_WEIRD_SERVER_REPLY);
	AssignConst(CURLE_SSL_CACERT);
	AssignConst(CURLE_UNKNOWN_TELNET_OPTION);
	AssignConst(CURLE_SSL_PEER_CERTIFICATE);
	AssignConst(CURLE_OBSOLETE);
	AssignConst(CURLE_BAD_PASSWORD_ENTERED);
	AssignConst(CURLE_BAD_CALLING_ORDER);
	AssignConst(CURLE_FTP_USER_PASSWORD_INCORRECT);
	AssignConst(CURLE_FTP_CANT_RECONNECT);
	AssignConst(CURLE_FTP_COULDNT_GET_SIZE);
	AssignConst(CURLE_FTP_COULDNT_SET_ASCII);
	AssignConst(CURLE_FTP_WEIRD_USER_REPLY);
	AssignConst(CURLE_FTP_WRITE_ERROR);
	AssignConst(CURLE_LIBRARY_NOT_FOUND);
	AssignConst(CURLE_MALFORMAT_USER);
	AssignConst(CURLE_SHARE_IN_USE);
	AssignConst(CURLE_URL_MALFORMAT_USER);
	AssignConst(CURLE_FTP_ACCESS_DENIED);
	AssignConst(CURLE_FTP_COULDNT_SET_BINARY);
	AssignConst(CURLE_FTP_QUOTE_ERROR);
	AssignConst(CURLE_TFTP_DISKFULL);
	AssignConst(CURLE_TFTP_EXISTS);
	AssignConst(CURLE_HTTP_RANGE_ERROR);
	AssignConst(CURLE_FTP_SSL_FAILED);
	AssignConst(CURLE_OPERATION_TIMEOUTED);
	AssignConst(CURLE_HTTP_NOT_FOUND);
	AssignConst(CURLE_HTTP_PORT_FAILED);
	AssignConst(CURLE_FTP_COULDNT_STOR_FILE);
	AssignConst(CURLE_FTP_PARTIAL_FILE);
	AssignConst(CURLE_FTP_BAD_DOWNLOAD_RESUME);
	AssignConst(CURLE_ALREADY_COMPLETE);
	// CURLOPTTYPE	
	AssignConst(CURLOPTTYPE_LONG);
	AssignConst(CURLOPTTYPE_OBJECTPOINT);
	AssignConst(CURLOPTTYPE_FUNCTIONPOINT);
	AssignConst(CURLOPTTYPE_OFF_T);
	AssignConst(CURLOPTTYPE_BLOB);
	AssignConst(CURLOPTTYPE_STRINGPOINT);
	AssignConst(CURLOPTTYPE_SLISTPOINT);
	AssignConst(CURLOPTTYPE_CBPOINT);
	AssignConst(CURLOPTTYPE_VALUES);
	// CURLoption
	AssignConst(CURLOPT_WRITEDATA);
	AssignConst(CURLOPT_URL);
	AssignConst(CURLOPT_PORT);
	AssignConst(CURLOPT_PROXY);
	AssignConst(CURLOPT_USERPWD);
	AssignConst(CURLOPT_PROXYUSERPWD);
	AssignConst(CURLOPT_RANGE);
	AssignConst(CURLOPT_READDATA);
	AssignConst(CURLOPT_ERRORBUFFER);
	AssignConst(CURLOPT_WRITEFUNCTION);
	AssignConst(CURLOPT_READFUNCTION);
	AssignConst(CURLOPT_TIMEOUT);
	AssignConst(CURLOPT_INFILESIZE);
	AssignConst(CURLOPT_POSTFIELDS);
	AssignConst(CURLOPT_REFERER);
	AssignConst(CURLOPT_FTPPORT);
	AssignConst(CURLOPT_USERAGENT);
	AssignConst(CURLOPT_LOW_SPEED_LIMIT);
	AssignConst(CURLOPT_LOW_SPEED_TIME);
	AssignConst(CURLOPT_RESUME_FROM);
	AssignConst(CURLOPT_COOKIE);
	AssignConst(CURLOPT_HTTPHEADER);
	AssignConst(CURLOPT_HTTPPOST);
	AssignConst(CURLOPT_SSLCERT);
	AssignConst(CURLOPT_KEYPASSWD);
	AssignConst(CURLOPT_CRLF);
	AssignConst(CURLOPT_QUOTE);
	AssignConst(CURLOPT_HEADERDATA);
	AssignConst(CURLOPT_COOKIEFILE);
	AssignConst(CURLOPT_SSLVERSION);
	AssignConst(CURLOPT_TIMECONDITION);
	AssignConst(CURLOPT_TIMEVALUE);
	AssignConst(CURLOPT_CUSTOMREQUEST);
	AssignConst(CURLOPT_STDERR);
	AssignConst(CURLOPT_POSTQUOTE);
	AssignConst(CURLOPT_OBSOLETE40);
	AssignConst(CURLOPT_VERBOSE);
	AssignConst(CURLOPT_HEADER);
	AssignConst(CURLOPT_NOPROGRESS);
	AssignConst(CURLOPT_NOBODY);
	AssignConst(CURLOPT_FAILONERROR);
	AssignConst(CURLOPT_UPLOAD);
	AssignConst(CURLOPT_POST);
	AssignConst(CURLOPT_DIRLISTONLY);
	AssignConst(CURLOPT_APPEND);
	AssignConst(CURLOPT_NETRC);
	AssignConst(CURLOPT_FOLLOWLOCATION);
	AssignConst(CURLOPT_TRANSFERTEXT);
	AssignConst(CURLOPT_PUT);
	AssignConst(CURLOPT_PROGRESSFUNCTION);
	AssignConst(CURLOPT_XFERINFODATA);
	AssignConst(CURLOPT_AUTOREFERER);
	AssignConst(CURLOPT_PROXYPORT);
	AssignConst(CURLOPT_POSTFIELDSIZE);
	AssignConst(CURLOPT_HTTPPROXYTUNNEL);
	AssignConst(CURLOPT_INTERFACE);
	AssignConst(CURLOPT_KRBLEVEL);
	AssignConst(CURLOPT_SSL_VERIFYPEER);
	AssignConst(CURLOPT_CAINFO);
	AssignConst(CURLOPT_MAXREDIRS);
	AssignConst(CURLOPT_FILETIME);
	AssignConst(CURLOPT_TELNETOPTIONS);
	AssignConst(CURLOPT_MAXCONNECTS);
	AssignConst(CURLOPT_OBSOLETE72);
	AssignConst(CURLOPT_FRESH_CONNECT);
	AssignConst(CURLOPT_FORBID_REUSE);
	AssignConst(CURLOPT_RANDOM_FILE);
	AssignConst(CURLOPT_EGDSOCKET);
	AssignConst(CURLOPT_CONNECTTIMEOUT);
	AssignConst(CURLOPT_HEADERFUNCTION);
	AssignConst(CURLOPT_HTTPGET);
	AssignConst(CURLOPT_SSL_VERIFYHOST);
	AssignConst(CURLOPT_COOKIEJAR);
	AssignConst(CURLOPT_SSL_CIPHER_LIST);
	AssignConst(CURLOPT_HTTP_VERSION);
	AssignConst(CURLOPT_FTP_USE_EPSV);
	AssignConst(CURLOPT_SSLCERTTYPE);
	AssignConst(CURLOPT_SSLKEY);
	AssignConst(CURLOPT_SSLKEYTYPE);
	AssignConst(CURLOPT_SSLENGINE);
	AssignConst(CURLOPT_SSLENGINE_DEFAULT);
	AssignConst(CURLOPT_DNS_USE_GLOBAL_CACHE);
	AssignConst(CURLOPT_DNS_CACHE_TIMEOUT);
	AssignConst(CURLOPT_PREQUOTE);
	AssignConst(CURLOPT_DEBUGFUNCTION);
	AssignConst(CURLOPT_DEBUGDATA);
	AssignConst(CURLOPT_COOKIESESSION);
	AssignConst(CURLOPT_CAPATH);
	AssignConst(CURLOPT_BUFFERSIZE);
	AssignConst(CURLOPT_NOSIGNAL);
	AssignConst(CURLOPT_SHARE);
	AssignConst(CURLOPT_PROXYTYPE);
	AssignConst(CURLOPT_ACCEPT_ENCODING);
	AssignConst(CURLOPT_PRIVATE);
	AssignConst(CURLOPT_HTTP200ALIASES);
	AssignConst(CURLOPT_UNRESTRICTED_AUTH);
	AssignConst(CURLOPT_FTP_USE_EPRT);
	AssignConst(CURLOPT_HTTPAUTH);
	AssignConst(CURLOPT_SSL_CTX_FUNCTION);
	AssignConst(CURLOPT_SSL_CTX_DATA);
	AssignConst(CURLOPT_FTP_CREATE_MISSING_DIRS);
	AssignConst(CURLOPT_PROXYAUTH);
	AssignConst(CURLOPT_FTP_RESPONSE_TIMEOUT);
	AssignConst(CURLOPT_IPRESOLVE);
	AssignConst(CURLOPT_MAXFILESIZE);
	AssignConst(CURLOPT_INFILESIZE_LARGE);
	AssignConst(CURLOPT_RESUME_FROM_LARGE);
	AssignConst(CURLOPT_MAXFILESIZE_LARGE);
	AssignConst(CURLOPT_NETRC_FILE);
	AssignConst(CURLOPT_USE_SSL);
	AssignConst(CURLOPT_POSTFIELDSIZE_LARGE);
	AssignConst(CURLOPT_TCP_NODELAY);
	AssignConst(CURLOPT_FTPSSLAUTH);
	AssignConst(CURLOPT_IOCTLFUNCTION);
	AssignConst(CURLOPT_IOCTLDATA);
	AssignConst(CURLOPT_FTP_ACCOUNT);
	AssignConst(CURLOPT_COOKIELIST);
	AssignConst(CURLOPT_IGNORE_CONTENT_LENGTH);
	AssignConst(CURLOPT_FTP_SKIP_PASV_IP);
	AssignConst(CURLOPT_FTP_FILEMETHOD);
	AssignConst(CURLOPT_LOCALPORT);
	AssignConst(CURLOPT_LOCALPORTRANGE);
	AssignConst(CURLOPT_CONNECT_ONLY);
	AssignConst(CURLOPT_CONV_FROM_NETWORK_FUNCTION);
	AssignConst(CURLOPT_CONV_TO_NETWORK_FUNCTION);
	AssignConst(CURLOPT_CONV_FROM_UTF8_FUNCTION);
	AssignConst(CURLOPT_MAX_SEND_SPEED_LARGE);
	AssignConst(CURLOPT_MAX_RECV_SPEED_LARGE);
	AssignConst(CURLOPT_FTP_ALTERNATIVE_TO_USER);
	AssignConst(CURLOPT_SOCKOPTFUNCTION);
	AssignConst(CURLOPT_SOCKOPTDATA);
	AssignConst(CURLOPT_SSL_SESSIONID_CACHE);
	AssignConst(CURLOPT_SSH_AUTH_TYPES);
	AssignConst(CURLOPT_SSH_PUBLIC_KEYFILE);
	AssignConst(CURLOPT_SSH_PRIVATE_KEYFILE);
	AssignConst(CURLOPT_FTP_SSL_CCC);
	AssignConst(CURLOPT_TIMEOUT_MS);
	AssignConst(CURLOPT_CONNECTTIMEOUT_MS);
	AssignConst(CURLOPT_HTTP_TRANSFER_DECODING);
	AssignConst(CURLOPT_HTTP_CONTENT_DECODING);
	AssignConst(CURLOPT_NEW_FILE_PERMS);
	AssignConst(CURLOPT_NEW_DIRECTORY_PERMS);
	AssignConst(CURLOPT_POSTREDIR);
	AssignConst(CURLOPT_SSH_HOST_PUBLIC_KEY_MD5);
	AssignConst(CURLOPT_OPENSOCKETFUNCTION);
	AssignConst(CURLOPT_OPENSOCKETDATA);
	AssignConst(CURLOPT_COPYPOSTFIELDS);
	AssignConst(CURLOPT_PROXY_TRANSFER_MODE);
	AssignConst(CURLOPT_SEEKFUNCTION);
	AssignConst(CURLOPT_SEEKDATA);
	AssignConst(CURLOPT_CRLFILE);
	AssignConst(CURLOPT_ISSUERCERT);
	AssignConst(CURLOPT_ADDRESS_SCOPE);
	AssignConst(CURLOPT_CERTINFO);
	AssignConst(CURLOPT_USERNAME);
	AssignConst(CURLOPT_PASSWORD);
	AssignConst(CURLOPT_PROXYUSERNAME);
	AssignConst(CURLOPT_PROXYPASSWORD);
	AssignConst(CURLOPT_NOPROXY);
	AssignConst(CURLOPT_TFTP_BLKSIZE);
	AssignConst(CURLOPT_SOCKS5_GSSAPI_SERVICE);
	AssignConst(CURLOPT_SOCKS5_GSSAPI_NEC);
	AssignConst(CURLOPT_PROTOCOLS);
	AssignConst(CURLOPT_REDIR_PROTOCOLS);
	AssignConst(CURLOPT_SSH_KNOWNHOSTS);
	AssignConst(CURLOPT_SSH_KEYFUNCTION);
	AssignConst(CURLOPT_SSH_KEYDATA);
	AssignConst(CURLOPT_MAIL_FROM);
	AssignConst(CURLOPT_MAIL_RCPT);
	AssignConst(CURLOPT_FTP_USE_PRET);
	AssignConst(CURLOPT_RTSP_REQUEST);
	AssignConst(CURLOPT_RTSP_SESSION_ID);
	AssignConst(CURLOPT_RTSP_STREAM_URI);
	AssignConst(CURLOPT_RTSP_TRANSPORT);
	AssignConst(CURLOPT_RTSP_CLIENT_CSEQ);
	AssignConst(CURLOPT_RTSP_SERVER_CSEQ);
	AssignConst(CURLOPT_INTERLEAVEDATA);
	AssignConst(CURLOPT_INTERLEAVEFUNCTION);
	AssignConst(CURLOPT_WILDCARDMATCH);
	AssignConst(CURLOPT_CHUNK_BGN_FUNCTION);
	AssignConst(CURLOPT_CHUNK_END_FUNCTION);
	AssignConst(CURLOPT_FNMATCH_FUNCTION);
	AssignConst(CURLOPT_CHUNK_DATA);
	AssignConst(CURLOPT_FNMATCH_DATA);
	AssignConst(CURLOPT_RESOLVE);
	AssignConst(CURLOPT_TLSAUTH_USERNAME);
	AssignConst(CURLOPT_TLSAUTH_PASSWORD);
	AssignConst(CURLOPT_TLSAUTH_TYPE);
	AssignConst(CURLOPT_TRANSFER_ENCODING);
	AssignConst(CURLOPT_CLOSESOCKETFUNCTION);
	AssignConst(CURLOPT_CLOSESOCKETDATA);
	AssignConst(CURLOPT_GSSAPI_DELEGATION);
	AssignConst(CURLOPT_DNS_SERVERS);
	AssignConst(CURLOPT_ACCEPTTIMEOUT_MS);
	AssignConst(CURLOPT_TCP_KEEPALIVE);
	AssignConst(CURLOPT_TCP_KEEPIDLE);
	AssignConst(CURLOPT_TCP_KEEPINTVL);
	AssignConst(CURLOPT_SSL_OPTIONS);
	AssignConst(CURLOPT_MAIL_AUTH);
	AssignConst(CURLOPT_SASL_IR);
	AssignConst(CURLOPT_XFERINFOFUNCTION);
	AssignConst(CURLOPT_XOAUTH2_BEARER);
	AssignConst(CURLOPT_DNS_INTERFACE);
	AssignConst(CURLOPT_DNS_LOCAL_IP4);
	AssignConst(CURLOPT_DNS_LOCAL_IP6);
	AssignConst(CURLOPT_LOGIN_OPTIONS);
	AssignConst(CURLOPT_SSL_ENABLE_NPN);
	AssignConst(CURLOPT_SSL_ENABLE_ALPN);
	AssignConst(CURLOPT_EXPECT_100_TIMEOUT_MS);
	AssignConst(CURLOPT_PROXYHEADER);
	AssignConst(CURLOPT_HEADEROPT);
	AssignConst(CURLOPT_PINNEDPUBLICKEY);
	AssignConst(CURLOPT_UNIX_SOCKET_PATH);
	AssignConst(CURLOPT_SSL_VERIFYSTATUS);
	AssignConst(CURLOPT_SSL_FALSESTART);
	AssignConst(CURLOPT_PATH_AS_IS);
	AssignConst(CURLOPT_PROXY_SERVICE_NAME);
	AssignConst(CURLOPT_SERVICE_NAME);
	AssignConst(CURLOPT_PIPEWAIT);
	AssignConst(CURLOPT_DEFAULT_PROTOCOL);
	AssignConst(CURLOPT_STREAM_WEIGHT);
	AssignConst(CURLOPT_STREAM_DEPENDS);
	AssignConst(CURLOPT_STREAM_DEPENDS_E);
	AssignConst(CURLOPT_TFTP_NO_OPTIONS);
	AssignConst(CURLOPT_CONNECT_TO);
	AssignConst(CURLOPT_TCP_FASTOPEN);
	AssignConst(CURLOPT_KEEP_SENDING_ON_ERROR);
	AssignConst(CURLOPT_PROXY_CAINFO);
	AssignConst(CURLOPT_PROXY_CAPATH);
	AssignConst(CURLOPT_PROXY_SSL_VERIFYPEER);
	AssignConst(CURLOPT_PROXY_SSL_VERIFYHOST);
	AssignConst(CURLOPT_PROXY_SSLVERSION);
	AssignConst(CURLOPT_PROXY_TLSAUTH_USERNAME);
	AssignConst(CURLOPT_PROXY_TLSAUTH_PASSWORD);
	AssignConst(CURLOPT_PROXY_TLSAUTH_TYPE);
	AssignConst(CURLOPT_PROXY_SSLCERT);
	AssignConst(CURLOPT_PROXY_SSLCERTTYPE);
	AssignConst(CURLOPT_PROXY_SSLKEY);
	AssignConst(CURLOPT_PROXY_SSLKEYTYPE);
	AssignConst(CURLOPT_PROXY_KEYPASSWD);
	AssignConst(CURLOPT_PROXY_SSL_CIPHER_LIST);
	AssignConst(CURLOPT_PROXY_CRLFILE);
	AssignConst(CURLOPT_PROXY_SSL_OPTIONS);
	AssignConst(CURLOPT_PRE_PROXY);
	AssignConst(CURLOPT_PROXY_PINNEDPUBLICKEY);
	AssignConst(CURLOPT_ABSTRACT_UNIX_SOCKET);
	AssignConst(CURLOPT_SUPPRESS_CONNECT_HEADERS);
	AssignConst(CURLOPT_REQUEST_TARGET);
	AssignConst(CURLOPT_SOCKS5_AUTH);
	AssignConst(CURLOPT_SSH_COMPRESSION);
	AssignConst(CURLOPT_MIMEPOST);
	AssignConst(CURLOPT_TIMEVALUE_LARGE);
	AssignConst(CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS);
	AssignConst(CURLOPT_RESOLVER_START_FUNCTION);
	AssignConst(CURLOPT_RESOLVER_START_DATA);
	AssignConst(CURLOPT_HAPROXYPROTOCOL);
	AssignConst(CURLOPT_DNS_SHUFFLE_ADDRESSES);
	AssignConst(CURLOPT_TLS13_CIPHERS);
	AssignConst(CURLOPT_PROXY_TLS13_CIPHERS);
	AssignConst(CURLOPT_DISALLOW_USERNAME_IN_URL);
	AssignConst(CURLOPT_DOH_URL);
	AssignConst(CURLOPT_UPLOAD_BUFFERSIZE);
	AssignConst(CURLOPT_UPKEEP_INTERVAL_MS);
	AssignConst(CURLOPT_CURLU);
	AssignConst(CURLOPT_TRAILERFUNCTION);
	AssignConst(CURLOPT_TRAILERDATA);
	AssignConst(CURLOPT_HTTP09_ALLOWED);
	AssignConst(CURLOPT_ALTSVC_CTRL);
	AssignConst(CURLOPT_ALTSVC);
	AssignConst(CURLOPT_MAXAGE_CONN);
	AssignConst(CURLOPT_SASL_AUTHZID);
	AssignConst(CURLOPT_MAIL_RCPT_ALLLOWFAILS);
	AssignConst(CURLOPT_SSLCERT_BLOB);
	AssignConst(CURLOPT_SSLKEY_BLOB);
	AssignConst(CURLOPT_PROXY_SSLCERT_BLOB);
	AssignConst(CURLOPT_PROXY_SSLKEY_BLOB);
	AssignConst(CURLOPT_ISSUERCERT_BLOB);
	AssignConst(CURLOPT_PROXY_ISSUERCERT);
	AssignConst(CURLOPT_PROXY_ISSUERCERT_BLOB);
	AssignConst(CURLOPT_SSL_EC_CURVES);
	AssignConst(CURLOPT_LASTENTRY);
	AssignConst(CURLOPT_ENCODING);
	AssignConst(CURLOPT_FILE);
	AssignConst(CURLOPT_INFILE);
	AssignConst(CURLOPT_WRITEHEADER);
	AssignConst(CURLOPT_WRITEINFO);
	AssignConst(CURLOPT_CLOSEPOLICY);
	AssignConst(CURLOPT_PROGRESSDATA);
	AssignConst(CURLOPT_SERVER_RESPONSE_TIMEOUT);
	AssignConst(CURLOPT_POST301);
	AssignConst(CURLOPT_SSLKEYPASSWD);
	AssignConst(CURLOPT_FTPAPPEND);
	AssignConst(CURLOPT_FTPLISTONLY);
	AssignConst(CURLOPT_FTP_SSL);
	AssignConst(CURLOPT_SSLCERTPASSWD);
	AssignConst(CURLOPT_KRB4LEVEL);
	AssignConst(CURLOPT_RTSPHEADER);
	// CURLINFO
	AssignConst(CURLINFO_STRING);
	AssignConst(CURLINFO_LONG);
	AssignConst(CURLINFO_DOUBLE);
	AssignConst(CURLINFO_SLIST);
	AssignConst(CURLINFO_PTR);
	AssignConst(CURLINFO_SOCKET);
	AssignConst(CURLINFO_OFF_T);
	AssignConst(CURLINFO_MASK);
	AssignConst(CURLINFO_TYPEMASK);
	AssignConst(CURLINFO_NONE);
	AssignConst(CURLINFO_EFFECTIVE_URL);
	AssignConst(CURLINFO_RESPONSE_CODE);
	AssignConst(CURLINFO_TOTAL_TIME);
	AssignConst(CURLINFO_NAMELOOKUP_TIME);
	AssignConst(CURLINFO_CONNECT_TIME);
	AssignConst(CURLINFO_PRETRANSFER_TIME);
	AssignConst(CURLINFO_SIZE_UPLOAD);
	AssignConst(CURLINFO_SIZE_UPLOAD_T);
	AssignConst(CURLINFO_SIZE_DOWNLOAD);
	AssignConst(CURLINFO_SIZE_DOWNLOAD_T);
	AssignConst(CURLINFO_SPEED_DOWNLOAD);
	AssignConst(CURLINFO_SPEED_DOWNLOAD_T);
	AssignConst(CURLINFO_SPEED_UPLOAD);
	AssignConst(CURLINFO_SPEED_UPLOAD_T);
	AssignConst(CURLINFO_HEADER_SIZE);
	AssignConst(CURLINFO_REQUEST_SIZE);
	AssignConst(CURLINFO_SSL_VERIFYRESULT);
	AssignConst(CURLINFO_FILETIME);
	AssignConst(CURLINFO_FILETIME_T);
	AssignConst(CURLINFO_CONTENT_LENGTH_DOWNLOAD);
	AssignConst(CURLINFO_CONTENT_LENGTH_DOWNLOAD_T);
	AssignConst(CURLINFO_CONTENT_LENGTH_UPLOAD);
	AssignConst(CURLINFO_CONTENT_LENGTH_UPLOAD_T);
	AssignConst(CURLINFO_STARTTRANSFER_TIME);
	AssignConst(CURLINFO_CONTENT_TYPE);
	AssignConst(CURLINFO_REDIRECT_TIME);
	AssignConst(CURLINFO_REDIRECT_COUNT);
	AssignConst(CURLINFO_PRIVATE);
	AssignConst(CURLINFO_HTTP_CONNECTCODE);
	AssignConst(CURLINFO_HTTPAUTH_AVAIL);
	AssignConst(CURLINFO_PROXYAUTH_AVAIL);
	AssignConst(CURLINFO_OS_ERRNO);
	AssignConst(CURLINFO_NUM_CONNECTS);
	AssignConst(CURLINFO_SSL_ENGINES);
	AssignConst(CURLINFO_COOKIELIST);
	AssignConst(CURLINFO_LASTSOCKET);
	AssignConst(CURLINFO_FTP_ENTRY_PATH);
	AssignConst(CURLINFO_REDIRECT_URL);
	AssignConst(CURLINFO_PRIMARY_IP);
	AssignConst(CURLINFO_APPCONNECT_TIME);
	AssignConst(CURLINFO_CERTINFO);
	AssignConst(CURLINFO_CONDITION_UNMET);
	AssignConst(CURLINFO_RTSP_SESSION_ID);
	AssignConst(CURLINFO_RTSP_CLIENT_CSEQ);
	AssignConst(CURLINFO_RTSP_SERVER_CSEQ);
	AssignConst(CURLINFO_RTSP_CSEQ_RECV);
	AssignConst(CURLINFO_PRIMARY_PORT);
	AssignConst(CURLINFO_LOCAL_IP);
	AssignConst(CURLINFO_LOCAL_PORT);
	AssignConst(CURLINFO_TLS_SESSION);
	AssignConst(CURLINFO_ACTIVESOCKET);
	AssignConst(CURLINFO_TLS_SSL_PTR);
	AssignConst(CURLINFO_HTTP_VERSION);
	AssignConst(CURLINFO_PROXY_SSL_VERIFYRESULT);
	AssignConst(CURLINFO_PROTOCOL);
	AssignConst(CURLINFO_SCHEME);
	AssignConst(CURLINFO_TOTAL_TIME_T);
	AssignConst(CURLINFO_NAMELOOKUP_TIME_T);
	AssignConst(CURLINFO_CONNECT_TIME_T);
	AssignConst(CURLINFO_PRETRANSFER_TIME_T);
	AssignConst(CURLINFO_STARTTRANSFER_TIME_T);
	AssignConst(CURLINFO_REDIRECT_TIME_T);
	AssignConst(CURLINFO_APPCONNECT_TIME_T);
	AssignConst(CURLINFO_RETRY_AFTER);
	AssignConst(CURLINFO_EFFECTIVE_METHOD);
	AssignConst(CURLINFO_PROXY_ERROR);
	AssignConst(CURLINFO_LASTONE);
	AssignConst(CURLINFO_HTTP_CODE);
	// curl_closepolicy
	AssignConst(CURLCLOSEPOLICY_NONE);
	AssignConst(CURLCLOSEPOLICY_OLDEST);
	AssignConst(CURLCLOSEPOLICY_LEAST_RECENTLY_USED);
	AssignConst(CURLCLOSEPOLICY_LEAST_TRAFFIC);
	AssignConst(CURLCLOSEPOLICY_SLOWEST);
	AssignConst(CURLCLOSEPOLICY_CALLBACK);
	AssignConst(CURLCLOSEPOLICY_LAST);
	// curl_sslbackend;
	AssignConst(CURLSSLBACKEND_NONE);
	AssignConst(CURLSSLBACKEND_OPENSSL);
	AssignConst(CURLSSLBACKEND_GNUTLS);
	AssignConst(CURLSSLBACKEND_NSS);
	AssignConst(CURLSSLBACKEND_OBSOLETE4);
	AssignConst(CURLSSLBACKEND_GSKIT);
	AssignConst(CURLSSLBACKEND_POLARSSL);
	AssignConst(CURLSSLBACKEND_WOLFSSL);
	AssignConst(CURLSSLBACKEND_SCHANNEL);
	AssignConst(CURLSSLBACKEND_SECURETRANSPORT);
	AssignConst(CURLSSLBACKEND_AXTLS);
	AssignConst(CURLSSLBACKEND_MBEDTLS);
	AssignConst(CURLSSLBACKEND_MESALINK);
	AssignConst(CURLSSLBACKEND_BEARSSL);
	// curlfiletype
	AssignConst(CURLFILETYPE_FILE);
	AssignConst(CURLFILETYPE_DIRECTORY);
	AssignConst(CURLFILETYPE_SYMLINK);
	AssignConst(CURLFILETYPE_DEVICE_BLOCK);
	AssignConst(CURLFILETYPE_DEVICE_CHAR);
	AssignConst(CURLFILETYPE_NAMEDPIPE);
	AssignConst(CURLFILETYPE_SOCKET);
	AssignConst(CURLFILETYPE_DOOR);
	AssignConst(CURLFILETYPE_UNKNOWN);
	// curlsocktype
	AssignConst(CURLSOCKTYPE_IPCXN);
	AssignConst(CURLSOCKTYPE_ACCEPT);
	AssignConst(CURLSOCKTYPE_LAST);
	// curlioerr
	AssignConst(CURLIOE_OK);
	AssignConst(CURLIOE_UNKNOWNCMD);
	AssignConst(CURLIOE_FAILRESTART);
	AssignConst(CURLIOE_LAST);
	// curliocmd	
	AssignConst(CURLIOCMD_NOP);
	AssignConst(CURLIOCMD_RESTARTREAD);
	AssignConst(CURLIOCMD_LAST);
	// curlinfotype
	AssignConst(CURLINFO_TEXT);
	AssignConst(CURLINFO_HEADER_IN);
	AssignConst(CURLINFO_HEADER_OUT);
	AssignConst(CURLINFO_DATA_IN);
	AssignConst(CURLINFO_DATA_OUT);
	AssignConst(CURLINFO_SSL_DATA_IN);
	AssignConst(CURLINFO_SSL_DATA_OUT);
	AssignConst(CURLINFO_END);
	// CURLproxycode
	AssignConst(CURLPX_OK);
	AssignConst(CURLPX_BAD_ADDRESS_TYPE);
	AssignConst(CURLPX_BAD_VERSION);
	AssignConst(CURLPX_CLOSED);
	AssignConst(CURLPX_GSSAPI);
	AssignConst(CURLPX_GSSAPI_PERMSG);
	AssignConst(CURLPX_GSSAPI_PROTECTION);
	AssignConst(CURLPX_IDENTD);
	AssignConst(CURLPX_IDENTD_DIFFER);
	AssignConst(CURLPX_LONG_HOSTNAME);
	AssignConst(CURLPX_LONG_PASSWD);
	AssignConst(CURLPX_LONG_USER);
	AssignConst(CURLPX_NO_AUTH);
	AssignConst(CURLPX_RECV_ADDRESS);
	AssignConst(CURLPX_RECV_AUTH);
	AssignConst(CURLPX_RECV_CONNECT);
	AssignConst(CURLPX_RECV_REQACK);
	AssignConst(CURLPX_REPLY_ADDRESS_TYPE_NOT_SUPPORTED);
	AssignConst(CURLPX_REPLY_COMMAND_NOT_SUPPORTED);
	AssignConst(CURLPX_REPLY_CONNECTION_REFUSED);
	AssignConst(CURLPX_REPLY_GENERAL_SERVER_FAILURE);
	AssignConst(CURLPX_REPLY_HOST_UNREACHABLE);
	AssignConst(CURLPX_REPLY_NETWORK_UNREACHABLE);
	AssignConst(CURLPX_REPLY_NOT_ALLOWED);
	AssignConst(CURLPX_REPLY_TTL_EXPIRED);
	AssignConst(CURLPX_REPLY_UNASSIGNED);
	AssignConst(CURLPX_REQUEST_FAILED);
	AssignConst(CURLPX_RESOLVE_HOST);
	AssignConst(CURLPX_SEND_AUTH);
	AssignConst(CURLPX_SEND_CONNECT);
	AssignConst(CURLPX_SEND_REQUEST);
	AssignConst(CURLPX_UNKNOWN_FAIL);
	AssignConst(CURLPX_UNKNOWN_MODE);
	AssignConst(CURLPX_USER_REJECTED);
	AssignConst(CURLPX_LAST);
	// curl_proxytype
	AssignConst(CURLPROXY_HTTP);
	AssignConst(CURLPROXY_HTTP_1_0);
	AssignConst(CURLPROXY_HTTPS);
	AssignConst(CURLPROXY_SOCKS4);
	AssignConst(CURLPROXY_SOCKS5);
	AssignConst(CURLPROXY_SOCKS4A);
	AssignConst(CURLPROXY_SOCKS5_HOSTNAME);
	// curl_usesssl
	AssignConst(CURLUSESSL_NONE);
	AssignConst(CURLUSESSL_TRY);
	AssignConst(CURLUSESSL_CONTROL);
	AssignConst(CURLUSESSL_ALL);
	AssignConst(CURLUSESSL_LAST);
	// curl_ftpccc
	AssignConst(CURLFTPSSL_CCC_NONE);
	AssignConst(CURLFTPSSL_CCC_PASSIVE);
	AssignConst(CURLFTPSSL_CCC_ACTIVE);
	AssignConst(CURLFTPSSL_CCC_LAST);
	// curl_ftpauth
	AssignConst(CURLFTPAUTH_DEFAULT);
	AssignConst(CURLFTPAUTH_SSL);
	AssignConst(CURLFTPAUTH_TLS);
	AssignConst(CURLFTPAUTH_LAST);
	// curl_ftpcreatedir
	AssignConst(CURLFTP_CREATE_DIR_NONE);
	AssignConst(CURLFTP_CREATE_DIR);
	AssignConst(CURLFTP_CREATE_DIR_RETRY);
	AssignConst(CURLFTP_CREATE_DIR_LAST);
	// curl_ftpmethod
	AssignConst(CURLFTPMETHOD_DEFAULT);
	AssignConst(CURLFTPMETHOD_MULTICWD);
	AssignConst(CURLFTPMETHOD_NOCWD);
	AssignConst(CURLFTPMETHOD_SINGLECWD);
	AssignConst(CURLFTPMETHOD_LAST);
	// CURLOPT_HTTP_VERSION
	AssignConst(CURL_HTTP_VERSION_NONE);
	AssignConst(CURL_HTTP_VERSION_1_0);
	AssignConst(CURL_HTTP_VERSION_1_1);
	AssignConst(CURL_HTTP_VERSION_2_0);
	AssignConst(CURL_HTTP_VERSION_2TLS);
	AssignConst(CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE);
	AssignConst(CURL_HTTP_VERSION_3);
	AssignConst(CURL_HTTP_VERSION_LAST);
	// RTSP requests
	AssignConst(CURL_RTSPREQ_NONE);
	AssignConst(CURL_RTSPREQ_OPTIONS);
	AssignConst(CURL_RTSPREQ_DESCRIBE);
	AssignConst(CURL_RTSPREQ_ANNOUNCE);
	AssignConst(CURL_RTSPREQ_SETUP);
	AssignConst(CURL_RTSPREQ_PLAY);
	AssignConst(CURL_RTSPREQ_PAUSE);
	AssignConst(CURL_RTSPREQ_TEARDOWN);
	AssignConst(CURL_RTSPREQ_GET_PARAMETER);
	AssignConst(CURL_RTSPREQ_SET_PARAMETER);
	AssignConst(CURL_RTSPREQ_RECORD);
	AssignConst(CURL_RTSPREQ_RECEIVE);
	AssignConst(CURL_RTSPREQ_LAST);
	// CURL_NETRC_OPTION
	AssignConst(CURL_NETRC_IGNORED);
	AssignConst(CURL_NETRC_OPTIONAL);
	AssignConst(CURL_NETRC_REQUIRED);
	AssignConst(CURL_NETRC_LAST);
	// CURL_SSLVERSION
	AssignConst(CURL_SSLVERSION_DEFAULT);
	AssignConst(CURL_SSLVERSION_TLSv1);
	AssignConst(CURL_SSLVERSION_SSLv2);
	AssignConst(CURL_SSLVERSION_SSLv3);
	AssignConst(CURL_SSLVERSION_TLSv1_0);
	AssignConst(CURL_SSLVERSION_TLSv1_1);
	AssignConst(CURL_SSLVERSION_TLSv1_2);
	AssignConst(CURL_SSLVERSION_TLSv1_3);
	AssignConst(CURL_SSLVERSION_LAST);
	// CURL_SSLVERSION_MAX
	AssignConst(CURL_SSLVERSION_MAX_NONE);
	AssignConst(CURL_SSLVERSION_MAX_DEFAULT);
	AssignConst(CURL_SSLVERSION_MAX_TLSv1_0);
	AssignConst(CURL_SSLVERSION_MAX_TLSv1_1);
	AssignConst(CURL_SSLVERSION_MAX_TLSv1_2);
	AssignConst(CURL_SSLVERSION_MAX_TLSv1_3);
	AssignConst(CURL_SSLVERSION_MAX_LAST);
	// CURL_TLSAUTH
	AssignConst(CURL_TLSAUTH_NONE);
	AssignConst(CURL_TLSAUTH_SRP);
	AssignConst(CURL_TLSAUTH_LAST);
	// curl_TimeCond
	AssignConst(CURL_TIMECOND_NONE);
	AssignConst(CURL_TIMECOND_IFMODSINCE);
	AssignConst(CURL_TIMECOND_IFUNMODSINCE);
	AssignConst(CURL_TIMECOND_LASTMOD);
	AssignConst(CURL_TIMECOND_LAST);
	// CURL Progress
	AssignConst(CURL_PROGRESSFUNC_CONTINUE);
	// CURLformoption
	AssignConst(CURLFORM_NOTHING);
	AssignConst(CURLFORM_COPYNAME);
	AssignConst(CURLFORM_PTRNAME);
	AssignConst(CURLFORM_NAMELENGTH);
	AssignConst(CURLFORM_COPYCONTENTS);
	AssignConst(CURLFORM_PTRCONTENTS);
	AssignConst(CURLFORM_CONTENTSLENGTH);
	AssignConst(CURLFORM_FILECONTENT);
	AssignConst(CURLFORM_ARRAY);
	AssignConst(CURLFORM_OBSOLETE);
	AssignConst(CURLFORM_FILE);
	AssignConst(CURLFORM_BUFFER);
	AssignConst(CURLFORM_BUFFERPTR);
	AssignConst(CURLFORM_BUFFERLENGTH);
	AssignConst(CURLFORM_CONTENTTYPE);
	AssignConst(CURLFORM_CONTENTHEADER);
	AssignConst(CURLFORM_FILENAME);
	AssignConst(CURLFORM_END);
	AssignConst(CURLFORM_OBSOLETE2);
	AssignConst(CURLFORM_STREAM);
	AssignConst(CURLFORM_CONTENTLEN);
	AssignConst(CURLFORM_LASTENTRY);
	// CURLFORMCode
	AssignConst(CURL_FORMADD_OK);
	AssignConst(CURL_FORMADD_MEMORY);
	AssignConst(CURL_FORMADD_OPTION_TWICE);
	AssignConst(CURL_FORMADD_NULL);
	AssignConst(CURL_FORMADD_UNKNOWN_OPTION);
	AssignConst(CURL_FORMADD_INCOMPLETE);
	AssignConst(CURL_FORMADD_ILLEGAL_ARRAY);
	AssignConst(CURL_FORMADD_DISABLED);
	AssignConst(CURL_FORMADD_LAST);
	// CURLsslset
	AssignConst(CURLSSLSET_OK);
	AssignConst(CURLSSLSET_UNKNOWN_BACKEND);
	AssignConst(CURLSSLSET_TOO_LATE);
	AssignConst(CURLSSLSET_NO_BACKENDS);
	// curl_closepolicy
	AssignConst(CURLCLOSEPOLICY_NONE);
	AssignConst(CURLCLOSEPOLICY_OLDEST);
	AssignConst(CURLCLOSEPOLICY_LEAST_RECENTLY_USED);
	AssignConst(CURLCLOSEPOLICY_LEAST_TRAFFIC);
	AssignConst(CURLCLOSEPOLICY_SLOWEST);
	AssignConst(CURLCLOSEPOLICY_CALLBACK);
	AssignConst(CURLCLOSEPOLICY_LAST);
	// curl_lock_data
	AssignConst(CURL_LOCK_DATA_NONE);
	AssignConst(CURL_LOCK_DATA_SHARE);
	AssignConst(CURL_LOCK_DATA_COOKIE);
	AssignConst(CURL_LOCK_DATA_DNS);
	AssignConst(CURL_LOCK_DATA_SSL_SESSION);
	AssignConst(CURL_LOCK_DATA_CONNECT);
	AssignConst(CURL_LOCK_DATA_PSL);
	AssignConst(CURL_LOCK_DATA_LAST);
	// curl_lock_accesss
	AssignConst(CURL_LOCK_ACCESS_NONE);
	AssignConst(CURL_LOCK_ACCESS_SHARED);
	AssignConst(CURL_LOCK_ACCESS_SINGLE);
	AssignConst(CURL_LOCK_ACCESS_LAST);
	// CURLSHcode
	AssignConst(CURLSHE_OK);
	AssignConst(CURLSHE_BAD_OPTION);
	AssignConst(CURLSHE_IN_USE);
	AssignConst(CURLSHE_INVALID);
	AssignConst(CURLSHE_NOMEM);
	AssignConst(CURLSHE_NOT_BUILT_IN);
	AssignConst(CURLSHE_LAST);
	// CURLSHoption
	AssignConst(CURLSHOPT_NONE);
	AssignConst(CURLSHOPT_SHARE);
	AssignConst(CURLSHOPT_UNSHARE);
	AssignConst(CURLSHOPT_LOCKFUNC);
	AssignConst(CURLSHOPT_UNLOCKFUNC);
	AssignConst(CURLSHOPT_USERDATA);
	AssignConst(CURLSHOPT_LAST);
	// CURLversion
	AssignConst(CURLVERSION_FIRST);
	AssignConst(CURLVERSION_SECOND);
	AssignConst(CURLVERSION_THIRD);
	AssignConst(CURLVERSION_FOURTH);
	AssignConst(CURLVERSION_FIFTH);
	AssignConst(CURLVERSION_SIXTH);
	AssignConst(CURLVERSION_SEVENTH);
	AssignConst(CURLVERSION_EIGHTH);
	AssignConst(CURLVERSION_LAST);
}

Gurax_EndModuleScope(curl)
