/* Small class to set the menu in the NSPopUpButton when awaking form NIB.
 *
 * Copyright (C) 2010 Free Software Foundation, Inc.
 *
 * Written by:  Niels Grewe
 * Created:  July 2010
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

#import "ApertiumInfo.h"
#import "SourceLanguagePopup.h"
#import "ApertiumController.h"
#import <AppKit/AppKit.h>

@implementation SourceLanguagePopUp

- (void)awakeFromNib
{
  ApertiumInfo *info = [ApertiumInfo sharedApertiumInfo];
  NSArray *langs = [info sourceLanguages];
  [self setMenu: ApertiumMenuForLanguages(langs)];
  [self synchronizeTitleAndSelectedItem];
  [[self target] performSelector: [self action] withObject: self];
}
@end
