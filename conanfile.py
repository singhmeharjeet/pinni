from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout


class PinniConan(ConanFile):
    name = "pinni"
    version = "0.1.7"
    license = "MIT"  # Change to your license
    author = "Your Name singhmeharjeet@gmail.com"
    url = "https://github.com/singhmeharjeet/pinni"
    description = "Pinni game engine library"
    topics = ("game", "engine", "graphics")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "cmake/*", "test/*"

    def requirements(self):
        if self.settings.build_type == "Debug":
            self.requires("gtest/1.16.0")
        self.requires("spdlog/1.15.1", transitive_headers=True)

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.variables["PINNI_STATIC"] = not self.options.shared

        # Only build tests in Debug mode, disable in Release
        if self.settings.build_type == "Debug":
            tc.variables["PINNI_BUILD_TESTS"] = True
        else:
            tc.variables["PINNI_BUILD_TESTS"] = False

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["pinni"]
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.set_property("cmake_file_name", "Pinni")
        self.cpp_info.set_property("cmake_target_name", "Pinni::Pinni")
        self.cpp_info.requires = ["spdlog::spdlog"]
