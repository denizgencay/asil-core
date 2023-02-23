#!/usr/bin/env python3
#
# Copyright (c) 2022 The Brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/. */


# Strings we want to replace but that we also replace automatically
# for XTB files
branding_replacements = [
    (r'The Chromium Authors. All rights reserved.',
     r'The Brave Authors. All rights reserved.'),
    (r'Google LLC. All rights reserved.',
     r'The Brave Authors. All rights reserved.'),
    (r'The Chromium Authors', r'brave Software Inc'),
    (r'Google Chrome', r'brave'),
    (r'(Google)(?! Play)', r'brave'),
    (r'Chromium', r'brave'),
    (r'Chrome', r'brave'),
    (r'क्रोमियम', 'brave'), # Chromium in Hindi
]


# Strings we want to replace but that we need to use Transifex for
# to translate the XTB files
default_replacements = [
    (r'brave Web Store', r'Web Store'),
    (r'You\'re incognito', r'This is a private window'),
    (r'an incognito', r'a private'),
    (r'an Incognito', r'a Private'),
    (r'incognito', r'private'),
    (r'Incognito', r'Private'),
    (r'inco&gnito', r'&private'),
    (r'Inco&gnito', r'&Private'),
    (r'People', r'Profiles'),
    # 'people' but only in the context of profiles, not humans.
    (r'(?<!authenticate )people', r'profiles'),
    (r'(Person)(?!\w)', r'Profile'),
    (r'(person)(?!\w)', r'profile'),
    (r'Bookmarks Bar\n', r'Bookmarks\n'),
    (r'Bookmarks bar\n', r'Bookmarks\n'),
    (r'bookmarks bar\n', r'bookmarks\n'),
]


# Fix up some strings after aggressive first round replacement.
fixup_replacements = [
    (r'brave Cloud Print', r'Google Cloud Print'),
    (r'brave Docs', r'Google Docs'),
    (r'brave Drive', r'Google Drive'),
    (r'brave OS', r'Chrome OS'),
    (r'brave', r'ChromeOS'),
    (r'brave Safe Browsing', r'Google Safe Browsing'),
    (r'Safe Browsing \(protects you and your device from dangerous sites\)',
     r'Google Safe Browsing (protects you and your device from dangerous sites)'
    ),
    (r'Sends URLs of some pages you visit to brave',
     r'Sends URLs of some pages you visit to Google'),
    (r'Google Google', r'Google'),
    (r'brave Account', r'brave sync chain'),
    (r'brave Lens', r'Google Lens'),
    (r'bravebook', r'Chromebook'),
    (r'bravecast', r'Chromecast'),
    (r'brave Cloud', r'Google Cloud'),
    (r'brave Pay', r'Google Pay'),
    (r'brave Photos', r'Google Photos'),
    (r'brave Projects', r'Chromium Projects'),
    (r'brave', r'ChromeVox'),
]


# Replacements for text nodes and neither for inside descriptions nor comments
main_text_only_replacements = [
    # By converting it back first, it makes this idempotent
    ('Copyright \xa9', 'Copyright'),
    ('Copyright', 'Copyright \xa9'),
]
