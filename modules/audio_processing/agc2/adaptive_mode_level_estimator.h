/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MODULES_AUDIO_PROCESSING_AGC2_ADAPTIVE_MODE_LEVEL_ESTIMATOR_H_
#define MODULES_AUDIO_PROCESSING_AGC2_ADAPTIVE_MODE_LEVEL_ESTIMATOR_H_

#include "modules/audio_processing/agc2/saturation_protector.h"
#include "modules/audio_processing/vad/vad_with_level.h"

namespace webrtc {
class ApmDataDumper;

class AdaptiveModeLevelEstimator {
 public:
  explicit AdaptiveModeLevelEstimator(ApmDataDumper* apm_data_dumper);
  void UpdateEstimation(const VadWithLevel::LevelAndProbability& vad_data);
  float LatestLevelEstimate() const;

 private:
  void DebugDumpEstimate();

  size_t buffer_size_ms_ = 0;
  float last_estimate_with_offset_dbfs_ = kInitialSpeechLevelEstimateDbfs;
  float estimate_numerator_ = 0.f;
  float estimate_denominator_ = 0.f;
  SaturationProtector saturation_protector_;
  ApmDataDumper* const apm_data_dumper_;
};

}  // namespace webrtc

#endif  // MODULES_AUDIO_PROCESSING_AGC2_ADAPTIVE_MODE_LEVEL_ESTIMATOR_H_
