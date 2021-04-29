#ifndef __ROOT_CERTIFICATES_H__
#define __ROOT_CERTIFICATES_H__

//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#include <boost/asio/ssl.hpp>
#include <string>
#include <iostream>

/*
    PLEASE READ
    These root certificates here are included just to make the
    SSL client examples work. They are NOT intended to be
    illustrative of best-practices for performing TLS certificate
    verification.
    A REAL program which needs to verify the authenticity of a
    server IP address resolved from a given DNS name needs to
    consult the operating system specific certificate store
    to validate the chain of signatures, compare the domain name
    properly against the domain name in the certificate, check
    the certificate revocation list, and probably do some other
    things.
    ALL of these operations are entirely outside the scope of
    both Boost.Beast and Boost.Asio.
    See (work in progress):
        https://github.com/djarek/certify
    tl;dr: root_certificates.hpp should not be used in production code
*/

// from https://www.javaer101.com/en/article/12616899.html
template <typename Verifier>
class verbose_verification
{
public:
  verbose_verification(Verifier verifier)
    : verifier_(verifier)
  {}

  bool operator()(
    bool preverified,
    boost::asio::ssl::verify_context& ctx
  )
  {
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    bool verified = verifier_(preverified, ctx);
    std::cout << "Verifying: " << subject_name << "\n"
                 "Verified: " << verified << std::endl;
    return verified;
  }
private:
  Verifier verifier_;
};

///@brief Auxiliary function to make verbose_verification objects.
template <typename Verifier>
verbose_verification<Verifier>
make_verbose_verification(Verifier verifier)
{
  return verbose_verification<Verifier>(verifier);
}

namespace detail
{

    inline void
    load_root_certificates(boost::asio::ssl::context &ctx, boost::system::error_code &ec)
    {
        ctx.set_verify_mode(boost::asio::ssl::verify_peer);
        ctx.add_verify_path("certs");
        ctx.use_certificate_file("client1.crt", boost::asio::ssl::context::pem);
        ctx.use_private_key_file("private/client1.key", boost::asio::ssl::context::pem);
    }

} // detail

// Load the root certificates into an ssl::context

inline void
load_root_certificates(boost::asio::ssl::context &ctx, boost::system::error_code &ec)
{
    detail::load_root_certificates(ctx, ec);
}

inline void
load_root_certificates(boost::asio::ssl::context &ctx)
{
    boost::system::error_code ec;
    detail::load_root_certificates(ctx, ec);
    if (ec)
        throw boost::system::system_error{ec};
}

#endif // __ROOT_CERTIFICATES_H__