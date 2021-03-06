/** Declaration of DKEndpoint class for integrating DBus into NSRunLoop.
   Copyright (C) 2010 Free Software Foundation, Inc.

   Written by:  Niels Grewe <niels.grewe@halbordnung.de>
   Created: May 2010

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02111 USA.
   */

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>
#import "DBusKit/DKPort.h"
#include <dbus/dbus.h>
#import "config.h"

#if HAVE_FUNC_ATTRIBUTE_VISIBILITY
#  define ATTR_HIDDEN __attribute__ ((visibility ("hidden")))
#else
#  define ATTR_HIDDEN
#endif

@class DKRunLoopContext, NSRunLoop, NSString, NSDictionary;
@protocol NSCoding;

/**
 * DKEndpoint is used internally to manage the low level details of a connection
 * to a D-Bus peer. This can be a well known bus as well as some special peer.
 */
@interface DKEndpoint: NSObject <NSCoding>
{
  DBusConnection *connection;
  NSDictionary *info;
  DKRunLoopContext *ctx;
}

/**
 * Use this initializer to use a pre-existing DBusConnection. Please note that
 * this will increase the reference count of the connection. It will still need
 * to be unreferenced by calling code.
 *
 * Please note that encoding and decoding an DKEndpoint encoded this way is only
 * possible if you also supply a proper info dictionary. This dictionary should
 * contain either the address of the bus (under the "address"-key) or the type
 * of the well-known bus (under the "wellKnownBus"-key).
 */
- (id) initWithConnection: (DBusConnection*)conn
                     info: (NSDictionary*)info;


/**
 * Returns the libdbus DBusConnection object.
 */
- (DBusConnection*) DBusConnection;

/**
 * Returns the type of the well known bus for this endpoint, or
 * DKDBusBusTypeOther does not connect to a well known bus.
 */
- (DKDBusBusType)DBusBusType;

/**
 * Flush the connection, so that it will marshall all pending messages to the
 * wire.
 */
- (void) flush;

/**
 * Returns the run loop in which D-Bus connections are handled.
 */
- (NSRunLoop*)runLoop;

/**
 * Returns the run loop mode in which D-Bus connections are handled.
 */
- (NSString*)runLoopMode;

@end

/**
 * Helper method to ensure that we are using a well known bus correctly.
 */
static inline DBusBusType
DBusBusTypeFromWellKnownBus(DKDBusBusType type)
{
  switch (type)
  {
    case DKDBusSystemBus:
      return DBUS_BUS_SYSTEM;
    case DKDBusSessionBus:
      return DBUS_BUS_SESSION;
    default:
      break;
  }
  [NSException raise: @"DKDbusBusException"
              format: @"Not a well known bus"];
  return 0;
}
