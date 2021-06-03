//
// Created by maros on 03/06/2021.
//

#ifndef EKONOM_CONFIG_PROVIDER_HPP
#define EKONOM_CONFIG_PROVIDER_HPP

#include <fstream>
#include <utility>
#include <mutex>

#include "nlohmann/json.hpp"

namespace ekonom {
    class config_provider {
    private:
        std::mutex m_fileMutex;
        std::shared_ptr<std::fstream> m_file;
        const std::string m_filePath;

    private:
        nlohmann::json m_jsonData;

    public:
        /**
         * Constructor, prepares config data (reads them or writes them to filesystem depending on state)
         * @param configPath Path to the configuration file
         */
        explicit config_provider(const std::string &configPath);

        virtual ~config_provider();

    public:
        /**
         * Loads default config data to memory
         */
        void loadDefault();
        /**
         * Writes config data to filesystem
         */
        bool writeConfig();
        /**
         * Reads config data from filesystem
         */
        bool readConfig();

    public:
        const std::string& getFilePath();
        const std::shared_ptr<std::fstream> getFileStream();
        const nlohmann::json& getJsonData();
    };
}


#endif //EKONOM_CONFIG_PROVIDER_HPP
