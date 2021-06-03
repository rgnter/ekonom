//
// Created by maros on 03/06/2021.
//

#ifndef EKONOM_CONFIG_PROVIDER_HPP
#define EKONOM_CONFIG_PROVIDER_HPP

#include <fstream>
#include <utility>

#include "nlohmann/json.hpp"

namespace ekonom {
    class config_provider {
    private:
        std::shared_ptr<std::fstream> m_fileStream;
        const std::string m_filePath;

    private:
        nlohmann::json m_jsonData;

    public:
        /**
         * Constructor, prepares config data (reads them or writes them to filesystem depending on state)
         * @param configPath Path to the configuration file
         */
        explicit config_provider(const std::string &configPath);

    public:
        /**
         * Writes config data to filesystem
         */
        void writeConfig();
        /**
         * Reads config data from filesystem
         */
        void readConfig();

    public:
        const std::string& getFilePath();
        const std::shared_ptr<std::fstream> getFileStream();
        const nlohmann::json& getJsonData();
    };
}


#endif //EKONOM_CONFIG_PROVIDER_HPP
