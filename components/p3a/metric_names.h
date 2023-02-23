/* Copyright (c) 2022 The brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_
#define BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_

#include "base/containers/fixed_flat_set.h"
#include "base/strings/string_piece.h"

namespace brave::p3a {

// Allowlist for histograms that we collect.
// A metric must be listed here to be reported.
//
// Please keep them properly sorted within their categories.
//
// Could be replaced with something built dynamically,
// although so far we've found it a useful review point.
//
// TODO(iefremov) Clean up obsolete metrics.
//
// clang-format off
constexpr inline auto kCollectedTypicalHistograms =
  base::MakeFixedFlatSet<base::StringPiece>({
    "brave.Core.BookmarksCountOnProfileLoad.2",
    "brave.Core.CrashReportsEnabled",
    "brave.Core.DomainsLoaded",
    "brave.Core.IsDefault",
    "brave.Core.LastTimeIncognitoUsed",
    "brave.Core.NumberOfExtensions",
    "brave.Core.PagesLoaded",
    "brave.Core.TabCount",
    "brave.Core.TorEverUsed",
    "brave.Core.WindowCount.2",
    "brave.Importer.ImporterSource.2",
    "brave.NTP.CustomizeUsageStatus",
    "brave.NTP.NewTabsCreated",
    "brave.NTP.SponsoredImagesEnabled",
    "brave.NTP.SponsoredNewTabsCreated",
    "brave.Omnibox.SearchCount",
    "brave.P3A.SentAnswersCount",
    "brave.Rewards.AdsState.2",
    "brave.Rewards.AutoContributionsState.2",
    "brave.Rewards.TipsState.2",
    "brave.Rewards.AdsEnabledDuration",
    "brave.Rewards.WalletBalance.3",
    "brave.Rewards.WalletState",
    "brave.Savings.BandwidthSavingsMB",
    "brave.Search.DefaultEngine.4",
    "brave.Search.Promo.Banner",
    "brave.Search.Promo.Button",
    "brave.Search.Promo.NewTabPage",
    "brave.Search.SwitchEngine",
    "brave.Search.WebDiscoveryEnabled",
    "brave.Shields.AdBlockSetting",
    "brave.Shields.CookieListEnabled",
    "brave.Shields.CookieListPrompt",
    "brave.Shields.DomainAdsSettingsAboveGlobal",
    "brave.Shields.DomainAdsSettingsBelowGlobal",
    "brave.Shields.DomainFingerprintSettingsAboveGlobal",
    "brave.Shields.DomainFingerprintSettingsBelowGlobal",
    "brave.Shields.FingerprintBlockSetting",
    "brave.Shields.UsageStatus",
    "brave.SpeedReader.Enabled",
    "brave.SpeedReader.ToggleCount",
    "brave.Today.DaysInMonthUsedCount",
    "brave.Today.DirectFeedsTotal",
    "brave.Today.LastUsageTime",
    "brave.Today.NewUserReturning",
    "brave.Today.WeeklyAddedDirectFeedsCount",
    "brave.Today.WeeklyDisplayAdsViewedCount",
    "brave.Today.WeeklyMaxCardViewsCount",
    "brave.Today.WeeklyMaxCardVisitsCount",
    "brave.Today.WeeklySessionCount",
    "brave.Today.WeeklyTotalCardViews",
    "brave.Toolbar.FrequentMenuGroup",
    "brave.Toolbar.MenuDismissRate",
    "brave.Toolbar.MenuOpens",
    "brave.Sync.Status.2",
    "brave.Sync.ProgressTokenEverReset",
    "brave.Uptime.BrowserOpenMinutes",
    "brave.VPN.NewUserReturning",
    "brave.VPN.DaysInMonthUsed",
    "brave.VPN.LastUsageTime",
    "brave.Wallet.ActiveEthAccounts",
    "brave.Wallet.ActiveFilAccounts",
    "brave.Wallet.ActiveSolAccounts",
    "brave.Wallet.EthProvider.2",
    "brave.Wallet.EthTransactionSent",
    "brave.Wallet.FilTransactionSent",
    "brave.Wallet.DefaultSolanaWalletSetting",
    "brave.Wallet.DefaultWalletSetting",
    "brave.Wallet.KeyringCreated",
    "brave.Wallet.LastUsageTime",
    "brave.Wallet.NewUserReturning",
    "brave.Wallet.OnboardingConversion.2",
    "brave.Wallet.SolTransactionSent",
    "brave.Wallet.UsageDaysInWeek",
    "brave.Wallet.UsageMonthly.2",
    "brave.Welcome.InteractionStatus",

    // IPFS
    "brave.IPFS.IPFSCompanionInstalled",
    "brave.IPFS.DetectionPromptCount",
    "brave.IPFS.GatewaySetting",
    "brave.IPFS.DaemonRunTime",
    "brave.IPFS.LocalNodeRetention",

    // P2A
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
    "brave.P2A.AdImpressionsPerSegment.untargeted"
});

constexpr inline auto kCollectedSlowHistograms =
  base::MakeFixedFlatSet<base::StringPiece>({
    // Please remove following placeholder metric once
    // static slow metrics are added
    "brave.P3A.ExampleSlowMetric"
});

constexpr inline auto kCollectedExpressHistograms =
  base::MakeFixedFlatSet<base::StringPiece>({
    // Please remove following placeholder metric once
    // static express metrics are added
    "brave.P3A.ExampleExpressMetric"
});

// clang-format on

}  // namespace brave::p3a

#endif  // BRAVE_COMPONENTS_P3A_METRIC_NAMES_H_
