cmake_minimum_required(VERSION 3.22)

project(PhaseSpaceVisualizer VERSION 1.0.0)

# Add JUCE as a subdirectory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_BINARY_DIR}/JUCE" EXCLUDE_FROM_ALL)

# Initialize JUCE
juce_add_plugin(PhaseSpaceVisualizer
    COMPANY_NAME "YourCompany"
    PLUGIN_MANUFACTURER_CODE Phsp
    PLUGIN_CODE Phsv
    FORMATS VST3 Standalone
    PRODUCT_NAME "Phase Space Visualizer"
    VST3_CATEGORIES Analyzer Fx Tools
    VST3_AUTO_MANIFEST TRUE
)

# Add source files
target_sources(PhaseSpaceVisualizer
    PRIVATE
        src/PluginProcessor.cpp
        src/PluginEditor.cpp
)

# Setup plugin parameters
juce_generate_juce_header(PhaseSpaceVisualizer)

target_compile_definitions(PhaseSpaceVisualizer
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(PhaseSpaceVisualizer
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)