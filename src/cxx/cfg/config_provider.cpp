//
// Created by maros on 03/06/2021.
//

#include <iostream>
#include <iomanip>

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include "config_provider.hpp"

ekonom::config_provider::config_provider(const std::string &configPath) :
        m_filePath(configPath) {
    spdlog::stopwatch sw;
    spdlog::info("Constructing config provider");

    this->m_fileStream = std::make_shared<std::fstream>(this->m_filePath);
    if(this->m_fileStream->fail()) {
        spdlog::debug("Creating new configuration");
        writeConfig();
    } else {
        spdlog::debug("Loading existing configuration");
        readConfig();
    }
    spdlog::info("Constructed config provider in {:.3}s", sw);
}

void ekonom::config_provider::writeConfig() {
    spdlog::debug("Writing configuration to: {}", this->m_filePath.c_str());
    // std::endl to flush buffer
    (*this->m_fileStream) << std::setw(4) << this->m_jsonData << std::endl;
}

void ekonom::config_provider::readConfig() {
    spdlog::debug("Reading configuration from: {}", this->m_filePath.c_str());
    (*this->m_fileStream) >> this->m_jsonData;
}

const std::string &ekonom::config_provider::getFilePath() {
    return this->m_filePath;
}

const std::shared_ptr<std::fstream> ekonom::config_provider::getFileStream() {
    return this->m_fileStream;
}

const nlohmann::json &ekonom::config_provider::getJsonData() {
    return this->m_jsonData;
}
