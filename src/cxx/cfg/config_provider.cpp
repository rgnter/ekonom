//
// Created by maros on 03/06/2021.
//

#include <filesystem>
#include <iostream>
#include <iomanip>
#include <mutex>

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include "config_provider.hpp"
ekonom::config_provider::config_provider(const std::string &configPath) :
        m_filePath(configPath) {
    spdlog::stopwatch sw;
    spdlog::info("Constructing config provider");

    {
        std::scoped_lock<std::mutex> lock(this->m_fileMutex);

        std::filesystem::create_directory(this->m_filePath.substr(0, this->m_filePath.find_last_of('/')));
        if (this->m_file != nullptr && this->m_file->is_open()) {
            this->m_file->close();
            spdlog::warn("Reusing already existing pointer to configuration file");
        } else
            this->m_file = std::make_shared<std::fstream>();
        this->m_file->open(this->m_filePath, std::ios::in);
    }

    bool markRewrite = true;
    if(!this->m_file->fail()) {
        if(!readConfig()) {
            const std::string badPath = this->m_filePath+".bad";
            spdlog::warn("Failed reading configuration, rewriting.");
            std::filesystem::copy_file(this->m_filePath, badPath);
            spdlog::warn("Bad config path: {}", badPath.c_str());

            markRewrite = true;
        } else {
            spdlog::info("Read existing configuration");
            markRewrite = false;
        }
    }
    if(markRewrite) {
        if(this->m_file->is_open())
            this->m_file->close();
        this->m_file->open(this->m_filePath, std::ios::out | std::ios::in | std::ios::trunc);

        loadDefault();
        writeConfig();

        spdlog::info("Written defaults to new configuration");
    }
    this->m_file->close();


    spdlog::info("Constructed config provider in {:.3}s", sw);
}


ekonom::config_provider::~config_provider() {
    std::scoped_lock<std::mutex> lock(this->m_fileMutex);
    if(this->m_file->is_open()) {
        this->m_file->close();
        if(this->m_file.use_count() > 1)
            spdlog::warn("Releasing pointer to configuration file with {} usage/s", this->m_file.use_count()-1);
        this->m_file = nullptr;
    }
}

void ekonom::config_provider::loadDefault() {
    this->m_jsonData = {
            {"test", "true"}
    };
}

bool ekonom::config_provider::writeConfig() {
    std::scoped_lock<std::mutex> lock(this->m_fileMutex);
    spdlog::debug("Writing configuration to: {}", this->m_filePath.c_str());
    // std::endl to flush buffer
    (*this->m_file) << std::setw(4) << this->m_jsonData << std::endl;
    return true;
}

bool ekonom::config_provider::readConfig() {
    std::scoped_lock<std::mutex> lock(this->m_fileMutex);
    spdlog::debug("Reading configuration from: {}", this->m_filePath.c_str());
    try {
        this->m_jsonData = nlohmann::json::parse(*this->m_file);
    } catch (...) {
        spdlog::error("Configuration read exception");
        return false;
    }
    return true;
}

const std::string &ekonom::config_provider::getFilePath() {
    return this->m_filePath;
}

const std::shared_ptr<std::fstream> ekonom::config_provider::getFileStream() {
    return this->m_file;
}

const nlohmann::json &ekonom::config_provider::getJsonData() {
    return this->m_jsonData;
}


