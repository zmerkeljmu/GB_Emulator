# Game Boy Emulator

Welcome to my Game Boy Emulator project! This is a passion project that I developed to deepen my understanding of low-level programming, hardware emulation, and software development. While still in development, the emulator is already capable of running some original Game Boy ROMs, such as *Tetris*. I am actively working to improve its accuracy and add new features.

---

## Description

This project is a from-scratch emulator for the original Nintendo Game Boy. It is designed to replicate the behavior of the Game Boy's hardware, including the CPU, memory, and graphics. The emulator is written in C++ and uses external libraries for rendering and user interface. While it is far from perfect, it serves as a testament to my dedication to learning and problem-solving.

---

## Controls

The emulator uses the following keyboard controls:

- **W** - Up
- **A** - Left
- **S** - Down
- **D** - Right

- **J** - A button
- **K** - B button

- **Backspace** - Select
- **Enter** - Start

---

## Research Resources

This project would not have been possible without the wealth of knowledge shared by the Game Boy development community. Below are some of the key resources I used for research:

- **[Game Boy CPU (SM83) Manual](https://rgbds.gbdev.io/docs/v0.9.0/gbz80.7)**  
  The official documentation for the Game Boy's CPU, which helped me understand the instruction set and behavior of the SM83 processor.

- **[Pan Docs](https://gbdev.io/pandocs/Specifications.html)**  
  A comprehensive technical reference for the Game Boy hardware, covering everything from memory mapping to graphics rendering.

- **[The Ultimate Game Boy Talk (YouTube)](https://www.youtube.com/watch?v=HyzD8pNlpwI&ab_channel=media.ccc.de)**  
  An excellent presentation by Michael Steil that dives deep into the architecture and inner workings of the Game Boy.

---

## Tests

This project would not have been possible without the incredible resources and test ROMs created by the Game Boy development community. Special thanks to the following:

- **Blargg Test Roms**: [https://github.com/retrio/gb-test-roms](https://github.com/retrio/gb-test-roms)  
  Used for testing CPU accuracy and timing.

- **Mooneye Test Roms**: [https://github.com/Gekkio/mooneye-test-suite](https://github.com/Gekkio/mooneye-test-suite)  
  Used for testing hardware behavior and edge cases.

- **CPU Instruction JSON Tests**: [https://github.com/SingleStepTests/sm83](https://github.com/SingleStepTests/sm83)  
  Used for validating the correctness of CPU instructions.

---

## External Libraries Used

This project leverages the following external libraries:

- **Dear ImGui**: [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)  
  Used for creating a customizable debug interface.

- **tinyfiledialogs**: [https://sourceforge.net/projects/tinyfiledialogs/](https://sourceforge.net/projects/tinyfiledialogs/)  
  Used for simple file dialogs to load ROMs.

- **OpenGL**  
  Used for rendering the Game Boy's graphics.

- **SDL2**  
  Used for window management and input handling.

---

## Known Issues

The emulator is still a work in progress, and there are several known issues:

- **Timer accuracy**: The timer implementation is not fully accurate and may cause timing-related issues in some games.
- **MBC support**: Currently, the emulator only supports games that do not use a Memory Bank Controller (MBC). I plan to implement MBC support in the future.
- **Audio support**: Audio is not currently implemented. While I may add it later, it is not a priority at the moment.

---

## Future Plans

I have several features and improvements planned for the emulator:

- **MBC support**: Add support for games that use Memory Bank Controllers.
- **Custom color palettes**: Allow users to customize the color palette for a personalized experience.
- **Save games**: Implement support for saving and loading game progress.

---

## Contributing

This project is a personal endeavor, but I welcome feedback and suggestions! If you have any ideas or find bugs, feel free to open an issue or reach out to me.

---

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to use, modify, and distribute it as you see fit.

---

Thank you for checking out my Game Boy Emulator project!
