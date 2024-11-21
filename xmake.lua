add_rules("mode.debug", "mode.release")

add_requires("blaze")

target("Quant")
    set_kind("shared")
    add_files("src/Quant/**.cpp")
    add_includedirs("lib", "lib/Quant")
    add_packages("blaze")

target("Test")
    set_kind("binary")
    add_files("src/Test/**.cpp")
    add_includedirs("lib")
    add_packages("blaze")
    add_deps("Quant")