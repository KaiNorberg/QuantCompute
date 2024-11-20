add_rules("mode.debug", "mode.release")

target("Quant")
    set_kind("shared")
    add_files("src/Quant/**.cpp")
    add_includedirs("lib", "lib/Quant")

target("Test")
    set_kind("binary")
    add_files("src/Test/**.cpp")
    add_includedirs("lib")
    add_deps("Quant")