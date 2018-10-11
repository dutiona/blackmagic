from conans import CMake, ConanFile, tools


class Blackmagic(ConanFile):
    name = "blackmagic"
    version = "0.4"
    license = "MIT"
    url = "https://gitlab.lrde.epita.fr/mroynard/blackmagic"
    description = "Metaprogramming toolbox to do blackmagic in C++17."
    settings = "os", "compiler", "arch", "build_type", "cppstd"
    options = {"shared": [True, False], "fPIC": [
        True, False], "build_tests": [True, False], "benchmark": [True, False]}
    default_options = "shared=False", "fPIC=True", "build_tests=False", "benchmark=True"
    generators = "cmake_find_package", "cmake"

    def configure(self):
        if self.settings.os == "Windows":
            self.options.remove("fPIC")

    def source(self):
        git = tools.Git()
        git.clone("{}.git".format(self.url))

    def build(self):
        cmake = CMake(self)

        cmake.configure()
        cmake.build()

        if self.options.build_tests:
            cmake.test()

    def package(self):
        self.copy("*.hpp", dst="include/blackmagic", src="include/blackmagic")

    def package_id(self):
        self.info.header_only()

    def requirements(self):
        self.requires("gtest/1.8.1@bincrafters/stable")

        if self.options.benchmark:
            self.requires("benchmark/1.4.1@dutiona/stable")
