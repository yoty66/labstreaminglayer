//
// socket_acceptor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.lslboost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SOCKET_ACCEPTOR_SERVICE_HPP
#define BOOST_ASIO_SOCKET_ACCEPTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <lslboost/asio/detail/config.hpp>
#include <lslboost/asio/basic_socket.hpp>
#include <lslboost/asio/error.hpp>
#include <lslboost/asio/io_service.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <lslboost/asio/detail/win_iocp_socket_service.hpp>
#else
# include <lslboost/asio/detail/reactive_socket_service.hpp>
#endif

#include <lslboost/asio/detail/push_options.hpp>

namespace lslboost {
namespace asio {

/// Default service implementation for a socket acceptor.
template <typename Protocol>
class socket_acceptor_service
#if defined(GENERATING_DOCUMENTATION)
  : public lslboost::asio::io_service::service
#else
  : public lslboost::asio::detail::service_base<socket_acceptor_service<Protocol> >
#endif
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The unique service identifier.
  static lslboost::asio::io_service::id id;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename protocol_type::endpoint endpoint_type;

private:
  // The type of the platform-specific implementation.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef detail::win_iocp_socket_service<Protocol> service_impl_type;
#else
  typedef detail::reactive_socket_service<Protocol> service_impl_type;
#endif

public:
  /// The native type of the socket acceptor.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined implementation_type;
#else
  typedef typename service_impl_type::implementation_type implementation_type;
#endif

  /// (Deprecated: Use native_handle_type.) The native acceptor type.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_type;
#else
  typedef typename service_impl_type::native_handle_type native_type;
#endif

  /// The native acceptor type.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename service_impl_type::native_handle_type native_handle_type;
#endif

  /// Construct a new socket acceptor service for the specified io_service.
  explicit socket_acceptor_service(lslboost::asio::io_service& io_service)
    : lslboost::asio::detail::service_base<
        socket_acceptor_service<Protocol> >(io_service),
      service_impl_(io_service)
  {
  }

  /// Construct a new socket acceptor implementation.
  void construct(implementation_type& impl)
  {
    service_impl_.construct(impl);
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a new socket acceptor implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    service_impl_.move_construct(impl, other_impl);
  }

  /// Move-assign from another socket acceptor implementation.
  void move_assign(implementation_type& impl,
      socket_acceptor_service& other_service,
      implementation_type& other_impl)
  {
    service_impl_.move_assign(impl, other_service.service_impl_, other_impl);
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroy a socket acceptor implementation.
  void destroy(implementation_type& impl)
  {
    service_impl_.destroy(impl);
  }

  /// Open a new socket acceptor implementation.
  lslboost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, lslboost::system::error_code& ec)
  {
    return service_impl_.open(impl, protocol, ec);
  }

  /// Assign an existing native acceptor to a socket acceptor.
  lslboost::system::error_code assign(implementation_type& impl,
      const protocol_type& protocol, const native_handle_type& native_acceptor,
      lslboost::system::error_code& ec)
  {
    return service_impl_.assign(impl, protocol, native_acceptor, ec);
  }

  /// Determine whether the acceptor is open.
  bool is_open(const implementation_type& impl) const
  {
    return service_impl_.is_open(impl);
  }

  /// Cancel all asynchronous operations associated with the acceptor.
  lslboost::system::error_code cancel(implementation_type& impl,
      lslboost::system::error_code& ec)
  {
    return service_impl_.cancel(impl, ec);
  }

  /// Bind the socket acceptor to the specified local endpoint.
  lslboost::system::error_code bind(implementation_type& impl,
      const endpoint_type& endpoint, lslboost::system::error_code& ec)
  {
    return service_impl_.bind(impl, endpoint, ec);
  }

  /// Place the socket acceptor into the state where it will listen for new
  /// connections.
  lslboost::system::error_code listen(implementation_type& impl, int backlog,
      lslboost::system::error_code& ec)
  {
    return service_impl_.listen(impl, backlog, ec);
  }

  /// Close a socket acceptor implementation.
  lslboost::system::error_code close(implementation_type& impl,
      lslboost::system::error_code& ec)
  {
    return service_impl_.close(impl, ec);
  }

  /// (Deprecated: Use native_handle().) Get the native acceptor implementation.
  native_type native(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  /// Get the native acceptor implementation.
  native_handle_type native_handle(implementation_type& impl)
  {
    return service_impl_.native_handle(impl);
  }

  /// Set a socket option.
  template <typename SettableSocketOption>
  lslboost::system::error_code set_option(implementation_type& impl,
      const SettableSocketOption& option, lslboost::system::error_code& ec)
  {
    return service_impl_.set_option(impl, option, ec);
  }

  /// Get a socket option.
  template <typename GettableSocketOption>
  lslboost::system::error_code get_option(const implementation_type& impl,
      GettableSocketOption& option, lslboost::system::error_code& ec) const
  {
    return service_impl_.get_option(impl, option, ec);
  }

  /// Perform an IO control command on the socket.
  template <typename IoControlCommand>
  lslboost::system::error_code io_control(implementation_type& impl,
      IoControlCommand& command, lslboost::system::error_code& ec)
  {
    return service_impl_.io_control(impl, command, ec);
  }

  /// Gets the non-blocking mode of the acceptor.
  bool non_blocking(const implementation_type& impl) const
  {
    return service_impl_.non_blocking(impl);
  }

  /// Sets the non-blocking mode of the acceptor.
  lslboost::system::error_code non_blocking(implementation_type& impl,
      bool mode, lslboost::system::error_code& ec)
  {
    return service_impl_.non_blocking(impl, mode, ec);
  }

  /// Gets the non-blocking mode of the native acceptor implementation.
  bool native_non_blocking(const implementation_type& impl) const
  {
    return service_impl_.native_non_blocking(impl);
  }

  /// Sets the non-blocking mode of the native acceptor implementation.
  lslboost::system::error_code native_non_blocking(implementation_type& impl,
      bool mode, lslboost::system::error_code& ec)
  {
    return service_impl_.native_non_blocking(impl, mode, ec);
  }

  /// Get the local endpoint.
  endpoint_type local_endpoint(const implementation_type& impl,
      lslboost::system::error_code& ec) const
  {
    return service_impl_.local_endpoint(impl, ec);
  }

  /// Accept a new connection.
  template <typename SocketService>
  lslboost::system::error_code accept(implementation_type& impl,
      basic_socket<protocol_type, SocketService>& peer,
      endpoint_type* peer_endpoint, lslboost::system::error_code& ec)
  {
    return service_impl_.accept(impl, peer, peer_endpoint, ec);
  }

  /// Start an asynchronous accept.
  template <typename SocketService, typename AcceptHandler>
  void async_accept(implementation_type& impl,
      basic_socket<protocol_type, SocketService>& peer,
      endpoint_type* peer_endpoint,
      BOOST_ASIO_MOVE_ARG(AcceptHandler) handler)
  {
    service_impl_.async_accept(impl, peer, peer_endpoint,
        BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
  }

private:
  // Destroy all user-defined handler objects owned by the service.
  void shutdown_service()
  {
    service_impl_.shutdown_service();
  }

  // The platform-specific implementation.
  service_impl_type service_impl_;
};

} // namespace asio
} // namespace lslboost

#include <lslboost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SOCKET_ACCEPTOR_SERVICE_HPP
