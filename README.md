# Phase Space Visualizer VST3

![VST Plugin](https://raw.githubusercontent.com/anttiluode/PhaseSpaceVisualizerVST/main/vst.png)


A real-time audio visualizer that creates mesmerizing phase space patterns from your audio signal. Creates unique visual patterns based on the relationships between consecutive audio samples, resulting in distinctive shapes for different waveforms and sounds.

A built vst3 version of the file is in 

Phase Space Visualizer.vst3/Contents/x86_64-win

You can drop that to program files/common files/vst3 in windows and it should show up in your daw after you rescan the vst plugins. 

## Features

- Real-time phase space visualization of audio signals
- Rainbow color trails with fade effect
- Rotation and zoom controls
- Smooth 60fps rendering
- Available as VST3 plugin and standalone application
- Zero latency - doesn't affect your audio signal
- CPU efficient

## Examples

Different audio inputs create different patterns:
- Sine waves → perfect circles/ovals
- Square waves → rectangular patterns
- Complex waveforms → intricate geometric shapes
- Multiple frequencies → layered patterns
- Noise → chaotic, scattered patterns

## Building from Source

### Prerequisites

- CMake 3.22 or higher
- Visual Studio 2019 or higher (Windows)
- Xcode 12.4 or higher (macOS)
- C++17 compatible compiler

### Build Steps

1. Clone the repository with submodules:
```bash
git clone --recursive https://github.com/yourusername/phase-space-visualizer
cd phase-space-visualizer
```

2. Create build directory and configure:
```bash
cmake . -B build
```

3. Build the project:
```bash
cmake --build build --config Release
```

### Installation

#### Windows
- Copy the entire `.vst3` folder from `build/PhaseSpaceVisualizer_artefacts/Release/VST3/` to:
  - `C:\Program Files\Common Files\VST3`

#### macOS
- Copy the `.vst3` bundle from `build/PhaseSpaceVisualizer_artefacts/Release/VST3/` to:
  - `/Library/Audio/Plug-Ins/VST3`

## Usage

1. Load the plugin in your DAW as an effect
2. Play audio through the track
3. Controls:
   - Rotate button: Toggle rotation effect
   - Zoom slider: Adjust visualization scale
   - Clear: Press 'C' to clear trails
   
## Technical Details

The visualizer works by plotting each audio sample against its next sample in 2D space:
- X coordinate = sample[n]
- Y coordinate = sample[n+1]

This creates a phase space representation that reveals patterns in how the audio signal changes over time. The coloring and trails help visualize these patterns more clearly.

## Contributing

Contributions are welcome! Some areas that could use improvement:

- Additional visualization modes
- More color schemes
- MIDI trigger support
- Pattern detection/analysis
- Presets system

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Credits

Built with [JUCE](https://github.com/juce-framework/JUCE) - an open-source C++ application framework.

## Known Issues

- Some DAWs may require rescanning plugins to detect the VST3
- High CPU usage with very long trails enabled

