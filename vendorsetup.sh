#!/bin/bash

### Using PE Telephony Repos ###
rm -rf frameworks/opt/telephony/ && git clone https://github.com/PixelExperience/frameworks_opt_telephony.git frameworks/opt/telephony/
rm -rf packages/services/Telephony/ && git clone https://github.com/PixelExperience/packages_services_Telephony.git packages/services/Telephony/
rm -rf vendor/codeaurora/telephony/ && git clone https://github.com/PixelExperience/vendor_codeaurora_telephony.git vendor/codeaurora/telephony/
