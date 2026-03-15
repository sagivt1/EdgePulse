from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class EdgePulseRecipe(ConanFile):
    name = "EdgePulse"
    version = "1.0.0"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Use cmake to build the project
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("spdlog/1.17.0")
        self.requires("sqlitecpp/3.3.1")

    def build_requirements(self):
        self.test_requires("gtest/1.17.0")

    def layout(self):
        # Configures the build folder structure (e.g., /build/Release)
        cmake_layout(self)

    def generate(self):
        # Generates the CMake toolchain file linking our Conan dependencies
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        # This allows us to build the project simply by running `conan build .`
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


