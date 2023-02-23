/* Copyright (c) 2020 The brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/browser/ads_p2a.h"

#include "base/logging.h"
#include "base/metrics/histogram_functions.h"
#include "brave/components/brave_ads/common/pref_names.h"
#include "brave/components/time_period_storage/weekly_storage.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace brave_ads {

namespace {

constexpr const char* kP2AQuestionNameList[] = {
    // Ad Opportunities
    "brave.P2A.TotalAdOpportunities",
    "brave.P2A.AdOpportunitiesPerSegment.architecture",
    "brave.P2A.AdOpportunitiesPerSegment.artsentertainment",
    "brave.P2A.AdOpportunitiesPerSegment.automotive",
    "brave.P2A.AdOpportunitiesPerSegment.business",
    "brave.P2A.AdOpportunitiesPerSegment.careers",
    "brave.P2A.AdOpportunitiesPerSegment.cellphones",
    "brave.P2A.AdOpportunitiesPerSegment.crypto",
    "brave.P2A.AdOpportunitiesPerSegment.education",
    "brave.P2A.AdOpportunitiesPerSegment.familyparenting",
    "brave.P2A.AdOpportunitiesPerSegment.fashion",
    "brave.P2A.AdOpportunitiesPerSegment.folklore",
    "brave.P2A.AdOpportunitiesPerSegment.fooddrink",
    "brave.P2A.AdOpportunitiesPerSegment.gaming",
    "brave.P2A.AdOpportunitiesPerSegment.healthfitness",
    "brave.P2A.AdOpportunitiesPerSegment.history",
    "brave.P2A.AdOpportunitiesPerSegment.hobbiesinterests",
    "brave.P2A.AdOpportunitiesPerSegment.home",
    "brave.P2A.AdOpportunitiesPerSegment.law",
    "brave.P2A.AdOpportunitiesPerSegment.military",
    "brave.P2A.AdOpportunitiesPerSegment.other",
    "brave.P2A.AdOpportunitiesPerSegment.personalfinance",
    "brave.P2A.AdOpportunitiesPerSegment.pets",
    "brave.P2A.AdOpportunitiesPerSegment.realestate",
    "brave.P2A.AdOpportunitiesPerSegment.science",
    "brave.P2A.AdOpportunitiesPerSegment.sports",
    "brave.P2A.AdOpportunitiesPerSegment.technologycomputing",
    "brave.P2A.AdOpportunitiesPerSegment.travel",
    "brave.P2A.AdOpportunitiesPerSegment.weather",
    "brave.P2A.AdOpportunitiesPerSegment.untargeted",
    // Ad Impressions
    "brave.P2A.TotalAdImpressions",
    "brave.P2A.AdImpressionsPerSegment.architecture",
    "brave.P2A.AdImpressionsPerSegment.artsentertainment",
    "brave.P2A.AdImpressionsPerSegment.automotive",
    "brave.P2A.AdImpressionsPerSegment.business",
    "brave.P2A.AdImpressionsPerSegment.careers",
    "brave.P2A.AdImpressionsPerSegment.cellphones",
    "brave.P2A.AdImpressionsPerSegment.crypto",
    "brave.P2A.AdImpressionsPerSegment.education",
    "brave.P2A.AdImpressionsPerSegment.familyparenting",
    "brave.P2A.AdImpressionsPerSegment.fashion",
    "brave.P2A.AdImpressionsPerSegment.folklore",
    "brave.P2A.AdImpressionsPerSegment.fooddrink",
    "brave.P2A.AdImpressionsPerSegment.gaming",
    "brave.P2A.AdImpressionsPerSegment.healthfitness",
    "brave.P2A.AdImpressionsPerSegment.history",
    "brave.P2A.AdImpressionsPerSegment.hobbiesinterests",
    "brave.P2A.AdImpressionsPerSegment.home",
    "brave.P2A.AdImpressionsPerSegment.law",
    "brave.P2A.AdImpressionsPerSegment.military",
    "brave.P2A.AdImpressionsPerSegment.other",
    "brave.P2A.AdImpressionsPerSegment.personalfinance",
    "brave.P2A.AdImpressionsPerSegment.pets",
    "brave.P2A.AdImpressionsPerSegment.realestate",
    "brave.P2A.AdImpressionsPerSegment.science",
    "brave.P2A.AdImpressionsPerSegment.sports",
    "brave.P2A.AdImpressionsPerSegment.technologycomputing",
    "brave.P2A.AdImpressionsPerSegment.travel",
    "brave.P2A.AdImpressionsPerSegment.weather",
    "brave.P2A.AdImpressionsPerSegment.untargeted"};

constexpr uint16_t kIntervalBuckets[] = {0, 5, 10, 20, 50, 100, 250, 500};

}  // namespace

void RegisterP2APrefs(PrefRegistrySimple* registry) {
  for (const char* const question_name : kP2AQuestionNameList) {
    std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
    pref_path.append(question_name);
    registry->RegisterListPref(pref_path);
  }
}

void RecordInWeeklyStorageAndEmitP2AHistogramAnswer(PrefService* prefs,
                                                    const std::string& name) {
  std::string pref_path(prefs::kP2AStoragePrefNamePrefix);
  pref_path.append(name);
  if (!prefs->FindPreference(pref_path)) {
    return;
  }
  WeeklyStorage storage(prefs, pref_path.c_str());
  storage.AddDelta(1);
  EmitP2AHistogramAnswer(name, storage.GetWeeklySum());
}

void EmitP2AHistogramAnswer(const std::string& name, uint16_t count_value) {
  const uint16_t* const iter = std::lower_bound(
      kIntervalBuckets, std::end(kIntervalBuckets), count_value);
  const uint16_t bucket = iter - kIntervalBuckets;

  for (const char* const question_name : kP2AQuestionNameList) {
    if (name != question_name) {
      continue;
    }

    base::UmaHistogramExactLinear(question_name, bucket,
                                  std::size(kIntervalBuckets) + 1);
  }
}

void SuspendP2AHistograms() {
  // Record "special value" to prevent sending this week's data to P2A server.
  // Matches INT_MAX - 1 for |kSuspendedMetricValue| in |brave_p3a_service.cc|
  for (const char* const question_name : kP2AQuestionNameList) {
    base::UmaHistogramExactLinear(question_name, INT_MAX,
                                  std::size(kIntervalBuckets) + 1);
  }

  VLOG(1) << "P2A histograms suspended";
}

}  // namespace brave_ads
