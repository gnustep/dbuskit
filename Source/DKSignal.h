/** Interface for DKSignal class encapsulating D-Bus signal information.
   Copyright (C) 2010 Free Software Foundation, Inc.

   Written by:  Niels Grewe <niels.grewe@halbordnung.de>
   Created: July 2010

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

   <title>DKSignal class reference</title>
   */

#import "DKIntrospectionNode.h"
#include <dbus/dbus.h>
@class NSString, NSMutableArray, DKArgument;

/**
 * DKSignal encapsulates information about D-Bus signals, allowing their
 * arguments to be deserialized into a dictionary that can be used as the
 * userInfo dictionary of a NSNotification.
 */
@interface DKSignal: DKIntrospectionNode
{
  NSMutableArray *args;
}

/**
 * Add an argument to the signal specification. It is invalid to specify
 * <code>kDKArgumentDirectionIn</code> as a value for <var>direction</var>.
 */
- (void)addArgument: (DKArgument*)arg
          direction: (NSString*)direction;

/**
 * Replace the arguments of the signal with the new array.
 */
- (void)setArguments: (NSMutableArray*)arguments;

/**
 * Returns a custom notification name if one was set for the signal.
 */
- (NSString*)notificationName;

/**
 * Registers the signal with the instance of DKNotificationCenter that is
 * responsible for the proxy that the signal descends from.
 */
- (void)registerWithNotificationCenter;

/**
 * Returns the values of the signals arguments in an dictionary. By default,
 * those values will have an keys like arg0, arg1, ..., argN. If an
 * org.gnustep.openstep.notification.key annotation is available for the
 * arguments of this signal, the values will additionally be available for the
 * key specified.
 */
- (NSDictionary*)userInfoFromIterator: (DBusMessageIter*)iter;


/**
 * Marshalls the arguments from an NSNotification's userInfo dictionary into
 * a libdbus iterator. The algorithm for resolving the values is as follows:
 *
 * 1. If an argument has an attached org.gnustep.openstep.notification.key
 *    annotation, get the value for that key.
 * 2. If the value is nil, try the argN key of the dictionary, where argN
 *    is the position of the argument in the introspection graph
 * 3. Marshall the value into the iterator.
 *
 * As a consequence, named arguments take precedence over positional ones,
 * and absence is interpreted as a null value, which may cause an exception
 * for some data types (e.g. object paths)
 */
- (void)marshallUserInfo: (NSDictionary*)userInfo
            intoIterator: (DBusMessageIter*)iter;

/**
 * Returns YES if the signal is a stub signal created by the notification
 * center.
 */
- (BOOL)isStub;

/**
 * The name of the interface this signal is a member of.
 */
- (NSString*)interface;

/**
 * Returns the index of the argument that has been annotated with the specified
 * key, or NSNotFound if no argument is annotated to be exposed under the key.
 */
- (NSInteger)argumentIndexForAnnotatedKey: (NSString*)key;
@end
