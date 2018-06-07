from conans import CMake, ConanFile, tools

class GtestconstexprextConan(ConanFile):
    name = "Blackmagic"
    version = "0.4"
    license = "MIT"
    url = "https://gitlab.lrde.epita.fr/mroynard/blackmagic"
    description = "Metaprogramming toolbox to do blackmagic in C++17."

    settings = "os", "compiler", "arch", "build_type", "cppstd"
    requires = "gtest/1.8.0@bincrafters/stable", "benchmark/1.4.1@dutiona/stable"
    generators = "cmake"

    no_copy_source = True

    def source(self):
        git = tools.Git()
        git.clone("https://gitlab.lrde.epita.fr/mroynard/blackmagic.git")

    def build(self):
        cmake = CMake(self, generator="Ninja")
        # cmake.configure(definitions={"WITH_BENCHMARKS": "ON", "WITH_EXAMPLES": "ON"})
        cmake.configure(definitions={"WITH_BENCHMARKS": "ON", "WITH_EXAMPLES": "ON"})
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.hpp", dst="include/blackmagic", src="include/blackmagic")

    def package_id(self):
        self.info.header_only()
