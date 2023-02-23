# Copyright (c) 2022 The brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

import override_utils

@override_utils.override_function(globals())
def GetConfigurationForBuild(original_function, defines):
  base = original_function(defines)
  return _merge_dicts(_BRAVE_VALUES, base)

_BRAVE_VALUES = {
  'build': 'brave',
  'app_name': 'brave',
  'doc_url':
    'https://support.brave.com/hc/en-us/articles/360039248271-Group-Policy',
  'frame_name': 'brave Frame',
  'webview_name': 'brave WebView',
  'win_config': {
    'win': {
      'reg_mandatory_key_name': 'Software\\Policies\\BraveSoftware\\brave',
      'reg_recommended_key_name':
        'Software\\Policies\\BraveSoftware\\brave\\Recommended',
      'mandatory_category_path': ['brave:Cat_Brave', 'brave'],
      'recommended_category_path': ['brave:Cat_Brave', 'brave_recommended'],
      'category_path_strings': {
        'brave': 'brave',
        'brave_recommended':
        'brave - {doc_recommended}'
      },
      'namespace': 'BraveSoftware.Policies.brave',
    },
  },
  # The string 'brave' is defined in brave.adml for ADMX, but ADM doesn't
  # support external references, so we define this map here.
  'adm_category_path_strings': {
    'brave:Cat_Brave': 'brave'
  },
  'admx_prefix': 'brave',
  'admx_using_namespaces': {
    'brave': 'BraveSoftware.Policies'  # prefix: namespace
  },
  'linux_policy_path': '/etc/brave/policies/',
  'bundle_id': 'com.brave.ios.core',
}

def _merge_dicts(src, dst):
  result = dict(dst)
  for k, v in src.items():
    result[k] = _merge_dicts(v, dst.get(k, {})) if isinstance(v, dict) else v
  return result
