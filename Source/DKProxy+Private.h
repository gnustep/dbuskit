/** Declaration of private methods for DKProxy.
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

#import "DBusKit/DKProxy.h"

#import "DKObjectPathNode.h"
#import "DKNonAutoInvalidatingPort.h"



enum
{
  DK_NO_TABLES,
  DK_HAVE_TABLES,
  DK_HAVE_INTROSPECT,
  DK_WILL_BUILD_CACHE,
  DK_BUILDING_CACHE,
  DK_CACHE_BUILT,
  DK_CACHE_READY
};


@class DKInterface, DKNotificationCenter, NSXMLNode;

@interface DKProxy (DKProxyPrivate) <DKObjectPathNode>
- (DKPort*)_port;
- (DKEndpoint*)_endpoint;
- (NSString*)_service;
- (BOOL)_isLocal;
- (NSString*)_uniqueName;
- (void)_registerSignalsWithNotificationCenter: (DKNotificationCenter*)center;
- (NSXMLNode*)XMLNode;
- (NSXMLNode*)XMLNodeIncludingCompleteIntrospection: (BOOL)includeIntrospection
                                           absolute: (BOOL)absolutePath;
- (BOOL)isKindOfClass: (Class)cls;
- (DKProxy*)proxyParent;
- (void)_installAllInterfaces;
@end

@interface DKDBus (DKDBusPrivate)
- (void)_reconnectedWithEndpoint: (DKEndpoint*)endpoint;
- (BOOL)_isConnected;
@end

@interface DKPort (DKPortEndpointInitializer)
- (id) initWithRemote: (NSString*)aRemote
           atEndpoint: (DKEndpoint*)anEndpoint;
@end

/* FIXME: Once we've got a dbuskit_make_protocol tool, replace this by a proper,
 * generated header for the org.freedesktop.DBus interface.
 */
@protocol DKDBusStub
- (NSString*)GetNameOwner: (NSString*)name;
- (void)AddMatch: (NSString*)matchRule;
- (void)RemoveMatch: (NSString*)matchRule;
@end

/**
 * _DKInterfaceIntrospectable is a prototype for the D-Bus
 * org.freedesktop.DBus.Introspectable. It will be added to the dispatch table
 * of a proxy because we need it to dispatch the initial introspection data.
 */
extern DKInterface *_DKInterfaceIntrospectable;

/**
 * The document type string for D-Bus introspection data
 */
extern NSString* kDKDBusDocType;
