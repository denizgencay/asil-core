/* Copyright (c) 2022 The brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_ads/brave_stats_updater_helper.h"

#include "base/files/file_path.h"
#include "base/functional/bind.h"
#include "brave/components/brave_ads/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "chrome/common/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"

namespace brave_ads {

BraveStatsUpdaterHelper::BraveStatsUpdaterHelper()
    : local_state_(g_browser_process->local_state()),
      profile_manager_(g_browser_process->profile_manager()) {
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.Init(local_state_);
  last_used_profile_pref_change_registrar_.Add(
      ::prefs::kProfileLastUsed,
      base::BindRepeating(&BraveStatsUpdaterHelper::OnLastUsedProfileChanged,
                          base::Unretained(this)));
#endif

  profile_manager_observer_.Observe(profile_manager_);
}

BraveStatsUpdaterHelper::~BraveStatsUpdaterHelper() {
  if (current_profile_) {
    current_profile_->RemoveObserver(this);
  }
}

void BraveStatsUpdaterHelper::RegisterLocalStatePrefs(
    PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(ads::prefs::kEnabledForLastProfile, false);
}

void BraveStatsUpdaterHelper::OnProfileAdded(Profile* profile) {
#if BUILDFLAG(IS_ANDROID)
  if (profile == ProfileManager::GetPrimaryUserProfile()) {
#else
  base::FilePath last_used_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  if ((!last_used_path.empty() && profile->GetBaseName() == last_used_path) ||
      (last_used_path.empty() &&
       profile == ProfileManager::GetLastUsedProfile())) {
#endif
    OnLastUsedProfileChanged();
  }
}

void BraveStatsUpdaterHelper::OnProfileWillBeDestroyed(Profile* profile) {
  if (profile != current_profile_) {
    return;
  }
  profile->RemoveObserver(this);
  current_profile_ = nullptr;
#if !BUILDFLAG(IS_ANDROID)
  last_used_profile_pref_change_registrar_.RemoveAll();
#endif
  ads_enabled_pref_change_registrar_.RemoveAll();
}

void BraveStatsUpdaterHelper::OnProfileManagerDestroying() {
  if (current_profile_ != nullptr) {
#if !BUILDFLAG(IS_ANDROID)
    last_used_profile_pref_change_registrar_.RemoveAll();
#endif
    ads_enabled_pref_change_registrar_.RemoveAll();
    current_profile_->RemoveObserver(this);
    current_profile_ = nullptr;
  }
  profile_manager_observer_.Reset();
}

PrefService* BraveStatsUpdaterHelper::GetLastUsedProfilePrefs() {
#if BUILDFLAG(IS_ANDROID)
  return ProfileManager::GetPrimaryUserProfile()->GetPrefs();
#else

  base::FilePath last_used_profile_path =
      local_state_->GetFilePath(::prefs::kProfileLastUsed);
  Profile* profile;
  if (last_used_profile_path.empty()) {
    profile = profile_manager_->GetLastUsedProfile();
  } else {
    profile = profile_manager_->GetProfileByPath(
        profile_manager_->user_data_dir().Append(last_used_profile_path));
  }
  if (profile == nullptr || profile->IsOffTheRecord()) {
    return nullptr;
  }
  if (current_profile_ != nullptr) {
    current_profile_->RemoveObserver(this);
    current_profile_ = nullptr;
  }
  current_profile_ = profile;
  profile->AddObserver(this);
  return profile->GetPrefs();
#endif
}

void BraveStatsUpdaterHelper::OnLastUsedProfileChanged() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  ads_enabled_pref_change_registrar_.RemoveAll();
  ads_enabled_pref_change_registrar_.Init(profile_prefs);
  ads_enabled_pref_change_registrar_.Add(
      ads::prefs::kEnabled,
      base::BindRepeating(&BraveStatsUpdaterHelper::UpdateLocalStateAdsEnabled,
                          base::Unretained(this)));
  UpdateLocalStateAdsEnabled();
}

void BraveStatsUpdaterHelper::UpdateLocalStateAdsEnabled() {
  PrefService* profile_prefs = GetLastUsedProfilePrefs();
  if (profile_prefs == nullptr) {
    return;
  }
  // Copying enabled pref to local state so the stats updater does not depend on
  // the profile
  local_state_->SetBoolean(ads::prefs::kEnabledForLastProfile,
                           profile_prefs->GetBoolean(ads::prefs::kEnabled));
}

}  // namespace brave_ads
