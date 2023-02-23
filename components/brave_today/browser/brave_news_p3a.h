// Copyright (c) 2022 The brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_BRAVE_TODAY_BROWSER_BRAVE_NEWS_P3A_H_
#define BRAVE_COMPONENTS_BRAVE_TODAY_BROWSER_BRAVE_NEWS_P3A_H_

#include <cstdint>

class PrefRegistrySimple;
class PrefService;

namespace brave_news {
namespace p3a {

constexpr char kDaysInMonthUsedCountHistogramName[] =
    "brave.Today.DaysInMonthUsedCount";
constexpr char kWeeklySessionCountHistogramName[] =
    "brave.Today.WeeklySessionCount";
constexpr char kWeeklyMaxCardVisitsHistogramName[] =
    "brave.Today.WeeklyMaxCardVisitsCount";
constexpr char kWeeklyMaxCardViewsHistogramName[] =
    "brave.Today.WeeklyMaxCardViewsCount";
constexpr char kTotalCardViewsHistogramName[] =
    "brave.Today.WeeklyTotalCardViews";
constexpr char kWeeklyDisplayAdsViewedHistogramName[] =
    "brave.Today.WeeklyDisplayAdsViewedCount";
constexpr char kDirectFeedsTotalHistogramName[] =
    "brave.Today.DirectFeedsTotal";
constexpr char kWeeklyAddedDirectFeedsHistogramName[] =
    "brave.Today.WeeklyAddedDirectFeedsCount";
constexpr char kLastUsageTimeHistogramName[] = "brave.Today.LastUsageTime";
constexpr char kNewUserReturningHistogramName[] =
    "brave.Today.NewUserReturning";

void RecordAtInit(PrefService* prefs);
void RecordAtSessionStart(PrefService* prefs);

void RecordWeeklyMaxCardVisitsCount(PrefService* prefs,
                                    uint64_t cards_visited_session_total_count);
void RecordWeeklyMaxCardViewsCount(PrefService* prefs,
                                   uint64_t cards_viewed_session_total_count);
void RecordWeeklyDisplayAdsViewedCount(PrefService* prefs, bool is_add);
void RecordWeeklyAddedDirectFeedsCount(PrefService* prefs, int change);
void RecordDirectFeedsTotal(PrefService* prefs);
void RecordTotalCardViews(PrefService* prefs,
                          uint64_t cards_viewed_session_total_count);
void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace p3a
}  // namespace brave_news

#endif  // BRAVE_COMPONENTS_BRAVE_TODAY_BROWSER_BRAVE_NEWS_P3A_H_
