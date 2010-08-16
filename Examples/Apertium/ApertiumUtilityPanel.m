/* Small class to set the style mask on the translate panel.
 *
 * Copyright (C) 2010 Free Software Foundation, Inc.
 *
 * Written by:  Niels Grewe
 * Created:  August 2010
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111
 * USA.
 */

#import "ApertiumUtilityPanel.h"

@implementation ApertiumUtilityPanel

- (id)initWithContentRect: (NSRect)cRect
                styleMask: (NSUInteger)mask
                  backing: (NSBackingStoreType)backingType
                    defer: (BOOL)doDefer
{
  if (nil == (self = [super initWithContentRect: cRect
                                      styleMask: NSUtilityWindowMask
                                        backing: backingType
                                          defer: doDefer]))
  {
    return nil;
  }
  [self setHasShadow: YES];
  [self setFloatingPanel: YES];
  return self;
}
@end
