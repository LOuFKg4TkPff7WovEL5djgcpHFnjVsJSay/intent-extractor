#include <cstdlib>
#include <iostream>

#include <fact_intent.hpp>
#include <lib.hpp>
#include <weather_intent.hpp>

static bool register_modules(ie::IntentExtractor& extractor) {
    {
        const auto register_result = extractor.intent_factory().register_builder(
            extractor.string_interner(), std::make_shared<ie::WeatherIntentBuilder>());
        if (register_result != ie::IntentFactoryRegistrationResult::Ok) {
            std::cerr << "Failed to register weather intent module";
            return false;
        }
    }
    {
        const auto register_result = extractor.intent_factory().register_builder(
            extractor.string_interner(), std::make_shared<ie::FactIntentBuilder>());
        if (register_result != ie::IntentFactoryRegistrationResult::Ok) {
            std::cerr << "Failed to register weather intent module";
            return false;
        }
    }
    return true;
}

int main() {
    ie::IntentExtractor extractor;
    if (!register_modules(extractor)) {
        return EXIT_FAILURE;
    }

    std::string text;
    while (!std::cin.eof()) {
        std::cout << "\nHow may I help you today?\n> ";
        try {
            std::getline(std::cin, text);
        } catch (const std::exception&) {
            std::cout << "Failed to read your question, please try again.\n";
            continue;
        }
        if (std::cin.eof()) {
            break;
        }

        if (text.size() == 0) {
            std::cout << "Your query was empty, please try again.\n";
        }

        try {
            const auto extractor_result = extractor.extract_intent(text);
            switch (extractor_result.result) {
                case ie::IntentExtractorResult::Ok: {
                    std::cout << "Intent: ";
                    extractor_result.intent->log_result(std::cout);
                    std::cout << '\n';
                    break;
                }
                case ie::IntentExtractorResult::IntentFailedToInit: {
                    std::cout << "Failed to process query, please try again.\n";
                    break;
                }
                case ie::IntentExtractorResult::CouldNotFindIntent: {
                    std::cout << "Could not locate any intents, please try again.\n";
                    break;
                }
                default:
                    break;
            }
        } catch (const std::exception&) {
            std::cout << "Something unexpected happened and we could not process your query. "
                         "Please try again.\n";
        }
    }
    std::cout << "Goodbye" << std::endl;
    return EXIT_SUCCESS;
}